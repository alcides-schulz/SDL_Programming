#include "Mover.h"

void Mover::Update(void) 
{
    velocity.Add(acceleration);
    velocity.Limit(top_speed);
    location.Add(velocity);
}

void Mover::Display(void) 
{
    framework->DrawCircle({ (int)location.x, (int)location.y }, radius, { 255, 0, 0, 0 }, true);
}

void Mover::CheckEdges(void)
{
    if (location.x > framework->WindowWidth()) location.x = 0;
    if (location.x < 0) location.x = (float)framework->WindowWidth();
    if (location.y > framework->WindowHeight()) location.y = 0;
    if (location.y < 0) location.y = (float)framework->WindowHeight();
}
