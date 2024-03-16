#include "SDL_Snowfall.h"

Snowflake::Snowflake(int x, int y)
{
    position_ = Vector2D(x, y);
    velocity_ = Vector2D(0, 0);
    acceleration_ = Vector2D(0, 0);
    radius_ = rand() % 8 + 1;
    angle_ = (float)(rand() % 6);
    direction_ = rand() % 2 ? 1 : -1;
    offset_ = 0;
}

void Snowflake::ApplyForce(Vector2D force)
{
    Vector2D adjusted_force = Vector2D(force.x, force.y);
    adjusted_force.Multiply((float)radius_);
    acceleration_.Add(adjusted_force);
}

void Snowflake::UpdatePosition()
{
    offset_ = (int)(sin(angle_ * 2) * 2 * radius_);
    velocity_.Add(acceleration_);
    if (velocity_.y > (double)(radius_ * 0.2)) {
        velocity_.y = (float)(radius_ * 0.2);
    }
    position_.Add(velocity_);
    acceleration_.Multiply(0);
    angle_ += direction_ * (velocity_.x * velocity_.x + velocity_.y * velocity_.y) / 200;
}

Vector2D Snowflake::GetPosition()
{
    Vector2D temp = { position_.x + offset_, position_.y };
    return temp;
}

int Snowflake::GetRadius() {
    return radius_;
}

bool SDL_Snowfall::UserInit()
{
    snowflake_list_.clear();
    return true;
}

bool SDL_Snowfall::UserRender(int elapsed_time)
{
    SDL_SetRenderDrawColor(Renderer(), 0, 0, 0, 0); // black color
    SDL_RenderClear(Renderer());
    if (snowflake_list_.size() < 400) {
        int x = rand() % WindowWidth();
        int y = (rand() % WindowHeight()) * -1;
        Snowflake *snowflake = new Snowflake(x, y);
        snowflake_list_.push_back(snowflake);
    }
    for each (auto &snowflake in snowflake_list_)
    {
        snowflake->ApplyForce(kGravity_);
        snowflake->UpdatePosition();
        SDL_Point center = { snowflake->GetPosition().IntX(), snowflake->GetPosition().IntY() };
        DrawCircle(center, snowflake->GetRadius(), { 255, 255, 255, 255 }, true);
    }
    for (int i = (int)snowflake_list_.size() - 1; i >= 0; i--) {
        Snowflake *snowflake = snowflake_list_[i];
        if (snowflake->GetPosition().y > WindowHeight()) {
            snowflake_list_.erase(snowflake_list_.begin() + i);
        }
    }
    return true;
}
