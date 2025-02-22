#include "Example_2_1.h"

bool Example_2_1::UserInit()
{
    PVector location(WindowWidth() / 2.0f, WindowHeight() / 2.0f);
    PVector velocity(0, 0);
    mover_ = new Example_2_1_Mover(this, location, velocity, 10);
    return true;
}

bool Example_2_1::UserRender(int elapsed_time)
{
    SDL_SetRenderDrawColor(Renderer(), 255, 255, 255, 255);
    SDL_RenderClear(Renderer());

    PVector gravity(0, 0.1f);
    mover_->ApplyForce(gravity);
    if (IsMouseButtonPressed(kMouseLeftButton)) {
        PVector wind(0.1f, 0);
        mover_->ApplyForce(wind);
    }
    mover_->Update();
    mover_->Display();
    mover_->CheckEdges();

    return true;
}

Example_2_1_Mover::Example_2_1_Mover(SDL_Framework *framework, PVector location, PVector velocity, int mass) :
    framework_(framework), location(location), velocity(velocity), mass(mass) {
    radius = 16;
    acceleration = PVector(0.0f, 0.0f);
};

void Example_2_1_Mover::ApplyForce(PVector force)
{
    PVector temp = PVector(force);
    temp.Div((float)mass);
    acceleration.Add(temp);
}

void Example_2_1_Mover::Update(void)
{
    velocity.Add(acceleration);
    location.Add(velocity);
    acceleration.Mult(0);
}

void Example_2_1_Mover::Display(void)
{
    framework_->DrawCircle({ (int)location.x, (int)location.y }, radius, { 255, 0, 0, 0 }, true);
}

void Example_2_1_Mover::CheckEdges(void)
{
    if (location.x > framework_->WindowWidth()) {
        location.x = (float)framework_->WindowWidth();
        velocity.x *= -1;
    }
    if (location.x < 0) {
        location.x = 0;
        velocity.x *= -1;
    }
    if (location.y > framework_->WindowHeight()) {
        location.y = (float)framework_->WindowHeight();
        velocity.y *= -1;
    }
    if (location.y < 0) {
        location.y = 0;
        velocity.y *= -1;
    }
}

// END
