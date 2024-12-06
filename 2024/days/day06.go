package days

import (
    "fmt"
    "os"
    "strings"
    "sync"
    "sync/atomic"
)

func Day06() (int64, int64) {
    in, err := os.ReadFile("input/day06.txt")
    if err != nil {
        fmt.Println(err)
        return -1, -1
    }

    grid := make([][]rune, 0)
    startPos := [2]int{0, 0}

    for i, line := range strings.Split(string(in), "\n") {
        row := make([]rune, 0)
        for j, char := range line {
            if char == '^' {
                startPos = [2]int{i, j}
            }
            row = append(row, char)
        }

        if len(row) > 0 {
            grid = append(grid, row)
        }
    }

    var uniqueTiles, fixesPossible int64

    // Part 1
    dir := Direction{-1, 0} // up
    r, c := startPos[0], startPos[1]
    for InBounds2D(grid, r, c) {
        nr, nc := r+dir[0], c+dir[1];
        if InBounds2D(grid, nr, nc) && grid[nr][nc] == '#' {
            dir[1], dir[0] = dir[0]*-1, dir[1]
        }
        if grid[r][c] != 'X' {
            grid[r][c] = 'X'
            uniqueTiles++
        }
        r += dir[0]
        c += dir[1]
    }

    // Part 2
    var wg sync.WaitGroup
    for i := range grid {
        for j := range grid[i] {
            wg.Add(1)
            go func(i, j int) {
                defer wg.Done()
                if grid[i][j] != 'X' || (i == startPos[0] && j == startPos[1]) {
                    return
                }

                dir := Direction{-1, 0} // up
                seen := make(map[[4]int]struct{}, uniqueTiles)
                r, c := startPos[0], startPos[1]

                for InBounds2D(grid, r, c) {
                    if _, found := seen[[4]int{r, c, dir[0], dir[1]}]; found {
                        atomic.AddInt64(&fixesPossible, 1)
                        break
                    }

                    nr, nc := r+dir[0], c+dir[1];
                    if (nr == i && nc == j) || (InBounds2D(grid, nr, nc) && grid[nr][nc] == '#') {
                        dir[1], dir[0] = -dir[0], dir[1];
                    } else {
                        seen[[4]int{r, c, dir[0], dir[1]}] = struct{}{}
                        r += dir[0]
                        c += dir[1]
                    }
                }
            }(i, j)
        }
    }
    wg.Wait()

    return uniqueTiles, fixesPossible
}
