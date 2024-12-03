package days

import (
    "fmt"
    "os"
    "regexp"
    "strconv"
)

func Day03() (int64, int64) {
    in, err := os.ReadFile("input/day03.txt")
    if err != nil {
        fmt.Print(err)
        return -1, -1
    }

    mulRe := regexp.MustCompile(`mul\((\d{1,3}),(\d{1,3})\)|(do)\(\)|(don't)\(\)`)
    mulMatches := mulRe.FindAllStringSubmatch(string(in), -1)

    do := true
    var mulTotal int64 = 0
    var mulTotalState int64 = 0

    for _, match := range mulMatches {
        if match[3] == "do" {
            do = true
        } else if match[4] == "don't" {
            do = false
        } else {
            n1, _ := strconv.Atoi(match[1])
            n2, _ := strconv.Atoi(match[2])
            mul := int64(n1 * n2)
            mulTotal += mul

            if do {
                mulTotalState += mul
            }
        }
    }

    return mulTotal, mulTotalState
}
