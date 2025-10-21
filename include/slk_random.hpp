//
// Created by sj on 21.10.2025.
//
#pragma once

#include <vector>
#include <random>
#include <algorithm>

/**
 * Generuje wektor n-elementowy zawierający losowe liczby całkowite
 * z zadanego zakresu [a, b].
 * * @param n Liczba elementów do wygenerowania (rozmiar wektora).
 * @param a Dolny limit zakresu (włącznie).
 * @param b Górny limit zakresu (włącznie).
 * @return std::vector<int> wypełniony losowymi liczbami.
 */
std::vector<int> generate_random_vector(size_t n, int a, int b) {
    if (a > b) {
        // Zapewnienie, że zakres jest poprawny
        std::swap(a, b);
    }

    // 1. Inicjalizacja Generatora (MT19937)
    // std::random_device::operator() dostarcza ziarno wysokiej jakości.
    std::random_device rd;
    // Mersenne Twister jest doskonałym, szybkim generatorem.
    std::mt19937 generator(rd());

    // 2. Definicja Rozkładu (Distribution)
    // std::uniform_int_distribution gwarantuje, że każda liczba
    // z zakresu [a, b] ma równe prawdopodobieństwo wylosowania.
    // UWAGA: oba końce, a i b, są WŁĄCZONE.
    std::uniform_int_distribution<int> distribution(a, b);

    // 3. Wypełnianie wektora
    std::vector<int> vec(n);

    // Algorytm std::generate wypełnia wektor,
    // używając funkcji lambda do generowania każdej nowej wartości
    std::generate(vec.begin(), vec.end(), [&]() {
        return distribution(generator);
    });

    return vec;
}