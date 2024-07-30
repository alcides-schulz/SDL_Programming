#include "SDL_RayCastingWalls.h"

bool SDL_RayCastingWalls::UserInit()
{
    position_ = Vector2D(22, 12);
    direction_ = Vector2D(-1, 0);
    plane_ = Vector2D(0.0, 0.66);

    printf("%zd\n", sizeof(SDL_KeyCode));

    return true;
}

bool SDL_RayCastingWalls::UserRender(int elapsed_time)
{
    SDL_SetRenderDrawColor(Renderer(), 0, 0, 0, 0); // black color
    SDL_RenderClear(Renderer());

    for (int x = 0; x < WindowWidth(); x++)
    {
        // Calculate ray position and direction
        float camera_x = 2 * x / (float)WindowWidth() - 1; // x-coordinate in camera space
        auto ray_direction = Vector2D(plane_);
        ray_direction.Multiply(camera_x);
        ray_direction.Add(direction_);
        
        // start position
        int map_x = position_.IntX();
        int map_y = position_.IntY();

        // length of ray from current position to next x or y-side
        auto side_distance = Vector2D(0, 0);

        // length of ray from one x or y-side to next x or y-side
        float delta_distance_x = (ray_direction.x == 0) ? 1e30f : std::fabs(1 / ray_direction.x);
        float delta_distance_y = (ray_direction.y == 0) ? 1e30f : std::fabs(1 / ray_direction.y);

        // what direction to step in x or y-direction (either +1 or -1)
        int step_x, step_y;
        if (ray_direction.x < 0) {
            step_x = -1;
            side_distance.x = (position_.x - map_x) * delta_distance_x;
        }
        else {
            step_x = 1;
            side_distance.x = (map_x + 1.0f - position_.x) * delta_distance_x;
        }
        if (ray_direction.y < 0) {
            step_y = -1;
            side_distance.y = (position_.y - map_y) * delta_distance_y;
        }
        else {
            step_y = 1;
            side_distance.y = (map_y + 1.0f - position_.y) * delta_distance_y;
        }

        // DDA - Digital Differential Analysis
        bool hit = false;
        int side;
        while (!hit) {
            if (side_distance.x < side_distance.y) {
                side_distance.x += delta_distance_x;
                map_x += step_x;
                side = 0;
            }
            else {
                side_distance.y += delta_distance_y;
                map_y += step_y;
                side = 1;
            }
            if (kWorldMap[map_x][map_y] > 0) {
                hit = true;
            }
        }

        float perpendicular_wall_distance;
        if (side == 0) {
            perpendicular_wall_distance = (side_distance.x - delta_distance_x);
        }
        else {
            perpendicular_wall_distance = (side_distance.y - delta_distance_y);
        }

        // Calculate height of line to draw on screen
        int line_height = (int)(WindowHeight() / perpendicular_wall_distance);

        // Calculate lowest and highest pixel to fill in current stripe
        int draw_start = max(0, -line_height / 2 + WindowHeight() / 2);
        int draw_end = min(WindowHeight() - 1, line_height / 2 + WindowHeight() / 2);
        
        // Choose wall color
        SDL_Color color;
        switch (kWorldMap[map_x][map_y])    
        {
        case 1: color = { 255, 0, 0 }; break; // red
        case 2: color = { 0, 255, 0 }; break; // green
        case 3: color = { 0, 0, 255 }; break; // blue
        case 4: color = { 255, 255, 255 }; break; // white
        default: color = { 255, 255, 0 }; break; // yellow
        }

        // Give x and y sides different brightness
        if (side == 1) {
            color.r /= 2;
            color.g /= 2;
            color.b /= 2;
        }

        // Draw the pixels of the stripe as a vertical line
        SDL_SetRenderDrawColor(Renderer(), color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(Renderer(), x, draw_start, x, draw_end);
    }

    // Speed modifiers
    float move_speed = (float)(elapsed_time / 1000.0 * 5.0);
    float rotation_speed = (float)(elapsed_time / 1000.0 * 3.0);

    // Move forward if no wall in front of you
    if (IsKeyPressed(SDLK_UP)) {
        if (kWorldMap[int(position_.x + direction_.x * move_speed)][int(position_.y)] == 0) {
            position_.x += direction_.x * move_speed;
        }
        if (kWorldMap[int(position_.x)][int(position_.y + direction_.y * move_speed)] == 0) {
            position_.y += direction_.y * move_speed;
        }
    }

    // Move backwards if no wall behind you
    if (IsKeyPressed(SDLK_DOWN)) {
        if (kWorldMap[int(position_.x - direction_.x * move_speed)][int(position_.y)] == 0) {
            position_.x -= direction_.x * move_speed;
        }
        if (kWorldMap[int(position_.x)][int(position_.y - direction_.y * move_speed)] == 0) {
            position_.y -= direction_.y * move_speed;
        }
    }

    // Rotate to the right
    if (IsKeyPressed(SDLK_RIGHT)) {
        float old_direction_x = direction_.x;
        direction_.x = direction_.x * cos(-rotation_speed) - direction_.y * sin(-rotation_speed);
        direction_.y = old_direction_x * sin(-rotation_speed) + direction_.y * cos(-rotation_speed);
        float old_plane_x = plane_.x;
        plane_.x = plane_.x * cos(-rotation_speed) - plane_.y * sin(-rotation_speed);
        plane_.y = old_plane_x * sin(-rotation_speed) + plane_.y * cos(-rotation_speed);
    }

    // Rotate to the left
    if (IsKeyPressed(SDLK_LEFT)) {
        float old_direction_x = direction_.x;
        direction_.x = direction_.x * cos(rotation_speed) - direction_.y * sin(rotation_speed);
        direction_.y = old_direction_x * sin(rotation_speed) + direction_.y * cos(rotation_speed);
        float old_plane_x = plane_.x;
        plane_.x = plane_.x * cos(rotation_speed) - plane_.y * sin(rotation_speed);
        plane_.y = old_plane_x * sin(rotation_speed) + plane_.y * cos(rotation_speed);

    }
    return true;
}

// END