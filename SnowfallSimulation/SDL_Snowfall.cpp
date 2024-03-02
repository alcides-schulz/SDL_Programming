#include "../SDL_Framework.h"

class Snowflake {

private:
    Vector2D    position_;
    Vector2D    velocity_;
    Vector2D    acceleration_;
    int         radius_;
    float       angle_;
    int         direction_;
    int         offset_;

public:
    Snowflake(int x, int y)
    {
        position_ = Vector2D(x, y);
        velocity_ = Vector2D(0, 0);
        acceleration_ = Vector2D(0, 0);
        radius_ = rand() % 8 + 1;
        angle_ = (float)(rand() % 6);
        direction_ = rand() % 2 ? 1 : -1;
        offset_ = 0;
    }

    void ApplyForce(Vector2D force)
    {
        Vector2D adjusted_force = Vector2D(force.x, force.y);
        adjusted_force.Multiply((float)radius_);
        acceleration_.Add(adjusted_force);
    }

    void UpdatePosition()
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

    Vector2D GetPosition()
    {
        Vector2D temp = { position_.x + offset_, position_.y };
        return temp;
    }

    int GetRadius() {
        return radius_;
    }
};

class SDL_Snowfall : public SDL_Framework
{
private:
    std::vector<Snowflake*> snowflake_list_;
    Vector2D                kGravity_ = { 0.0, 0.3 };

public:
    bool UserRender(int elapsed_time) override
    {
        SDL_SetRenderDrawColor(Renderer(), 0, 0, 0, 0); // black color_
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
};

void RunSnowfallSimulation(void)
{
    SDL_Snowfall snowfall;
    if (snowfall.Init("Snowfall Simulation", 400, 100, 1200, 800, 0)) {
        snowfall.Run();
    }
}



