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

void PVector::SetMag(float max)
{
    Normalize();
    Mult(max);
}

void PVector::Limit(float max)
{
    if (Mag() > max * max) {
        Normalize();
        Mult(max);
    }
}

PVector PVector::Random2D()
{
    float min = -1;
    float max = +1;
    float r = (min + 1) + (((float)rand()) / (float)RAND_MAX) * (max - (min + 1));
    float angle = (float)(r * PI_VALUE * 2);
    return PVector(cos(angle), sin(angle));
}

// End