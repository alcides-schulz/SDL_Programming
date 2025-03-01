#include "Example_2_7.h"

bool Example_2_7::UserInit()
{
    for (int i = 0; i < std::size(mover_); i++) {
        auto x = (float)(std::rand() % WindowWidth());
        auto y = (float)(std::rand() % WindowHeight());
        auto m = std::rand() % 5 + 1;
        mover_[i] = new Chapter02MoverV1(PVector(x, y), m);
    }
    attractor_ = new Attractor(PVector(WindowWidth() / 2.0f, WindowHeight() / 2.0f), 10);
    return true;
}

bool Example_2_7::UserRender(int elapsed_time)
{
    SDL_SetRenderDrawColor(Renderer(), 255, 255, 255, 255);
    SDL_RenderClear(Renderer());

    attractor_->Display(this);

    for (int i = 0; i < std::size(mover_); i++) {
        PVector force = attractor_->Attract(mover_[i]);
        mover_[i]->ApplyForce(force);
        mover_[i]->Update();
        mover_[i]->CheckEdges(this);
        mover_[i]->Display(this);
    }
    return true;
}

// END