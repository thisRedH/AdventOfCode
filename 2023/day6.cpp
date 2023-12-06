
#include "days.h"

std::vector<uint16_t> get_u16s(std::string line) {
    std::istringstream ss(std::move(line));
    std::vector<uint16_t> r;
    for (uint16_t n; ss >> n;) r.push_back(n);
    return r;
}

uint32_t solve6a() {
    std::ifstream input("./input/day6.txt");
    std::vector<std::string> lines;

    for (std::string line; getline(input, line);) {
        if (line.length() < 1) continue;
        line.erase(0, line.find_first_of(' '));
        lines.push_back(line);
    }

    std::vector<uint16_t> times = std::move(get_u16s(lines[0]));
    std::vector<uint16_t> distances = std::move(get_u16s(lines[1]));

    std::vector<uint16_t> wins(times.size(), 0);
    for (uint16_t i = 0; i < times.size(); ++i) {
        uint16_t time = times[i];
        uint16_t dist = distances[i];

        for (uint16_t held_ms = 1; held_ms <= time; held_ms++) {
            uint16_t current_dist = held_ms * (time - held_ms);
            if (current_dist > dist)
                wins[i]++;
        }
    }

    uint32_t result = 1;
    for (const auto& n : wins)
        result *= n;

    return result;
}


uint32_t solve6b() {
    std::ifstream input("./input/day6.txt");

    for (std::string line; getline(input, line);) {

    }

    return 0;
}
