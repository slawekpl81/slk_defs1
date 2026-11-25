#include "slk_defs1/slk_args.hpp"
#include "slk_defs1/slk_random.hpp"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <set>
#include <string>
#include <vector>

// Minimal assertion macro that prints the failing condition and location before aborting.
#define CHECK(cond)                                                                                \
    do {                                                                                           \
        if (!(cond)) {                                                                             \
            std::cerr << "Test failed: " << #cond << " at " << __FILE__ << ":" << __LINE__ << '\n'; \
            std::exit(1);                                                                          \
        }                                                                                          \
    } while (false)

namespace {

// Verifies argument collection, invalid argc/argv handling, and null-entry filtering.
void test_process_args() {
    char prog[] = "app";
    char arg1[] = "-n";
    char arg2[] = "10";
    char* argv[] = {prog, arg1, arg2};

    const auto res = process_args(3, argv);
    CHECK((res == std::vector<std::string>{"app", "-n", "10"}));

    CHECK(process_args(0, argv).empty());
    CHECK(process_args(-1, argv).empty());
    CHECK(process_args(3, nullptr).empty());

    char* argv_with_null[] = {prog, nullptr, arg2};
    const auto filtered = process_args(3, argv_with_null);
    CHECK((filtered == std::vector<std::string>{"app", "10"}));
}

// Verifies option formats, negative numeric values, bare '-', and "--" termination.
void test_parse_cli_args() {
    char prog[] = "app";
    char* only_prog[] = {prog};
    CHECK(!parse_cli_args(1, only_prog).has_value());
    CHECK(!parse_cli_args(0, only_prog).has_value());
    CHECK(!parse_cli_args(2, nullptr).has_value());

    char o1[] = "-foo-bar";
    char v1[] = "123";
    char o2[] = "--verbose";
    char o3[] = "--port=8080";
    char o4[] = "-min";
    char v4[] = "-10";
    char o5[] = "-offset";
    char v5[] = "-3.5";
    char dash[] = "-";
    char sep[] = "--";
    char ignored[] = "--after-sep";
    char* argv[] = {prog, o1, v1, o2, o3, o4, v4, o5, v5, dash, sep, ignored};
    constexpr int argc = static_cast<int>(sizeof(argv) / sizeof(argv[0]));

    const auto parsed = parse_cli_args(argc, argv);
    CHECK(parsed.has_value());
    const auto& opts = *parsed;

    CHECK(opts.at("foo-bar") == "123");
    CHECK(opts.at("verbose") == "true");
    CHECK(opts.at("port") == "8080");
    CHECK(opts.at("min") == "-10");
    CHECK(opts.at("offset") == "-3.5");
    CHECK(opts.find("") == opts.end());
    CHECK(opts.find("after-sep") == opts.end());
}

// Verifies degenerate [x, x] ranges, swapped bounds, and full coverage of [-3, 5].
void test_generate_random_int() {
    CHECK(generate_random_int(42, 42) == 42);

    std::set<int> seen;
    for (int i = 0; i < 1000; ++i) {
        const int val = generate_random_int(5, -3);
        CHECK(val >= -3 && val <= 5);
        seen.insert(val);
    }
    CHECK(seen.size() == 9);
}

// Verifies finite float output within [0.0f, 1.0f] and non-constant distribution.
void test_generate_random_float() {
    std::set<float> sample;
    for (int i = 0; i < 1000; ++i) {
        const float val = generate_random_float();
        CHECK(std::isfinite(val));
        CHECK(val >= 0.0f && val <= 1.0f);
        sample.insert(val);
    }
    CHECK(sample.size() > 100);
}

// Verifies zero-length vectors and range bounds when min/max arguments are reversed.
void test_generate_random_vector() {
    CHECK(generate_random_vector(0, 1, 10).empty());

    const auto vec = generate_random_vector(200, 10, -10);
    CHECK(vec.size() == 200);
    for (int v : vec) {
        CHECK(v >= -10 && v <= 10);
    }
}

} // namespace

int main() {
    test_process_args();
    test_parse_cli_args();
    test_generate_random_int();
    test_generate_random_float();
    test_generate_random_vector();
    return 0;
}
