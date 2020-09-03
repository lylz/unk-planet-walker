#pragma once

#include <random>

class Randomizer
{
public:
    static Randomizer &GetInstance()
    {
        static Randomizer instance;

        return instance;
    }

    double Random(double a, double b)
    {
        std::uniform_real_distribution<double> distribution(a, b);

        return distribution(mt_);
    }

    int Random(int a, int b)
    {
        std::uniform_int_distribution<int> distribution(a, b);

        return distribution(mt_);
    }

    Randomizer(Randomizer const &) = delete;
    void operator=(Randomizer const &) = delete;

private:
    Randomizer()
    {
        mt_.seed(random_device_());
    };

private:
    std::random_device random_device_;
    std::mt19937 mt_;
};
