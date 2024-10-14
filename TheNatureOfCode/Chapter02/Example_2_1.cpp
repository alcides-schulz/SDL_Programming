#include "Example_2_1.h"
#include "../Common/PVector.h"

bool Example_2_1::UserRender(int elapsed_time)
{
    SDL_SetRenderDrawColor(Renderer(), 255, 255, 255, 255);
    SDL_RenderClear(Renderer());
    x += xspeed;
    y += yspeed;
    if (x > WindowWidth() - radius || x < radius) {
        xspeed *= -1;
    }
    if (y > WindowHeight() - radius || y < radius) {
        yspeed *= -1;
    }
    DrawCircle({ (int)x, (int)y }, radius, { 255, 0, 0, 0 }, true);
    return true;
}

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
        top_speed = 2;
    };
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
};

// END
