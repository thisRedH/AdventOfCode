package days

import (
    "fmt"
    "os"
)

func Day20() (int64, int64) {
    _, err := os.ReadFile("input/day20.txt")
    if err != nil {
        fmt.Println(err)
        return -1, -1
    }

    return 0, 0
}
