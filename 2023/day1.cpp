
#include "days.h"

uint32_t solve1a() {
    std::vector<int> calibrationValues;
    std::ifstream inputFile("./input/day1.txt");

    for (std::string line; getline(inputFile, line);) {
        uint8_t first = 0;
        uint8_t last = 0;

        for (char c : line) {
            if (c >= '1' && c <= '9') {
                first = first == 0 ? c - '0' : first;
                last = c - '0';
            }
        }

        calibrationValues.push_back((first * 10) + last);
    }
    return std::reduce(calibrationValues.begin(), calibrationValues.end());
}

uint32_t solve1b() {
    std::vector<int> calibrationValues;
    std::ifstream inputFile("./input/day1.txt");

    for (std::string line; getline(inputFile, line);) {
        uint8_t first = 0;
        uint8_t last = 0;

        const std::array<std::string, 9> numLookup {
            "one", "two", "three",
            "four", "five", "six",
            "seven", "eight", "nine",
        };

        // replace words with number with the following format:
        // one -> o1e, five -> f5e, eight -> e8t
        // this handles strings like oneight or threeightwo
        for (uint8_t i = 0; i < numLookup.size(); i++) {
            size_t pos = line.find(numLookup[i]);
            if (pos == std::string::npos) continue;
            line.replace(pos +1, numLookup[i].size() -2, std::to_string(i +1));
            
            pos = line.rfind(numLookup[i]);
            if (pos == std::string::npos) continue;
            line.replace(pos +1, numLookup[i].size() -2, std::to_string(i +1));
        }

        for (char c : line) {
            if (c >= '1' && c <= '9') {
                first = first == 0 ? c - '0' : first;
                last = c - '0';
            }
        }

        calibrationValues.push_back((first * 10) + last);
    }
    return std::reduce(calibrationValues.begin(), calibrationValues.end());
}
