#include "SDL_Sand.h"

bool SDL_Sand::UserInit()
{
    rows_ = WindowHeight() / kCellSize;
    cols_ = WindowWidth() / kCellSize;
    size_ = rows_ * cols_;
    current_grid_ = new bool[size_];
    next_grid_ = new bool[size_];
    ResetGrid(current_grid_);
    ResetGrid(next_grid_);
    return true;
}

void SDL_Sand::ResetGrid(bool *grid)
{
    for (int i = 0; i < size_; i++) {
        grid[i] = false;
    }
}

bool SDL_Sand::UserRender(int elapsed_time)
{
    SDL_SetRenderDrawColor(Renderer(), 0, 0, 0, 0); // black color
    SDL_RenderClear(Renderer());
    ProcessInput();
    UpdateGrid();
    RenderGrid();
    return true;
}

void SDL_Sand::ProcessInput()
{
    if (IsMouseButtonPressed(kMouseLeftButton)) {
        int row = MousePosition().y / kCellSize;
        int col = MousePosition().x / kCellSize;
        for (int r = row - 5; r < row + 5; r++) {
            for (int c = col - 5; c < col + 5; c++) {
                if (r >= 0 && r < rows_ && c >= 0 && c < cols_) {
                    if (rand() % 100 > 60) {
                        current_grid_[r * cols_ + c] = true;
                    }
                }
            }
        }
    }
}

void SDL_Sand::UpdateGrid()
{
    ResetGrid(next_grid_);
    for (int r = 0; r < rows_; r++)
    {
        for (int c = 0; c < cols_; c++) 
        {
            int index = r * cols_ + c;
            if (current_grid_[index]) {
                // on the last row just update to display the grain
                if (r == rows_ - 1) {
                    next_grid_[index] = true;
                    continue;
                }
                int below_index = index + cols_;
                if (!current_grid_[below_index]) {
                    // empty grid below, set the grain to drop
                    next_grid_[index] = false;
                    next_grid_[below_index] = true;
                    continue;
                }
                // try to drop on either side
                if (rand() % 100 >= 50) {
                    if (c > 0 && !current_grid_[below_index - 1]) {
                        next_grid_[index] = false;
                        next_grid_[below_index - 1] = true;
                        continue;
                    }
                }
                else {
                    if (c < cols_ - 1 && !current_grid_[below_index + 1]) {
                        next_grid_[index] = false;
                        next_grid_[below_index + 1] = true;
                        continue;
                    }
                }
                // just keep the same
                next_grid_[index] = true;
                next_grid_[below_index] = true;
            }
        }
    }
    bool *temp = current_grid_;
    current_grid_ = next_grid_;
    next_grid_ = temp;
}

void SDL_Sand::RenderGrid()
{
    SDL_Rect rect = { 0, 0, kCellSize, kCellSize };
    SDL_SetRenderDrawColor(Renderer(), 253, 254, 2, 0);
    for (int r = 0; r < rows_; r++)
    {
        for (int c = 0; c < cols_; c++)
        {
            if (current_grid_[r * cols_ + c]) {
                rect.x = c * kCellSize;
                rect.y = r * kCellSize;
                SDL_RenderFillRect(Renderer(), &rect);
            }
        }
    }
}

// END