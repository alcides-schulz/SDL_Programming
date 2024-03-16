#include "../../SDL_Framework.h"

class Example_1_1 : public SDL_Framework
{
public:
    Example_1_1() : 
        SDL_Framework("Example 1.1: Bouncing ball with no vectors", 400, 100, 1200, 800, 0) {}

    bool UserRender(int elapsed_time) override
    {
        SDL_SetRenderDrawColor(Renderer(), 255, 255, 255, 255);
        SDL_RenderClear(Renderer());
        x += xspeed;
        y += yspeed;
        if (x > WindowWidth() - radius || x < radius) {
            xspeed *= -1;
        }
        if (y > WindowHeight() - radius || y < radius) {
            yspeed *= -1;
        }
        DrawCircle({ (int)x, (int)y }, radius, { 255, 0, 0, 0 }, true);
        return true;
    }
private:
    float x = 100;
    float y = 100;
    float xspeed = 1;
    float yspeed = 3.3f;
    int radius = 16;
};

SDL_Framework *GetInstanceExample_1_1()
{
    return new Example_1_1();
}

// END
