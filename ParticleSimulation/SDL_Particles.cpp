#include "../SDL_Framework.h"

#define NUM_TYPES 6
#define NUM_PARTICLES 900
#define SPEED_CONTROL 0.03f
#define FRICTION 0.85f

#define TESTID -1

float MIN_DISTANCE[NUM_TYPES][NUM_TYPES];
float FORCES[NUM_TYPES][NUM_TYPES];
float RADII[NUM_TYPES][NUM_TYPES];

SDL_Color PALLETE[NUM_TYPES] = { {77,238,234}, {116,238,21}, {255,231,0}, {240,0,255}, {0,30,255}, {228,3,3} };

class Particle {
private:
    int         id;
    Vector2D    position;
    Vector2D    velocity;
    int         type;
    SDL_Color   color;
public:
    Particle(int id, int width, int height)
    {
        this->id = id;
        position = Vector2D((rand() % width), (rand() % height));
        velocity = Vector2D(0, 0);
        type = rand() % NUM_TYPES;
        color = PALLETE[type];
    }

    void Display(SDL_Framework *framework)
    {
        framework->DrawCircle({ (int)position.x, (int)position.y }, 1, color, true);
    }

    float Interpolate(float value, float istart, float istop, float ostart, float ostop)
    {
        return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
    }

    void Update(SDL_Framework *framework, std::vector<Particle *> swarm) 
    {
        Vector2D direction;
        Vector2D total_force;
        Vector2D acceleration;
        float distance;

        for each (Particle *other in swarm) {
            if (this->id == other->id) {
                continue;
            }
            direction.x = other->position.x;
            direction.y = other->position.y;
            direction.Subtract(position);
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
            if (distance < MIN_DISTANCE[type][other->type]) {
                Vector2D force(direction.x, direction.y);
                force.Multiply(fabs(FORCES[type][other->type]) * -3.0f);
                force.Multiply(Interpolate(distance, 0, MIN_DISTANCE[type][other->type], 1, 0));
                force.Multiply(SPEED_CONTROL);
                total_force.Add(force);
            }
            if (distance < RADII[type][other->type]) {
                Vector2D force(direction.x, direction.y);
                force.Multiply(FORCES[type][other->type]);
                force.Multiply(Interpolate(distance, 0, RADII[type][other->type], 1, 0));
                force.Multiply(SPEED_CONTROL);
                total_force.Add(force);
            }
        }

        if (id == TESTID) {
            cout << "id: " << id << endl;
            cout << "position1: " << position.x << "," << position.y << endl << endl;
            cout << "velocity1: " << velocity.x << "," << velocity.y << endl;
        }
        acceleration.Add(total_force);
        velocity.Add(acceleration);
        position.Add(velocity);
        if (position.x > framework->WindowWidth()) {
            position.x -= framework->WindowWidth();
        }
        if (position.x < 0) {
            position.x += framework->WindowWidth();
        }
        if (position.y > framework->WindowHeight()) {
            position.y -= framework->WindowHeight();
        }
        if (position.y < 0) {
            position.y += framework->WindowHeight();
        }
        //position.x = (float)((int)(position.x + framework->WindowWidth()) % framework->WindowWidth());
        //position.y = (float)((int)(position.y + framework->WindowHeight()) % framework->WindowHeight());
        velocity.Multiply(FRICTION);

        if (id == TESTID) {
            cout << "id: " << id << endl;
            cout << "position1: " << position.x << "," << position.y << endl << endl;
            cout << "total_force: " << total_force.x << "," << total_force.y << endl;
            cout << "acceleration: " << acceleration.x << "," << acceleration.y << endl;
            cout << "position2: " << position.x << "," << position.y << endl;
            cout << "velocity2: " << velocity.x << "," << velocity.y << endl << endl;
        }
    }
};

class SDL_Particles : public SDL_Framework
{
private:
    std::vector<Particle *>  swarm;
    Uint32 start_time;

public:
    bool UserInit() override
    {
        for (int i = 0; i < NUM_PARTICLES; i++) {
            swarm.push_back(new Particle(i, WindowWidth(), WindowHeight()));
        }
        SetParameters();
        start_time = SDL_GetTicks();
        return true;
    }

    bool UserRender(int elapsed_time) override
    {
        SDL_SetRenderDrawColor(renderer(), 0, 0, 0, 0); // black color
        SDL_RenderClear(renderer());

        for each (Particle *particle in swarm)
        {
            particle->Update(this, swarm);
            particle->Display(this);
        }

        Uint32 current_time = SDL_GetTicks();
        if (current_time > start_time + 60000) {
            SetParameters();
            start_time = current_time;
        }

        float line_width = WindowWidth() * (float)((current_time - start_time) / 60000.0);

        SDL_SetRenderDrawColor(renderer(), 253, 254, 2, 0);
        SDL_RenderDrawLine(renderer(), 0, 5, (int)line_width, 5);

        if (PressedKey() == SDLK_x) {
            SetParameters();
            start_time = current_time;
        }

        return true;
    }

    float RandomFloat(float min, float max)
    {
        float random = ((float)rand()) / (float)RAND_MAX;
        float range = max - min;
        return (random * range) + min;
    }

    void SetParameters()
    {
        for (int i = 0; i < NUM_TYPES; i++) {
            for (int j = 0; j < NUM_TYPES; j++) {
                FORCES[i][j] = RandomFloat(0.3f, 1.0f);
                if (rand() % 100 < 50) {
                    FORCES[i][j] *= -1.0;
                }
                MIN_DISTANCE[i][j] = RandomFloat(30, 50);
                RADII[i][j] = RandomFloat(100, 200);
            }
        }
    }

    void PrintParameters()
    {
        for (int i = 0; i < NUM_TYPES; i++) {
            cout << "FORCE[" << i << "]: ";
            for (int j = 0; j < NUM_TYPES; j++) {
                if (j > 0) cout << ", ";
                cout << FORCES[i][j];
            }
            cout << endl;
        }
        for (int i = 0; i < NUM_TYPES; i++) {
            cout << "MIN_DIST[" << i << "]: ";
            for (int j = 0; j < NUM_TYPES; j++) {
                if (j > 0) cout << ", ";
                cout << MIN_DISTANCE[i][j];
            }
            cout << endl;
        }
        for (int i = 0; i < NUM_TYPES; i++) {
            cout << "RADII[" << i << "]: ";
            for (int j = 0; j < NUM_TYPES; j++) {
                if (j > 0) cout << ", ";
                cout << RADII[i][j];
            }
            cout << endl;
        }
    }
};

void RunParticles(void)
{
    SDL_Particles particles;
    if (particles.Init("Particles Simulation", 400, 100, 1200, 800, 0)) {
        particles.Run();
    }
}



