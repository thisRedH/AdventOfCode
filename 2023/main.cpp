
#define IMPL_DAYS
#include "days.h"

int main(int argc, char const *argv[]) {
    if (argc == 1) {
        if(kCURRENT_DAY >= 25) solveAll();
        else solve(kCURRENT_DAY);
    } else if (std::isdigit(argv[1][0])) {
        if (atoi(argv[1]) <= kCURRENT_DAY && atoi(argv[1]) > 0)
            solve(atoi(argv[1]));
        else
            std::cerr << "[ERROR]: \"" << atoi(argv[1])
            << "\" is not a valid day to choose! [0-" << kCURRENT_DAY << ']'
            << std::endl;
    } else if (argv[1][0] == 'a') {
        solveAll();
    } else {
        std::cerr << "[ERROR]: \"" << argv[1] << "\" is not a valid argument!"
        << std::endl;
    }

    return 0;
}
