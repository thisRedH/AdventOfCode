package days

import (
    "fmt"
    "os"
    "strconv"
    "strings"
)

func abs(x int) int {
    if x < 0 {
        return -x
    }
    return x
}

func gcd(a, b int) int {
    for b != 0 {
        a, b = b, a%b
    }
    return a
}

func lcm(a, b int) int {
    return abs(a*b) / gcd(a, b)
}

func Day14() (int64, int64) {
    in, err := os.ReadFile("input/day14.txt")
    if err != nil {
        fmt.Println(err)
        return -1, -1
    }

    var safetyFactor, tree int64
    robots := make([][2][2]int, 0)

    for _, line := range strings.Split(string(in), "\n") {
        if len(line) == 0 {
            continue
        }

        var rob [2][2]int
        for i, p := range strings.SplitN(line, " ", 2){
            for j, s := range strings.SplitN(p[2:], ",", 2) {
                rob[i][j], _ = strconv.Atoi(s)
            }
        }
        robots = append(robots, rob)
    }

    add := func(a, b [2]int) [2]int {
        return [2]int{a[0]+b[0], a[1]+b[1]}
    }

    mul := func(a, b [2]int) [2]int {
        return [2]int{a[0]*b[0], a[1]*b[1]}
    }

    mod := func(a, b [2]int) [2]int {
        return [2]int{
            (a[0] % b[0] + b[0]) % b[0],
            (a[1] % b[1] + b[1]) % b[1],
        }
    }

    height, width := 103, 101
    secs := 100
    var quads [4]int
    for _, rob := range robots {
        rob[0] = add(rob[0], mul(rob[1], [2]int{secs, secs}))
        rob[0] = mod(rob[0], [2]int{width,height})

        if rob[0][0] < width/2 {
            if rob[0][1] < height/2 {
                quads[0]++
            } else if rob[0][1] > (height/2) {
                quads[1]++
            }
        } else if rob[0][0] > (width/2) {
            if rob[0][1] < height/2 {
                quads[2]++
            } else if rob[0][1] > (height/2) {
                quads[3]++
            }
        }
    }

    safetyFactor = 1
    for _, q := range quads {
        safetyFactor *= int64(q)
    }

    for sec := range lcm(width, height) {
        var img = make([][]int, height)
        for i := range img {
            img[i] = make([]int, width)
        }

        for _, rob := range robots {
            rob[0] = add(rob[0], mul(rob[1], [2]int{sec, sec}))
            rob[0] = mod(rob[0], [2]int{width,height})
            img[rob[0][1]][rob[0][0]]++
        }

        overlap := false
        for i := range img {
            for j := range img[i] {
                if img[i][j] > 1 {
                    overlap = true
                    break
                }
            }
        }

        if !overlap {
            tree = int64(sec)
            // Uncomment to print the tree
            /* for i := range img {
                for j := range img[i] {
                    if img[i][j] == 0 {
                        fmt.Print(" ")
                    } else {
                        fmt.Print(img[i][j])
                    }
                }
                fmt.Println()
            } */
            break
        }
    }

    return safetyFactor, tree
}
