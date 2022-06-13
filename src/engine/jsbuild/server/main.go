package main

import (
	"fmt"
	"net/http"
)

func main() {
	fmt.Println("ARA Web Server, runnin on port 8080")

	// Start the server
	fileServer := http.FileServer(http.Dir("./web"))
	http.Handle("/", fileServer)

	if err := http.ListenAndServe(":8080", nil); err != nil {
		panic(err)
	}
}
