package days

import (
    "fmt"
    "math"
    "os"
    "strconv"
    "strings"
)

func IntGetDigitCount(n int) int {
    return int(math.Log10(float64(n))) + 1
}

func IntSplitInMiddle(n int) (int, int) {
    count := IntGetDigitCount(n)
    if count % 2 != 0 {
        return 0, 0
    }

    div := int(math.Pow(10, float64(count/2)))
    return n/div, n%div
}

func Day11() (int64, int64) {
    in, err := os.ReadFile("input/day11.txt")
    if err != nil {
        fmt.Println(err)
        return -1, -1
    }

    stones := make(map[int]int, 2048)
    for _, s := range strings.Fields(string(in)) {
        n, err := strconv.Atoi(s)
        if err == nil {
            stones[n] = 1
        }
    }

    stoneCountShort, stoneCount := 0, 0
    for j := range 75 {
        newStones := make(map[int]int, len(stones)*2)
        stoneCount = 0

        for stone, count := range stones {
            stoneCount += count
            if stone == 0 {
                newStones[1] += count
            } else if a, b := IntSplitInMiddle(stone); a != 0 {
                newStones[a] += count
                newStones[b] += count
                stoneCount += count
            } else {
                newStones[stone * 2024] += count
            }
        }

        stones = newStones
        if j == 25-1 {
            stoneCountShort = stoneCount
        }
    }

    return int64(stoneCountShort), int64(stoneCount)
}
