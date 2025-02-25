#ifndef CHAPTER_02_MOVERFRICTION_H
#define CHAPTER_02_MOVERFRICTION_H

#include "../../SDL_Framework.h"
#include "../Common/PVector.h"

class Chapter02MoverFriction
{
public:
    SDL_Framework   *framework_;
    PVector         location;
    PVector         velocity;
    PVector         acceleration;
    int             radius;
    int             mass;

    Chapter02MoverFriction(SDL_Framework *framework, PVector location, int mass);
    void ApplyForce(PVector force);
    void Update(void);
    void Display(void);
    void CheckEdges(void);
    bool ContactEdge(void);
    void BounceEdges(void);
};

#endif

