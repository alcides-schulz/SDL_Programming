#ifndef SDL_SAND_H
#define SDL_SAND_H

#include "../SDL_Framework.h"

class SDL_Sand : public SDL_Framework
{
public:
    SDL_Sand() :
        SDL_Framework("Sand Simulation", 400, 100, 1200, 800, 0) {};
    bool UserInit() override;
    bool UserRender(int elapsed_time) override;
private:
    int kCellSize = 4;
    int rows_;
    int cols_;
    int size_;
    bool *current_grid_;
    bool *next_grid_;
    void ResetGrid(bool *grid);
    void ProcessInput();
    void UpdateGrid();
    void RenderGrid();
};

#endif