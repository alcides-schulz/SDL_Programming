#ifndef TEST_ROTATION_H
#define TEST_ROTATION_H

#include "../SDL_Framework.h"

class TestRotation : public SDL_Framework
{
public:
    TestRotation() : SDL_Framework("Test Rotation", 400, 100, 1200, 800, 0) {};
    bool UserInit() override;
    bool UserRender(int elapsed_time) override;
private:
    double angle_ = 0;
};

#endif