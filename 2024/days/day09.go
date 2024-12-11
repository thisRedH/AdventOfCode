package days

import (
    "fmt"
    _"os"
    "unicode"
)

func Day09() (int64, int64) {
    // in, err := os.ReadFile("input/day09.txt")
    // if err != nil {
    //     fmt.Println(err)
    //     return -1, -1
    // }
    //in := "2333133121414131402"
    in := "1313165"

    fileMap := make([]int, 0)
    freeMap := make([]int, 0)
    for i, char := range string(in) {
        if unicode.IsDigit(char) {
            if i % 2 == 0 {
                fileMap = append(fileMap, int(char-'0'))
            } else {
                freeMap = append(freeMap, int(char-'0'))
            }
        }
    }

    var checksumFrag, checksumDefrag int64
    var p int
    /* lfid := len(fileMap)-1
    for i := 0; i < len(fileMap)-1+len(freeMap)-1 && lfid >= i/2; i++ {
        if i % 2 == 0 {
            fid := i/2
            flen := fileMap[fid]
            ////checksum += int64(fid * (flen*(flen-1)/2))
            for range flen {
                checksumFrag += int64(p * fid)
                p++
            }
        } else {
            f := freeMap[i/2]
            for f > 0 && lfid > i/2 {
                if f >= fileMap[lfid] {
                    f -= fileMap[lfid]
                    ////checksum += int64(lfid * (fileMap[lfid]*(fileMap[lfid]-1)/2))
                    for range fileMap[lfid] {
                        checksumFrag += int64(p * lfid)
                        p++
                    }
                    fileMap[lfid] = 0
                    lfid--
                } else {
                    ////checksum += int64(lfid * (f*(f-1)/2))
                    for range f {
                        checksumFrag += int64(p * lfid)
                        p++
                    }
                    fileMap[lfid] -= f
                    f = 0
                }
            }
        }
    } */

    p = 0
    freeMap = append(freeMap, 0, 0)
    fmt.Println(fileMap)
    fmt.Println(freeMap)
    line := make([]string, 40)
    for i := range fileMap {
        // for range fileMap[i] {
        //     line[p] = string(i+'0')
        //     checksumDefrag += int64(p * i)
        //     p++
        // }

        ic := len(fileMap)-1-i
        fmt.Println()
        for range fileMap[ic] {
            fmt.Print(ic)
        }
        fmt.Println()
        pc := p
        for f := i; f < len(freeMap); f++ {
            pc += freeMap[f] + fileMap[f]
            if freeMap[f] >= fileMap[ic] {
                for range fileMap[ic] {
                    line[pc] = string(ic+'0')
                    checksumDefrag += int64(pc * ic)
                    pc++
                }
                freeMap[f] -= fileMap[ic]
                freeMap[ic] += fileMap[ic]
                fileMap[ic] = -fileMap[ic]
                break
            }
        }

        // for range freeMap[i] {
        //     fmt.Print(".")
        //     p++
        // }
        //fmt.Print("|")
        for _,c := range line {
            if c == "" {
                fmt.Print(".")
            } else {
                fmt.Print(c)
            }
        }
        fmt.Println()
    }
    return checksumFrag, checksumDefrag
}
