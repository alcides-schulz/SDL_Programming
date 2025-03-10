#include "SDL_Framework.h"

using namespace std;

bool SDL_Framework::Init(const char* title, int x, int y, int width, int height, int flags)
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

    renderer_ = SDL_CreateRenderer(window_, -1, 0);
    if (renderer_ == 0) {
        std::cout << "SDL_CreateRenderer failed.\n";
        std::getchar();
        return false;
    }

    is_running_ = UserInit();

    return is_running_;
}

bool SDL_Framework::Init()
{
    int result = SDL_Init(SDL_INIT_EVERYTHING);
    if (result != 0) {
        std::cout << "SDL_Init failed, result: " << result << ".\n";
        std::getchar();
        return false;
    }
    window_ = SDL_CreateWindow(window_title_, window_x_, window_y_, window_width_, window_height_, window_flags_);
    if (window_ == 0) {
        std::cout << "SDL_CreateWindow failed.\n";
        std::getchar();
        return false;
    }
    SDL_GetWindowSize(window_, &window_width_, &window_height_);
    renderer_ = SDL_CreateRenderer(window_, -1, 0);
    if (renderer_ == 0) {
        std::cout << "SDL_CreateRenderer failed.\n";
        std::getchar();
        return false;
    }
    is_running_ = UserInit();
    return is_running_;
}

void SDL_Framework::Run()
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

void SDL_Framework::DrawCircle(SDL_Point center, int radius, SDL_Color color, bool fill)
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

void SDL_Framework::HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_KEYDOWN:
            {
                auto found = std::find(pressed_keys_.begin(), pressed_keys_.end(), event.key.keysym.sym);
                if (found == pressed_keys_.end()) {
                    pressed_keys_.push_back(event.key.keysym.sym);
                }
            }
            break;
        case SDL_KEYUP:
            pressed_keys_.remove(event.key.keysym.sym);
            break;
        case SDL_QUIT:
            is_running_ = false;
            break;
        case SDL_MOUSEMOTION:
            mouse_position_.x = event.motion.x;
            mouse_position_.y = event.motion.y;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
                mouse_button_states_[kMouseLeftButton] = true;
            if (event.button.button == SDL_BUTTON_MIDDLE)
                mouse_button_states_[kMouseMiddleButton] = true;
            if (event.button.button == SDL_BUTTON_RIGHT)
                mouse_button_states_[kMouseRightButton] = true;
            break;
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT)
                mouse_button_states_[kMouseLeftButton] = false;
            if (event.button.button == SDL_BUTTON_MIDDLE)
                mouse_button_states_[kMouseMiddleButton] = false;
            if (event.button.button == SDL_BUTTON_RIGHT)
                mouse_button_states_[kMouseRightButton] = false;
            break;
        default:
            break;
        }
    }
}

bool SDL_Framework::IsKeyPressed(Sint32 key)
{
    return std::find(pressed_keys_.begin(), pressed_keys_.end(), key) != pressed_keys_.end();
}
    
//END
