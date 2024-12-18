package days

import (
    "fmt"
    "os"
    "regexp"
    "slices"
    "strconv"
    "strings"
)

func FmtBitSegmented(n, seg int) string {
    binaryStr := fmt.Sprintf("%b", n)

    padding := (seg - len(binaryStr)%seg) % seg
    binaryStr = strings.Repeat("0", padding) + binaryStr

    var segmented strings.Builder
    segmented.WriteString("0b")
    for i, char := range binaryStr {
        if i > 0 && i%seg == 0 {
            segmented.WriteByte('_')
        }
        segmented.WriteByte(byte(char))
    }

    return segmented.String()
}

func Day17() (int64, int64) {
    in, err := os.ReadFile("input/day17.txt")
    if err != nil {
        fmt.Println(err)
        return -1, -1
    }

    regRe := regexp.MustCompile(`Register .: (\d+)`)
    progRe := regexp.MustCompile(`(?:\d,)+\d`)
    matches := regRe.FindAllString(string(in), -1)
    rai, _ := strconv.Atoi(matches[0][len("Register X: "):])
    rbi, _ := strconv.Atoi(matches[1][len("Register X: "):])
    rci, _ := strconv.Atoi(matches[2][len("Register X: "):])
    ra, rb, rc := int64(rai), int64(rbi), int64(rci)
    prog := make([]int, 0)
    for _, s := range strings.Split(progRe.FindString(string(in)), ",") {
        n, _ := strconv.Atoi(s)
        prog = append(prog, n)
    }

    run := func(a, b, c int64) []int {
        comboOP := func(op int) int64 {
            switch op {
                case 4: return a
                case 5: return b
                case 6: return c
                case 7: panic("Invalid comboOP (7)")
                default: return int64(op)
            }
        }

        out := make([]int, 0)
        for i := 0; i < len(prog); i+=2 {
            switch prog[i] {
            case 0: // adv
                a = a >> comboOP(prog[i+1])
            case 1: // bxl
                b ^= int64(prog[i+1])
            case 2: // bst
                b = comboOP(prog[i+1]) % 8
            case 3: // jnz
                if a != 0 {
                    i = prog[i+1] - 2
                }
            case 4: // bxc
                b ^= c
            case 5: // out
                out = append(out, int(comboOP(prog[i+1]) % 8))
            case 6: // bdv
                b = a >> comboOP(prog[i+1])
            case 7: // cdv
                c = a >> comboOP(prog[i+1])
            default:
                panic("Invalid opcode")
            }
        }
        return out
    }

    outStr := strings.Join(strings.Fields(fmt.Sprint(run(ra, rb, rc))), ",")
    fmt.Println(" -", outStr[1:len(outStr)-1])

    queue := []int64{0, 1, 2, 3, 4, 5, 6, 7}
    for i := 0; i < len(queue); i++ {
        out := run(queue[i], rb, rc)

        if slices.Equal(out, prog) {
            fmt.Println(" -", queue[i])
            break
        }

        if slices.Equal(out, prog[len(prog)-len(out):]) {
            for j := range 8 {
                queue = append(queue, (queue[i] << 3) + int64(j))
            }
        }
    }

    return -1, -1
}
