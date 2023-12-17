
#include "days.h"

uint16_t holiday_ascii_helper(std::string_view in) {
    uint16_t re = 0;

    for (const char& c : in) {
        re += static_cast<uint16_t>(c);
        re *= 17;
        re %= 256;
    }

    return re;
}

uint32_t solve15a() {
    std::ifstream input("./input/day15.txt");
    std::string line;
    std::getline(input, line);
    std::stringstream ss(line);

    uint32_t total = 0;

    for (std::string s; getline(ss, s, ',');) {
        total += holiday_ascii_helper(s);
    }

    input.close();
    return total;
}


struct Lens {
    std::string label;
    uint16_t focal;
};

uint32_t solve15b() {
    std::ifstream input("./input/day15.txt");
    std::string line;
    std::getline(input, line);
    std::stringstream ss(std::move(line));

    std::unordered_map<uint16_t, std::vector<Lens>> boxes;

    uint32_t total = 0;

    for (std::string s; getline(ss, s, ',');) {
        const uint16_t pos = s.find_first_of("-=");
        uint16_t num = 0;
        std::from_chars(
            s.data() + pos +1,
            s.data() + s.size(),
            num
        );
        s.erase(pos);

        uint16_t hash = holiday_ascii_helper(s);
        std::vector<Lens>& box = boxes[hash];
        auto it = std::ranges::find_if(box,
            [&s](const Lens& a)
            { return a.label == s; }
        );

        if (num == 0) {
            if (it != box.end())
                box.erase(it);
        } else {
            if (it != box.end()) {
                it->focal = num;
            } else {
                box.push_back({std::move(s), num});
            }
        }
    }

    for (const auto& [box_num, box] : boxes) {
        uint32_t i = 1;
        for (const auto& [label, focal] : box) {
            total += (box_num +1) * i * focal;
            i++;
        }
    }

    input.close();
    return total;
}
