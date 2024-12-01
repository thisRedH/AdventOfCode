package days

import (
    "fmt"
    "strings"
    "strconv"
    "slices"
    "math"
    "os"
)

func Day01() (int64, int64) {
    in, err := os.ReadFile("input/day01.txt")
    if err != nil {
        fmt.Print(err)
        return -1, -1
    }

    var left, right []int
    for _, line := range strings.Split(strings.TrimSpace(string(in)), "\n") {
        numbers := strings.Fields(line)
        if len(numbers) == 2 {
            numl, err1 := strconv.Atoi(numbers[0])
            numr, err2 := strconv.Atoi(numbers[1])
            if err1 == nil && err2 == nil {
                left = append(left, numl)
                right = append(right, numr)
            }
        }
    }

    // part 1
    slices.Sort(left)
    slices.Sort(right)
    var dist int64 = 0
    for i := range left {
        d := left[len(left) - i - 1] - right[len(right) - i - 1]
        dist += int64(math.Abs(float64(d)))
    }

    // part 2
    var count int64 = 0
    for _, v := range left {
        cnt := 0
        for _, v2 := range right {
            if v2 == v {
                cnt++
            }
        }
        count += int64(v * cnt)
    }

    return dist, count
}
