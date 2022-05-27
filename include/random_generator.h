#ifndef RANDOM_GENERATOR
#define RANDOM_GENERATOR

#include <cstdint>
#include <random>
#include <cassert>

class RandomGenerator
{
public:
    RandomGenerator(int baseSeed)
        : baseSeed_{baseSeed} {}

    void seed(int x, int y)
    {
        mt.seed(chunkSeed(x, y) + baseSeed_);
    }

    bool drawLots(unsigned int chance, unsigned int max)
    {
        assert(chance <= max);

        return (mt() % max) < chance;
    }

    bool drawLots(double chance, double max)
    {
        assert(chance <= max);

        int bigNumber = mt();
        return (bigNumber / max - static_cast<int>(bigNumber / max)) * max < chance;
    }

    void setBaseSeed(int seed) { baseSeed_ = seed; }

private:
    int chunkSeed(int x, int y)
    {
        return (x & 0xFFFF) << 16 | (y & 0xFFFF);
    }

    std::mt19937 mt;
    int baseSeed_;
};

#endif
