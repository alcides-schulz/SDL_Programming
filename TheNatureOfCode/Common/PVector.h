#pragma once

#include <cmath>

class PVector
{
public:
    float x;
    float y;
    PVector(float x, float y);
    void Add(PVector other);
    void Sub(PVector other);
    void Mult(float value);
    void Div(float value);
    float Mag();
    void Normalize();
};
