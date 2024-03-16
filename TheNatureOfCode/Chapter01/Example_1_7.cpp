#include "../../SDL_Framework.h"
#include "../Common/PVector.h"
#include "../Common/Mover.h"

#include <cstdlib>
#include <time.h>

class Example_1_7 : public SDL_Framework
{
public:
    Example_1_7() :
        SDL_Framework("Example 1.7: Motion 101 (velocity)", 400, 100, 1200, 800, 0) {}

    bool UserInit() override
    {
        srand((unsigned int)time(NULL));
        PVector location((float)(rand() % WindowWidth()), (float)(rand() % WindowHeight()));
        PVector velocity((float)(rand() % 8 - 4), (float)(rand() % 8 - 4));
        mover = new Mover(this, location, velocity);
        return true;
    }

    bool UserRender(int elapsed_time) override
    {
        SDL_SetRenderDrawColor(Renderer(), 255, 255, 255, 255);
        SDL_RenderClear(Renderer());
        mover->Update();
        mover->CheckEdges();
        mover->Display();
        return true;
    }
private:
    Mover *mover;
};

SDL_Framework *GetInstanceExample_1_7()
{
    return new Example_1_7();
}

//END
