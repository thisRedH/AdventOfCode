package days

import (
    "fmt"
    "os"
    "slices"
    "strings"
    "strconv"
    "sort"
)

func CorrectPageNums(nums []int, beforeMap, afterMap map[int][]int) bool {
    for i, n := range nums {
        bef := beforeMap[n]
        aft := afterMap[n]
        for j, n := range nums {
            if j < i {
                if slices.Contains(bef, n) {
                    return false
                }
            } else if j > i {
                if slices.Contains(aft, n) {
                    return false
                }
            }
        }
    }
    return true
}

func FixPageNums(nums []int, afterMap map[int][]int) []int {
    result := make([]int, len(nums))
    copy(result, nums)

    sort.Slice(result, func(i, j int) bool {
        a, b := result[i], result[j]
        if v, _ := afterMap[a]; slices.Contains(v, b) {
            return true
        }
        return false
    })

    return result
}

func Day05() (int64, int64) {
    in, err := os.ReadFile("input/day05.txt")
    if err != nil {
        fmt.Println(err)
        return -1, -1
    }

    var goodPageTotal, fixedPageTotal int64
    sections := strings.Split(string(in), "\n\n")

    beforeMap := make(map[int][]int)
    afterMap := make(map[int][]int)
    for _, line := range strings.Split(sections[0], "\n") {
        nums := strings.Split(line, "|")
        before, _ := strconv.Atoi(nums[0])
        after, _ := strconv.Atoi(nums[1])
        beforeMap[before] = append(beforeMap[before], after)
        afterMap[after] = append(afterMap[after], before)
    }

    for _, line  := range strings.Split(sections[1], "\n") {
        nums := make([]int, 0)
        for _, n := range strings.Split(line, ",") {
            if n, err := strconv.Atoi(n); err == nil {
                nums = append(nums, n)
            }
        }

        if len(nums) == 0 {
            continue
        }

        if CorrectPageNums(nums, beforeMap, afterMap) {
            goodPageTotal += int64(nums[len(nums) / 2])
        } else {
            nums := FixPageNums(nums, afterMap)
            fixedPageTotal += int64(nums[len(nums) / 2])
        }
    }

    return goodPageTotal, fixedPageTotal
}
