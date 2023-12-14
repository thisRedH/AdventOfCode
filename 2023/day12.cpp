
#include "days.h"

std::vector<uint32_t> memo;
uint32_t valid_comb(
    std::string& springs, std::vector<uint16_t>& groups,
    uint16_t si = 0, uint16_t gi = 0, uint16_t count = 0
) {
    uint32_t r = 0;

    if (si < springs.size()) {
        const char& c = springs[si];
        si++;

        if (c == '?' || c == '.') {
            if (c == '?') {
                r += valid_comb(springs, groups, si, gi, count +1);
            }

            if (gi < groups.size() && groups[gi] == count) {
                // match, moving to next group
                r += valid_comb(springs, groups, si, gi +1, 0);
            } else if (count == 0) {
                // no match, move to next character
                r += valid_comb(springs, groups, si, gi, 0);
            }
        } else {
            r += valid_comb(springs, groups, si, gi, count +1);
        }
    } else {
        r = (gi == (groups.size() -1) && groups[gi] == count) ||
            (gi == groups.size() && count == 0)
            ? 1 : 0;
    }

    return r;
}


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
