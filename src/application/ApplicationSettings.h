#pragma once

struct ApplicationSettings
{
    ApplicationSettings(unsigned int width, unsigned int height)
        : width(width), height(height) {};

    unsigned int width;
    unsigned int height;
};

