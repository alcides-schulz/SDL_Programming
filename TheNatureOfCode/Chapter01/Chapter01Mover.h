#pragma once

#include "../Common/PVector.h"
#include "../../SDL_Framework.h"

class Chapter01Mover 
{
public:
    SDL_Framework *framework;
    PVector location;
    PVector velocity;
    PVector acceleration;
    float top_speed;
    int radius;
    Chapter01Mover(SDL_Framework *framework, PVector location, PVector velocity) : 
        framework(framework), location(location), velocity(velocity)
    {
        radius = 16; 
        acceleration = PVector((float)0, (float)0);
        top_speed = 2;
    };
    void Update(void);
    void Display(void);
    void CheckEdges(void);
};