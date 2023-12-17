
#include <cstdint>
#include <cstring>
#include <cctype>

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <ranges>
#include <chrono>

#include <vector>
#include <array>
#include <set>
#include <unordered_set>
#include <tuple>
#include <map>
#include <unordered_map>

const uint16_t kCURRENT_DAY = 15;

#define SHOW_AB(day,a,b)        (std::cout << "Day " << (day) <<\
                                 "\ta: " << (a) << '\n' <<\
                                 "\tb: " << (b))

void solve(uint16_t day);
uint32_t solve1a();             uint32_t solve1b();
uint32_t solve2a();             uint32_t solve2b();
uint32_t solve3a();             uint32_t solve3b();
uint32_t solve4a();             uint32_t solve4b();
uint32_t solve5a();             uint32_t solve5b();
uint32_t solve6a();             uint32_t solve6b();
uint32_t solve7a();             uint32_t solve7b();
uint32_t solve8a();             uint64_t solve8b();
uint32_t solve9a();             uint32_t solve9b();
uint32_t solve10a();            uint32_t solve10b();
uint32_t solve11a();            uint64_t solve11b();
uint32_t solve12a();            uint64_t solve12b();
uint32_t solve13a();            uint32_t solve13b();
uint32_t solve14a();            uint64_t solve14b();
uint32_t solve15a();            uint32_t solve15b();

#ifdef IMPL_DAYS

void solve(uint16_t day) {
    switch (day) {
    case 1:
        SHOW_AB(day, solve1a(), solve1b());
        break;
    case 2:
        SHOW_AB(day, solve2a(), solve2b());
        break;
    case 3:
        SHOW_AB(day, solve3a(), solve3b());
        break;
    case 4:
        SHOW_AB(day, solve4a(), solve4b());
        break;
    case 5:
        SHOW_AB(day, solve5a(), solve5b());
        break;
    case 6:
        SHOW_AB(day, solve6a(), solve6b());
        break;
    case 7:
        SHOW_AB(day, solve7a(), solve7b());
        break;
    case 8:
        SHOW_AB(day, solve8a(), solve8b());
        break;
    case 9:
        SHOW_AB(day, solve9a(), solve9b());
        break;
    case 10:
        SHOW_AB(day, solve10a(), solve10b());
        break;
    case 11:
        SHOW_AB(day, solve11a(), solve11b());
        break;
    case 12:
        SHOW_AB(day, solve12a(), solve12b());
        break;
    case 13:
        SHOW_AB(day, solve13a(), solve13b());
        break;
    case 14:
        SHOW_AB(day, solve14a(), solve14b());
        break;
    case 15:
        SHOW_AB(day, solve15a(), solve15b());
        break;
    default:
        break;
    }

    std::cout << std::endl;
}

inline void solveAll() {
    for (size_t i = 1; i <= kCURRENT_DAY; i++) {
        solve(i);
    }
}

#endif // IMPL_DAYS
