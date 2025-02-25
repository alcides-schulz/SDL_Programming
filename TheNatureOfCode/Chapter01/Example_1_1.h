#ifndef EXAMPLE_1_1_H
#define EXAMPLE_1_1_H

#include "../../SDL_Framework.h"

class Example_1_1 : public SDL_Framework
{
public:
    Example_1_1() : SDL_Framework("Example 1.1: Bouncing ball with no vectors", 400, 100, 1200, 800, 0) {}
    bool UserRender(int elapsed_time) override;
private:
    float x = 100;
    float y = 100;
    float xspeed = 1;
    float yspeed = 3.3f;
    int radius = 16;
};

#endif

// END
