package main

import (
    "fmt"
    "strconv"
    "os"

    "aoc2024/days"
)

func main() {
    daysMap := map[int]func() (int64, int64) {
        1: days.Day01,
        2: days.Day02,
        3: days.Day03,
        4: days.Day04,
        5: days.Day05,
        6: days.Day06,
        7: days.Day07,
        8: days.Day08,
        9: days.Day09,
    }

    latestDay := len(daysMap)

    arg := strconv.Itoa(latestDay)
    if len(os.Args) > 1 {
        arg = os.Args[1]
    }

    switch arg {
    case "all":
        fmt.Println("Running all days...")
        for i := 1; i <= latestDay; i++ {
            fmt.Printf("Day %d:\n", i)
            p1, p2 := daysMap[i]()
            fmt.Printf(" - %d\n - %d\n", p1, p2)
        }
    default:
        dayNum, err := strconv.Atoi(arg)
        if err != nil || dayNum < 1 || dayNum > latestDay {
            fmt.Printf("Invalid day: '%s'\nPlease enter a day between 1 and %d or 'all'.\n", arg, latestDay)
            return
        }

        fmt.Printf("Day %d:\n", dayNum)
        p1, p2 := daysMap[dayNum]()
        fmt.Printf(" - %d\n - %d\n", p1, p2)
    }
}
