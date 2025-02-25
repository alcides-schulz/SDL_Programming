#include "Example_1_10.h"

bool Example_1_10::UserInit()
{
    PVector location((float)(WindowWidth() / 2), (float)(WindowHeight() / 2));
    PVector velocity(0, 0);
    mover = new Chapter01Mover(this, location, velocity);
    mover->acceleration = PVector((float)-0.001, (float)0.01);
    return true;
}

bool Example_1_10::UserRender(int elapsed_time)
{
    SDL_SetRenderDrawColor(Renderer(), 255, 255, 255, 255);
    SDL_RenderClear(Renderer());
    PVector mouse = PVector((float)MousePosition().x, (float)MousePosition().y);
    PVector direction = PVector(mouse.x, mouse.y);
    direction.Sub(mover->location);
    direction.Normalize();
    direction.Mult(0.2f);
    mover->acceleration = direction;
    mover->Update();
    mover->CheckEdges();
    mover->Display();
    return true;
}

// END
