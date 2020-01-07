package main

import "fmt"
import "time"

func say() {
    time.Sleep(time.Millisecond * 600)
    fmt.Println("Hello, World!")
}

func main() {
    go say()
    time.Sleep(time.Millisecond * 750)
}