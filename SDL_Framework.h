#pragma once

#include "SDL.h"
#include <SDL_image.h>

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <cmath>
#include <random>
#include <cstdlib>

using namespace std;

class Vector2D
{
public:
    float x;
    float y;

    Vector2D() : x(0), y(0) {}
    Vector2D(float x, float y) : x(x), y(y) {}
    Vector2D(double x, double y) : x((float)x), y((float)y) {}
    Vector2D(int x, int y) : x((float)x), y((float)y) {}

    int IntX() { return (int)x; }
    int IntY() { return (int)y; }

    void Add(Vector2D v2)
    {
        x += v2.x;
        y += v2.y;
    }

    void Subtract(Vector2D v2)
    {
        x -= v2.x;
        y -= v2.y;
    }

    void Multiply(float value)
    {
        x *= value;
        y *= value;
    }

    void Divide(float value)
    {
        x /= value;
        y /= value;
    }

    float Magnitude()
    {
        return sqrtf(x * x + y * y);
    }

    void Normalize()
    {
        float magnitude = Magnitude();
        if (magnitude != 0) {
            Divide(magnitude);
        }
    }

    void Limit(float max)
    {
        if (Magnitude() > max * max) {
            Normalize();
            Multiply(max);
        }
    }
 
};

class SDL_Framework
{
private:
    SDL_Window          *window_;
    const char          *window_title_;
    SDL_Renderer        *renderer_;
    SDL_Keycode         last_key_pressed_ = 0;
    std::vector<bool>   mouse_button_states_;
    SDL_Point           mouse_position_ = { 0,0 };
    int                 window_width_ = 0;
    int                 window_height_ = 0;
    bool                is_running_ = false;

    const int           kFPS = 60;
    const Uint32        kMaxFrameTime = (Uint32)(1000.0f / kFPS);

public:
    enum MOUSE_BUTTONS
    {
        LEFT = 0,
        MIDDLE = 1,
        RIGHT = 2
    };

    SDL_Framework()
    {
        mouse_button_states_.push_back(false);
        mouse_button_states_.push_back(false);
        mouse_button_states_.push_back(false);
    }

    virtual bool UserInit() { return true; };
    virtual bool UserRender(int elapsed_time) { if (elapsed_time) return true; return true; };
    virtual void UserClean() {};

    int SDL_Framework::WindowWidth() { return window_width_; }
    int SDL_Framework::WindowHeight() { return window_height_; }
    SDL_Renderer* SDL_Framework::Renderer() { return renderer_; }
    SDL_Window* SDL_Framework::Window() { return window_; }

    SDL_Keycode PressedKey() { return last_key_pressed_; }

    SDL_Point MousePosition() { return mouse_position_; }

    bool IsMouseButtonPressed(enum MOUSE_BUTTONS mouse_button) { return mouse_button_states_[mouse_button]; }

    bool Init(const char* title, int x, int y, int width, int height, int flags)
    {
        int result = SDL_Init(SDL_INIT_EVERYTHING);
        if (result != 0)
        {
            std::cout << "SDL_Init failed, result: " << result << ".\n";
            std::getchar();
            return false;
        }

        window_title_ = title;

        window_ = SDL_CreateWindow(title, x, y, width, height, flags);
        if (window_ == 0) {
            std::cout << "SDL_CreateWindow failed.\n";
            std::getchar();
            return false;
        }

        SDL_GetWindowSize(window_, &window_width_, &window_height_);
        if (window_width_ <= 0) window_width_ = 1;
        if (window_height_ <= 0) window_height_ = 1;

        renderer_ = SDL_CreateRenderer(window_, -1, 0);
        if (renderer_ == 0) {
            std::cout << "SDL_CreateRenderer failed.\n";
            std::getchar();
            return false;
        }

        is_running_ = UserInit();

        return is_running_;
    }

    void Run()
    {
        Uint32 start_time = SDL_GetTicks();
        Uint32 timer = start_time;
        int frame_count = 0;

        while (is_running_) {
            Uint32 frame_start = SDL_GetTicks();
            Uint32 elapsed_time = frame_start - start_time;
            start_time = frame_start;

            HandleEvents();
            if (!UserRender(elapsed_time)) {
                is_running_ = false;
            }
            SDL_RenderPresent(Renderer());

            frame_count++;
            if (SDL_GetTicks() - timer > 1000) {
                std::string t = window_title_;
                t.append(" (");
                t.append(std::to_string(frame_count));
                t.append(" FPS)");
                SDL_SetWindowTitle(window_, t.c_str());
                timer += 1000;
                frame_count = 0;
            }

            Uint32 frame_time = SDL_GetTicks() - frame_start;
            if (frame_time < kMaxFrameTime) {
                SDL_Delay((int)(kMaxFrameTime - frame_time));
            }
        }

        UserClean();

        SDL_DestroyWindow(window_);
        SDL_DestroyRenderer(renderer_);
        SDL_Quit();
    }

    void DrawCircle(SDL_Point center, int radius, SDL_Color color, bool fill)
    {
        int radius2 = radius * radius;

        SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
        for (int w = 0; w <= radius * 2; w++) {
            for (int h = 0; h <= radius * 2; h++) {
                int dx = radius - w;
                int dy = radius - h;
                int pos = dx * dx + dy * dy;
                if (fill && pos <= radius2) {
                    SDL_RenderDrawPoint(renderer_, center.x + dx, center.y + dy);
                }
                int diff = pos - radius2;
                if (!fill && abs(diff) <= 10) {
                    SDL_RenderDrawPoint(renderer_, center.x + dx, center.y + dy);
                }
            }
        }
    }

private:
    void HandleEvents()
    {
        last_key_pressed_ = 0;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYDOWN:
                last_key_pressed_ = event.key.keysym.sym;
                break;
            case SDL_QUIT:
                is_running_ = false;
                break;
            case SDL_MOUSEMOTION:
                mouse_position_.x = event.motion.x;
                mouse_position_.y = event.motion.y;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) mouse_button_states_[LEFT] = true;
                if (event.button.button == SDL_BUTTON_MIDDLE) mouse_button_states_[MIDDLE] = true;
                if (event.button.button == SDL_BUTTON_RIGHT) mouse_button_states_[RIGHT] = true;
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) mouse_button_states_[LEFT] = false;
                if (event.button.button == SDL_BUTTON_MIDDLE) mouse_button_states_[MIDDLE] = false;
                if (event.button.button == SDL_BUTTON_RIGHT) mouse_button_states_[RIGHT] = false;
                break;
            default:
                break;
            }
        }
    }

};

//END
