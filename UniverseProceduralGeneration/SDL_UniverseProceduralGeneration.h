#ifndef SDL_UNIVERSE_PROCEDURAL_GENERATION_H
#define SDL_UNIVERSE_PROCEDURAL_GENERATION_H

#include "../SDL_Framework.h"

class SDL_UniverseProceduralGeneration : public SDL_Framework
{
private:
    SDL_Point   galaxy_offset_ = { 0, 0 };
    bool        start_is_selected_ = false;
    uint32_t    selected_start_seed1_ = 0;
    uint32_t    selected_start_seed2_ = 0;
public:
    SDL_UniverseProceduralGeneration() : 
        SDL_Framework("Universe Procedural Generation", 400, 100, 1200, 800, 0)
    {
        
    }
    bool UserRender(int elapsed_time) override;
};

#endif
