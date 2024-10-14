#ifndef EXAMPLE_2_1_H
#define EXAMPLE_2_1_H

#include "../../SDL_Framework.h"

class Example_2_1 : public SDL_Framework
{
public:
    Example_2_1() :
        SDL_Framework("Example 2.1: new", 400, 100, 1200, 800, 0) {}
    bool UserRender(int elapsed_time) override;
private:
    float x = 100;
    float y = 100;
    float xspeed = 1;
    float yspeed = 3.3f;
    int radius = 16;
};

#endif