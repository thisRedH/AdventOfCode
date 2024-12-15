package days

import (
    "fmt"
    "os"
    "strings"
)

func day15P1(in string) int64 {
    inParts := strings.SplitN(in, "\n\n", 2)
    grid := make([][]rune, 0, len(inParts[0]))
    movements := make([][2]int, 0, len(inParts[1]))
    var botPos [2]int

    dirMap := map[rune][2]int{'^':{-1,0},'v':{1,0},'<':{0,-1},'>':{0,1}}
    for _, char := range inParts[1] {
        if d, ok := dirMap[char]; ok {
            movements = append(movements, d)
        }
    }

    for i, line := range strings.Split(inParts[0], "\n") {
        row := make([]rune, 0, len(line))
        for j, char := range line {
            if char == '@' {
                botPos = [2]int{i, j}
                char = '.'
            }
            row = append(row, char)
        }
        grid = append(grid, row)
    }

    add := func(a, b [2]int) [2]int {
        return [2]int(IntArrAdd([]int{a[0], a[1]}, []int{b[0], b[1]}))
    }

    var gpsSum int64
    for _, dir := range movements {
        np := add(botPos, dir)
        switch grid[np[0]][np[1]] {
        case '.':
            botPos = np
        case 'O':
            for nbp := np; grid[nbp[0]][nbp[1]] != '#'; nbp = add(nbp, dir) {
                if grid[nbp[0]][nbp[1]] == '.' {
                    grid[np[0]][np[1]] = '.'
                    grid[nbp[0]][nbp[1]] = 'O'
                    botPos = np
                    break
                }
            }
        }
    }

    for r, row := range grid {
        for c, char := range row {
            if char == 'O' {
                gpsSum += int64(100 * r + c)
            }
        }
    }

    return gpsSum
}

func day15P2(in string) int64 {
    inParts := strings.SplitN(in, "\n\n", 2)
    grid := make(map[[2]int]rune)
    movements := make([][2]int, 0, len(inParts[1]))
    var botPos [2]int

    dirMap := map[rune][2]int{'^':{-1,0},'v':{1,0},'<':{0,-1},'>':{0,1}}
    for _, char := range inParts[1] {
        if d, ok := dirMap[char]; ok {
            movements = append(movements, d)
        }
    }

    for i, line := range strings.Split(inParts[0], "\n") {
        for j, char := range line {
            if char == '@' {
                botPos = [2]int{i, j*2}
            } else if char == '#' {
                grid[[2]int{i, j*2}] = '#'
                grid[[2]int{i, j*2+1}] = '#'
            } else if char == 'O' {
                grid[[2]int{i, j*2}] = '['
            }
        }
    }

    add := func(a, b [2]int) [2]int {
        return [2]int(IntArrAdd([]int{a[0], a[1]}, []int{b[0], b[1]}))
    }

    getBox := func(p [2]int) ([2][2]int, bool) {
        if grid[p] == '[' {
            return [2][2]int{p, add(p, dirMap['>'])}, true
        } else if np := add(p, dirMap['<']); grid[np] == '[' {
            return [2][2]int{np, p}, true
        }
        return [2][2]int{{0,0}, {0,0}}, false
    }

    moveBox := func(d, p [2]int) bool {
        stack := make([][2]int, 0)
        stack = append(stack, p)
        walked := make(map[[2]int]rune)

        for i := 0; i < len(stack); i++ {
            walked[stack[i]] = grid[stack[i]]
            np := add(stack[i], d)
            if _, ok := walked[np]; ok {
                continue
            }

            if bp, ok := getBox(np); ok {
                stack = append(stack, bp[0], bp[1])
            } else if grid[np] == '#' {
                return false
            }
        }

        ngrid := make(map[[2]int]rune, len(grid))
        for p, v := range grid {
            if walked[p] == '[' {
                ngrid[add(p, d)] = '['
            } else {
                ngrid[p] = v
            }
        }
        grid = ngrid

        return true
    }

    var gpsSum int64
    for _, dir := range movements {
        np := add(botPos, dir)
        if _, ok := getBox(np); ok {
            if moveBox(dir, botPos) {
                botPos = np
            }
        } else if grid[np] != '#' {
            botPos = np
        }
    }

    for p, char := range grid {
        if char == '[' {
            gpsSum += int64(100 * p[0] + p[1])
        }
    }

    return gpsSum
}

func Day15() (int64, int64) {
    in, err := os.ReadFile("input/day15.txt")
    if err != nil {
        fmt.Println(err)
        return -1, -1
    }

    return day15P1(string(in)), day15P2(string(in))
}
