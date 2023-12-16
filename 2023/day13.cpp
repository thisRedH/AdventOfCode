
#include "days.h"

std::vector<std::string> transpose_vec_str(const std::vector<std::string>& vec) {
    if (vec.empty())
        return std::vector<std::string>();

    size_t max_length = 0;
    for (const std::string& str : vec)
        max_length = std::max(max_length, str.size());

    std::vector<std::string> transposed(max_length, std::string(vec.size(), ' '));
    for (size_t i = 0; i < vec.size(); i++)
        for (size_t j = 0; j < vec[i].size(); ++j)
            transposed[j][i] = vec[i][j];

    return transposed;
}

uint16_t row_mirrored(const std::vector<std::string>& map) {
    uint16_t row = 1;
    bool found = false;

    for (row = 1; row < map.size() && !found; row++) {
        for (uint16_t off = 0;; off++) {
            if (((row -1) - off) < 0 || (row + off) >= map.size()) {
                found = true;
                break;
            }

            if (map[row -(off +1)] != map[row + off])
                break;
        }

    }

    return found ? row -1 : 0;
}

inline uint32_t mirrored(const std::vector<std::string>& map) {
    return (100 * row_mirrored(map)) + row_mirrored(transpose_vec_str(map));
}

uint32_t solve13a() {
    std::ifstream input("./input/day13.txt");

    std::vector<std::vector<std::string>> mirror_maps;
    uint32_t total = 0;

    std::vector<std::string> current_map;
    for (std::string line; std::getline(input, line);) {
        if (line.empty()) {
            if (!current_map.empty()) {
                mirror_maps.push_back(std::move(current_map));
                current_map.clear();
            }
        } else {
            current_map.push_back(line);
        }
    }

    if (!current_map.empty())
        mirror_maps.push_back(std::move(current_map));

    for (const auto& map : mirror_maps)
        total += mirrored(map);

    input.close();
    return total;
}

uint32_t solve13b() {
    return 69;
}
