//
// Created by sj on 21.10.2025.
//
#pragma once

#include <cstddef>
#include <vector>

/**
 * Generates a single random integer within the closed range [a, b].
 * Swaps the bounds automatically if a > b.
 *
 * @param a Lower bound of the range (inclusive).
 * @param b Upper bound of the range (inclusive).
 * @return A random integer in [min(a, b), max(a, b)].
 */
int generate_random_int(int a, int b);

/**
 * Generates a single random floating-point number of type float
 * within the closed range [0.0f, 1.0f].
 *
 * @return A random float in [0.0f, 1.0f].
 */
float generate_random_float();

/**
 * Generates an n-element vector containing random integers
 * within the closed range [a, b]. Swaps the bounds automatically if a > b.
 *
 * @param n Number of elements to generate (vector size).
 * @param a Lower bound of the range (inclusive).
 * @param b Upper bound of the range (inclusive).
 * @return std::vector<int> populated with random integers.
 */
std::vector<int> generate_random_vector(std::size_t n, int a, int b);
