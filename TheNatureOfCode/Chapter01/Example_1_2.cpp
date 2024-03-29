#include "../../SDL_Framework.h"
#include "../Common/PVector.h"

class Example_1_2 : public SDL_Framework
{
public:
    Example_1_2() :
        SDL_Framework("Example 1.2: Bouncing ball with PVectors", 400, 100, 1200, 800, 0) {}

    bool UserRender(int elapsed_time) override
    {
        SDL_SetRenderDrawColor(Renderer(), 255, 255, 255, 255);
        SDL_RenderClear(Renderer());
        location.Add(velocity);
        if (location.x > WindowWidth() - radius || location.x < radius) {
            velocity.x *= -1;
        }
        if (location.y > WindowHeight() - radius || location.y < radius) {
            velocity.y *= -1;
        }
        DrawCircle({ (int)location.x, (int)location.y }, radius, { 255, 0, 0, 0 }, true);
        return true;
    }
private:
    PVector location = PVector(100, 100);
    PVector velocity = PVector(1, 3.3f);
    int radius = 16;
};

SDL_Framework *GetInstanceExample_1_2()
{
    return new Example_1_2();
}

// END
