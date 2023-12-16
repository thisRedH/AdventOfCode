
#include "days.h"

uint64_t solve14a() {
    std::ifstream input("./input/day14.txt");
    std::vector<std::string> map;
    uint64_t total = 0;

    for (std::string line; std::getline(input, line);) {
        if (!line.empty())
            map.push_back(line);
    }

    for (size_t row = 0; row < map.size(); row++) {
        for (size_t col = 0; col < map[row].size(); col++) {
            if (map[row][col] == 'O') {
                map[row][col] = '.';

                for (int32_t rowb = row -1; rowb >= -1; rowb--) {
                    if (rowb < 0 || map[rowb][col] == 'O' || map[rowb][col] == '#') {
                        map[rowb +1][col] = 'O';
                        break;
                    }
                }
            }
        }
    }

    for (size_t i = 0; i < map.size(); i++) {
        total += std::ranges::count(map[i], 'O') * (map.size() - i);
    }

    input.close();
    return total;
}

uint64_t solve14b() {
    return 69;
}
