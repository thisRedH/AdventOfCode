#include "days.h"

template<typename T, typename ...Opts>
static inline bool matches_any(T v, Opts ...opts) {
    return (... || (v == opts));
}

std::vector<std::string> split_str(std::string_view str, std::string_view delim = "\n") {
    std::vector<std::string> result;
    size_t start = 0;
    while (true) {
        size_t pos = str.find(delim, start);
        if (pos == std::string_view::npos) {
            result.emplace_back(str, start, std::string::npos);
            break;
        }

        result.emplace_back(str, start, pos - start);
        start = pos + delim.size();
    }
    return result;
}

std::vector<std::string> split_str(std::string str, std::string_view delim = "\n") {
    std::vector<std::string> result;

    for(size_t p = 0; (p = str.find(delim)) != std::string::npos;){
        result.emplace_back(str, 0, p);
        str = str.substr(p + 1);
    }

    if (!str.empty()) result.push_back(str);
    return result;
}

namespace {
    struct Component {

    };

    struct FlipFlop : public Component { // %
    };

    struct Congunction : public Component { // &
    };
};

uint32_t solve20a() {
    //std::ifstream input("./input/day20.txt");
    std::istringstream input(R"(
broadcaster -> a
%a -> inv, con
&inv -> b
%b -> con
&con -> output
)");

    std::unordered_map<std::string, std::vector<std::string>> graph;

    for (std::string l; std::getline(input, l);) {
        if (l.empty()) continue;

        char type = l[0];
        auto parts = split_str({l, 1}, " -> ");
        graph[parts[0]] = split_str(parts[1], ", ");
    }

    //input.close();
    return 123;
}

uint32_t solve20b() {
    return 69;
}
