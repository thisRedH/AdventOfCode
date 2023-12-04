
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

    std::vector<uint16_t> win_nums(10);
    std::unordered_map<uint16_t, uint64_t> cards_to_run;
    uint16_t current_card = 1;
    uint64_t total_cards = 0;

    for (std::string line; getline(input, line); current_card++) {
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
            ) points++;
        }

        cards_to_run[current_card]++;
        for (size_t i = 0; i < cards_to_run[current_card]; i++) {
            for (uint16_t j = 1; j <= points; j++)
                cards_to_run[current_card + j]++;
            total_cards++;
        }

        win_nums.clear();
    }

    return total_cards;
}
