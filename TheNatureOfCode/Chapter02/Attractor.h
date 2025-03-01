#ifndef ATTRACTOR_H
#define ATTRACTOR_H

#include "../../SDL_Framework.h"
#include "../Common/PVector.h"
#include "Chapter02MoverV1.h"

constexpr int kGravity = 1;

class Attractor
{
public:
    Attractor(PVector position, int mass) : position_(position), mass_(mass) 
    { 
        radius_ = mass * 10;
    };
    PVector Attract(Chapter02MoverV1 *mover);
    void Display(SDL_Framework *framework);
private:
    PVector position_;
    PVector velocity_;
    PVector acceleration_;
    int     radius_;
    int     mass_;
};


#endif

