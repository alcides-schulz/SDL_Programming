#pragma once

#include "SDL.h"

#include <iostream>
#include <vector>
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
    bool mIsRunning = false;
    SDL_Window* mWindow;
    const char *mWindowTitle;
    SDL_Renderer* mRenderer;
    SDL_Keycode mPressedKey = 0;
    std::vector<bool> mMouseButtonStates;
    SDL_Point mMousePosition = { 0,0 };
    int mWindowWidth = 0;
    int mWindowHeight = 0;

    const int FPS = 60;
    const Uint32 MAX_FRAME_TIME = (Uint32)(1000.0f / FPS);

public:
    enum MOUSE_BUTTONS
    {
        LEFT = 0,
        MIDDLE = 1,
        RIGHT = 2
    };

    SDL_Framework()
    {
        mMouseButtonStates.push_back(false);
        mMouseButtonStates.push_back(false);
        mMouseButtonStates.push_back(false);
    }

    virtual bool UserInit() { return true; };
    virtual bool UserRender(int elapsed_time) { if (elapsed_time) return true; return true; };
    virtual void UserClean() {};

    int SDL_Framework::WindowWidth() { return mWindowWidth; }
    int SDL_Framework::WindowHeight() { return mWindowHeight; }
    SDL_Renderer* SDL_Framework::renderer() { return mRenderer; }

    SDL_Keycode PressedKey() { return mPressedKey; }

    SDL_Point MousePosition() { return mMousePosition; }

    bool IsMouseButtonPressed(enum MOUSE_BUTTONS mouse_button) { return mMouseButtonStates[mouse_button]; }

    bool Init(const char* title, int x, int y, int width, int height, int flags)
    {
        int result = SDL_Init(SDL_INIT_EVERYTHING);
        if (result != 0)
        {
            std::cout << "SDL_Init failed, result: " << result << ".\n";
            std::getchar();
            return false;
        }

        mWindowTitle = title;

        mWindow = SDL_CreateWindow(title, x, y, width, height, flags);
        if (mWindow == 0) {
            std::cout << "SDL_CreateWindow failed.\n";
            std::getchar();
            return false;
        }

        SDL_GetWindowSize(mWindow, &mWindowWidth, &mWindowHeight);
        if (mWindowWidth <= 0) mWindowWidth = 1;
        if (mWindowHeight <= 0) mWindowHeight = 1;

        mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
        if (mRenderer == 0) {
            std::cout << "SDL_CreateRenderer failed.\n";
            std::getchar();
            return false;
        }

        mIsRunning = UserInit();

        return mIsRunning;
    }

    void Run()
    {
        Uint32 start_time = SDL_GetTicks();
        Uint32 timer = start_time;
        int frame_count = 0;

        while (mIsRunning) {
            Uint32 frame_start = SDL_GetTicks();
            Uint32 elapsed_time = frame_start - start_time;
            start_time = frame_start;

            HandleEvents();
            if (!UserRender(elapsed_time)) {
                mIsRunning = false;
            }
            SDL_RenderPresent(renderer());

            frame_count++;
            if (SDL_GetTicks() - timer > 1000) {
                std::string t = mWindowTitle;
                t.append(" (");
                t.append(std::to_string(frame_count));
                t.append(" FPS)");
                SDL_SetWindowTitle(mWindow, t.c_str());
                timer += 1000;
                frame_count = 0;
            }

            Uint32 frame_time = SDL_GetTicks() - frame_start;
            if (frame_time < MAX_FRAME_TIME) {
                SDL_Delay((int)(MAX_FRAME_TIME - frame_time));
            }
        }

        UserClean();

        SDL_DestroyWindow(mWindow);
        SDL_DestroyRenderer(mRenderer);
        SDL_Quit();
    }

    void DrawCircle(SDL_Point center, int radius, SDL_Color color, bool fill)
    {
        int radius2 = radius * radius;

        SDL_SetRenderDrawColor(mRenderer, color.r, color.g, color.b, color.a);
        for (int w = 0; w <= radius * 2; w++) {
            for (int h = 0; h <= radius * 2; h++) {
                int dx = radius - w;
                int dy = radius - h;
                int pos = dx * dx + dy * dy;
                if (fill && pos <= radius2) {
                    SDL_RenderDrawPoint(mRenderer, center.x + dx, center.y + dy);
                }
                int diff = pos - radius2;
                if (!fill && abs(diff) <= 10) {
                    SDL_RenderDrawPoint(mRenderer, center.x + dx, center.y + dy);
                }
            }
        }
    }

private:
    void HandleEvents()
    {
        mPressedKey = 0;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYDOWN:
                mPressedKey = event.key.keysym.sym;
                break;
            case SDL_QUIT:
                mIsRunning = false;
                break;
            case SDL_MOUSEMOTION:
                mMousePosition.x = event.motion.x;
                mMousePosition.y = event.motion.y;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) mMouseButtonStates[LEFT] = true;
                if (event.button.button == SDL_BUTTON_MIDDLE) mMouseButtonStates[MIDDLE] = true;
                if (event.button.button == SDL_BUTTON_RIGHT) mMouseButtonStates[RIGHT] = true;
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) mMouseButtonStates[LEFT] = false;
                if (event.button.button == SDL_BUTTON_MIDDLE) mMouseButtonStates[MIDDLE] = false;
                if (event.button.button == SDL_BUTTON_RIGHT) mMouseButtonStates[RIGHT] = false;
                break;
            default:
                break;
            }
        }
    }

};

//END
