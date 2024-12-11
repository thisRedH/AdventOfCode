package days

import (
    "fmt"
    "os"
)

func Day10() (int64, int64) {
    in, err := os.ReadFile("input/day10.txt")
    if err != nil {
        fmt.Println(err)
        return -1, -1
    }

    var p1, p2 int64

    fmt.Println(in)

    return p1, p2
}
