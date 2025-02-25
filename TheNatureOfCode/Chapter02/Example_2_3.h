#ifndef EXAMPLE_2_3_H
#define EXAMPLE_2_3_H

#include "../../SDL_Framework.h"
#include "Chapter02Mover.h"

class Example_2_3 : public SDL_Framework
{
public:
    Example_2_3() : SDL_Framework("Example 2.3: Gravity scaled by Mass", 400, 100, 1200, 800, 0) {};
    bool UserInit() override;
    bool UserRender(int elapsed_time) override;
private:
    Chapter02Mover *moverA_;
    Chapter02Mover *moverB_;
};

#endif