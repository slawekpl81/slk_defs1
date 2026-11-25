//
// Created by sj on 21.10.2025.
//
#pragma once

#include <vector>
#include <string>
#include <map>
#include <optional>

/**
 * Converts C-style command-line arguments into a vector of strings.
 * Null entries in argv are skipped; returns an empty vector if argc <= 0 or argv is null.
 *
 * @param argc Argument count passed to main().
 * @param argv Argument vector passed to main().
 * @return Vector containing all non-null command-line argument strings.
 */
std::vector<std::string> process_args(int argc, char* argv[]);

/**
 * Parses command-line options from argv (skipping argv[0]) into a key-value map.
 *
 * Supported option formats:
 * - `--key=value` / `-key=value`
 * - `--key value` / `-key value` (negative numbers such as `-10` or `-3.5` are accepted as values)
 * - `--flag` / `-flag` (stored with value `"true"`)
 *
 * Parsing stops at the `--` end-of-options separator; standalone positional tokens
 * and bare `-` are ignored.
 *
 * @param argc Argument count passed to main().
 * @param argv Argument vector passed to main().
 * @return Map of parsed option names to values, or std::nullopt if argc <= 1 or argv is null.
 */
std::optional<std::map<std::string, std::string>> parse_cli_args(int argc, char* argv[]);
