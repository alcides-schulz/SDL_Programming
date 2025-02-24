#ifndef EXAMPLE_2_1_H
#define EXAMPLE_2_1_H

#include "../../SDL_Framework.h"
#include "Chapter02Mover.h"

class Example_2_1 : public SDL_Framework
{
public:
    Example_2_1() : SDL_Framework("Example 2.1: Forces", 400, 100, 1200, 800, 0) {};
    bool UserInit() override;
    bool UserRender(int elapsed_time) override;
private:
    Chapter02Mover *mover_;
};

#endif