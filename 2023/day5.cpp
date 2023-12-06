
#include "days.h"

struct MapValue {
    uint64_t src;
    uint64_t dest;
    uint64_t range;
};

inline MapValue parse_map_value(std::istream& line) {
    MapValue r;
    line >> r.dest >> r.src >> r.range;
    return r;
}

uint32_t solve5a() {
    std::ifstream input("./input/day5.txt");
    std::string line;
    std::string dummy;

    std::vector<uint64_t> current_objects;
    std::vector<uint64_t> next_objects;

    std::getline(input, line);
    std::istringstream ss_seeds(std::move(line));
    current_objects = {
        std::istream_iterator<uint64_t>(ss_seeds >> dummy >> std::ws),
        std::istream_iterator<uint64_t>()
    };

    while (std::getline(input, line)) {
        if (std::isalpha(line[0])) continue;
        if (!std::isdigit(line[0])) {
            if (next_objects.empty()) continue;
            current_objects = std::move(next_objects);
        }

        std::istringstream ss_line(std::move(line));
        const MapValue value = parse_map_value(ss_line);
        for (const uint64_t& n : current_objects) {
            if (n >= value.src && n < (value.src + value.range)) {
                next_objects.push_back(value.dest + (n - value.src));
            }
        }
    }

    return *std::min_element(next_objects.begin(), next_objects.end());
}

uint32_t solve5b() {
    std::ifstream input("./input/day5.txt");

    for (std::string line; getline(input, line);) {

    }

    return 0;
}
