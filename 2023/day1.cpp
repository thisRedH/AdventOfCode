
#include "days.h"

uint32_t solve1a() {
    std::vector<int> calibrationValues;
    std::ifstream inputFile("./input/day1.txt");

    for (std::string line; getline(inputFile, line);) {
        uint8_t first = 0;
        uint8_t last = 0;

        for (char c : line) {
            if (c >= '1' && c <= '9') {
                first = c - '0';
                break;
            }
        }

        std::reverse(line.begin(), line.end());
        for (char c : line) {
            if (c >= '1' && c <= '9') {
                last = c - '0';
                break;
            }
        }

        calibrationValues.push_back((first * 10) + last);
    }

    return std::reduce(calibrationValues.begin(), calibrationValues.end());
}

uint32_t solve1b() {
    return 0;
}
