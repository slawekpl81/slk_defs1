//
// Created by sj on 21.10.2025.
//
#include "slk_defs1/slk_args.hpp"

#include <charconv>
#include <cctype>
#include <cstddef>
#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace {

// Checks whether a token represents a valid negative number (e.g. "-10", "-3.5")
// so numeric option values are not mistaken for CLI option flags.
bool is_negative_number(std::string_view token) {
    if (token.size() < 2 || token[0] != '-') {
        return false;
    }
    const auto next = static_cast<unsigned char>(token[1]);
    if (!std::isdigit(next) && token[1] != '.') {
        return false;
    }
    double parsed = 0.0;
    const auto [ptr, ec] = std::from_chars(token.data(), token.data() + token.size(), parsed);
    return ec == std::errc{} && ptr == token.data() + token.size();
}

// Options start with '-' (at least 2 chars, excluding bare "-" and negative numbers).
bool is_option_token(std::string_view token) {
    return token.size() >= 2 && token[0] == '-' && !is_negative_number(token);
}

} // namespace

std::vector<std::string> process_args(const int argc, char* argv[]) {
    if (argc <= 0 || argv == nullptr) {
        return {};
    }

    std::vector<std::string> args_vector;
    args_vector.reserve(static_cast<std::size_t>(argc));
    for (int i = 0; i < argc; ++i) {
        if (argv[i] != nullptr) {
            args_vector.emplace_back(argv[i]);
        }
    }
    return args_vector;
}

std::optional<std::map<std::string, std::string>> parse_cli_args(const int argc, char* argv[]) {
    if (argc <= 1 || argv == nullptr) {
        return std::nullopt;
    }

    const auto args = process_args(argc, argv);
    std::map<std::string, std::string> options;

    // Start at index 1 to skip the program name (argv[0]).
    for (std::size_t i = 1; i < args.size(); ++i) {
        const std::string& arg = args[i];

        // Stop option parsing at the standard end-of-options delimiter.
        if (arg == "--") {
            break;
        }
        if (!is_option_token(arg)) {
            continue;
        }

        // Strip leading "--" or "-" prefix to obtain the option key.
        std::string key = arg.starts_with("--") ? arg.substr(2) : arg.substr(1);
        if (key.empty()) {
            continue;
        }

        // Handle inline assignment format: --key=value / -key=value.
        if (const auto eq_pos = key.find('='); eq_pos != std::string::npos) {
            std::string value = key.substr(eq_pos + 1);
            key.resize(eq_pos);
            if (!key.empty()) {
                options[key] = std::move(value);
            }
            continue;
        }

        // Handle "-key value" when the next token is not "--" or another option;
        // otherwise treat the option as a boolean flag.
        if (i + 1 < args.size() && args[i + 1] != "--" && !is_option_token(args[i + 1])) {
            options[key] = args[i + 1];
            ++i;
        } else {
            options[key] = "true";
        }
    }

    return options;
}
