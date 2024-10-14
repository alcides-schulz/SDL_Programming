#ifndef EXAMPLE_2_1_MOVER_H
#define EXAMPLE_2_1_MOVER_H

#include "../../SDL_Framework.h"
#include "../Common/PVector.h"

class Example_2_1_Mover
{
public:
    SDL_Framework   *framework_;
    PVector         location;
    PVector         velocity;
    PVector         acceleration;
    int             radius;
    int             mass;

    Example_2_1_Mover(SDL_Framework *framework, PVector location, PVector velocity, int mass);
    void ApplyForce(PVector force);
    void Update(void);
    void Display(void);
    void CheckEdges(void);
};

#endif

