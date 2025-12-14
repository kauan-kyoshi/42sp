package main

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/hmac"
	"crypto/rand"
	"crypto/sha1"
	"crypto/sha256"
	"encoding/hex"
	"errors"
	"flag"
	"fmt"
	"io"
	"io/ioutil"
	"os"
	"strings"
	"time"
)

// static passphrase used to derive AES key (change if you want)
const staticPass = "FT_OTP_STATIC_KEY_CHANGE_ME"
const outFile = "ft_otp.key"

func deriveKey() []byte {
	h := sha256.Sum256([]byte(staticPass))
	return h[:]
}

func encryptAndWrite(hexKey string, path string) error {
	key := deriveKey()
	block, err := aes.NewCipher(key)
	if err != nil {
		return err
	}
	gcm, err := cipher.NewGCM(block)
	if err != nil {
		return err
	}
	nonce := make([]byte, gcm.NonceSize())
	if _, err := io.ReadFull(rand.Reader, nonce); err != nil {
		return err
	}
	ct := gcm.Seal(nil, nonce, []byte(hexKey), nil)
	// write nonce + ciphertext
	data := append(nonce, ct...)
	return ioutil.WriteFile(path, data, 0600)
}

func readAndDecrypt(path string) (string, error) {
	data, err := ioutil.ReadFile(path)
	if err != nil {
		return "", err
	}
	key := deriveKey()
	block, err := aes.NewCipher(key)
	if err != nil {
		return "", err
	}
	gcm, err := cipher.NewGCM(block)
	if err != nil {
		return "", err
	}
	ns := gcm.NonceSize()
	if len(data) < ns {
		return "", errors.New("file too short")
	}
	nonce := data[:ns]
	ct := data[ns:]
	pt, err := gcm.Open(nil, nonce, ct, nil)
	if err != nil {
		return "", err
	}
	return string(pt), nil
}

func isHex64(s string) bool {
	if len(s) != 64 {
		return false
	}
	_, err := hex.DecodeString(s)
	return err == nil
}

func hotp(secret []byte, counter uint64) string {
	// counter 8-byte big endian
	var msg [8]byte
	for i := 7; i >= 0; i-- {
		msg[i] = byte(counter & 0xff)
		counter >>= 8
	}
	mac := hmac.New(sha1.New, secret)
	mac.Write(msg[:])
	h := mac.Sum(nil)
	// dynamic truncation
	offset := int(h[len(h)-1] & 0x0f)
	code := (int(h[offset]&0x7f) << 24) | (int(h[offset+1]&0xff) << 16) | (int(h[offset+2]&0xff) << 8) | int(h[offset+3]&0xff)
	otp := code % 1000000
	return fmt.Sprintf("%06d", otp)
}

func main() {
	gflag := flag.String("g", "", "Provide a hexadecimal key (or path to file) to store encrypted in ft_otp.key")
	kflag := flag.String("k", "", "Read encrypted key file and print current OTP (pass path to ft_otp.key)")
	flag.Parse()

	if *gflag == "" && *kflag == "" {
		fmt.Fprintf(os.Stderr, "Usage: %s -g <hexkey|file> | -k <ft_otp.key>\n", os.Args[0])
		os.Exit(1)
	}

	if *gflag != "" {
		arg := strings.TrimSpace(*gflag)
		// if arg is a file path, read its content
		if _, err := os.Stat(arg); err == nil {
			b, err := ioutil.ReadFile(arg)
			if err == nil {
				arg = strings.TrimSpace(string(b))
			}
		}
		if !isHex64(arg) {
			fmt.Fprintf(os.Stderr, "%s: error: key must be 64 hexadecimal characters.\n", os.Args[0])
			os.Exit(1)
		}
		// store encrypted
		if err := encryptAndWrite(arg, outFile); err != nil {
			fmt.Fprintf(os.Stderr, "%s: error: failed to save key: %v\n", os.Args[0], err)
			os.Exit(1)
		}
		fmt.Printf("Key was successfully saved in %s.\n", outFile)
		return
	}

	if *kflag != "" {
		path := *kflag
		if _, err := os.Stat(path); err != nil {
			fmt.Fprintf(os.Stderr, "%s: error: cannot open %s\n", os.Args[0], path)
			os.Exit(1)
		}
		hexkey, err := readAndDecrypt(path)
		if err != nil {
			fmt.Fprintf(os.Stderr, "%s: error: failed to decrypt key: %v\n", os.Args[0], err)
			os.Exit(1)
		}
		hexkey = strings.TrimSpace(hexkey)
		if !isHex64(hexkey) {
			fmt.Fprintf(os.Stderr, "%s: error: invalid stored key\n", os.Args[0])
			os.Exit(1)
		}
		secret, _ := hex.DecodeString(hexkey)
		// TOTP: moving factor is current unix / 30
		counter := uint64(time.Now().Unix() / 30)
		otp := hotp(secret, counter)
		fmt.Println(otp)
		return
	}
}
