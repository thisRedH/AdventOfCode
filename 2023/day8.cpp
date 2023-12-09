
#include "days.h"

std::vector<std::string> extract_words(const std::string& input) {
    std::vector<std::string> words;
    
    std::string word;
    for (char c : input) {
        if (std::isalpha(c)) {
            word.push_back(c);
        } else {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        }
    }

    if (!word.empty())
        words.push_back(std::move(word));

    return words;
}

uint32_t solve8a() {
    std::ifstream input("./input/day8.txt");

    std::map<size_t, std::pair<size_t, size_t>> map;
    std::string route;

    getline(input, route);

    for (std::string line; getline(input, line);) {
        if (!std::isalpha(line[0])) continue;
        std::vector<std::string> words = std::move(extract_words(line));

        map[std::hash<std::string>{}(words[0])] = std::make_pair(
            std::hash<std::string>{}(words[1]),
            std::hash<std::string>{}(words[2])
        );
    }

    uint32_t total_steps = 0;
    size_t current = std::hash<std::string>{}("AAA");
    const size_t goal = std::hash<std::string>{}("ZZZ");
    for (uint32_t i;; i++) {
        const char c = route[i % route.length()];
        switch (c) {
        case 'L':
            current = map.at(current).first;
            break;
        case 'R':
            current = map.at(current).second;
            break;
        default:
            break;
        }

        if (current == goal) {
            total_steps = i +1;
            break;
        }
    }
    

    input.close();
    return total_steps;
}


uint32_t get_steps(size_t start, const std::vector<size_t>& goal,
    const std::string& route,
    const std::map<size_t, std::pair<size_t, size_t>>& map
) {
    uint32_t total_steps = 0;
    for (;; total_steps++) {
        const char c = route[total_steps % route.length()];
        switch (c) {
        case 'L':
            start = map.at(start).first;
            break;
        case 'R':
            start = map.at(start).second;
            break;
        default:
            break;
        }

        if (std::find(goal.begin(), goal.end(), start) != goal.end())
            break;

    }

    return total_steps +1;
}

uint64_t solve8b() {
    std::ifstream input("./input/day8.txt");

    std::map<size_t, std::pair<size_t, size_t>> map;
    std::vector<size_t> current;
    std::vector<size_t> goal;
    std::string route;

    getline(input, route);

    for (std::string line; getline(input, line);) {
        if (!std::isalpha(line[0])) continue;
        std::vector<std::string> words = std::move(extract_words(line));

        if (words[0].back() == 'A')
            current.push_back(std::hash<std::string>{}(words[0]));
        if (words[0].back() == 'Z')
            goal.push_back(std::hash<std::string>{}(words[0]));

        map[std::hash<std::string>{}(words[0])] = std::make_pair(
            std::hash<std::string>{}(words[1]),
            std::hash<std::string>{}(words[2])
        );
    }

    std::vector<size_t> each_steps;
    for (const size_t& n : current)
        each_steps.push_back(get_steps(n, goal, route, map));
    
    uint64_t total_steps = each_steps[0];
    for (size_t i = 1; i < each_steps.size(); i++) {
        total_steps = std::lcm(total_steps, each_steps[i]);
    }

    input.close();
    return total_steps;
}
