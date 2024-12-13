package days

import (
    "fmt"
    "os"
    "strings"
)

func IntArrAdd(a, b []int) []int {
    r := make([]int, len(a))
    for i := range a {
        r[i] = a[i] + b[i]
    }
    return r
}

func Day12() (int64, int64) {
    in, err := os.ReadFile("input/day12.txt")
    if err != nil {
        fmt.Println(err)
        return -1, -1
    }

    plants := make(map[rune]map[[2]int]struct{})
    for i, line := range strings.Split(string(in), "\n") {
        for j, char := range line {
            if plants[char] == nil {
                plants[char] = make(map[[2]int]struct{})
            }
            plants[char][[2]int{i, j}] = struct{}{}
        }
    }

    getPlot := func(pos [2]int, plant map[[2]int]struct{}) map[[2]int]int {
        plot := make(map[[2]int]int)
        plot[pos]--
        stack := make([][2]int, 0)
        stack = append(stack, pos)

        for i := 0; i < len(stack); i++ {
            for _, d := range [][2]int{{1,0}, {-1,0}, {0,1}, {0,-1}} {
                np := [2]int{stack[i][0]+d[0], stack[i][1]+d[1]}
                if _, ok := plant[np]; ok {
                    if _, ok := plot[np]; !ok {
                        plot[np]--
                        stack = append(stack, np)
                    }
                } else {
                    plot[np]++
                }
            }
        }
        return plot
    }

    add := func(a, b [2]int) [2]int {
        return [2]int(IntArrAdd([]int{a[0], a[1]}, []int{b[0], b[1]}))
    }

    countInnerCorner := func(pos [2]int, plot map[[2]int]int) int {
        directions := [][3][2]int{
            {{ 1, 0}, {0,  1}, { 1, 1}},
            {{ 1, 0}, {0, -1}, { 1,-1}},
            {{-1, 0}, {0,  1}, {-1, 1}},
            {{-1, 0}, {0, -1}, {-1,-1}},
        }

        count := 0
        for _, dir := range directions {
            if plot[pos] > 0 &&
            plot[add(pos, dir[0])] < 0 &&
            plot[add(pos, dir[1])] < 0 &&
            plot[add(pos, dir[2])] < 0 {
                count++
            }
        }
        return count
    }

    var price, priceDiscount int64
    for _, plant := range plants {
        visited := make(map[[2]int]struct{})
        for pos := range plant {
            if _, ok := visited[pos]; ok {
                continue
            }

            var perimeter, size, corners int
            plot := getPlot(pos, plant)
            for p, v := range plot {
                if v < 0 {
                    visited[p] = struct{}{}
                    size++
                    for _, r := range []int{1, -1} {
                        for _, c := range []int{1, -1} {
                            if plot[[2]int{p[0]+r, p[1]}] > 0 && plot[[2]int{p[0], p[1]+c}] > 0 {
                                corners++
                            }
                        }
                    }
                } else {
                    perimeter += v
                    if c := countInnerCorner(p, plot); c > 0 {
                        corners += c
                    }
                }
            }

            price += int64(size * perimeter)
            priceDiscount += int64(size * corners)
        }
    }

    return price, priceDiscount
}
