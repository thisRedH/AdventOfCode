
#include "days.h"

uint32_t solve2a() {
    std::ifstream inputFile("./input/day2.txt");

    const uint16_t redMax = 12;
    const uint16_t greenMax = 13;
    const uint16_t blueMax = 14;
    
    uint32_t IDSum = 0;

    size_t i = 1;
    for (std::string line; getline(inputFile, line); i++) {
        line = line.substr(line.find(": ") +1);
        std::replace(line.begin(), line.end(), ';', ',');
        std::stringstream ssLine(line);

        bool outOfRange = false;

        for (std::string color; getline(ssLine, color, ',');) {
            color.erase(0, color.find_first_not_of(" \t\n\r\f\v"));

            uint16_t currentNum = 0;
            for (char c : color) {
                if (!std::isdigit(c)) break;
                currentNum = (currentNum * 10) + (c - '0');
            }

            if (currentNum > redMax && color.find("red") != std::string::npos
                || currentNum > greenMax && color.find("green") != std::string::npos 
                || currentNum > blueMax && color.find("blue") != std::string::npos
            ) {
                outOfRange = true;
                break;
            }
        }

        if (outOfRange) continue;
        IDSum += i;
    }
    return IDSum;
}



uint32_t solve2b() {
    std::ifstream inputFile("./input/day2.txt");

    for (std::string line; getline(inputFile, line);) {

    }

    return 0;
}
