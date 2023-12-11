
#include "days.h"

template<typename T>
inline bool all_zero(const std::vector<T>& v) {
    return std::all_of(v.begin(), v.end(), [](T n) { return n==0; });
}

int32_t calc_prediction(const std::vector<int32_t>& line) {
    std::vector<std::vector<int32_t>> steps{line};
    int32_t prediction = 0;

    while (!all_zero(steps.back())) {
        std::vector<int32_t> step;
        for (size_t i = 1; i < steps.back().size(); i++)
            step.push_back(steps.back()[i] - steps.back()[i -1]);

        steps.push_back(step);
    }

    for (const auto& step : steps)
        prediction += step.back();

    return prediction;
}

uint32_t solve9a() {
    std::ifstream input("./input/day9.txt");

    std::vector<std::vector<int32_t>> lines_num;
    int32_t total = 0;

    for (std::string line; getline(input, line);) {
        std::istringstream ss(std::move(line));
        std::vector<int32_t> line_num;

        for (int32_t n; ss >> n;)
            line_num.push_back(n);

        lines_num.push_back(line_num);
    }

    for (const auto& line : lines_num)
        total += calc_prediction(line);

    input.close();
    return total;
}

uint32_t solve9b() {
    std::ifstream input("./input/day9.txt");

    std::vector<std::vector<int32_t>> lines_num;
    int32_t total = 0;

    for (std::string line; getline(input, line);) {
        std::istringstream ss(std::move(line));
        std::vector<int32_t> line_num;

        for (int32_t n; ss >> n;)
            line_num.push_back(n);

        lines_num.push_back(line_num);
    }

    for (auto& line : lines_num) {
        std::reverse(line.begin(), line.end());
        total += calc_prediction(line);
    }

    input.close();
    return total;
}