#include "PVector.h"

PVector::PVector(float x, float y)
{
    this->x = x;
    this->y = y;
}

void PVector::Add(PVector other)
{
    this->x += other.x;
    this->y += other.y;
}

void PVector::Sub(PVector other)
{
    this->x -= other.x;
    this->y -= other.y;
}

void PVector::Mult(float value)
{
    this->x *= value;
    this->y *= value;
}

void PVector::Div(float value)
{
    this->x /= value;
    this->y /= value;
}

float PVector::Mag()
{
    return sqrtf(this->x * this->x + this->y * this->y);
}

void PVector::Normalize()
{
    float magnitude = Mag();
    if (magnitude != 0) {
        Div(magnitude);
    }
}

// End