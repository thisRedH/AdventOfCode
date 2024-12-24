package days

import (
    "fmt"
    "os"
    "strings"
    "slices"
)

func Day23() (int64, int64) {
    in, err := os.ReadFile("input/day23.txt")
    if err != nil {
        fmt.Println(err)
        return -1, -1
    }

    graph := make(map[string][]string)
    for _, line := range strings.Split(string(in), "\n") {
        if len(line) > 0 {
            node := strings.Split(line, "-")
            graph[node[0]] = append(graph[node[0]], node[1])
            graph[node[1]] = append(graph[node[1]], node[0])
        }
    }

    findCliques := func(g map[string][]string) [][]string {
        var cliques [][]string
        seen := make(map[string]bool)
        for node := range g {
            if seen[node] {
                continue
            }

            clique := []string{node}
            for _, n := range g[node] {
                fullyCon := true
                for _, member := range clique {
                    if !slices.Contains(g[n], member) {
                        fullyCon = false
                        break
                    }
                }

                if fullyCon {
                    clique = append(clique, n)
                    seen[n] = true
                }
            }

            if len(clique) > 1 {
                cliques = append(cliques, clique)
            }
            seen[node] = true
        }
        return cliques
    }

    findTriplets := func(g map[string][]string) [][]string {
        var trip [][]string
        for a := range g {
            for _, b := range g[a] {
                if b < a {
                    continue
                }

                for _, c := range g[b] {
                    if c < b {
                        continue
                    }

                    if slices.Contains(g[c], a) {
                        trip = append(trip, []string{a, b, c})
                    }
                }
            }
        }
        return trip
    }

    var tripletsT int
    for _, arr := range findTriplets(graph) {
        for _, str := range arr {
            if str[0] == 't' {
                tripletsT++
                break
            }
        }
    }

    var biggest []string
    for _, arr := range findCliques(graph) {
        if len(arr) > len(biggest) {
            biggest = arr
        }
    }
    slices.Sort(biggest)

    fmt.Println(" -", tripletsT)
    fmt.Println(" -", strings.Join(biggest, ","))
    return -1, -1
}
