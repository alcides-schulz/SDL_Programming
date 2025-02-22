#include "Chapter02Mover.h"

Chapter02Mover::Chapter02Mover(SDL_Framework *framework, PVector location, int mass) :
    framework_(framework), location(location), mass(mass) {
    velocity = PVector(0, 0);
    radius = 10 * mass;
    acceleration = PVector(0.0f, 0.0f);
};

void Chapter02Mover::ApplyForce(PVector force)
{
    PVector temp = PVector(force);
    temp.Div((float)mass);
    acceleration.Add(temp);
}

void Chapter02Mover::Update(void)
{
    velocity.Add(acceleration);
    location.Add(velocity);
    acceleration.Mult(0);
}

void Chapter02Mover::Display(void)
{
    framework_->DrawCircle({ (int)location.x, (int)location.y }, radius, { 255, 0, 0, 0 }, true);
}

void Chapter02Mover::CheckEdges(void)
{
    if (location.x > framework_->WindowWidth() - radius) {
        location.x = (float)framework_->WindowWidth() - radius;
        velocity.x *= -1;
    }
    if (location.x < radius) {
        location.x = (float)radius;
        velocity.x *= -1;
    }
    if (location.y > framework_->WindowHeight() - radius) {
        location.y = (float)framework_->WindowHeight() - radius;
        velocity.y *= -1;
    }
    if (location.y < radius) {
        location.y = (float)radius;
        velocity.y *= -1;
    }
}

// EOF