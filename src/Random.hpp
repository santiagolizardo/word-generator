#pragma once

#include <random>

#include <ctime>

class Random
{
private:
    std::default_random_engine re{static_cast<unsigned int>(std::time(nullptr))};

public:
    double nextDouble();
};