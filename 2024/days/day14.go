package days

import (
    "fmt"
    "os"
)

func Day14() (int64, int64) {
    in, err := os.ReadFile("input/day14.txt")
    if err != nil {
        fmt.Println(err)
        return -1, -1
    }

    fmt.Println(string(in))
    var p1, p2 int64

    return p1, p2
}
