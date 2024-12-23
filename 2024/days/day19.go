package days

import (
    "fmt"
    "os"
    "strings"
)

func Day19() (int64, int64) {
    in, err := os.ReadFile("input/day19.txt")
    if err != nil {
        fmt.Println(err)
        return -1, -1
    }

    inParts := strings.SplitN(string(in), "\n\n", 2)

    patterns := make([]string, 0)
    for _, s := range strings.Split(inParts[0], ", ") {
        if len(s) > 0 {
            patterns = append(patterns, s)
        }
    }

    designs := make([]string, 0)
    for _, line := range strings.Split(inParts[1], "\n") {
        if len(line) > 0 {
            designs = append(designs, line)
        }
    }

    memo := make(map[string]int)
    var combs func(string) int
    combs = func(des string) int {
        if len(des) == 0 {
            return 1
        }

        if v, ok := memo[des]; ok {
            return v
        }

        ans := 0
        for _, pat := range patterns {
            if strings.HasPrefix(des, pat) {
                ans += combs(des[len(pat):])
            }
        }

        memo[des] = ans
        return ans
    }

    var possible, arrangements int64
    for _, des := range designs {
        if n := combs(des); n != 0 {
            possible++
            arrangements += int64(n)
        }
    }

    return possible, arrangements
}
