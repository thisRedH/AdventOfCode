package days

import (
    "fmt"
    "math"
    "os"
    "strings"
)

func findPaths(grid [][]rune, start, end [2]int) (map[int][][][2]int, int) {
    result := make(map[int][][][2]int)
    var cpath [][2]int
    visited := make(map[[2]int]bool)
    cheapest := math.MaxInt

    getPathCost := func(path [][2]int) int {
        cost := 0
        lp := start
        for _, p := range path {
            cost += abs((p[0]-lp[0]) + (p[1]-lp[1]))
            cost += 1000
            lp = p
        }
        cost += abs((end[0]-lp[0]) + (end[1]-lp[1]))
        fmt.Println(cost, path)
        return cost
    }

    var dfs func(int, int, [2]int)
    dfs = func(y, x int, pdir [2]int) {
        if !InBounds2D(grid, y, x) || grid[y][x] == '#' {
            return
        }

        if visited[[2]int{y, x}] {
            return
        }
        visited[[2]int{y, x}] = true
        defer func() { visited[[2]int{y, x}] = false }()

        if y == end[0] && x == end[1] {
            cpy := append([][2]int{}, cpath...)
            cost := getPathCost(cpy)
            result[cost] = append(result[cost], cpy)
            if cost < cheapest {
                cheapest = cost
            }
            return
        }

        for _, ndir := range [][2]int{{0,1}, {1,0}, {0,-1}, {-1,0}} {
            ny, nx := y+ndir[0], x+ndir[1]

            if pdir != ndir {
                cpath = append(cpath, [2]int{y, x})
            }

            dfs(ny, nx, ndir)

            if len(cpath) > 0 && cpath[len(cpath)-1] == [2]int{y, x} {
                cpath = cpath[:len(cpath)-1]
            }
        }
    }


    dfs(start[0], start[1], [2]int{0, 1})
    return result, cheapest
}

func Day16() (int64, int64) {
    _, err := os.ReadFile("input/day16.txt")
    if err != nil {
        fmt.Println(err)
        return -1, -1
    }

    in := `###############
#.......#....E#
#.#.###.#.###.#
#.....#.#...#.#
#.###.#####.#.#
#.#.#.......#.#
#.#.#####.###.#
#...........#.#
###.#.#####.#.#
#...#.....#.#.#
#.#.#.###.#.#.#
#.....#...#.#.#
#.###.#.#.#.#.#
#S..#.....#...#
###############`

//     in := `####################################################
// #......................................#..........E#
// #......................................#...........#
// #....................#.................#...........#
// #....................#.................#...........#
// #....................#.................#...........#
// #....................#.................#...........#
// #....................#.................#...........#
// #....................#.................#...........#
// #....................#.................#...........#
// #....................#.................#...........#
// #....................#.............................#
// #S...................#.............................#
// ####################################################`

    grid := make([][]rune, 0)
    var start, end [2]int
    for i, line := range strings.Split(string(in), "\n") {
        row := make([]rune, 0, len(line))
        for j, char := range line {
            if char == 'S' {
                start = [2]int{i, j}
            } else if char == 'E' {
                end = [2]int{i, j}
            }
            row = append(row, char)
        }
        grid = append(grid, row)
    }

    var p2 int64

    _, best := findPaths(grid, start, end)

    return int64(best), p2
}
