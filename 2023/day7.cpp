
#include "days.h"

struct Play {
    std::string hand;
    uint16_t bidding;
};

struct _GamesStrength {
    const static inline std::unordered_map<char, uint8_t> cards = {
        {'2', 0},   {'3', 1},   {'4', 2},   {'5', 3},
        {'6', 4},   {'7', 5},   {'8', 6},   {'9', 7},
        {'T', 8},   {'J', 9},   {'Q', 10},  {'K', 11},
        {'A', 12},
    };

    const inline uint8_t card_value(char card) const { return cards.at(card); }

    const uint8_t evaluateHand(const std::string& hand) const {
        std::unordered_map<char, uint8_t> card_count;

        uint8_t count = 0;
        uint8_t distinct_cards = 0;

        for (char card : hand)
            card_count[card]++;

        for (const auto& entry : card_count) {
            count = std::max(count, (uint8_t)entry.second);
            distinct_cards++;
        }

        if (count == 5) {
            return 6; // Five of a kind
        } else if (count == 4) {
            return 5; // Four of a kind
        } else if (count == 3 && distinct_cards == 2) {
            return 4; // Full house
        } else if (count == 3) {
            return 3; // Three of a kind
        } else if (count == 2 && distinct_cards == 3) {
            return 2; // Two pair
        } else if (count == 2) {
            return 1; // One pair
        } else {
            return 0; // High card
        }
    }

    bool operator()(const Play& a, const Play& b) const {
        uint32_t a_value = evaluateHand(a.hand);
        uint32_t b_value = evaluateHand(b.hand);
        if (a_value == b_value) {
            for (size_t i = 0; i < a.hand.size(); i++) {
                if (a.hand[i] == b.hand[i]) continue;
                return card_value(a.hand[i]) < card_value(b.hand[i]);
            }
        }
        return a_value < b_value;
    }
} GamesStrength;

uint32_t solve7a() {
    std::ifstream input("./input/day7.txt");

    std::vector<Play> games;
    uint32_t total = 0;

    for (std::string line; getline(input, line);) {
        std::string hand;
        uint16_t bidding;

        std::istringstream ss(std::move(line));
        if (!(ss >> hand >> bidding)) continue;

        games.push_back({hand, bidding});
    }

    std::sort(games.begin(), games.end(), GamesStrength);

    size_t i = 1;
    for (const auto& play : games) {
        total += (play.bidding * i);
        i++;
    }

    input.close();
    return total;
}


struct _JokerGamesStrength {
    const static inline std::unordered_map<char, uint8_t> cards = {
        {'J', 0},   {'2', 1},   {'3', 2},   {'4', 3},
        {'5', 4},   {'6', 5},   {'7', 6},   {'8', 7},
        {'9', 8},   {'T', 9},   {'Q', 10},  {'K', 11},
        {'A', 12},
    };

    const inline uint8_t card_value(char card) const { return cards.at(card); }

    const uint8_t evaluateHand(const std::string& hand) const {
        std::unordered_map<char, uint8_t> card_count;

        uint8_t count = 0;
        uint8_t distinct_cards = 0;

        for (char card : hand)
            card_count[card]++;
        
        if (card_count.find('J') != card_count.end() && card_count.at('J') < 5) {
            uint8_t j_count = card_count.at('J');
            card_count.erase('J');

            const auto max_char = std::max_element(card_count.begin(), card_count.end(),
                [](const auto& a, const auto& b) -> bool
                    { return a.second < b.second; });

            card_count[(*max_char).first] += j_count;
        }

        for (const auto& entry : card_count) {
            count = std::max(count, (uint8_t)entry.second);
            distinct_cards++;
        }

        if (count == 5) {
            return 6; // Five of a kind
        } else if (count == 4) {
            return 5; // Four of a kind
        } else if (count == 3 && distinct_cards == 2) {
            return 4; // Full house
        } else if (count == 3) {
            return 3; // Three of a kind
        } else if (count == 2 && distinct_cards == 3) {
            return 2; // Two pair
        } else if (count == 2) {
            return 1; // One pair
        } else {
            return 0; // High card
        }
    }

    bool operator()(const Play& a, const Play& b) const {
        uint32_t a_value = evaluateHand(a.hand);
        uint32_t b_value = evaluateHand(b.hand);
        if (a_value == b_value) {
            for (size_t i = 0; i < a.hand.size(); i++) {
                if (a.hand[i] == b.hand[i]) continue;
                return card_value(a.hand[i]) < card_value(b.hand[i]);
            }
        }
        return a_value < b_value;
    }
} JokerGamesStrength;

uint32_t solve7b() {
    std::ifstream input("./input/day7.txt");

    std::vector<Play> games;
    uint32_t total = 0;

    for (std::string line; getline(input, line);) {
        std::string hand;
        uint16_t bidding;

        std::istringstream ss(std::move(line));
        if (!(ss >> hand >> bidding)) continue;

        games.push_back({hand, bidding});
    }

    std::sort(games.begin(), games.end(), JokerGamesStrength);

    size_t i = 1;
    for (const auto& play : games) {
        total += (play.bidding * i);
        i++;
    }

    input.close();
    return total;
}
