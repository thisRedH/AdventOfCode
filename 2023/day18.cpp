#include "days.h"

static uint64_t shoelace(std::vector<std::pair<int64_t, int64_t>> verts) {
    const size_t size = verts.size();
    int64_t l = 0, r = 0;

    for (size_t i = 0; i < size; i++) {
        size_t j = (i + 1) % size;
        l += verts[i].first * verts[j].second;
        r += verts[j].first * verts[i].second;
    }

    return std::abs(l - r) / 2;
}

static uint64_t count_boundary(const std::vector<std::pair<int64_t, int64_t>>& verts) {
    uint64_t b = 0;
    for (size_t i = 0; i < verts.size(); i++) {
        auto p1 = verts[i];
        auto p2 = verts[(i + 1) % verts.size()];
        b += std::gcd(std::abs(p2.first - p1.first), std::abs(p2.second - p1.second));
    }
    return b;
}

inline static std::pair<int8_t, int8_t> get_dir(char c) {
    switch (c) {
        case 'U': return{ 0, -1};
        case 'D': return{ 0,  1};
        case 'R': return{ 1,  0};
        case 'L': return{-1,  0};
        default: return {0, 0};
    }
}

inline static std::pair<int8_t, int8_t> get_dir_hex(int d) {
    switch (d) {
        case 0: return get_dir('R');
        case 1: return get_dir('D');
        case 2: return get_dir('L');
        case 3: return get_dir('U');
        default: return get_dir('0');
    }
}

uint32_t solve18a() {
    std::ifstream input("./input/day18.txt");

    std::vector<std::pair<int64_t, int64_t>> verts = {std::make_pair(0, 0)};
    verts.reserve(512);

    for (std::string l; std::getline(input, l);) {
        if (l.empty()) continue;
        std::istringstream ss(l);
        char d = '0';
        int len = 0;
        ss >> d >> len;

        auto last = verts.back();
        auto dir = get_dir(d);
        verts.emplace_back(std::make_pair(
            last.first + (len * dir.first),
            last.second + (len * dir.second)
        ));
    }

    // Pick's theorem
    uint64_t i = shoelace(verts);
    uint64_t b = count_boundary(verts);
    uint64_t a = i - (b / 2) + 1;

    input.close();
    return a + b;
}

uint64_t solve18b() {
    std::ifstream input("./input/day18.txt");

    std::vector<std::pair<int64_t, int64_t>> verts = {std::make_pair(0, 0)};
    verts.reserve(512);

    for (std::string l; std::getline(input, l);) {
        size_t pos = l.find('#');
        if (pos == std::string::npos) continue;
        l = l.substr(pos + 1);

        int len = std::stoi(l.substr(0, 5), nullptr, 16);
        auto dir = get_dir_hex(l[5] - '0');

        auto last = verts.back();
        verts.emplace_back(std::make_pair(
            last.first + (len * dir.first),
            last.second + (len * dir.second)
        ));
    }

    // Pick's theorem
    uint64_t i = shoelace(verts);
    uint64_t b = count_boundary(verts);
    uint64_t a = i - (b / 2) + 1;

    input.close();
    return a + b;
}
