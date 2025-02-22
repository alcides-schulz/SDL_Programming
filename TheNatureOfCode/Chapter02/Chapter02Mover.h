#ifndef CHAPTER_02_MOVER_H
#define CHAPTER_02_MOVER_H

#include "../../SDL_Framework.h"
#include "../Common/PVector.h"

class Chapter02Mover
{
public:
    SDL_Framework   *framework_;
    PVector         location;
    PVector         velocity;
    PVector         acceleration;
    int             radius;
    int             mass;

    Chapter02Mover(SDL_Framework *framework, PVector location, int mass);
    void ApplyForce(PVector force);
    void Update(void);
    void Display(void);
    void CheckEdges(void);
};

#endif

