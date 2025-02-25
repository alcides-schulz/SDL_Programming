#include "Example_2_4.h"

bool Example_2_4::UserInit()
{
    PVector location(WindowWidth() / 2.0f, WindowHeight() / 2.0f);
    mover_ = new Chapter02MoverFriction(this, location, 5);
    return true;
}

bool Example_2_4::UserRender(int elapsed_time)
{
    SDL_SetRenderDrawColor(Renderer(), 255, 255, 255, 255);
    SDL_RenderClear(Renderer());

    PVector gravity(0, 0.1f);
    gravity.Mult((float)mover_->mass);
    mover_->ApplyForce(gravity);

    if (IsMouseButtonPressed(kMouseLeftButton)) {
        PVector wind(0.1f, 0);
        mover_->ApplyForce(wind);
    }

    if (mover_->ContactEdge()) {
        float c = 0.1f;
        PVector friction(mover_->velocity.x, mover_->velocity.y);
        friction.Mult(-1);
        friction.Limit(c); // setMag()
        mover_->ApplyForce(friction);
    }

    mover_->BounceEdges();

    mover_->Update();
    mover_->Display();

    return true;
}

// END
