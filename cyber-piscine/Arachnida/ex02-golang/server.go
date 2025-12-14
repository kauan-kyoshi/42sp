package main

import (
	"bytes"
	"encoding/binary"
	"encoding/json"
	"fmt"
	"io"
	"net/http"
	"os"
	"os/exec"
	"path/filepath"
	"strings"
	"time"

	"github.com/rwcarlsen/goexif/exif"
	"github.com/rwcarlsen/goexif/tiff"
)

type tagCollector struct{ M map[string]string }

func (tc *tagCollector) Walk(name exif.FieldName, tag *tiff.Tag) error {
	tc.M[string(name)] = fmt.Sprintf("%v", tag)
	return nil
}

func startServer() {
	http.Handle("/", http.FileServer(http.Dir("./web")))
	http.HandleFunc("/api/files", listFilesHandler)
	http.HandleFunc("/api/metadata", metadataHandler)
	http.HandleFunc("/api/clear", clearHandler)
	http.HandleFunc("/api/undo", undoHandler)
	http.HandleFunc("/api/edit", editHandler)
	addr := "127.0.0.1:8080"
	fmt.Printf("GUI disponível em http://%s/ (servidor ligado em localhost apenas)\n", addr)
	http.ListenAndServe(addr, nil)
}

func listFilesHandler(w http.ResponseWriter, r *http.Request) {
	files, err := os.ReadDir(".")
	if err != nil {
		http.Error(w, err.Error(), 500)
		return
	}
	var out []string
	for _, f := range files {
		if f.IsDir() {
			continue
		}
		ext := strings.ToLower(filepath.Ext(f.Name()))
		if _, ok := supportedExts[ext]; ok {
			out = append(out, f.Name())
		}
	}
	w.Header().Set("Content-Type", "application/json")
	json.NewEncoder(w).Encode(out)
}

func metadataHandler(w http.ResponseWriter, r *http.Request) {
	file := r.URL.Query().Get("file")
	if file == "" {
		http.Error(w, "missing file", 400)
		return
	}
	file = filepath.Base(file)
	fi, err := os.Stat(file)
	if err != nil {
		http.Error(w, err.Error(), 404)
		return
	}
	m := map[string]interface{}{
		"name":     file,
		"size":     fi.Size(),
		"mod_time": fi.ModTime().Format(time.RFC3339),
	}
	ext := strings.ToLower(filepath.Ext(file))
	switch ext {
	case ".jpg", ".jpeg":
		f, err := os.Open(file)
		if err == nil {
			defer f.Close()
			x, err := exif.Decode(f)
			if err == nil {
				if tm, err2 := x.DateTime(); err2 == nil {
					m["exif_datetime"] = tm.Format(time.RFC3339)
				}
				if lat, lon, err2 := x.LatLong(); err2 == nil {
					m["gps"] = map[string]float64{"lat": lat, "lon": lon}
				}
				tc := &tagCollector{M: map[string]string{}}
				x.Walk(tc)
				m["exif_tags"] = tc.M
			}
		}
	case ".png":
		f, err := os.Open(file)
		if err == nil {
			defer f.Close()
			buf := make([]byte, 8)
			if _, err := io.ReadFull(f, buf); err == nil {
				pngSig := []byte{137, 80, 78, 71, 13, 10, 26, 10}
				if !bytes.Equal(buf, pngSig) {
					break
				}
				txts := []string{}
				for {
					var length uint32
					if err := binary.Read(f, binary.BigEndian, &length); err != nil {
						break
					}
					t := make([]byte, 4)
					if _, err := io.ReadFull(f, t); err != nil {
						break
					}
					typ := string(t)
					data := make([]byte, length)
					if _, err := io.ReadFull(f, data); err != nil {
						break
					}
					crc := make([]byte, 4)
					if _, err := io.ReadFull(f, crc); err != nil {
						break
					}
					if typ == "tEXt" || typ == "iTXt" || typ == "zTXt" {
						txts = append(txts, string(data))
					}
					if typ == "IEND" {
						break
					}
				}
				m["png_text_chunks"] = txts
			}
		}
	}
	w.Header().Set("Content-Type", "application/json")
	json.NewEncoder(w).Encode(m)
}

func clearHandler(w http.ResponseWriter, r *http.Request) {
	if r.Method != http.MethodPost {
		http.Error(w, "only POST", 405)
		return
	}
	file := r.URL.Query().Get("file")
	if file == "" {
		http.Error(w, "missing file", 400)
		return
	}
	file = filepath.Base(file)
	if err := clearExifJPEG(file); err != nil {
		http.Error(w, err.Error(), 500)
		return
	}
	w.Write([]byte("ok"))
}

func undoHandler(w http.ResponseWriter, r *http.Request) {
	if r.Method != http.MethodPost {
		http.Error(w, "only POST", 405)
		return
	}
	file := r.URL.Query().Get("file")
	if file == "" {
		http.Error(w, "missing file", 400)
		return
	}
	file = filepath.Base(file)
	bak := file + ".bak"
	if _, err := os.Stat(bak); err != nil {
		http.Error(w, "backup not found", 404)
		return
	}
	if err := os.Rename(bak, file); err != nil {
		http.Error(w, err.Error(), 500)
		return
	}
	w.Write([]byte("ok"))
}

type editRequest struct {
	Remove []string `json:"remove"`
	Set    []string `json:"set"`
	File   string   `json:"file"`
}

func editHandler(w http.ResponseWriter, r *http.Request) {
	if r.Method != http.MethodPost {
		http.Error(w, "only POST", 405)
		return
	}
	var req editRequest
	if err := json.NewDecoder(r.Body).Decode(&req); err != nil {
		http.Error(w, err.Error(), 400)
		return
	}
	file := filepath.Base(req.File)
	if _, err := os.Stat(file); err != nil {
		http.Error(w, "file not found", 404)
		return
	}
	if _, err := exec.LookPath("exiftool"); err != nil {
		http.Error(w, "exiftool not found", 500)
		return
	}
	bak := file + ".bak"
	if _, err := os.Stat(bak); os.IsNotExist(err) {
		data, _ := os.ReadFile(file)
		_ = os.WriteFile(bak, data, 0o644)
	}
	args := []string{"-overwrite_original"}
	for _, t := range req.Remove {
		args = append(args, fmt.Sprintf("-%s=", t))
	}
	for _, s := range req.Set {
		args = append(args, fmt.Sprintf("-%s", s))
	}
	args = append(args, file)
	out, err := exec.Command("exiftool", args...).CombinedOutput()
	if err != nil {
		http.Error(w, string(out), 500)
		return
	}
	w.Write([]byte(string(out)))
}
