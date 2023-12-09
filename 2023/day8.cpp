
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

//    std::map<size_t, std::pair<size_t, size_t>> map;
    std::map<std::string, std::pair<std::string, std::string>> map;
    std::string route;

    getline(input, route);

    for (std::string line; getline(input, line);) {
        if (!std::isalpha(line[0])) continue;
        std::vector<std::string> words = std::move(extract_words(line));

/*         map[std::hash<std::string>{}(words[0])] = std::make_pair(
            std::hash<std::string>{}(words[1]),
            std::hash<std::string>{}(words[2])
        ); */
        map[words[0]] = std::make_pair(words[1], words[2]);
    }

    uint32_t total_steps = 0;
    //size_t current = std::hash<std::string>{}("AAA");
    //const size_t goal = std::hash<std::string>{}("ZZZ");
    std::string current = "AAA";
    const char* goal = "ZZZ";
    for (uint32_t i;; i++) {
        const char c = route[i % route.length()];
        switch (c){
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


uint32_t solve8b() {
    std::ifstream input("./input/day8.txt");

    for (std::string line; getline(input, line);) {

    }

    input.close();
    return 1;
}
