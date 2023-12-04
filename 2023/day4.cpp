
#include "days.h"

uint32_t solve4a() {
    std::ifstream input("./input/day4.txt");

    std::vector<uint16_t> win_nums(10);
    uint32_t total_points = 0;

    for (std::string line; getline(input, line);) {
        line = line.substr(line.find(": ") +1);
        std::string win_section = line.substr(0, line.find("|"));
        std::string scratch_section = line.substr(line.find("|") +1);

        std::stringstream ss_win(win_section);
        for (uint16_t n; ss_win >> n;) {
            win_nums.push_back(n);
        }

        uint16_t points = 0;
        std::stringstream ss_scratch(scratch_section);
        for (uint16_t n; ss_scratch >> n;) {
            if (std::find(win_nums.begin(), win_nums.end(), n)
                != win_nums.end()
            ) points = points == 0 ? 1 : points * 2;
        }
        total_points += points;

        win_nums.clear();
    }


    return total_points;
}


uint32_t solve4b() {
    std::ifstream input("./input/day4.txt");
    
    return 0;
}
