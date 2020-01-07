package main

// Begin Template
import (
	"bufio"
	"fmt"
	"os"
)

var reader = bufio.NewReader(os.Stdin)
var writer = bufio.NewWriter(os.Stdout)

func printf(f string, a ...interface{}) { fmt.Fprintf(writer, f, a...) }
func println(a ...interface{})          { fmt.Fprintln(writer, a...) }
func scanf(f string, a ...interface{})  { fmt.Fscanf(reader, f, a...) }

// End Template

var n, k, j, bj, bf, bk int
var dif [100010]int

func main() {
	defer writer.Flush() // Flush Output

	scanf("%d\n%d\n%d\n", &n, &k, &j)

	// fmt.Println("ionam", n, k, j)

	for i := 0; i < j; i++ {
		scanf("%d %d %d\n", &bj, &bf, &bk)
		dif[bj] += bk
		dif[bf+1] -= bk
	}

	for i := 1; i <= n; i++ {
		dif[i] += dif[i-1]
	}

	tot := 0
	for i := 1; i <= n; i++ {
		if dif[i] < k {
			tot++
		}
	}
	println(tot)
}