package days

import (
    "fmt"
    "os"
    "strings"
)

func InBounds[T any](v []T, i int) bool {
    return i >= 0 && i < len(v)
}

func InBounds2D[T any](v [][]T, i, j int) bool {
    return i >= 0 && i < len(v) && j >= 0 && j < len(v[i])
}

func StrReverse(s string) string {
    runes := []rune(s)
    for i, j := 0, len(runes)-1; i < j; i, j = i+1, j-1 {
        runes[i], runes[j] = runes[j], runes[i]
    }
    return string(runes)
}

type Direction [2]int

func WordSearch(grid [][]rune, r, c int, dir Direction, word string) bool {
    if !InBounds2D(grid, r, c) {
        return false
    }

    if grid[r][c] == rune(word[len(word)-1]) {
        word = StrReverse(word)
    }

    for _, char := range word {
        if !InBounds2D(grid, r, c) || grid[r][c] != char {
            return false
        }

        r += dir[0]
        c += dir[1]
    }

    return true
}

func XmasSearchCount(grid [][]rune) int {
    dirs := []Direction{
        {-1, -1}, { 0, -1}, {-1,  0},
        { 1,  1}, { 0,  1}, { 1,  0},
        {-1,  1},
        { 1, -1},
    }

    count := 0
    for r := 0; r < len(grid); r++ {
        for c := 0; c < len(grid[r]); c++ {
            for _, dir := range dirs {
                if s := WordSearch(grid, r, c, dir, "XMAS"); s {
                    count++
                }
            }
        }
    }

    return count / 2
}

func MasXSearchCount(grid [][]rune) int {
    dirs := []Direction{
        {-1, -1},
        { 1,  1},
        {-1,  1},
        { 1, -1},
    }

    count := 0
    for r := 0; r < len(grid); r++ {
        for c := 0; c < len(grid[r]); c++ {
            for _, dir := range dirs {
                if WordSearch(grid, r, c, dir, "MAS") {
                    nr := r + 2 * dir[0]
                    nd := Direction{dir[0] * -1, dir[1]}
                    if WordSearch(grid, nr, c, nd, "MAS") {
                        count++
                    }
                }
            }
        }
    }

    return count / 4
}

func Day04() (int64, int64) {
    in, err := os.ReadFile("input/day04.txt")
    if err != nil {
        fmt.Println(err)
        return -1, -1
    }

    lines := strings.Split(string(in), "\n")
    grid := make([][]rune, len(lines))
    for i, line := range lines {
        grid[i] = []rune(line)
    }

    return int64(XmasSearchCount(grid)), int64(MasXSearchCount(grid)) 
}
