#include "Example_1_9.h"

bool Example_1_9::UserInit()
{
    PVector location((float)(WindowWidth() / 2), (float)(WindowHeight() / 2));
    PVector velocity(0, 0);
    mover = new Chapter01Mover(this, location, velocity);
    mover->acceleration = PVector((float)-0.001, (float)0.01);
    return true;
}

bool Example_1_9::UserRender(int elapsed_time)
{
    SDL_SetRenderDrawColor(Renderer(), 255, 255, 255, 255);
    SDL_RenderClear(Renderer());
    mover->acceleration = PVector::Random2D();
    mover->Update();
    mover->CheckEdges();
    mover->Display();
    return true;
}

// END
