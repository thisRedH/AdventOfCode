
#include "days.h"

inline void push_north(std::vector<std::string>& map) {
    for (size_t row = 0; row < map.size(); row++) {
        for (size_t col = 0; col < map[row].size(); col++) {
            if (map[row][col] == 'O') {
                map[row][col] = '.';

                int32_t rowb = row - 1;
                while (rowb >= 0 && map[rowb][col] == '.')
                    rowb--;

                map[rowb +1][col] = 'O';
            }
        }
    }
}

uint32_t solve14a() {
    std::ifstream input("./input/day14.txt");
    std::vector<std::string> map;
    uint32_t total = 0;

    for (std::string line; std::getline(input, line);) {
        if (!line.empty())
            map.push_back(line);
    }

    push_north(map);

    for (size_t i = 0; i < map.size(); i++)
        total += std::ranges::count(map[i], 'O') * (map.size() - i);

    input.close();
    return total;
}


inline void rotate_clockwise(std::vector<std::string>& grid) {
    std::vector<std::string> transposed(grid[0].size(), std::string(grid.size(), ' '));
    for (size_t i = 0; i < grid.size(); ++i) {
        for (size_t j = 0; j < grid[0].size(); ++j) {
            transposed[j][i] = grid[i][j];
        }
    }

    for (size_t i = 0; i < transposed.size(); i++)
        std::reverse(transposed[i].begin(), transposed[i].end());

    grid = std::move(transposed);
}

inline void roll_map(std::vector<std::string>& map) {
    for (uint8_t i = 0; i < 4; i++) {
        push_north(map);
        rotate_clockwise(map);
    }
}

uint64_t solve14b() {
    std::ifstream input("./input/day14.txt");

    std::vector<std::string> map;
    uint64_t total = 0;

    for (std::string line; std::getline(input, line);) {
        if (!line.empty())
            map.push_back(line);
    }

    std::unordered_map<std::string, uint64_t> cache;
    uint32_t cycles = 1'000'000'000;

    for (uint32_t i = 0; i < cycles; i++) {
        roll_map(map);

        auto [it, inserted] = cache.try_emplace(
            std::accumulate(map.begin(), map.end(), std::string{}), i);

        if (!inserted) {
            const uint32_t& cycle_begin = it->second;
            const uint32_t& cycle_length = i - cycle_begin;

            // The amount of time it has to roll,
            // as it cannot be determined by cycle detection
            cycles = ((cycles - cycle_begin) % cycle_length) -1;
            break;
        }
    }

    for (uint32_t i = 0; i < cycles; i++)
        roll_map(map);

    for (size_t i = 0; i < map.size(); i++) {
        total += std::ranges::count(map[i], 'O') * (map.size() - i);
    }

    input.close();
    return total;
}
