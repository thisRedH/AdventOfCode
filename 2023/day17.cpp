
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

template <>
struct std::hash<vec2> {
    std::size_t operator()(const vec2& v) const {
        std::size_t hashY = std::hash<int16_t>()(v.y);
        std::size_t hashX = std::hash<int16_t>()(v.x);

        return hashY ^ (hashX + 0x9e3779b9 + (hashY << 6) + (hashY >> 2));
    }
};

enum Directions : int8_t {
    NORTH = -1,
    SOUTH =  1,
    WEST  = -1,
    EAST  =  1,
};

inline vec2 opposite_dir(vec2 d) {
    d.y = -d.y;
    d.x = -d.x;
    return d;
}

struct HeatMap{
    std::vector<uint8_t> grid;
    uint16_t width = 0;
    uint16_t height = 0;

    uint8_t get(const vec2& v) const {
        return grid[v.y * width + v.x];
    }

    bool in_grid(const vec2& v) const {
        return
            (v.x >= 0 && v.x < width) &&
            (v.y >= 0 && v.y < height);
    }
};

struct Node {
    vec2 pos;
    vec2 dir;
    uint32_t dist;
    uint32_t steps;
    //std::vector<vec2> path;                     //!DBG

    bool operator>(const Node& other) const {
        return dist > other.dist;
    }

    bool operator==(const Node& other) const {
        return pos == other.pos
            && dir == other.dir
            && steps == other.steps;
    }
};

template <>
struct std::hash<Node> {
    std::size_t operator()(const Node& n) const {
        std::size_t a = std::hash<vec2>()(n.pos);
        std::size_t b = std::hash<vec2>()(n.dir);

        std::size_t c = std::hash<uint32_t>()(n.dist);
        std::size_t d = std::hash<uint32_t>()(n.steps);

        return a ^ b
            ^ (c + 0x9e3779b9 + (a << 6) + (a >> 2))
            ^ (d + 0x9e3779b9 + (a << 6) + (a >> 2));
    }
};

uint32_t dijkstra(
    const HeatMap& heat_map,
    vec2 start, vec2 end, uint8_t max_steps = 3
) {
    const std::array<vec2, 4> all_moves
        = {{{NORTH, 0}, {SOUTH, 0}, {0, EAST}, {0, WEST}}};
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> q;
    std::unordered_set<Node> visited;

    //q.push({start, {0,0}, 0, 0, {}});
    q.push({start, {0,0}, 0, 0});

    while (!q.empty()) {
        const Node curr = q.top();
        q.pop();

        if (visited.count(curr)) continue;
        visited.insert(curr);

        if (curr.pos == end && curr.steps < max_steps -1) {
            //! DEBG Print
/*             auto mappp = heat_map;
            for (auto pas : curr.path) {
                mappp.grid[pas.y * mappp.width + pas.x] = 0;
            }

            std::cout << std::endl;
            int iii = 0;
            for (auto n : mappp.grid) {
                if (n == 0)
                    printf("#");
                else
                    printf("%d",n);
                if ((iii + 1) % mappp.width == 0) {
                    std::cout << std::endl;
                }
                iii++;
            }
 */
           return curr.dist;
        }

        std::vector<vec2> moves(all_moves.begin(), all_moves.end());
        auto it = std::ranges::find(moves, opposite_dir(curr.dir));
        if (it != moves.end()) moves.erase(it);
        
        if (curr.steps >= max_steps -1)
            moves.erase(std::ranges::find(moves, curr.dir));

        for (const vec2& move : moves) {
            Node next;
            next.dir = move;
            next.pos = curr.pos + next.dir;
            next.steps = 0;
            //next.path = curr.path;              //!DBG
            //next.path.push_back(next.pos);      //!DBG
            if (heat_map.in_grid(next.pos)) {
                if (next.dir == curr.dir || curr.dir == (vec2){0, 0}) next.steps = curr.steps +1;
                next.dist = curr.dist + heat_map.get(next.pos);
                q.push(next);
            }
        }
    }

    return UINT32_MAX;
}


uint32_t solve17a() {
    //std::ifstream input("./input/day17.txt");
    std::stringstream input(R"(
2413432311323
3215453535623
3255245654254
3446585845452
4546657867536
1438598798454
4457876987766
3637877979653
4654967986887
4564679986453
1224686865563
2546548887735
4322674655533
)");

    HeatMap heat_map = {{}, 0, 0};

    for (std::string line; getline(input, line);) {
        if (line.empty()) continue;

        for (const char& c : line)
            if (std::isdigit(c)) 
                heat_map.grid.push_back(static_cast<uint8_t>(c - '0'));

        heat_map.width = static_cast<uint16_t>(line.size());
        heat_map.height++;
    }

    uint32_t r = dijkstra(
        heat_map,
        {0, 0},
        {heat_map.width -1, heat_map.height -1}
    );

    //input.close();
    return r;
}

uint32_t solve17b() {
    return 80;
}
