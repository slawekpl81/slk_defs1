//
// Created by sj on 21.10.2025.
//
#include "slk_defs1/slk_random.hpp"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <limits>
#include <random>
#include <utility>
#include <vector>

namespace {

// Returns a per-thread Mersenne Twister engine seeded with 256 bits of entropy
// from std::random_device to avoid contention across threads.
std::mt19937& random_engine() {
    thread_local std::mt19937 generator = [] {
        std::random_device rd;
        std::seed_seq seed{rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()};
        return std::mt19937(seed);
    }();
    return generator;
}

} // namespace

int generate_random_int(int a, int b) {
    if (a > b) {
        std::swap(a, b);
    }
    std::uniform_int_distribution<int> distribution(a, b);
    return distribution(random_engine());
}

float generate_random_float() {
    // Use std::nextafter to widen the half-open distribution [0.0f, upper) so 1.0f is reachable,
    // and clamp with std::min to guard against floating-point rounding exceeding 1.0f.
    static const float upper = std::nextafter(1.0f, std::numeric_limits<float>::infinity());
    std::uniform_real_distribution<float> distribution(0.0f, upper);
    return std::min(distribution(random_engine()), 1.0f);
}

std::vector<int> generate_random_vector(std::size_t n, int a, int b) {
    if (a > b) {
        std::swap(a, b);
    }

    // Cache the engine reference and distribution once for the entire vector.
    auto& generator = random_engine();
    std::uniform_int_distribution<int> distribution(a, b);

    std::vector<int> vec(n);
    std::generate(vec.begin(), vec.end(), [&]() {
        return distribution(generator);
    });

    return vec;
}
