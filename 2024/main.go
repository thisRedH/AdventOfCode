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
        10: days.Day10,
        11: days.Day11,
        12: days.Day12,
        13: days.Day13,
        14: days.Day14,
        15: days.Day15,
        16: days.Day16,
        17: days.Day17,
        18: days.Day18,
        19: days.Day19,
        20: days.Day20,
        21: days.Day21,
        22: days.Day22,
    }

    latestDay := len(daysMap)

    arg := strconv.Itoa(latestDay)
    if len(os.Args) > 1 {
        arg = os.Args[1]
    }

    printDay := func(day int) {
        fmt.Printf("Day %d:\n", day)
        p1, p2 := daysMap[day]()
        if p1 != -1 && p2 != -1 {
            fmt.Printf(" - %d\n - %d\n", p1, p2)
        }
    }

    switch arg {
    case "all":
        fmt.Println("Running all days...")
        for i := 1; i <= latestDay; i++ {
            printDay(i)
        }
    default:
        dayNum, err := strconv.Atoi(arg)
        if err != nil || dayNum < 1 || dayNum > latestDay {
            fmt.Printf("Invalid day: '%s'\nPlease enter a day between 1 and %d or 'all'.\n", arg, latestDay)
            return
        }

        printDay(dayNum)
    }
}
