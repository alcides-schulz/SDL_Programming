#pragma once

#include "PVector.h"
#include "../../SDL_Framework.h"

class Mover 
{
public:
    SDL_Framework *framework;
    PVector location;
    PVector velocity;
    int radius;
    Mover(SDL_Framework *framework, PVector location, PVector velocity) : framework(framework), location(location), velocity(velocity) 
    { 
        radius = 16; 
    };
    void Update(void);
    void Display(void);
    void CheckEdges(void);
};