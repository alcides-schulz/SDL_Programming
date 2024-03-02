#include "../../SDL_Framework.h"
#include "../Common/PVector.h"


class Example_1_3 : public SDL_Framework
{
public:
    bool UserRender(int elapsed_time) override
    {
        SDL_SetRenderDrawColor(Renderer(), 255, 255, 255, 255);
        SDL_RenderClear(Renderer());

        PVector mouse = PVector((float)MousePosition().x, (float)MousePosition().y);
        PVector center = PVector((float)(WindowWidth() / 2), (float)(WindowHeight() / 2));

        mouse.Sub(center);
        
        int translate_x = WindowWidth() / 2;
        int translate_y = WindowHeight() / 2;

        SDL_SetRenderDrawColor(Renderer(), 0, 0, 0, 255);
        SDL_RenderDrawLine(Renderer(), translate_x, translate_y, (int)mouse.x + translate_x, (int)mouse.y + translate_y);

        return true;
    }
};

void RunExample_1_3(void)
{
    Example_1_3 example;
    if (example.Init("Example 1.3: PVector subtraction", 400, 100, 1200, 800, 0)) {
        example.Run();
    }
}



