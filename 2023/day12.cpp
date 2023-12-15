
#include "days.h"

inline bool is_valid(const uint16_t& count, const uint16_t& gi, const std::vector<uint16_t>& groups) {
    return
        (gi == (groups.size() -1) && count == groups[gi]) ||
        (gi == (groups.size()) && count == 0);
}

struct VCKey {
    uint16_t si, gi, count;

    bool operator==(const VCKey& other) const {
        return si == other.si && gi == other.gi && count == other.count;
    }
};

struct VCKeyHash {
    size_t operator()(const VCKey& key) const {
        size_t hash = 17;
        hash = hash * 31 + std::hash<uint16_t>{}(key.si);
        hash = hash * 31 + std::hash<uint16_t>{}(key.gi);
        hash = hash * 31 + std::hash<uint16_t>{}(key.count);
        return hash;
    }
};

//#define NO_MEMO 1
using MemoTable = std::unordered_map<VCKey, uint32_t, VCKeyHash>;

//#define DEBUG_GRAPH_STEPPING 1
//#define DEBUG_GRAPH 1
#ifdef DEBUG_GRAPH
uint32_t valid_comb(
    const std::string& springs, const std::vector<uint16_t>& groups, MemoTable& memo,
    uint16_t si = 0, uint16_t gi = 0, uint16_t count = 0,
    char last_c = '.', std::string deug_str = ""
) {
#if NO_MEMO != 1
    VCKey key{si, gi, count};
    auto it = memo.find(key);
    if (it != memo.end()) {
        //std::cout << "cache" << std::endl;
        return it->second;
    }
#endif

    uint32_t r = 0;
    
    deug_str += last_c;
    
    if (si < springs.size()) {
        const char& c = springs[si++];
    
        if (count != 0) {
            if (count > groups[gi]) return 0;
        }

#ifdef DEBUG_GRAPH_STEPPING
        std::cout << "\x1b[90m" << deug_str << "\x1b[0m" << std::endl;
#endif

        if (c == '#' || c == '?') {
            r += valid_comb(springs, groups, memo, si, gi, count +1, '#', deug_str);
        }

        if (c == '.' || c == '?') {
            if (gi < groups.size() && count == groups[gi]) {
                r += valid_comb(springs, groups, memo, si, gi +1, 0, '.', deug_str);
            } else if (count == 0) {
                r += valid_comb(springs, groups, memo, si, gi,    0, '.', deug_str);
            }
        }
    } else {
        if (is_valid(count, gi, groups)) {
            std::cout << "\x1b[97m" << deug_str << "\x1b[0m" << std::endl;
            return 1;
        } else {
            std::cout << "\x1b[90m" << deug_str << "\x1b[0m" << std::endl;
            return 0;
        }
    }

#if NO_MEMO != 1
    memo[key] = r;
#endif
    return r;
}
#else

uint32_t valid_comb(
    const std::string& springs, const std::vector<uint16_t>& groups, MemoTable& memo,
    uint16_t si = 0, uint16_t gi = 0, uint16_t count = 0
) {
#if NO_MEMO != 1
    VCKey key{si, gi, count};
    auto it = memo.find(key);
    if (it != memo.end()) {
        return it->second;
    }
#endif

    uint32_t r = 0;

    if (si < springs.size()) {
        const char& c = springs[si++];

        if (count != 0) {
            if (count > groups[gi]) return 0;
        }

        if (c == '#' || c == '?') {
            r += valid_comb(springs, groups, memo, si, gi, count +1);
        }

        if (c == '.' || c == '?') {
            if (gi < groups.size() && count == groups[gi]) {
                r += valid_comb(springs, groups, memo, si, gi +1, 0);
            } else if (count == 0) {
                r += valid_comb(springs, groups, memo, si, gi, 0);
            }
        }
    } else {
        return is_valid(count, gi, groups) ? 1 : 0;
    }

#if NO_MEMO != 1
    memo[key] = r;
#endif
    return r;
}
#endif //DEBUG_GRAPH

uint32_t solve12a() {
    std::ifstream input("./input/day12.txt");
    /*std::stringstream input(
        "???.### 1,1,3\n"
        ".??..??...?##. 1,1,3\n"
        "?#?#?#?#?#?#?#? 1,3,1,6\n"
        "????.#...#... 4,1,1\n"
        "????.######..#####. 1,6,5\n"
        "?###???????? 3,2,1\n"
    );*/

    std::vector<std::string> springs_rows;
    std::vector<std::vector<uint16_t>> groups_rows;

    for (std::string line; getline(input, line);) {
        std::istringstream ss(std::move(line));

        std::string springs;
        std::vector<uint16_t> groups;
        
        ss >> springs;
        for (uint16_t n = 0; ss >> n;) {
            groups.push_back(n);
            ss.ignore();
        }

        springs_rows.push_back(std::move(springs));
        groups_rows.push_back(std::move(groups));
    }

    uint32_t arrangements = 0;

    MemoTable memo;
    for (auto [springs, group] : std::views::zip(springs_rows, groups_rows)) {
        arrangements += valid_comb(springs, group, memo);
        memo.clear();
    }

    std::cout << arrangements << std::endl;
    input.close();
    return arrangements;
}

uint32_t solve12b() {
    std::ifstream input("./input/day12.txt");

    for (std::string line; getline(input, line);) {
    }

    input.close();
    return 23;
}
