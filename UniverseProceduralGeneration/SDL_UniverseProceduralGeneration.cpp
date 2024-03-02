#include "../SDL_Framework.h"

constexpr SDL_Color kStarColors[8] =
{
    {0xFF, 0xFF, 0xFF, 0xFF}, {0xFF, 0xFF, 0xD9, 0xFF}, {0xFF, 0xFF, 0xA3, 0xFF}, {0xC8, 0xC8, 0xFF, 0xFF},
    {0x9D, 0xCB, 0xFF, 0xFF}, {0xFF, 0x9F, 0x9F, 0xFF}, {0xFF, 0x5E, 0x41, 0xFF}, {0x9D, 0x19, 0x28, 0xFF}
};

struct sPlanet
{
    double  distance = 0.0;
    double  diameter = 0.0;
    double  foliage = 0.0;
    double  minerals = 0.0;
    double  water = 0.0;
    double  gases = 0.0;
    double  temperature = 0.0;
    double  population = 0.0;
    bool    ring = false;
    vector<double> moons;
};

class StarSystem
{
public:
    vector<sPlanet> planets;
    bool		start_exists = false;
    double		start_diameter = 0.0f;
    SDL_Color	start_color;

    StarSystem(uint32_t x, uint32_t y, bool generate_full_system = false)
    {
        generation_seed_ = (x & 0xFFFF) << 16 | (y & 0xFFFF);

        start_exists = (GetRandomInt(0, 20) == 1);
        if (!start_exists) return;

        start_diameter = GetRandomDouble(10.0, 40.0);
        start_color = kStarColors[GetRandomInt(0, 8)];

        if (!generate_full_system) return;

        double distance_from_star = GetRandomDouble(60.0, 200.0);

        int max_planets = GetRandomInt(0, 10);

        for (int i = 0; i < max_planets; i++)
        {
            sPlanet p;
            p.distance = distance_from_star;
            distance_from_star += GetRandomDouble(20.0, 200.0);
            p.diameter = GetRandomDouble(4.0, 20.0);

            p.temperature = GetRandomDouble(-200.0, 300.0);

            p.foliage = GetRandomDouble(0.0, 1.0);
            p.minerals = GetRandomDouble(0.0, 1.0);
            p.gases = GetRandomDouble(0.0, 1.0);
            p.water = GetRandomDouble(0.0, 1.0);

            double dSum = 1.0 / (p.foliage + p.minerals + p.gases + p.water);
            p.foliage *= dSum;
            p.minerals *= dSum;
            p.gases *= dSum;
            p.water *= dSum;

            p.population = std::max(GetRandomInt(-5000000, 20000000), 0);

            p.ring = GetRandomInt(0, 10) == 1;

            int max_moons = std::max(GetRandomInt(-5, 5), 0);
            for (int n = 0; n < max_moons; n++)
            {
                p.moons.push_back(GetRandomDouble(1.0, 5.0));
            }

            planets.push_back(p);
        }
    }

    ~StarSystem()
    {

    }


private:
    uint32_t generation_seed_ = 0;

    double GetRandomDouble(double min, double max)
    {
        return ((double)GetRandom() / (double)(0x7FFFFFFF)) * (max - min) + min;
    }

    int GetRandomInt(int min, int max)
    {
        return (GetRandom() % (max - min)) + min;
    }

    uint32_t GetRandom()
    {
        generation_seed_ += 0xe120fc15;
        uint64_t tmp;
        tmp = (uint64_t)generation_seed_ * 0x4a39b70d;
        uint32_t m1 = (uint32_t)((tmp >> 32) ^ tmp);
        tmp = (uint64_t)m1 * 0x12fad5c9;
        uint32_t m2 = (uint32_t)((tmp >> 32) ^ tmp);
        return m2;
    }
};


