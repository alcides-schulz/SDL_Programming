#include "Example_2_2.h"

bool Example_2_2::UserInit()
{
    PVector locationA(WindowWidth() / 4.0f, WindowHeight() / 2.0f);
    PVector locationB(WindowWidth() / 4.0f * 3, WindowHeight() / 2.0f);
    moverA_ = new Chapter02Mover(this, locationA, 10);
    moverB_ = new Chapter02Mover(this, locationB, 1);
    return true;
}

bool Example_2_2::UserRender(int elapsed_time)
{
    SDL_SetRenderDrawColor(Renderer(), 255, 255, 255, 255);
    SDL_RenderClear(Renderer());

    PVector gravity(0, 0.1f);
    moverA_->ApplyForce(gravity);
    moverB_->ApplyForce(gravity);

    if (IsMouseButtonPressed(kMouseLeftButton)) {
        PVector wind(0.1f, 0);
        moverA_->ApplyForce(wind);
        moverB_->ApplyForce(wind);
    }

    moverA_->Update();
    moverA_->Display();
    moverA_->CheckEdges();

    moverB_->Update();
    moverB_->Display();
    moverB_->CheckEdges();

    return true;
}

// END
