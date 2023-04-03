#pragma once

#include <cmath>

class PVector
{
public:
    float x;
    float y;
    PVector() : x(0), y(0) {};
    PVector(float x, float y);
    void Add(PVector other);
    void Sub(PVector other);
    void Mult(float value);
    void Div(float value);
    float Mag();
    void Normalize();
    void Limit(float max);
};
