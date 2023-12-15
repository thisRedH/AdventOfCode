
#include "days.h"

inline bool is_valid(const uint16_t& count, const uint16_t& gi, const std::vector<uint16_t>& groups) {
    return
        (gi == (groups.size() -1) && count == groups[gi]) ||
        (gi == (groups.size()) && count == 0);
}

//#define DEBUG_GRAPH 1
#ifdef DEBUG_GRAPH
uint32_t valid_comb(
    const std::string& springs, const std::vector<uint16_t>& groups,
    uint16_t si = 0, uint16_t gi = 0, uint16_t count = 0,
    char last_c = '.', std::string deug_str = ""
) {
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
            r += valid_comb(springs, groups, si, gi, count +1, '#', deug_str);
        }

        if (c == '.' || c == '?') {
            if (gi < groups.size() && count == groups[gi]) {
                r += valid_comb(springs, groups, si, gi +1, 0, '.', deug_str);
            } else if (count == 0) {
                r += valid_comb(springs, groups, si, gi,    0, '.', deug_str);
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
    return r;
}
#else

uint32_t valid_comb(
    const std::string& springs, const std::vector<uint16_t>& groups,
    uint16_t si = 0, uint16_t gi = 0, uint16_t count = 0
) {
    uint32_t r = 0;

    if (si < springs.size()) {
        const char& c = springs[si++];

        if (count != 0) {
            if (count > groups[gi]) return 0;
        }

        if (c == '#' || c == '?') {
            r += valid_comb(springs, groups, si, gi, count +1);
        }

        if (c == '.' || c == '?') {
            if (gi < groups.size() && count == groups[gi]) {
                r += valid_comb(springs, groups, si, gi +1, 0);
            } else if (count == 0) {
                r += valid_comb(springs, groups, si, gi, 0);
            }
        }
    } else {
        return is_valid(count, gi, groups) ? 1 : 0;
    }

    return r;
}
#endif //DEBUG_GRAPH

uint32_t solve12a() {
    std::ifstream input("./input/day12.txt");

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

    for (auto [springs, group] : std::views::zip(springs_rows, groups_rows)) {
        arrangements += valid_comb(springs, group);
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
