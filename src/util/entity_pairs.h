//
// Created by alex on 25/02/19.
//

#pragma once

#include <unordered_set>

typedef std::pair<uint32_t, uint32_t> uint_pair;

struct PairHash {
    inline std::size_t operator()(const uint_pair& val) const {
        auto a = val.first;
        auto b = val.second;
        auto c = a + b;
        return c * (c + 1) / 2 + a;
    }
};

std::unordered_set<uint_pair, PairHash> entity_pair_set() {
    return std::unordered_set<uint_pair, PairHash> {};
}

bool unordered_pair_check(
    const std::unordered_set<uint_pair, PairHash> & set,
    uint32_t v1,
    uint32_t v2
) {
   return set.count(uint_pair(v1, v2)) > 0 || set.count(uint_pair(v2, v1)) > 0;
}


bool ordered_pair_check(
    const std::unordered_set<uint_pair, PairHash> & set,
    uint32_t v1,
    uint32_t v2
) {
    return set.count(uint_pair(v1, v2)) > 0;
}
