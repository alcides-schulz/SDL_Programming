#pragma once

#include "PVector.h"
#include "../../SDL_Framework.h"

class Mover 
{
public:
    SDL_Framework *framework;
    PVector location;
    PVector velocity;
    PVector acceleration;
    float top_speed;
    int radius;
    Mover(SDL_Framework *framework, PVector location, PVector velocity) : 
        framework(framework), location(location), velocity(velocity)
    {
        radius = 16; 
        acceleration = PVector((float)0, (float)0);
        top_speed = 10;
    };
    void Update(void);
    void Display(void);
    void CheckEdges(void);
};