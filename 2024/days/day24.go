package days

import (
    "fmt"
    "os"
    "strconv"
    "strings"
)

func Day24() (int64, int64) {
    in, err := os.ReadFile("input/day24.txt")
    if err != nil {
        fmt.Println(err)
        return -1, -1
    }

    inParts := strings.SplitN(string(in), "\n\n", 2)
    type Gate struct{op rune; l string; r string; o string}

    wires := make(map[string]bool)
    for _, line := range strings.Split(inParts[0], "\n") {
        if len(line) > 0 {
            wire := strings.SplitN(line, ": ", 2)
            if wire[1] == "0" {
                wires[wire[0]] = false
            } else if wire[1] == "1" {
                wires[wire[0]] = true
            }
        }
    }

    gates := make([]Gate, 0)
    for _, line := range strings.Split(inParts[1], "\n") {
        if len(line) > 0 {
            s := strings.Fields(line)
            gates = append(gates, Gate{[]rune(s[1])[0], s[0], s[2], s[4]})
        }
    }

    performGate := func(op rune, l, r bool) bool {
        switch op {
            case 'A': return l == true && r == true
            case 'O': return l == true || r == true
            case 'X': return l != r
        }
        panic("Operation unkown")
    }

    var wireOut uint64
    curQ := gates
    for len(curQ) > 0 {
        nextQ := []Gate{}
        for i := 0; i < len(curQ); i++ {
            v := curQ[i]
            l, lok := wires[v.l]
            r, rok := wires[v.r]
            if lok && rok {
                wires[v.o] = performGate(v.op, l, r)
                if v.o[0] == 'z' {
                    if wires[v.o] {
                        pos, _ := strconv.Atoi(v.o[1:])
                        wireOut |= 1 << pos
                    }
                }
            } else {
                nextQ = append(nextQ, curQ[i])
            }
        }
        curQ = nextQ
    }

    fmt.Println(" -", wireOut)
    fmt.Println(" -", "TODO")

    return -1, -1
}
