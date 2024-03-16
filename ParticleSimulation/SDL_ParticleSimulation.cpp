#include "SDL_ParticleSimulation.h"

#define kNumTypes       6
#define kNumParticles   900
#define kSpeedControl   0.03f
#define kFriction       0.85f

#define kTestID         -1

float kMinDistance[kNumTypes][kNumTypes];
float kForces[kNumTypes][kNumTypes];
float kRADII[kNumTypes][kNumTypes];

SDL_Color kPallete[kNumTypes] = { {77,238,234}, {116,238,21}, {255,231,0}, {240,0,255}, {0,30,255}, {228,3,3} };

Particle::Particle(int id, int width, int height)
{
    this->id_ = id;
    position_ = Vector2D((rand() % width), (rand() % height));
    velocity_ = Vector2D(0, 0);
    type_ = rand() % kNumTypes;
    color_ = kPallete[type_];
}

void Particle::Display(SDL_Framework *framework)
{
    framework->DrawCircle({ (int)position_.x, (int)position_.y }, 1, color_, true);
}

float Particle::Interpolate(float value, float istart, float istop, float ostart, float ostop)
{
    return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}

void Particle::Update(SDL_Framework *framework, std::vector<Particle *> swarm)
{
    Vector2D direction;
    Vector2D total_force;
    Vector2D acceleration;
    float distance;

    for each (Particle *other in swarm) {
        if (this->id_ == other->id_) {
            continue;
        }
        direction.x = other->position_.x;
        direction.y = other->position_.y;
        direction.Subtract(position_);
        if (direction.x > 0.5 * framework->WindowWidth()) {
            direction.x -= framework->WindowWidth();
        }
        if (direction.x < -0.5 * framework->WindowWidth()) {
            direction.x += framework->WindowWidth();
        }
        if (direction.y > 0.5 * framework->WindowHeight()) {
            direction.y -= framework->WindowHeight();
        }
        if (direction.y < -0.5 * framework->WindowHeight()) {
            direction.y += framework->WindowHeight();
        }
        distance = direction.Magnitude();
        direction.Normalize();
        if (distance < kMinDistance[type_][other->type_]) {
            Vector2D force(direction.x, direction.y);
            force.Multiply(fabs(kForces[type_][other->type_]) * -3.0f);
            force.Multiply(Interpolate(distance, 0, kMinDistance[type_][other->type_], 1, 0));
            force.Multiply(kSpeedControl);
            total_force.Add(force);
        }
        if (distance < kRADII[type_][other->type_]) {
            Vector2D force(direction.x, direction.y);
            force.Multiply(kForces[type_][other->type_]);
            force.Multiply(Interpolate(distance, 0, kRADII[type_][other->type_], 1, 0));
            force.Multiply(kSpeedControl);
            total_force.Add(force);
        }
    }

    if (id_ == kTestID) {
        cout << "id: " << id_ << endl;
        cout << "position1: " << position_.x << "," << position_.y << endl << endl;
        cout << "velocity1: " << velocity_.x << "," << velocity_.y << endl;
    }
    acceleration.Add(total_force);
    velocity_.Add(acceleration);
    position_.Add(velocity_);
    if (position_.x > framework->WindowWidth()) {
        position_.x -= framework->WindowWidth();
    }
    if (position_.x < 0) {
        position_.x += framework->WindowWidth();
    }
    if (position_.y > framework->WindowHeight()) {
        position_.y -= framework->WindowHeight();
    }
    if (position_.y < 0) {
        position_.y += framework->WindowHeight();
    }
    velocity_.Multiply(kFriction);

    if (id_ == kTestID) {
        cout << "id: " << id_ << endl;
        cout << "position1: " << position_.x << "," << position_.y << endl << endl;
        cout << "total_force: " << total_force.x << "," << total_force.y << endl;
        cout << "acceleration: " << acceleration.x << "," << acceleration.y << endl;
        cout << "position2: " << position_.x << "," << position_.y << endl;
        cout << "velocity2: " << velocity_.x << "," << velocity_.y << endl << endl;
    }
}

bool SDL_ParticleSimulation::UserInit()
{
    for (int i = 0; i < kNumParticles; i++) {
        swarm_.push_back(new Particle(i, WindowWidth(), WindowHeight()));
    }
    SetParameters();
    start_time_ = SDL_GetTicks();
    return true;
}

bool SDL_ParticleSimulation::UserRender(int elapsed_time)
{
    SDL_SetRenderDrawColor(Renderer(), 0, 0, 0, 0); // black color
    SDL_RenderClear(Renderer());

    for each (Particle *particle in swarm_)
    {
        particle->Update(this, swarm_);
        particle->Display(this);
    }

    Uint32 current_time = SDL_GetTicks();
    if (current_time > start_time_ + 60000) {
        SetParameters();
        start_time_ = current_time;
    }

    float line_width = WindowWidth() * (float)((current_time - start_time_) / 60000.0);

    SDL_SetRenderDrawColor(Renderer(), 253, 254, 2, 0);
    SDL_RenderDrawLine(Renderer(), 0, 5, (int)line_width, 5);

    if (PressedKey() == SDLK_x) {
        SetParameters();
        start_time_ = current_time;
    }

    return true;
}

float SDL_ParticleSimulation::RandomFloat(float min, float max)
{
    float random = ((float)rand()) / (float)RAND_MAX;
    float range = max - min;
    return (random * range) + min;
}

void SDL_ParticleSimulation::SetParameters()
{
    for (int i = 0; i < kNumTypes; i++) {
        for (int j = 0; j < kNumTypes; j++) {
            kForces[i][j] = RandomFloat(0.3f, 1.0f);
            if (rand() % 100 < 50) {
                kForces[i][j] *= -1.0;
            }
            kMinDistance[i][j] = RandomFloat(30, 50);
            kRADII[i][j] = RandomFloat(100, 200);
        }
    }
}

void SDL_ParticleSimulation::PrintParameters()
{
    for (int i = 0; i < kNumTypes; i++) {
        cout << "FORCE[" << i << "]: ";
        for (int j = 0; j < kNumTypes; j++) {
            if (j > 0) cout << ", ";
            cout << kForces[i][j];
        }
        cout << endl;
    }
    for (int i = 0; i < kNumTypes; i++) {
        cout << "MIN_DIST[" << i << "]: ";
        for (int j = 0; j < kNumTypes; j++) {
            if (j > 0) cout << ", ";
            cout << kMinDistance[i][j];
        }
        cout << endl;
    }
    for (int i = 0; i < kNumTypes; i++) {
        cout << "RADII[" << i << "]: ";
        for (int j = 0; j < kNumTypes; j++) {
            if (j > 0) cout << ", ";
            cout << kRADII[i][j];
        }
        cout << endl;
    }
}


// END