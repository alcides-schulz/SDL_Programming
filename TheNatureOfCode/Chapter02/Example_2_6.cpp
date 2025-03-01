#include "Example_2_6.h"

bool Example_2_6::UserInit()
{
    mover_ = new Chapter02MoverV1(PVector(300, 0), 2);
    attractor_ = new Attractor(PVector(WindowWidth() / 2.0f, WindowHeight() / 2.0f), 10);
    return true;
}

bool Example_2_6::UserRender(int elapsed_time)
{
    SDL_SetRenderDrawColor(Renderer(), 255, 255, 255, 255);
    SDL_RenderClear(Renderer());

    PVector force = attractor_->Attract(mover_);
    mover_->ApplyForce(force);
    mover_->Update();
    mover_->CheckEdges(this);

    attractor_->Display(this);
    mover_->Display(this);

    return true;
}

// END