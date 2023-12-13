
#include "days.h"

struct vec2_u64 {
    uint64_t y;
    uint64_t x;
};

// Uses Manhattan distance formula
uint32_t get_distance(const vec2_u64& start, const vec2_u64& end) {
    return static_cast<uint32_t>(
        (uint32_t)abs((uint32_t)(start.x - end.x)) + (uint32_t)abs((uint32_t)(start.y - end.y))
    );
}

uint32_t solve11a() {
    std::ifstream input("./input/day11.txt");

    std::vector<std::string> universe;
    std::vector<vec2_u64> galaxies;
    std::vector<uint16_t> empty_rows;
    std::vector<uint16_t> empty_cols;
    uint32_t total_distance = 0;

    for (std::string line; getline(input, line);) {
        universe.push_back(line);
    }

    for (uint16_t i = 0; i < universe.size(); i++) {
        if (universe[i].find('#') == std::string::npos) {
            empty_rows.push_back(i);
        }
    }

    for (uint16_t j = 0; j < universe[0].size(); j++) {
        std::string col;
        for (uint16_t i = 0; i < universe.size(); i++) {
            col += universe[i][j];
        }

        if (col.find('#') == std::string::npos) {
            empty_cols.push_back(j);
        }
    }

    uint32_t my = 0, mx = 0;
    for (uint32_t i = 0; i < universe.size(); i++) {
        if (std::ranges::find(empty_rows, i) != empty_rows.end()) {
            my++;
            continue;
        }

        mx = 0;
        for (uint32_t j = 0; j < universe[i].size(); j++) {
            if (std::ranges::find(empty_cols, j) != empty_cols.end()) {
                mx++;
                continue;
            }

            if (universe[i][j] == '#')
                galaxies.push_back(vec2_u64{
                    static_cast<uint32_t>(i + my),
                    static_cast<uint32_t>(j + mx)
                });
        }
    }
 
    for (size_t i = 0; i < galaxies.size(); i++) {
        for (size_t j = i +1; j < galaxies.size(); j++) {
            total_distance += get_distance(galaxies[i], galaxies[j]);
        }
    }

    input.close();
    return total_distance;
}


uint64_t solve11b() {
    std::ifstream input("./input/day11.txt");

    std::vector<std::string> universe;
    std::vector<vec2_u64> galaxies;
    std::vector<uint16_t> empty_rows;
    std::vector<uint16_t> empty_cols;
    uint64_t total_distance = 0;

    for (std::string line; getline(input, line);) {
        universe.push_back(line);
    }

    for (uint16_t i = 0; i < universe.size(); i++) {
        if (universe[i].find('#') == std::string::npos) {
            empty_rows.push_back(i);
        }
    }

    for (uint16_t j = 0; j < universe[0].size(); j++) {
        std::string col;
        for (uint16_t i = 0; i < universe.size(); i++) {
            col += universe[i][j];
        }

        if (col.find('#') == std::string::npos) {
            empty_cols.push_back(j);
        }
    }

    uint64_t my = 0, mx = 0;
    for (uint64_t i = 0; i < universe.size(); i++) {
        if (std::ranges::find(empty_rows, i) != empty_rows.end()) {
            my += (1000000 -1);
            continue;
        }

        mx = 0;
        for (uint64_t j = 0; j < universe[i].size(); j++) {
            if (std::ranges::find(empty_cols, j) != empty_cols.end()) {
                mx += (1000000 -1);
                continue;
            }

            if (universe[i][j] == '#')
                galaxies.push_back(vec2_u64{
                    static_cast<uint64_t>(i + my),
                    static_cast<uint64_t>(j + mx)
                });
        }
    }
 
    for (size_t i = 0; i < galaxies.size(); i++) {
        for (size_t j = i +1; j < galaxies.size(); j++) {
            total_distance += get_distance(galaxies[i], galaxies[j]);
        }
    }

    input.close();
    return total_distance;
}
