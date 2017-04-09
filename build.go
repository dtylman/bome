package main

import (
	"io"
	"log"
	"net/http"
	"os"
	"path/filepath"
	"runtime"
)

const (
	linkNWJSWindows = "https://dl.nwjs.io/v0.21.5/nwjs-v0.21.5-win-x64.zip"
	linkNWJSLinux   = "https://dl.nwjs.io/v0.21.5/nwjs-v0.21.5-linux-x64.tar.gz"
	linkYoloWeights = "http://pjreddie.com/media/files/yolo.weights"
	linkOpenCV      = "https://sourceforge.net/projects/opencvlibrary/files/opencv-win/3.2.0/opencv-3.2.0-vc14.exe/download"
)

func fileExists(filePath string) bool {
	_, err := os.Stat(filePath)
	return err == nil
}

func downloadFile(url string, filepath string) (err error) {
	if fileExists(filepath) {
		log.Println(filepath, " exists")
		return nil
	}
	log.Println("Downloading " + url)
	// Create the file
	out, err := os.Create(filepath)
	if err != nil {
		return err
	}
	defer out.Close()

	// Get the data
	resp, err := http.Get(url)
	if err != nil {
		return err
	}
	defer resp.Body.Close()

	// Writer the body to file
	_, err = io.Copy(out, resp.Body)
	if err != nil {
		return err
	}

	return nil
}

func buildWindows() error {
	links := []string{linkNWJSWindows, linkOpenCV, linkYoloWeights}
	for _, link := range links {
		err := downloadFile(link, filepath.Base(link))
		if err != nil {
			return err
		}
	}
	return nil
}

func buildLinux() error {
	err := downloadFile(linkNWJSLinux, "nwjs-v0.21.5-linux-x64.tar.gz")
	return err
}

func build() error {
	log.Printf("Building for %s...", runtime.GOOS)
	if runtime.GOOS == "windows" {
		return buildWindows()
	}
	return buildLinux()
}

func main() {
	err := build()
	if err != nil {
		log.Println(err)
	}
}
