package days

import (
    "fmt"
    "os"
    "strconv"
    "strings"
)

func nextSecretNum(secret int) int {
    mix := func(a, b int) int { return a^b }
    prune := func(a int) int { return a%16777216 }

    secret = prune(mix(secret, secret*64))
    secret = prune(mix(secret, secret/32))
    secret = prune(mix(secret, secret*2048))
    return secret
}

func Day22() (int64, int64) {
    in, err := os.ReadFile("input/day22.txt")
    if err != nil {
        fmt.Println(err)
        return -1, -1
    }

    secrets := make([]int, 0)
    for _, line := range strings.Split(string(in), "\n") {
        if len(line) > 0 {
            n, _ := strconv.Atoi(line)
            secrets = append(secrets, n)
        }
    }

    var secret2k int64
    var mostBananas uint32
    bananas := make([]uint32, 1<<20)
    for _, num := range secrets {
        var seen [1<<20]bool
        var seq uint32
        var prev int

        for i := 0; i < 2000; i++ {
            num = nextSecretNum(num)

            count := num%10
            diff := count-prev
            prev = count

            seq = (seq<<5 & ((1<<20)-1)) | uint32(diff+10)
            if i >= 3 && !seen[seq] {
                seen[seq] = true
                bananas[seq] += uint32(count)
                if bananas[seq] > mostBananas {
                    mostBananas = bananas[seq]
                }
            }
        }

        secret2k += int64(num)
    }

    return secret2k, int64(mostBananas)
}
