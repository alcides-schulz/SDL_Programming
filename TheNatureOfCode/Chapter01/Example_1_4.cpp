#include "../../SDL_Framework.h"
#include "../Common/PVector.h"

class Example_1_4 : public SDL_Framework
{
public:
    Example_1_4() :
        SDL_Framework("Example 1.4: Multiplying a vector", 400, 100, 1200, 800, 0) {}

    bool UserRender(int elapsed_time) override
    {
        SDL_SetRenderDrawColor(Renderer(), 255, 255, 255, 255);
        SDL_RenderClear(Renderer());
        PVector mouse = PVector((float)MousePosition().x, (float)MousePosition().y);
        PVector center = PVector((float)(WindowWidth() / 2), (float)(WindowHeight() / 2));
        mouse.Sub(center);
        mouse.Mult(0.5);
        int translate_x = WindowWidth() / 2;
        int translate_y = WindowHeight() / 2;
        SDL_SetRenderDrawColor(Renderer(), 0, 0, 0, 255);
        SDL_RenderDrawLine(Renderer(), translate_x, translate_y, (int)mouse.x + translate_x, (int)mouse.y + translate_y);
        return true;
    }
};

SDL_Framework *GetInstanceExample_1_4()
{
    return new Example_1_4();
}

//END