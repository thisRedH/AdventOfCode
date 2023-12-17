
#include "days.h"

uint8_t holiday_ascii_helper(std::string_view in) {
    uint16_t re = 0;

    for (const char& c : in) {
        re += static_cast<uint16_t>(c);
        re *= 17;
        re %= 256;
    }

    return static_cast<uint8_t>(re);
}

uint32_t solve15a() {
    std::ifstream input("./input/day15.txt");
    std::string line;
    std::getline(input, line);
    std::stringstream ss(line);

    std::vector<std::string> init_sequence;
    uint32_t total = 0;

    for (std::string s; getline(ss, s, ',');) {
        total += holiday_ascii_helper(s);
    }

    input.close();
    return total;
}

uint32_t solve15b() {
    std::ifstream input("./input/day15.txt");
    uint32_t total = 0;

    std::string line;
    std::getline(input, line);

    input.close();
    return total;
}
