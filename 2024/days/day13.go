package days

import (
    "fmt"
    "math"
    "os"
    "regexp"
    "strconv"
    "strings"
)

func Day13() (int64, int64) {
    in, err := os.ReadFile("input/day13.txt")
    if err != nil {
        fmt.Println(err)
        return -1, -1
    }

    var tokens, tokensBig int64
    clawConfs := make([][3][2]int, 0)

    reg := regexp.MustCompile(`(Y|X)(=|\+)(\d+)`)
    for _, group := range strings.Split(string(in), "\n\n") {
        var conf [3][2]int
        for i, l := range strings.Split(group, "\n") {
            for j, match := range reg.FindAllString(l, -1) {
                conf[i][j], _ = strconv.Atoi(reg.FindStringSubmatch(match)[3])
            }
        }
        clawConfs = append(clawConfs, conf)
    }

    for _, conf := range clawConfs {
        a, b, p := conf[0], conf[1], conf[2]
        test := func(i, j int) bool {
            x := a[0] * i + b[0] * j
            y := a[1] * i + b[1] * j
            return x == p[0] && y == p[1]
        }

        best := math.MaxInt
        for i := range 100 {
            for j := range 100 {
                if test(i, j) {
                    best = min(best, i*3 + j)
                }
            }
        }

        if best < math.MaxInt {
            tokens += int64(best)
        }
    }

    for _, conf := range clawConfs {
        a, b, p := conf[0], conf[1], conf[2]
        ax, ay, bx, by := a[0], a[1], b[0], b[1]
        px, py := p[0]+10000000000000, p[1]+10000000000000

        i := (px*by - py*bx) / (ax*by - ay*bx)
        j := (ax*py - ay*px) / (ax*by - ay*bx)
        x := ax * i + bx * j
        y := ay * i + by * j
        if x == px && y == py {
            tokensBig += int64(i*3 + j)
        }
    }

    return tokens, tokensBig
}
