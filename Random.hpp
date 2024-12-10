/**
 * @file This header-only Random namespace implements a self-seeding Mersenne Twister.
 * Requires C++17 or newer.
 * It can be #included into as many code files as needed (The inline keyword avoids ODR violations)
 * Freely redistributable, courtesy of learncpp.com (https://www.learncpp.com/cpp-tutorial/global-random-numbers-random-h/)
 */

#pragma once

#ifndef RANDOM_MT_H
#define RANDOM_MT_H

#include <random>
#include <chrono>

namespace Random
{
    /**
     * @brief Create a seeded Mersenne Twister
     * @return a seeded Mersenne Twister
     */
    inline std::mt19937 generate()
    {
        std::random_device rd{};

        // Create seed_seq with clock and 7 random numbers from std::random_device
        std::seed_seq ss{
            static_cast<std::seed_seq::result_type>(
                std::chrono::steady_clock::now().time_since_epoch().count()),
                rd(), rd(), rd(), rd(), rd(), rd(), rd()
        };

        return std::mt19937{ ss };
    }


    // Our global std::mt19937 object
    inline std::mt19937 mt{ generate() };


    /**
     * @brief Generate a random int between [min, max] (inclusive) 
     * @param min minimum number
     * @param max maximum number
     * @return a random int between [min, max]
     */
    inline int randint(int min, int max)
    {
        return std::uniform_int_distribution{ min, max }(mt);
    }


    /**
     * @brief Generate a random number between [min, max] of type chosen
     * @tparam T Type of the random value you want to generate
     * @param min minimum value
     * @param max maximum value
     * @return a random value of type T between [min, max]
     */
    template <typename T>
    T randNum(T min, T max)
    {
        return std::uniform_int_distribution<T> { min, max }(mt);
    }


    /**
     * @brief Generate a random value between [min, max] while min and max are different types. Must explicitly specify return type as template type argument. min and max will be static_cast to R.
     * @tparam R type of the return value
     * @tparam S type of the minimun value 
     * @tparam T type of the maximum value
     * @param min minimum value
     * @param max maximum value
     * @return a random value of type T between [min, max]
     */
    template <typename R, typename S, typename T>
    R randNum(S min, T max)
    {
        return randNum<R>(static_cast<R>(min), static_cast<R>(max));
    }
}

#endif // !RANDOM_MT_H

/*
Example:

    std::cout << "r0: " << Random::randint(1, 6) << '\n';

    unsigned short a = 1, b = 10;
    // r1 is short via template argument deduction
    auto r1 = Random::randNum(a, b);
    std::cout << "r1: " << r1 << '\n';

    // int obviously [-3, -2]
    auto r2 = Random::randNum<int>(-3, 0xFFFFFFFFFFFFFFFEULL);
    std::cout << "r2: " << r2 << '\n';

    // size_t obviously
    auto r3 = Random::randNum<size_t>(1, 6u);
    std::cout << "r3: " << r3 << '\n';
*/