package days

import (
    "fmt"
    "math"
    "os"
    "strconv"
    "strings"
)

func appendN[T any](in []T, count int, v T) []T {
    if count <= 0 {
        return in
    }

    tmp := make([]T, count)
    for i := range count {
        tmp[i] = v
    }
    return append(in, tmp...)
}

func buttonSeq(grid [][]rune, start, end [2]int) []rune {
    var allPaths [][][2]int
    var getPaths func([2]int, [2]int, [][2]int)
    getPaths = func(cur, end [2]int, path [][2]int) {
        if cur == end {
            p := make([][2]int, len(path))
            copy(p, path)
            allPaths = append(allPaths, p)
            return
        }

        for _, dir := range [][2]int{{-1,0}, {0,1}, {1,0}, {0,-1}} {
            ny, nx := cur[0]+dir[0], cur[1]+dir[1]
            if InBounds2D(grid, ny, nx) && grid[ny][nx] != ' ' {
                prev := grid[cur[0]][cur[1]]
                grid[cur[0]][cur[1]] = ' '
                getPaths([2]int{ny, nx}, end, append(path, dir))
                grid[cur[0]][cur[1]] = prev
            }
        }
    }

    getCost := func(cur, prev rune) int {
        if cur == prev {
            return 0
        }

        bonus := 0
        switch prev {
            case '^': bonus = 3
            case '>': bonus = 3
            case 'v': bonus = 2
            case '<': bonus = 1
        }
        switch cur {
            case '^': return 10 + bonus
            case '>': return 10 + bonus
            case 'v': return 20 + bonus
            case '<': return 30 + bonus
            default: return 0
        }
    }

    translatePath := func(path [][2]int) ([]rune, int) {
        p, c := make([]rune, len(path)), 0
        prev := 'A'
        for i, v := range path {
            switch v {
                case [2]int{-1, 0}: p[i] = '^'
                case [2]int{ 0, 1}: p[i] = '>'
                case [2]int{ 1, 0}: p[i] = 'v'
                case [2]int{ 0,-1}: p[i] = '<'
            }
            c += getCost(p[i], prev)
            prev = p[i]
        }
        return append(p, 'A'), c
    }

    getPaths(start, end, [][2]int{})

    minCost := math.MaxInt
    var bestPath []rune
    for _, p := range allPaths {
        path, cost := translatePath(p)
        if cost == minCost {
        } else if cost < minCost {
            minCost = cost
            bestPath = path
        }
    }

    return bestPath
}

func Day21() (int64, int64) {
    in, err := os.ReadFile("input/day21.txt")
    if err != nil {
        fmt.Println(err)
        return -1, -1
    }

    numericKeypad := [][]rune{
        {'7', '8', '9'},
        {'4', '5', '6'},
        {'1', '2', '3'},
        {' ', '0', 'A'},
    }

    nkpdMap := make(map[[2]rune][]rune)
    for i, r := range numericKeypad {
        for j, c := range r {
            for ii, rr := range numericKeypad {
                for jj, cc := range rr {
                    if c == ' ' || cc == ' ' {
                        continue
                    }
                    path := buttonSeq(numericKeypad, [2]int{i,j}, [2]int{ii,jj})
                    nkpdMap[[2]rune{c, cc}] = path
                }
            }
        }
    }

    directionalKeypad := [][]rune{
        {' ', '^', 'A'},
        {'<', 'v', '>'},
    }

    dkpdMap := make(map[[2]rune][]rune)
    for i, r := range directionalKeypad {
        for j, c := range r {
            for ii, rr := range directionalKeypad {
                for jj, cc := range rr {
                    if c == ' ' || cc == ' ' {
                        continue
                    }
                    path := buttonSeq(directionalKeypad, [2]int{i,j}, [2]int{ii,jj})
                    dkpdMap[[2]rune{c, cc}] = path
                }
            }
        }
    }

    memo := make(map[string]int)
    var pressDirectional func([]rune, int) int
    pressDirectional = func(sequence []rune, n int) int {
        if v, ok := memo[string(sequence)+string(n)]; ok {
            return v
        }

        seq, lc := 0, 'A'
        for _, c := range sequence {
            if v, ok := dkpdMap[[2]rune{lc, c}]; ok {
                if n < 1 {
                    seq += len(v)
                } else {
                    seq += pressDirectional(v, n-1)
                }
            }
            lc = c
        }

        memo[string(sequence)+string(n)] = seq
        return seq
    }

    pressNumeric := func(sequence string, n int) int {
        seq, lc := 0, 'A'
        for _, c := range sequence {
            seq += pressDirectional(nkpdMap[[2]rune{lc, c}], n-1)
            lc = c
        }
        return seq
    }

    var sum, sumBig int64
    for _, line := range strings.Split(string(in), "\n") {
        if len(line) > 0 {
            n, _ := strconv.Atoi(line[:3])
            seq := pressNumeric(line, 2)
            sum += int64(n*seq)
            seqBig := pressNumeric(line, 25)
            sumBig += int64(n*seqBig)
        }
    }

    return sum, sumBig
}
