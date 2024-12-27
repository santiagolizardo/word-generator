#include "Random.hpp"

double Random::next()
{
    std::uniform_real_distribution distribution(0.0, 1.0);

    return distribution(re);
}
