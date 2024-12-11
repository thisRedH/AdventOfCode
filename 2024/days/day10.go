package days

import (
    "fmt"
    "os"
    "strings"
    "unicode"
)

func Day10() (int64, int64) {
    in, err := os.ReadFile("input/day10.txt")
    if err != nil {
        fmt.Println(err)
        return -1, -1
    }

    var score, rating int64
    var grid [][]int
    var visited [][]bool
    for _, l := range strings.Split(string(in), "\n") {
        row := make([]int, 0, len(l))
        for _, c := range l {
            if unicode.IsDigit(c) {
                row = append(row, int(c-'0'))
            }
        }
        if len(row) > 0 {
            grid = append(grid, row)
            visited = append(visited, make([]bool, len(row)))
        }
    }

    var traverse func(int, int, int, map[[2]int]struct{}) (int, int)
    traverse = func(r, c, last int, dest map[[2]int]struct{}) (int, int) {
        if !InBounds2D(grid, r, c) || visited[r][c] || grid[r][c] != last+1 {
            return 0, 0
        }

        if grid[r][c] == 9 {
            if _, ok := dest[[2]int{r, c}]; ok {
                return 0, 1
            } else {
                dest[[2]int{r, c}] = struct{}{}
                return 1, 1
            }
        }

        visited[r][c] = true
        var ta, tb int
        for _, d := range [][2]int{{0, 1}, {1, 0}, {0, -1}, {-1, 0}} {
            a, b := traverse(r+d[0], c+d[1], grid[r][c], dest)
            ta += a
            tb += b
        }
        visited[r][c] = false
        return ta, tb
    }

    for r := range grid {
        for c, v := range grid[r] {
            if v == 0 {
                a, b := traverse(r, c, -1, map[[2]int]struct{}{})
                score += int64(a)
                rating += int64(b)
            }
        }
    }

    return score, rating
}
