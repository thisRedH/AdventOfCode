
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

void _walk(vec2& current, vec2& old,
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
    vec2 current = start;
    vec2 old = start;
    _walk(current, old, map, steps);
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



//#define DEBUG_GRAPH 1
#ifdef DEBUG_GRAPH
std::vector<std::string> graph(140);

int print_graph(const std::vector<std::string>& graph) {
    for (const auto& row : graph) {
        for (char value : row) {
            std::cout << value;
        }
        std::cout << '\n';
    }
    return 0;
}
#endif


void _walk_path(vec2& current, vec2& old,
    const std::vector<std::string>& map, std::vector<vec2>& path_r
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

#ifdef DEBUG_GRAPH
    graph[current.y][current.x] = map[current.y][current.x];
#endif

    path_r.push_back(current);
    _walk_path(current, old, map, path_r);
}

inline std::vector<vec2> walk_path(
    const vec2& start, const std::vector<std::string>& map
) {
    std::vector<vec2> path = {start};
    vec2 current = start;
    vec2 old = start;
    _walk_path(current, old, map, path);
    return path;
}

bool point_inside_polygon(const vec2& point, const std::vector<vec2>& polygon) {
    bool inside = false;

    for (size_t i = 0, j = polygon.size() -1; i < polygon.size(); j = i++) {
        const auto& vertexI = polygon[i];
        const auto& vertexJ = polygon[j];

        if (((vertexI.y > point.y) != (vertexJ.y > point.y)) &&
            (point.x < (vertexJ.x - vertexI.x)
            * (point.y - vertexI.y)
            / (vertexJ.y - vertexI.y) + vertexI.x)
        ) inside = !inside;
    }

    return inside;
}


uint32_t solve10b() {
    std::ifstream input("./input/day10.txt");

    vec2 start;
    uint32_t total = 0;
    std::vector<std::string> map;

#ifdef DEBUG_GRAPH
    for (auto& row : graph) {
        row.resize(140, '.');
    }
#endif

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

    std::vector<vec2> path = walk_path(start, map);

    for (int16_t i = 0; i < map.size(); i++) {
        for (int16_t j = 0; j < map[i].size(); j++) {
            if (std::find(path.begin(), path.end(), vec2{i, j}) != path.end())
                continue;
            if (point_inside_polygon({i, j}, path)) {
                total++;
#ifdef DEBUG_GRAPH
                graph[i][j] = 'I';
            } else {
                graph[i][j] = 'O';
#endif
            }
        }
    }

#ifdef DEBUG_GRAPH
    std::cout << std::endl;
    print_graph(graph);
#endif

    return total;
}
