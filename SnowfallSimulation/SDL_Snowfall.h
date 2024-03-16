#ifndef SDL_SNOWFALL_H
#define SDL_SNOWFALL_H

#include "../SDL_Framework.h"

class Snowflake {
public:
    Snowflake(int x, int y);
    void ApplyForce(Vector2D force);
    void UpdatePosition();
    Vector2D GetPosition();
    int GetRadius();
private:
    Vector2D    position_;
    Vector2D    velocity_;
    Vector2D    acceleration_;
    int         radius_;
    float       angle_;
    int         direction_;
    int         offset_;
};

class SDL_Snowfall : public SDL_Framework
{
public:
    SDL_Snowfall() : SDL_Framework("Snowfall Simulation", 400, 100, 1200, 800, 0) { }
    bool UserRender(int elapsed_time) override;
    bool UserInit() override;
private:
    std::vector<Snowflake*> snowflake_list_;
    Vector2D                kGravity_ = { 0.0, 0.3 };
};

#endif
