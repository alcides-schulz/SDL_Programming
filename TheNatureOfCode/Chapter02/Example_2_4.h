#ifndef EXAMPLE_2_4_H
#define EXAMPLE_2_4_H

#include "../../SDL_Framework.h"
#include "Chapter02MoverFriction.h"

class Example_2_4 : public SDL_Framework
{
public:
    Example_2_4() : SDL_Framework("Example 2.4: Including friction", 400, 100, 1200, 800, 0) {};
    bool UserInit() override;
    bool UserRender(int elapsed_time) override;
private:
    Chapter02MoverFriction *mover_;
};

#endif