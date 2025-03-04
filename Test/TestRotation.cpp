#include "TestRotation.h"

bool TestRotation::UserInit()
{
    return true;
}

bool TestRotation::UserRender(int elapsed_time)
{
    SDL_SetRenderDrawColor(Renderer(), 0, 0, 0, 0); // black color
    SDL_RenderClear(Renderer());
    
    //// Rotate a line using mathematical calculations
    //int x1 = 100, y1 = 100;
    //int x2 = 200, y2 = 100;

    //// Rotation center
    //int centerX = x1;
    //int centerY = y1;

    //// Convert angle to radians
    //double radAngle = angle_ * M_PI / 180.0;

    //// Rotate point (x2, y2) around (centerX, centerY)
    //int rotatedX = (int)(centerX + (x2 - centerX) * std::cos(radAngle) - (y2 - centerY) * std::sin(radAngle));
    //int rotatedY = (int)(centerY + (x2 - centerX) * std::sin(radAngle) + (y2 - centerY) * std::cos(radAngle));

    //SDL_SetRenderDrawColor(Renderer(), 255, 0, 0, 255); // Red line
    //SDL_RenderDrawLine(Renderer(), x1, y1, rotatedX, rotatedY);

    // Rotate a line around its center
    int x1 = 100, y1 = 100;
    int x2 = 200, y2 = 200;

    // Calculate center of the line
    int centerX = (x1 + x2) / 2;
    int centerY = (y1 + y2) / 2;

    // Convert angle to radians
    double radAngle = angle_ * M_PI / 180.0;

    // Rotate point (x1, y1) around (centerX, centerY)
    int rotatedX1 = (int)(centerX + (x1 - centerX) * std::cos(radAngle) - (y1 - centerY) * std::sin(radAngle));
    int rotatedY1 = (int)(centerY + (x1 - centerX) * std::sin(radAngle) + (y1 - centerY) * std::cos(radAngle));

    // Rotate point (x2, y2) around (centerX, centerY)
    int rotatedX2 = (int)(centerX + (x2 - centerX) * std::cos(radAngle) - (y2 - centerY) * std::sin(radAngle));
    int rotatedY2 = (int)(centerY + (x2 - centerX) * std::sin(radAngle) + (y2 - centerY) * std::cos(radAngle));

    SDL_SetRenderDrawColor(Renderer(), 255, 0, 0, 255); // Red line
    SDL_RenderDrawLine(Renderer(), rotatedX1, rotatedY1, rotatedX2, rotatedY2);

    angle_ += 1.0; // Increment angle for rotation

    return true;
}
// END
