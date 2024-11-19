#include "days.h"

struct Node {
    int32_t x, y;

    uint32_t cost;
    uint32_t steps;
    std::pair<int8_t, int8_t> direction;

    bool operator>(const Node& other) const {
        return cost > other.cost;
    }

    bool operator==(const Node& other) const {
        return x == other.x && y == other.y;
    }

    struct Hash {
        std::size_t operator()(const Node& node) const {
            constexpr std::size_t k1 = 0x9e3779b97f4a7c15;
            constexpr std::size_t k2 = 0x85ebca6b;
            constexpr std::size_t k3 = 0xc2b2ae35;

            std::size_t h = static_cast<std::size_t>(node.x) * k1;
            h ^= static_cast<std::size_t>(node.y) * k2;
            h ^= static_cast<std::size_t>(node.steps) * k3;
            h ^= static_cast<std::size_t>(node.direction.first) * k2;
            h ^= static_cast<std::size_t>(node.direction.second) * k1;

            h ^= (h >> 33);
            h *= k3;
            h ^= (h >> 29);
            h *= k2;
            h ^= (h >> 32);

            return h;
        }
    };
};

std::vector<Node> get_neighbours(
    const Node& current,
    const std::vector<std::vector<uint8_t>>& grid,
    uint32_t min_steps,
    uint32_t max_steps
) {
    static const std::array<std::pair<int8_t, int8_t>, 4> directions = {
        {{-1, 0}, {1, 0}, {0, 1}, {0, -1}},
    };

    std::vector<Node> neighbours;
    neighbours.reserve(4);
    for (const auto& d : directions) {
        if (current.direction == d && current.steps >= max_steps) continue;
        if (current.direction != std::pair<int8_t, int8_t>{0, 0} && current.direction != d && current.steps < min_steps) continue;
        if (current.direction.first + d.first == 0 && current.direction.second + d.second == 0) continue; // prevent 180°

        int32_t ny = current.y + d.first;
        int32_t nx = current.x + d.second;

        if (nx >= 0 && ny >= 0 && ny < grid.size() && nx < grid[0].size()) {
            neighbours.push_back(Node{
                nx,
                ny,
                current.cost + grid[ny][nx],
                current.direction == d ? current.steps + 1 : 1,
                d
            });
        }
    }

    return neighbours;
}

uint32_t find_path(
    const std::vector<std::vector<uint8_t>>& grid,
    Node start,
    Node end,
    uint8_t min_steps,
    uint8_t max_steps
) {
    std::vector<Node> container;
    container.reserve(512);
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq(std::greater<Node>(), std::move(container));
    std::unordered_set<Node, Node::Hash> visited;
    pq.push(start);

    while (!pq.empty()) {
        const auto current = pq.top();
        pq.pop();

        if (visited.contains(current)) continue;
        if (current.steps >= min_steps && current.x == end.x && current.y == end.y) return current.cost;
        visited.emplace(current);

        for (const auto& n : get_neighbours(current, grid, min_steps, max_steps)) {
            pq.push(n);
        }
    }

    return UINT32_MAX;
}

uint32_t solve17a() {
    std::ifstream input("./input/day17.txt");
    std::vector<std::vector<uint8_t>> grid;

    for (std::string line; getline(input, line);) {
        if (line.empty()) continue;
        std::vector<uint8_t> row;
        for (const char& c : line) {
            if (std::isdigit(c)) row.push_back((uint8_t)(c - '0'));
        }
        grid.push_back(std::move(row));
    }

    input.close();
    return find_path(
        grid,
        Node{0, 0, 0, 1, {0, 0}},
        Node{(int32_t) grid[0].size() - 1, (int32_t) grid.size() - 1, 0, 1, {0, 0}},
        1,
        3
    );
}

uint32_t solve17b() {
    std::ifstream input("./input/day17.txt");

    std::vector<std::vector<uint8_t>> grid;

    for (std::string line; getline(input, line);) {
        if (line.empty()) continue;
        std::vector<uint8_t> row;
        for (const char& c : line) {
            if (std::isdigit(c)) row.push_back((uint8_t)(c - '0'));
        }
        grid.push_back(std::move(row));
    }

    input.close();
    return find_path(
        grid,
        Node{0, 0, 0, 1, {0, 0}},
        Node{(int32_t) grid[0].size() - 1, (int32_t) grid.size() - 1, 0, 1, {0, 0}},
        4,
        10
    );
}
