#include "Chapter02MoverFriction.h"

Chapter02MoverFriction::Chapter02MoverFriction(SDL_Framework *framework, PVector location, int mass) :
    framework_(framework), location(location), mass(mass) {
    velocity = PVector(0, 0);
    radius = 10 * mass;
    acceleration = PVector(0.0f, 0.0f);
};

void Chapter02MoverFriction::ApplyForce(PVector force)
{
    PVector temp = PVector(force);
    temp.Div((float)mass);
    acceleration.Add(temp);
}

void Chapter02MoverFriction::Update(void)
{
    velocity.Add(acceleration);
    location.Add(velocity);
    acceleration.Mult(0);
}

void Chapter02MoverFriction::Display(void)
{
    framework_->DrawCircle({ (int)location.x, (int)location.y }, radius, { 255, 0, 0, 0 }, true);
}

void Chapter02MoverFriction::CheckEdges(void)
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

bool Chapter02MoverFriction::ContactEdge(void)
{
    return location.y > framework_->WindowWidth() - radius - 1;
}

void Chapter02MoverFriction::BounceEdges(void)
{
    float bounce = -0.9f;
    if (location.x > framework_->WindowWidth() - radius) {
        location.x = (float)(framework_->WindowWidth() - radius);
        velocity.x *= bounce;
    }
    else if (location.x < radius) {
        location.x = (float)radius;
        velocity.x *= bounce;
    }
    if (location.y > framework_->WindowHeight() - radius) {
        location.y = (float)(framework_->WindowHeight() - radius);
        velocity.y *= bounce;
    }
}
/*
  bounceEdges() {
    // A new variable to simulate an inelastic collision
    // 10% of the velocity's x or y component is lost
    let bounce = -0.9;
    if (this.position.x > width - this.radius) {
      this.position.x = width - this.radius;
      this.velocity.x *= bounce;
    } else if (this.position.x < this.radius) {
      this.position.x = this.radius;
      this.velocity.x *= bounce;
    }
    if (this.position.y > height - this.radius) {
      this.position.y = height - this.radius;
      this.velocity.y *= bounce;
    }
  }
*/

// EOF