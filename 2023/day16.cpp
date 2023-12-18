
#include "days.h"

template<class T>
inline bool in_bounds(const T& v, const size_t& i) {
    return i >= 0 && i < v.size();
}

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

template <>
struct std::hash<vec2> {
    std::size_t operator()(const vec2& v) const {
        std::size_t hashY = std::hash<int16_t>()(v.y);
        std::size_t hashX = std::hash<int16_t>()(v.x);

        return hashY ^ (hashX + 0x9e3779b9 + (hashY << 6) + (hashY >> 2));
    }
};

template <>
struct std::hash<std::pair<vec2, vec2>> {
    std::size_t operator()(const std::pair<vec2, vec2>& v) const {
        std::size_t hasha = std::hash<vec2>()(v.first);
        std::size_t hashb = std::hash<vec2>()(v.second);

        return hasha ^ (hashb + 0x9e3779b9 + (hasha << 6) + (hasha >> 2));
    }
};

enum Directions : int8_t {
    NORTH = -1,
    SOUTH =  1,
    WEST  = -1,
    EAST  =  1,
};

uint32_t walk(
    const std::vector<std::string>& map,
    std::unordered_set<vec2>& wlkd,
    std::unordered_set<std::pair<vec2, vec2>>& wlkdd,
    vec2 pos = {0, 0}, vec2 d = {0, EAST}
) {
    while (in_bounds(map, pos.y) && in_bounds(map[pos.y], pos.x)) {
        const char& c = map[pos.y][pos.x];
        wlkd.emplace(pos);

        if (c != '.') {
            if (wlkdd.count(std::make_pair(pos, d)))
                return wlkd.size();
            wlkdd.emplace(std::make_pair(pos, d));
        }
        
        switch (c) {
        case '-':
        case '|':
            if ((d.x != 0 && c == '|') || (d.y != 0 && c == '-')) {
                d = {
                    static_cast<int16_t>(!d.y),
                    static_cast<int16_t>(!d.x)
                };
                vec2 d2 = {
                    static_cast<int16_t>(-d.y),
                    static_cast<int16_t>(-d.x)
                };
                walk(map, wlkd, wlkdd, pos + d2, d2);
            }
            break;
        case '\\':
            d = {
                static_cast<int16_t>(d.x),
                static_cast<int16_t>(d.y)
            };
            break;
        case '/':
            d = {
                static_cast<int16_t>(-d.x),
                static_cast<int16_t>(-d.y)
            };
            break;
        default:
            break;
        }

        pos += d;
    }

    return wlkd.size();
}


uint32_t solve16a() {
    std::ifstream input("./input/day16.txt");

    std::vector<std::string> map;
    uint32_t energized = 0;

    for (std::string line; getline(input, line);)
        if (!line.empty())
            map.push_back(line);

    std::unordered_set<vec2> wlkd;
    std::unordered_set<std::pair<vec2, vec2>> wlkdd;
    energized = walk(map, wlkd, wlkdd);

    input.close();
    return energized;
}

uint32_t solve16b() {
    std::ifstream input("./input/day16.txt");

    std::vector<std::string> map;
    uint32_t energized = 0;

    for (std::string line; getline(input, line);)
        if (!line.empty())
            map.push_back(line);

    std::unordered_set<vec2> wlkd;
    std::unordered_set<std::pair<vec2, vec2>> wlkdd;

    for (int16_t row = 0; row < map.size(); row++) {
        energized = std::max(
            walk(
                map, wlkd, wlkdd,
                {row, 0},
                {0, EAST}
            ),
            energized
        );
        wlkd.clear();
        wlkdd.clear();

        energized = std::max(
            walk(
                map, wlkd, wlkdd,
                {row, static_cast<int16_t>(map[0].size() -1)},
                {0, WEST}
            ),
            energized
        );
        wlkd.clear();
        wlkdd.clear();
    }

    for (int16_t col = 0; col < map[0].size(); col++) {
        energized = std::max(
            walk(
                map, wlkd, wlkdd,
                {0, col},
                {SOUTH, 0}
            ),
            energized
        );
        wlkd.clear();
        wlkdd.clear();

        energized = std::max(
            walk(
                map, wlkd, wlkdd,
                {static_cast<int16_t>(map.size() -1), col},
                {NORTH, 0}
            ),
            energized
        );
        wlkd.clear();
        wlkdd.clear();
    }

    input.close();
    return energized;
}
