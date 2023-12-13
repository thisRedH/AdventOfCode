
#include "days.h"

struct vec2 {
    int16_t y;
    int16_t x;

    auto operator+(const vec2& other) const {
        return vec2{
            static_cast<int16_t>(y + other.y),
            static_cast<int16_t>(x + other.x)
        };
    }
    auto operator-(const vec2& other) const {
        return vec2{
            static_cast<int16_t>(y - other.y),
            static_cast<int16_t>(x - other.x)
        };
    }
    auto operator+=(const vec2& other) {
        y += static_cast<int16_t>(other.y);
        x += static_cast<int16_t>(other.x);
        return *this;
    }
    auto operator-=(const vec2& other) {
        y -= static_cast<int16_t>(other.y);
        x -= static_cast<int16_t>(other.x);
        return *this;
    }
    auto operator==(const vec2& other) const {
        return (y == other.y && x == other.x);
    }
    auto operator!=(const vec2& other) const {
        return (y != other.y || x != other.x);
    }
};

// Uses Manhattan distance formula
uint32_t get_distance(const vec2& start, const vec2& end) {
    return static_cast<uint32_t>(
        abs(start.x - end.x) + abs(start.y - end.y)
    );
}

uint32_t solve11a() {
    std::ifstream input("./input/day11.txt");
/*     std::stringstream input(
        "...#......\n"
        ".......#..\n"
        "#.........\n"
        "..........\n"
        "......#...\n"
        ".#........\n"
        ".........#\n"
        "..........\n"
        ".......#..\n"
        "#...#.....\n"
    );
 */
    std::vector<std::string> universe;
    std::vector<vec2> galaxies;
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

    int16_t my = 0, mx = 0;
    for (int16_t i = 0; i < universe.size(); i++) {
        if (std::ranges::find(empty_rows, i) != empty_rows.end()) {
            my++;
            continue;
        }

        mx = 0;
        for (int16_t j = 0; j < universe[i].size(); j++) {
            if (std::ranges::find(empty_cols, j) != empty_cols.end()) {
                mx++;
                continue;
            }

            if (universe[i][j] == '#') {
                galaxies.push_back(vec2{
                    static_cast<int16_t>(i + my),
                    static_cast<int16_t>(j + mx)
                });
            }
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


uint32_t solve11b() {
    std::ifstream input("./input/day11.txt");

    for (std::string line; getline(input, line);) {
    }

    input.close();
    return 15;
}
