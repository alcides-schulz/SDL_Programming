#include "Mover.h"

void Mover::Update(void) 
{
    location.Add(velocity);
}

void Mover::Display(void) 
{
    framework->DrawCircle({ (int)location.x, (int)location.y }, radius, { 255, 0, 0, 0 }, true);
}

void Mover::CheckEdges(void)
{
    if (location.x > framework->WindowWidth() - radius) velocity.x *= -1;
    if (location.x < radius) velocity.x *= -1;
    if (location.y > framework->WindowHeight() - radius) velocity.y *= -1;
    if (location.y < radius) velocity.y *= -1;
}
