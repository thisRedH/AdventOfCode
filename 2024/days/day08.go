package days

import (
    "fmt"
    "os"
    "strings"
)

func GetAntinode(a, b [2]int) ([2]int, [2]int) {
    dy, dx := a[0] - b[0], a[1]-b[1]
    return [2]int{a[0]+dy, a[1]+dx}, [2]int{b[0]-dy, b[1]-dx}
}

func Day08() (int64, int64) {
    in, err := os.ReadFile("input/day08.txt")
    if err != nil {
        fmt.Println(err)
        return -1, -1
    }

    antennaMap := make([][]rune, 0)
    antennas := make(map[rune][][2]int)
    for i, line := range strings.Split(string(in), "\n") {
        if len(line) < 1 {
            continue
        }

        antennaMap = append(antennaMap, make([]rune, 0))
        for j, char := range line {
            antennaMap[i] = append(antennaMap[i], char)
            if char != '.' {
                antennas[char] = append(antennas[char], [2]int{i, j})
            }
        }
    }

    antinodes := make(map[[2]int]struct{})
    antinodesLine := make(map[[2]int]struct{})
    for _, f := range antennas {
        for i, p1 := range f {
            for _, p2 := range f[:i] {
                if p1 == p2 {
                    continue
                }

                a, b := GetAntinode(p1, p2)
                if InBounds2D(antennaMap, a[0], a[1]) {
                    antinodes[a] = struct{}{}
                }
                if InBounds2D(antennaMap, b[0], b[1]) {
                    antinodes[b] = struct{}{}
                }

                p := p1
                for InBounds2D(antennaMap, p[0], p[1]) {
                    antinodesLine[p] = struct{}{}
                    t, _ := GetAntinode(p, a)
                    a, p = p, t
                }
                p = p2
                for InBounds2D(antennaMap, p[0], p[1]) {
                    antinodesLine[p] = struct{}{}
                    t, _ := GetAntinode(p, b)
                    b, p = p, t
                }
            }
        }
    }

    return int64(len(antinodes)), int64(len(antinodesLine))
}
