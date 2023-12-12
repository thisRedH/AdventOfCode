
#include "days.h"

struct vec2 {
    int32_t y : 16,
            x : 16;

    auto operator+(const vec2& other) const {
        return vec2{y + other.y, x + other.x};
    }
    auto operator-(const vec2& other) const {
        return vec2{y - other.y, x - other.x};
    }
    auto operator+=(const vec2& other) -> vec2& {
        y += other.y;
        x += other.x;
        return *this;
    }
    auto operator-=(const vec2& other) -> vec2& {
        y -= other.y;
        x -= other.x;
        return *this;
    }
    auto operator==(const vec2& other) const {
        return (y == other.y && x == other.x);
    }
    auto operator!=(const vec2& other) const {
        return (y != other.y || x != other.x);
    }
};

enum Directions : int8_t {
    NORTH = -1,
    SOUTH =  1,
    WEST  = -1,
    EAST  =  1,
};

const std::map<char, std::pair<vec2, vec2>> tiles = {
    //      NS    EW    NS    EW                (N = -1, S = 1, E = 1, W = -1)
    {'|', {{NORTH, 0}, {SOUTH, 0}}},            // north and south
    {'-', {{0, EAST},  {0, WEST}}},             // east and west
    {'L', {{NORTH, 0}, {0, EAST}}},             // north and east
    {'J', {{NORTH, 0}, {0, WEST}}},             // north and west
    {'7', {{SOUTH, 0}, {0, WEST}}},             // south and west
    {'F', {{SOUTH, 0}, {0, EAST}}},             // south and east
    {'.', {{0, 0}, {0, 0}}},                    // None
    {'S', {{0, 0}, {0, 0}}},                    // None
};

inline bool in_map(const vec2& pos, const std::vector<std::string>& map) {
    return
        pos.y >= 0 && pos.x >= 0 &&
        pos.y < map.size() && pos.x < map[0].size();
}

void _walk(vec2 current, vec2 old,
    const std::vector<std::string>& map, uint32_t& steps_r
) {
    if (!in_map(current, map)) return;
    
    if (map[current.y][current.x] == 'S') {
        if (old != current) return;
        std::array<vec2, 4> s_dirs = {
            vec2{0, EAST}, vec2{SOUTH, 0},
            vec2{0, WEST}, vec2{NORTH, 0},
        };

        for (vec2 d : s_dirs) {
            d += current;
            old = current;

            if (!in_map(d, map)) continue;

            auto tile = tiles.at(map[d.y][d.x]);
            if ((d + tile.first) == current) {
                current = d;
                break;
            }
            else if ((d + tile.second) == current) {
                current = d;
                break;
            }
        }
    } else {
        auto tile = tiles.at(map[current.y][current.x]);

        if ((current + tile.first) != old) {
            old = current;
            current += tile.first;
        }
        else {
            old = current;
            current += tile.second;
        }
    }

    steps_r++;
    _walk(current, old, map, steps_r);
}

inline uint32_t walk(const vec2& start, const std::vector<std::string>& map) {
    uint32_t steps = 0;
    _walk(start, start, map, steps);
    return steps;
}

uint32_t solve10a() {
    std::ifstream input("./input/day10.txt");

    vec2 start;
    std::vector<std::string> map;

    for (std::string line; getline(input, line);) {
        if (std::isspace((line[0]))) continue;
        map.push_back(line);
    }

    input.close();

    for (int16_t i = 0; i < map.size(); i++) {
        for (int16_t j = 0; j < map[i].size(); j++) {
            if (map[i][j] == 'S') start = {i, j};
        }
    }

    return (walk(start, map) / 2);
}


uint32_t solve10b() {
    std::ifstream input("./input/day10.txt");

    for (std::string line; getline(input, line);) {
    }

    input.close();
    return 2;
}
