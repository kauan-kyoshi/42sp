package main

import (
	"bytes"
	"crypto/sha256"
	"encoding/binary"
	"flag"
	"fmt"
	"io/ioutil"
	"log"
	"os"
	"path/filepath"
	"strings"
	"time"
)

var supportedExts = map[string]struct{}{
	".jpg": {}, ".jpeg": {}, ".png": {}, ".gif": {}, ".bmp": {},
}

// The main program shares some functionality with the server; keep minimal CLI features.
func printHeader(name string) {
	fmt.Println("===============================")
	fmt.Printf("Arquivo: %s\n", name)
}

func fileBasicInfo(path string) {
	fi, err := os.Stat(path)
	if err != nil {
		fmt.Printf("  Erro a obter info do ficheiro: %v\n", err)
		return
	}
	fmt.Printf("  Tamanho: %d bytes\n", fi.Size())
	mod := fi.ModTime()
	fmt.Printf("  Modificação: %s\n", mod.Format(time.RFC3339))
}

// remove EXIF APP1 segments from a JPEG file; makes a backup at path+.bak
func clearExifJPEG(pathname string) error {
	data, err := os.ReadFile(pathname)
	if err != nil {
		return err
	}
	if len(data) < 4 || data[0] != 0xFF || data[1] != 0xD8 {
		return fmt.Errorf("não é um JPEG válido")
	}
	out := make([]byte, 0, len(data))
	// copy SOI
	out = append(out, data[0], data[1])
	pos := 2
	for pos+4 <= len(data) {
		if data[pos] != 0xFF {
			// corrupted or reached image data
			break
		}
		marker := data[pos+1]
		pos += 2
		if marker == 0xDA {
			out = append(out, 0xFF, marker)
			out = append(out, data[pos:]...)
			return writeBackupAndReplace(pathname, out, data)
		}
		if pos+2 > len(data) {
			break
		}
		segLen := int(binary.BigEndian.Uint16(data[pos : pos+2]))
		if pos+segLen > len(data) {
			break
		}
		segStart := pos - 2
		segEnd := pos + segLen
		if marker == 0xE1 && segLen >= 8 {
			payloadStart := pos + 2
			if payloadStart+6 <= len(data) {
				if bytes.Equal(data[payloadStart:payloadStart+6], []byte("Exif\x00\x00")) {
					pos = segEnd
					continue
				}
			}
		}
		out = append(out, data[segStart:segEnd]...)
		pos = segEnd
	}
	if pos < len(data) {
		out = append(out, data[pos:]...)
	}
	return writeBackupAndReplace(pathname, out, data)
}

func writeBackupAndReplace(pathname string, newData, orig []byte) error {
	backup := pathname + ".bak"
	if err := ioutil.WriteFile(backup, orig, 0o644); err != nil {
		return fmt.Errorf("erro ao criar backup: %v", err)
	}
	if err := ioutil.WriteFile(pathname, newData, 0o644); err != nil {
		return fmt.Errorf("erro ao gravar ficheiro sem EXIF: %v", err)
	}
	return nil
}

func processFile(pathname string) {
	printHeader(pathname)
	fileBasicInfo(pathname)
	ext := strings.ToLower(filepath.Ext(pathname))
	switch ext {
	case ".jpg", ".jpeg":
		fmt.Println("  JPEG: analisador de EXIF disponível via GUI")
	case ".png":
		fmt.Println("  PNG: leitura de tEXt/iTXt implementada no GUI")
	default:
		fmt.Printf("  Observação: suporte EXIF limitado para extensão %s; mostramos apenas info do ficheiro.\n", ext)
	}
}

// simple encrypted storage used by CLI variants (not used by server directly here)
func deriveKey(pass string) []byte {
	h := sha256.Sum256([]byte(pass))
	return h[:]
}

func main() {
	clear := flag.Bool("clear", false, "Remover EXIF de arquivos JPEG (faz backup com sufixo .bak)")
	undo := flag.Bool("undo", false, "Restaurar backup .bak")
	gui := flag.Bool("gui", false, "Iniciar interface web local (GUI)")
	flag.Parse()
	if *gui {
		startServer()
		return
	}
	if flag.NArg() == 0 {
		flag.Usage()
		os.Exit(1)
	}
	for i := 0; i < flag.NArg(); i++ {
		p := flag.Arg(i)
		if _, err := os.Stat(p); err != nil {
			log.Printf("Arquivo não encontrado: %s (erro: %v)\n", p, err)
			continue
		}
		if *undo {
			backup := p + ".bak"
			if _, err := os.Stat(backup); err != nil {
				fmt.Printf("Backup não encontrado para %s: %s\n", p, backup)
				continue
			}
			if err := os.Rename(backup, p); err != nil {
				fmt.Printf("  Erro ao restaurar %s a partir de %s: %v\n", p, backup, err)
			} else {
				fmt.Printf("  Restaurado %s a partir de %s\n", p, backup)
			}
			continue
		}
		if *clear {
			ext := strings.ToLower(filepath.Ext(p))
			if ext == ".jpg" || ext == ".jpeg" {
				fmt.Printf("Removendo EXIF de %s (backup: %s.bak)...\n", p, p)
				if err := clearExifJPEG(p); err != nil {
					fmt.Printf("  Erro ao limpar EXIF: %v\n", err)
				} else {
					fmt.Printf("  EXIF removido e backup criado: %s.bak\n", p)
				}
				continue
			} else {
				fmt.Printf("Ignorando %s: clear só suporta JPEG (.jpg/.jpeg)\n", p)
				continue
			}
		}
		processFile(p)
	}
}
