
#include "days.h"

struct Number {
    int64_t row, col;
    uint32_t num;
    uint16_t len;
};


uint32_t solve3a() {
    std::ifstream inputFile("./input/day3.txt");

    int64_t row = 0, col = 0;

    std::vector<std::string> lines;
    std::vector<Number> numbers;
    std::vector<uint32_t> parts;

    for (std::string line; getline(inputFile, line); row++) {
        lines.push_back(line);

        int64_t beginCol = 0;
        uint32_t currentNumber = 0;
        for (char& c : line) {
            if (std::isdigit(c)) {
                beginCol = beginCol == 0 ? col : beginCol;
                currentNumber = (currentNumber * 10) + (c - '0');
            } else if (currentNumber != 0) {
                numbers.push_back(Number{
                    row, beginCol,
                    currentNumber,
                    (uint16_t)(col - beginCol)
                });
                beginCol = 0;
                currentNumber = 0;
            }
            col++;
        }
        col = 0;
    }
    
    for (Number& n : numbers) {
        bool found = false;

        for (int64_t row = n.row -1; (row <= n.row +1) && !found; row++) {
            if (row < 0 || row > lines.size() -1) continue;

            for (int64_t col = n.col -1; (col <= n.col + n.len); col++) {
                if (col < 0 || col > lines[row].size()) continue;
                if (lines[row][col] != '.' && !std::isdigit(lines[row][col])) {
                    found = true;
                    parts.push_back(n.num);
                    break;
                }
            }
        }
    }
    
    return std::reduce(parts.begin(), parts.end());
}


inline int64_t hash(int64_t a, int64_t b) {
    return (a + b) * (a + b + 1) / 2 + a;
}

uint32_t solve3b() {
    std::ifstream inputFile("./input/day3.txt");

    int64_t row = 0, col = 0;

    std::vector<std::string> lines;
    std::vector<Number> numbers;
    std::unordered_map<size_t, std::vector<size_t>> gears;

    for (std::string line; getline(inputFile, line); row++) {
        lines.push_back(line);

        int64_t beginCol = 0;
        uint32_t currentNumber = 0;
        for (char& c : line) {
            if (std::isdigit(c)) {
                beginCol = beginCol == 0 ? col : beginCol;
                currentNumber = (currentNumber * 10) + (c - '0');
            } else if (currentNumber != 0) {
                numbers.push_back(Number{
                    row, beginCol,
                    currentNumber,
                    (uint16_t)(col - beginCol)
                });
                beginCol = 0;
                currentNumber = 0;
            }
            col++;
        }
        col = 0;
    }
    
    for (Number& n : numbers) {
        for (int64_t row = n.row -1; (row <= n.row +1); row++) {
            if (row < 0 || row > lines.size() -1) continue;

            for (int64_t col = n.col -1; (col <= n.col + n.len); col++) {
                if (col < 0 || col > lines[row].size()) continue;
                if (lines[row][col] == '*') {
                    if(gears.find(hash(row, col)) != gears.end()) {
                        gears[hash(row, col)].push_back(n.num);
                    } else {
                        gears[hash(row, col)] = {n.num};
                    }
                }
            }
        }
    }

    size_t sumRatios = 0;
    for (const auto& pair : gears) {
        if (pair.second.size() == 2)
            sumRatios += pair.second[0] * pair.second[1];
    }
    
    return sumRatios;
}
