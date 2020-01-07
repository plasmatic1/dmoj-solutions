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
func scan(a ...interface{})             { fmt.Fscan(reader, a...) }

// End Template

type nothing struct{}
type set map[string]nothing

var n int
var buf string
var mp = make(set)

func (v set) contains(key string) bool {
	_, ok := v[key]
	return ok
}

func main() {
	defer writer.Flush() // Flush Output

	scan(&n)

	for i, nn := 0, (n<<1)-1; i < nn; i++ {
		scan(&buf)
		if mp.contains(buf) {
			delete(mp, buf)
		} else {
			mp[buf] = nothing{}
		}
	}

	for k := range mp {
		println(k)
	}
}