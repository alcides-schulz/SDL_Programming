#include "Example_2_3.h"

bool Example_2_3::UserInit()
{
    PVector locationA(WindowWidth() / 4.0f, WindowHeight() / 2.0f);
    PVector locationB(WindowWidth() / 4.0f * 3, WindowHeight() / 2.0f);
    moverA_ = new Chapter02Mover(this, locationA, 5);
    moverB_ = new Chapter02Mover(this, locationB, 1);
    return true;
}

bool Example_2_3::UserRender(int elapsed_time)
{
    SDL_SetRenderDrawColor(Renderer(), 255, 255, 255, 255);
    SDL_RenderClear(Renderer());

    PVector gravityA(0, 0.1f);
    gravityA.Mult((float)moverA_->mass);
    moverA_->ApplyForce(gravityA);

    PVector gravityB(0, 0.1f);
    gravityB.Mult((float)moverB_->mass);
    moverB_->ApplyForce(gravityB);

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