class SDL_UniverseProceduralGeneration : public SDL_Framework
{
private:
    SDL_Point   galaxy_offset_ = { 0, 0 };
    bool        start_is_selected_ = false;
    uint32_t    selected_start_seed1_ = 0;
    uint32_t    selected_start_seed2 = 0;
public:
    bool UserRender(int elapsed_time) override
    {
        SDL_SetRenderDrawColor(Renderer(), 0, 0, 0, 0); // black color_
        SDL_RenderClear(Renderer());

        if (PressedKey() == SDLK_w) galaxy_offset_.y -= 50;
        if (PressedKey() == SDLK_s) galaxy_offset_.y += 50;
        if (PressedKey() == SDLK_a) galaxy_offset_.x -= 50;
        if (PressedKey() == SDLK_d) galaxy_offset_.x += 50;

        //std::cout << "(" << galaxy_offset_.x << "," << galaxy_offset_.y << ")\n";

        int sectors_x = WindowWidth() / 16;
        int sectors_y = WindowHeight() / 16;

        SDL_Point vMouse = { MousePosition().x / 16 , MousePosition().y / 16 };

        for (int screen_sector_x = 0; screen_sector_x < sectors_x; screen_sector_x++) {

            for (int screen_sector_y = 0; screen_sector_y < sectors_y; screen_sector_y++) {

                uint32_t seed1 = galaxy_offset_.x + screen_sector_x;
                uint32_t seed2 = galaxy_offset_.y + screen_sector_y;

                StarSystem star(seed1, seed2);
                if (star.start_exists)
                {
                    SDL_Point p = { screen_sector_x * 16 + 8, screen_sector_y * 16 + 8 };
                    
                    DrawCircle(p, (int)star.start_diameter / 8, star.start_color, true);

                    if (vMouse.x == screen_sector_x && vMouse.y == screen_sector_y) {
                        p.x = screen_sector_x * 16 + 8;
                        p.y = screen_sector_y * 16 + 8;
                        DrawCircle(p, 12, { 255,255,255,255 }, false);
                    }
                }
            }
        }

        if (IsMouseButtonPressed(LEFT))
        {
            uint32_t seed1 = galaxy_offset_.x + vMouse.x;
            uint32_t seed2 = galaxy_offset_.y + vMouse.y;

            StarSystem star(seed1, seed2);
            if (star.start_exists)
            {
                start_is_selected_ = true;
                selected_start_seed1_ = seed1;
                selected_start_seed2 = seed2;
            }
            else
                start_is_selected_ = false;
        }

        if (start_is_selected_)
        {
            StarSystem star(selected_start_seed1_, selected_start_seed2, true);

            SDL_SetRenderDrawColor(Renderer(), 0, 0, 128, 0); // dark blue color_
            SDL_Rect r = { 8, WindowHeight() - 232, 550, 232 };
            SDL_RenderFillRect(Renderer(), &r);
            SDL_SetRenderDrawColor(Renderer(), 255, 255, 255, 0); // white color_
            SDL_RenderDrawRect(Renderer(), &r);

            SDL_Point body = { 14, WindowHeight() - 232 / 2 };

            body.x += (int)(star.start_diameter * 1.375);
            DrawCircle(body, (int)(star.start_diameter * 1.375), star.start_color, true);
            body.x += (int)((star.start_diameter * 1.375) + 8);

            for (auto& planet : star.planets)
            {
                if (body.x + planet.diameter >= 496) break;

                body.x += (int)planet.diameter;
                DrawCircle(body, (int)(planet.diameter * 1.0), { 255, 0, 0, 0 }, true); // red

                if (planet.ring) {
                    DrawCircle(body, (int)(planet.diameter * 1.0 + 5), { 255, 255, 255, 255 }, false);// white
                }

                SDL_Point moon_position = { body.x, body.y };
                moon_position.y += (int)(planet.diameter + 10);

                for (auto& moon : planet.moons)
                {
                    moon_position.y += (int)moon;
                    DrawCircle(moon_position, (int)moon, { 192, 192, 192, 0 }, true); // gray
                    moon_position.y += (int)(moon + 10);
                }

                body.x += (int)(planet.diameter + 8);
            }
        }

        return true;
    }
};

void RunUniverseProceduralGeneration(void)
{
    SDL_UniverseProceduralGeneration universe;
    if (universe.Init("Universe Procedural Generation", 400, 100, 1200, 800, 0)) {
        universe.Run();
    }
}



