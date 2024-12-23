package days

import (
    "fmt"
    "os"
)

func Day18() (int64, int64) {
    _, err := os.ReadFile("input/day18.txt")
    if err != nil {
        fmt.Println(err)
        return -1, -1
    }

    // same as Day16

    return 1, 1
}
