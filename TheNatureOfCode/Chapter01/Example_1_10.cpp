#include "../../SDL_Framework.h"
#include "../Common/PVector.h"
#include "../Common/Mover.h"

class Example_1_10 : public SDL_Framework
{
public:
    Example_1_10() :
        SDL_Framework("Example 1.10: Accelerating Toward the Mouse", 400, 100, 1200, 800, 0) {}

    bool UserInit() override
    {
        PVector location((float)(WindowWidth() / 2), (float)(WindowHeight() / 2));
        PVector velocity(0, 0);
        mover = new Mover(this, location, velocity);
        mover->acceleration = PVector((float)-0.001, (float)0.01);
        return true;
    }

    bool UserRender(int elapsed_time) override
    {
        SDL_SetRenderDrawColor(Renderer(), 255, 255, 255, 255);
        SDL_RenderClear(Renderer());
        PVector mouse = PVector((float)MousePosition().x, (float)MousePosition().y);
        PVector direction = PVector(mouse.x, mouse.y);
        direction.Sub(mover->location);
        direction.Normalize();
        direction.Mult(0.2f);
        mover->acceleration = direction;
        mover->Update();
        mover->CheckEdges();
        mover->Display();
        return true;
    }
private:
    Mover *mover;
};

SDL_Framework *GetInstanceExample_1_10()
{
    return new Example_1_10();
}

// END
