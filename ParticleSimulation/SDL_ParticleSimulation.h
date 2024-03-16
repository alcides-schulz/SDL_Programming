#ifndef SDL_PARTICLE_SIMULATION_H
#define SDL_PARTICLE_SIMULATION_H

#include "../SDL_Framework.h"

class Particle {
private:
    int         id_;
    Vector2D    position_;
    Vector2D    velocity_;
    int         type_;
    SDL_Color   color_;
public:
    Particle(int id, int width, int height);
    void Display(SDL_Framework *framework);
    float Interpolate(float value, float istart, float istop, float ostart, float ostop);
    void Update(SDL_Framework *framework, std::vector<Particle *> swarm);
};

class SDL_ParticleSimulation : public SDL_Framework
{
public:
    SDL_ParticleSimulation() :
        SDL_Framework("Particles Simulation", 400, 100, 1200, 800, 0) {};
    bool UserInit() override;
    bool UserRender(int elapsed_time) override;
    float RandomFloat(float min, float max);
    void SetParameters();
    void PrintParameters();
private:
    std::vector<Particle *> swarm_;
    Uint32                  start_time_;
};

#endif