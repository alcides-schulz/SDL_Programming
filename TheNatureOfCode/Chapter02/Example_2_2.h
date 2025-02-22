#ifndef EXAMPLE_2_2_H
#define EXAMPLE_2_2_H

#include "../../SDL_Framework.h"
#include "Chapter02Mover.h"

class Example_2_2 : public SDL_Framework
{
public:
    Example_2_2() : SDL_Framework("Example 2.2: Forces on 2 objects", 400, 100, 1200, 800, 0) {};
    bool UserInit() override;
    bool UserRender(int elapsed_time) override;
private:
    Chapter02Mover *moverA_;
    Chapter02Mover *moverB_;
};

#endif