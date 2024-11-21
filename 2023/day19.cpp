#include "days.h"

template<typename T, typename ...Opts>
static inline bool matches_any(T v, Opts ...opts) {
    return (... || (v == opts));
}

namespace {
    struct RuleInputVars {
        int16_t x = 0, m = 0, a = 0, s = 0;

        RuleInputVars(int16_t x_, int16_t m_, int16_t a_, int16_t s_) : x(x_), m(m_), a(a_), s(s_) {}
        RuleInputVars(std::string_view sv) { parse(sv); }
        RuleInputVars(int16_t v) : x(v), m(v), a(v), s(v) {}

        bool parse(std::string_view sv) {
            size_t xpos = sv.find('x');
            size_t mpos = sv.find('m');
            size_t apos = sv.find('a');
            size_t spos = sv.find('s');
            if (matches_any(std::string::npos, xpos, mpos, apos, spos)) {
                std::cerr << "Error day18: could not parse \"" << sv << '\"' << std::endl;
                return false;
            }

            x = std::atoi(sv.data() + xpos + 2);
            m = std::atoi(sv.data() + mpos + 2);
            a = std::atoi(sv.data() + apos + 2);
            s = std::atoi(sv.data() + spos + 2);
            return true;
        }

        inline RuleInputVars operator+(RuleInputVars o) const {
            return {int16_t(x + o.x), int16_t(m + o.m), int16_t(a + o.a), int16_t(s + o.s)};
        }
        inline RuleInputVars operator-(RuleInputVars o) const {
            return {int16_t(x - o.x), int16_t(m - o.m), int16_t(a - o.a), int16_t(s - o.s)};
        }

        inline int64_t inner_sum() const {
            return (int64_t)x + (int64_t)m + (int64_t)a + (int64_t)s;
        }

        inline int64_t inner_mul() const {
            return (int64_t)x * (int64_t)m * (int64_t)a * (int64_t)s;
        }

        inline const int16_t& get_var(char c) const {
            static int16_t tmp = 0;
            switch (c) {
                case 'x': return x;
                case 'm': return m;
                case 'a': return a;
                case 's': return s;
                default: return tmp;
            }
        }

        inline int16_t& get_var(char c) {
            return const_cast<int16_t&>(static_cast<const RuleInputVars&>(*this).get_var(c));
        }

        inline const int16_t& operator[](char c) const { return get_var(c); }
        inline int16_t& operator[](char c) { return get_var(c); }
    };

    struct RuleRangedInputVars {
        RuleInputVars from;
        RuleInputVars to;
    };

    struct RuleCondition {
        char var;
        char op; // < >
        int16_t val;
        std::string action; // next rule name or R/A
    };

    struct Rule {
        std::vector<RuleCondition> conditions;
        std::string fallback;

        Rule() {}
        Rule(const std::string& in) { parse(in); }

        inline void parse(const std::string& in) {
            std::istringstream is(in);
            for (std::string s; std::getline(is, s, ',');) {
                size_t colon_pos = s.find(':');
                if (colon_pos == std::string::npos) {
                    fallback = s;
                    break;
                }

                conditions.emplace_back(
                    s[0], s[1],
                    std::atoi(s.substr(2, colon_pos - 2).c_str()),
                    s.substr(colon_pos + 1)
                );
            }
        }

        const std::string& perform(const RuleInputVars& v) {
            for (const auto& c : conditions) {
                if (c.op == '>' && v[c.var] > c.val ||
                    c.op == '<' && v[c.var] < c.val
                ) return c.action;
            }
            return fallback;
        }
    };
}

static uint32_t run_data(
    std::unordered_map<std::string, Rule>& rules,
    const std::vector<RuleInputVars>& variables
) {
    uint32_t total = 0;
    for (const auto& v : variables) {
        Rule r = rules["in"];
        while (!r.fallback.empty()) { // check if rule exists
            const std::string& result = r.perform(v);
            if (result[0] == 'A') total += v.inner_sum();
            r = rules[result];
        }
    }
    return total;
}

uint32_t solve19a() {
    std::ifstream input("./input/day19.txt");

    std::unordered_map<std::string, Rule> rules;
    for (std::string l; std::getline(input, l);) {
        if (l.empty()) break;

        size_t obracket = l.find('{');
        size_t cbracket = l.find('}');
        if (matches_any(std::string::npos, obracket, cbracket)) continue;

        rules[l.substr(0, obracket)] = Rule(
            l.substr(obracket + 1, cbracket - obracket - 1)
        );
    }

    std::vector<RuleInputVars> variables;
    for (std::string l; std::getline(input, l);) {
        variables.emplace_back(std::string_view(l));
    }

    input.close();
    return run_data(rules, variables);
}

uint64_t perform_ranged(std::unordered_map<std::string, Rule>& rules, const std::string& rs, RuleRangedInputVars in) {
    if (rs[0] == 'A') {
        return (in.to - in.from + 1).inner_mul();
    } else if (rs[0] == 'R') {
        return 0;
    }

    Rule r = rules[rs];
    uint64_t total = 0;

    for (const auto& c : r.conditions) {
        RuleRangedInputVars in_nxt = in;
        if (c.op == '<') {
            in_nxt.to[c.var] = std::min(in_nxt.to[c.var], (int16_t)(c.val - 1));
            in.from[c.var] = std::max(in.from[c.var], c.val);
        } else if (c.op == '>') {
            in_nxt.from[c.var] = std::max(in_nxt.from[c.var], (int16_t)(c.val + 1));
            in.to[c.var] = std::min(in.to[c.var], c.val);
        }
        total += perform_ranged(rules, c.action, in_nxt);
    }
    total += perform_ranged(rules, r.fallback, in);

    return total;
}

uint64_t solve19b() {
    std::ifstream input("./input/day19.txt");
    std::unordered_map<std::string, Rule> rules;

    for (std::string l; std::getline(input, l);) {
        if (l.empty()) break;

        size_t obracket = l.find('{');
        size_t cbracket = l.find('}');
        if (matches_any(std::string::npos, obracket, cbracket)) continue;

        rules[l.substr(0, obracket)] = Rule(
            l.substr(obracket + 1, cbracket - obracket - 1)
        );
    }

    input.close();
    return perform_ranged(rules, "in", {{1}, {4000}});
}
