//
// Created by sj on 21.10.2025.
//
#pragma once

#include <vector>
#include <string>
#include <map>
#include <optional>

std::vector<std::string> process_args(const int argc, char* argv[]) {
    // Konwersja na std::vector<std::string>
    // Używamy konstruktora zakresowego: [argv, argv + argc]
    // To tworzy wektor z elementów, na które wskazują wskaźniki od argv[0] do argv[argc-1]
    std::vector<std::string> args_vector(argv, argv + argc);

    return args_vector;
}

std::optional<std::map<std::string, std::string>> parse_cli_args(const int argc, char* argv[]) {
    if (argc >1) {
        const auto args = process_args(argc, argv);
        std::map<std::string, std::string> options;

        // Zaczynamy od i = 1, aby pominąć nazwę programu
        for (size_t i = 1; i < args.size(); ++i) {
            std::string arg = args[i];

            // 1. Sprawdzenie, czy jest to opcja (zaczyna się od '-' lub '--')
            if (arg.rfind('-', 0) == 0) {

                // Usunięcie początkowych myślników (np. "-name" -> "name")
                std::string key = arg.substr(arg.rfind('-') == 0 && arg[1] != '-' ? 1 : 2);

                    // Format: -klucz [wartość] lub -flaga

                    // Sprawdzenie, czy następny argument nie istnieje lub nie jest kolejną opcją
                    if (i + 1 < args.size() && args[i + 1].rfind('-', 0) != 0) {
                        // Jest to format: -klucz wartość (rozdzielony spacją)
                        options[key] = args[i + 1];
                        i++; // Przesunięcie licznika o jeden, aby pominąć wartość w następnej iteracji
                    } else {
                        // Jest to format: -flaga (opcja binarna, wartość ustawiana na "true")
                        options[key] = "true";
                    }

            }
        }
        return options;
    }else {
        return std::nullopt;
    }
}