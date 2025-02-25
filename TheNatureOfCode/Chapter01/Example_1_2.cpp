#include "Example_1_2.h"

bool Example_1_2::UserRender(int elapsed_time)
{
    SDL_SetRenderDrawColor(Renderer(), 255, 255, 255, 255);
    SDL_RenderClear(Renderer());
    location.Add(velocity);
    if (location.x > WindowWidth() - radius || location.x < radius) {
        velocity.x *= -1;
    }
    if (location.y > WindowHeight() - radius || location.y < radius) {
        velocity.y *= -1;
    }
    DrawCircle({ (int)location.x, (int)location.y }, radius, { 255, 0, 0, 0 }, true);
    return true;
}

// END
