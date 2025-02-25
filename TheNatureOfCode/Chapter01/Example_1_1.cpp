#include "Example_1_1.h"

bool Example_1_1::UserRender(int elapsed_time)
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

// END
