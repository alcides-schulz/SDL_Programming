#include "../../SDL_Framework.h"
#include "../Common/PVector.h"
#include "../Common/Mover.h"

#include <cstdlib>
#include <time.h>

class Example_1_9 : public SDL_Framework
{
public:
    Example_1_9() :
        SDL_Framework("Example 1.9: Motion 101 (velocity and random acceleration)", 400, 100, 1200, 800, 0) {}

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
        mover->acceleration = PVector::Random2D();
        mover->Update();
        mover->CheckEdges();
        mover->Display();
        return true;
    }
private:
    Mover *mover;
};

SDL_Framework *GetInstanceExample_1_9()
{
    return new Example_1_9();
}

// END
