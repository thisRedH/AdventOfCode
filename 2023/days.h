
#include <stdint.h>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <array>

const uint16_t kCURRENT_DAY = 2;

#define SHOW_AB(day,a,b)        (std::cout << "Day " << (day) <<\
                                 "\ta: " << (a) << '\n' <<\
                                 "\tb: " << (b))

void solve(uint16_t day);
uint32_t solve1a();             uint32_t solve1b();
uint32_t solve2a();             uint32_t solve2b();

#ifdef IMPL_DAYS

void solve(uint16_t day) {
    switch (day) {
    case 1:
        SHOW_AB(day, solve1a(), solve1b());
        break;
    case 2:
        SHOW_AB(day, solve2a(), solve2b());
        break;
    default:
        break;
    }

    std::cout << std::endl;
}

#endif // IMPL_DAYS
