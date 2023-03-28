#include "../../SDL_Framework.h"
#include "../Common/PVector.h"
#include "../Common/Mover.h"

#include <cstdlib>
#include <time.h>

class Example_1_7 : public SDL_Framework
{
private:
    Mover *mover;

public:
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
        SDL_SetRenderDrawColor(renderer(), 255, 255, 255, 255);
        SDL_RenderClear(renderer());

        mover->Update();
        mover->CheckEdges();
        mover->Display();

        return true;
    }
};

void RunExample_1_7(void)
{
    Example_1_7 example;
    if (example.Init("Example 1.7: Motion 101 (velocity)", 400, 100, 1200, 800, 0)) {
        example.Run();
    }
}



