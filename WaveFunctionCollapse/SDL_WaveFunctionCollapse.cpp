#include "../SDL_Framework.h"

#include <filesystem>

//namespace fs = std::filesystem;

class Image
{
public:
    string          filename;
    SDL_Surface     *surface;
    SDL_Texture     *texture;
    int             rotation; // 0, 90, 180, 270
    vector<Image *> top_images;
    vector<Image *> down_images;
    vector<Image *> right_images;
    vector<Image *> left_images;
};

class Tile
{
public:
    int             row;
    int             col;
    Image           *image = nullptr;
    vector<Image *> options;
    Tile            *top_tile = nullptr;
    Tile            *right_tile = nullptr;
    Tile            *bottom_tile = nullptr;
    Tile            *left_tile = nullptr;
    int             reductions;

    Tile(int row, int col, vector<Image *>& images) : row(row), col(col)
    {
        options.insert(options.begin(), images.begin(), images.end());
        reductions = (int)options.size();
    }

    void Collapse(Image *to_image)
    {
        image = to_image;
        options.clear();
        reductions = INT_MAX;
    }

    bool IsCollapsed()
    {
        return image != nullptr;
    }

};

class SDL_WaveFunctionCollapse : public SDL_Framework
{
private:
    int                 kTileWidth = 20;
    int                 kTileHeight = 20;
    int                 kTileRows;
    int                 kTileColumns;
    int                 kTotalOptions;
    int                 kUpdateTimeMs = 25;

    string              folder_name_;
    vector<Image *>     all_images_;
    vector<Tile *>      all_tiles_;

    bool                debug_images_ = false;
    int                 current_index_ = 0;
    Uint32              start_time_ = 0;

public:

    SDL_WaveFunctionCollapse(string pFolderName) : SDL_Framework()
    {
        folder_name_ = pFolderName;
        srand((unsigned int)time(nullptr));
    }

    bool UserInit() override
    {
        if (IMG_Init(IMG_INIT_PNG) < 0) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL_image: %s", IMG_GetError());
            return false;
        }
        
        LoadImagesFromFolder();

        GenerateImageOptions();

        kTileColumns = WindowWidth() / kTileWidth;
        kTileRows = WindowHeight() / kTileHeight;

        kTotalOptions = (int)all_images_.size();

        cout << "TileWidth: " << kTileWidth << " TitleHeight: " << kTileHeight << endl;
        cout << "TileRows: " << kTileRows << " TitleColumns: " << kTileColumns << endl;

        CreateTiles();

        start_time_ = SDL_GetTicks();

        return true;
    }

    void CreateTiles()
    {
        all_tiles_.clear();
        for (int row = 0; row < kTileRows; row++) {
            for (int col = 0; col < kTileColumns; col++) {
                all_tiles_.push_back(new Tile(row, col, all_images_));
            }
        }
        for (int row = 0; row < kTileRows; row++) {
            for (int col = 0; col < kTileColumns; col++) {
                auto tile = all_tiles_[row * kTileColumns + col];
                if (row > 0) {
                    tile->top_tile = all_tiles_[(row - 1) * kTileColumns + col];
                }
                if (row < kTileRows - 1) {
                    tile->bottom_tile = all_tiles_[(row + 1) * kTileColumns + col];
                }
                if (col > 0) {
                    tile->left_tile = all_tiles_[row * kTileColumns + col - 1];
                }
                if (col < kTileColumns - 1) {
                    tile->right_tile = all_tiles_[row * kTileColumns + col + 1];
                }
            }
        }
    }

    bool UserRender(int elapsed_time) override
    {
        SDL_SetRenderDrawColor(Renderer(), 0, 0, 0, 0); // black color_
        SDL_RenderClear(Renderer());

        if (debug_images_) {
            DrawDebug();
        }
        else {
            DrawTiles();
            UpdateTiles();
        }

        if (PressedKey() == SDLK_d) {
            debug_images_ = !debug_images_;
        }

        return true;
    }

    void DrawTiles()
    {
        SDL_SetRenderDrawColor(Renderer(), 255, 255, 255, 0);

        for each (auto tile in all_tiles_)
        {
            if (tile->image != NULL) {
                ShowImage(tile->row, tile->col, tile->image);
            }
        }
    }

    void UpdateTiles()
    {
        if (!IsUpdateTime()) {
            return;
        }
        Tile *selected = GetTileWithFewestOptions();
        if (selected == nullptr) {
            return; // done
        }
        if (!selected->options.size()) {
            Backtrack(selected);
        }
        else {
            selected->Collapse(selected->options[rand() % selected->options.size()]);
            Propagate(selected);
        }
    }

    void Propagate(Tile *tile)
    {
        if (tile->top_tile != nullptr && !tile->top_tile->IsCollapsed()) {
            ReduceTile(tile->top_tile);
        }
        if (tile->right_tile != nullptr && !tile->right_tile->IsCollapsed()) {
            ReduceTile(tile->right_tile);
        }
        if (tile->bottom_tile != nullptr && !tile->bottom_tile->IsCollapsed()) {
            ReduceTile(tile->bottom_tile);
        }
        if (tile->left_tile != nullptr && !tile->left_tile->IsCollapsed()) {
            ReduceTile(tile->left_tile);
        }
    }

    void ReduceTile(Tile *tile) 
    {
        tile->options.clear();
        tile->options.insert(tile->options.begin(), all_images_.begin(), all_images_.end());
        if (tile->top_tile != nullptr && tile->top_tile->IsCollapsed()) {
            ReduceOptions(tile, tile->top_tile->image->down_images);
        }
        if (tile->right_tile != nullptr && tile->right_tile->IsCollapsed()) {
            ReduceOptions(tile, tile->right_tile->image->left_images);
        }
        if (tile->bottom_tile != nullptr && tile->bottom_tile->IsCollapsed()) {
            ReduceOptions(tile, tile->bottom_tile->image->top_images);
        }
        if (tile->left_tile != nullptr && tile->left_tile->IsCollapsed()) {
            ReduceOptions(tile, tile->left_tile->image->right_images);
        }
        tile->reductions = (int)tile->options.size();
    }

    void ReduceOptions(Tile *tile, vector<Image *>& options)
    {
        vector<Image *> to_delete;
        for each (auto image in tile->options) {
            auto found = std::find(options.begin(), options.end(), image);
            if (found == options.end()) {
                to_delete.push_back(image);
            }
        }
        for each (auto image in to_delete) {
            auto found = std::find(tile->options.begin(), tile->options.end(), image);
            tile->options.erase(found);
        }
    }

    void Backtrack(Tile *tile)
    {
        Undo(tile->top_tile);
        Undo(tile->right_tile);
        Undo(tile->bottom_tile);
        Undo(tile->left_tile);
        Undo(tile);
        ReduceTile(tile);
    }

    void Undo(Tile *tile)
    {
        if (tile == nullptr || !tile->IsCollapsed()) { return; }
        tile->image = nullptr;
        tile->options.insert(tile->options.begin(), all_images_.begin(), all_images_.end());
        tile->reductions = (int)tile->options.size();
    }

    Tile *GetTileWithFewestOptions()
    {
        int min_reductions = kTotalOptions + 1;
        vector<Tile *> fewest_options;
        for each (auto tile in all_tiles_) {
            if (tile->image != nullptr) {
                continue;
            }
            if (tile->reductions < min_reductions) {
                min_reductions = tile->reductions;
                fewest_options.clear();
            }
            if (tile->reductions == min_reductions) {
                fewest_options.push_back(tile);
            }
        }
        if (fewest_options.size() == 0) {
            return nullptr;
        }
        return fewest_options[rand() % fewest_options.size()];
    }

    bool IsUpdateTime()
    {
        Uint32 current_time = SDL_GetTicks();
        if (current_time < start_time_ + kUpdateTimeMs) {
            return false;
        }
        start_time_ = current_time;
        return true;
    }

    void DrawDebug()
    {
        auto image = all_images_[current_index_];

        int row = 0;
        int col = 0;
        for each (auto option in image->top_images)
        {
            ShowImage(row, col, option);
            ShowImage(row + 1, col, image);
            col += 2;
            if (col >= kTileColumns - 2) {
                col = 0;
                row += 3;
            }
        }
        col = 0;
        row += 3;
        for each (auto option in image->down_images)
        {
            ShowImage(row, col, image);
            ShowImage(row + 1, col, option);
            col += 2;
            if (col >= kTileColumns - 2) {
                col = 0;
                row += 3;
            }
        }

        col = 0;
        row += 3;
        for each (auto option in image->right_images)
        {
            ShowImage(row, col, image);
            ShowImage(row, col + 1, option);
            col += 3;
            if (col >= kTileColumns - 3) {
                col = 0;
                row += 3;
            }
        }

        col = 0;
        row += 3;
        for each (auto option in image->left_images)
        {
            ShowImage(row, col, option);
            ShowImage(row, col + 1, image);
            col += 3;
            if (col >= kTileColumns - 3) {
                col = 0;
                row += 3;
            }
        }

        if (PressedKey() == SDLK_n) {
            if (current_index_ < all_images_.size() - 1) {
                current_index_++;
            }
        }
        if (PressedKey() == SDLK_p) {
            if (current_index_ > 0) {
                current_index_--;
            }
        }
    }

    void ShowImage(int row, int col, Image *image)
    {
        SDL_Rect r = { col * kTileWidth, row * kTileHeight, kTileWidth, kTileHeight };
        SDL_RenderCopy(Renderer(), image->texture, NULL, &r);
    }

    SDL_Surface* RotateSurface(SDL_Surface* surface)
    {
        SDL_Surface* rotated = SDL_CreateRGBSurface(0, surface->w, surface->h, surface->format->BitsPerPixel,
            surface->format->Rmask,
            surface->format->Gmask,
            surface->format->Bmask,
            surface->format->Amask);
        if (!rotated) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create rotated surface: %s", SDL_GetError());
            return nullptr;
        }
        for (int y = 0; y < surface->h; y++) {
            for (int x = 0; x < surface->w; x++) {
                int newx = surface->h - 1 - y;
                int newy = x;
                Uint8 *source_index = (Uint8*)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel;
                Uint8 *target_index = (Uint8*)rotated->pixels + newy * rotated->pitch + newx * rotated->format->BytesPerPixel;
                for (int i = 0; i < surface->format->BytesPerPixel; i++) {
                    *target_index++ = *source_index++;
                }
            }
        }
        return rotated;
    }

    void GenerateImageOptions()
    {
        float match_percent = 100;
        for each (auto image in all_images_)
        {
            for each (auto option in all_images_)
            {
                if (image->filename.find("03") != string::npos && option->filename.find("03") != string::npos) { continue; }
                if (image->filename.find("03") != string::npos && option->filename.find("03") != string::npos) { continue; }
                if (image->filename.find("12") != string::npos && option->filename.find("12") != string::npos) { continue; }
                if (image->filename.find("01") != string::npos && option->filename.find("01") != string::npos) { continue; }
                if (IsRestriction(image, option, "02")) { continue; }
                if (IsRestriction(image, option, "17")) { continue; }
                if (IsRestriction(image->filename, option->filename, "13", "13", "14", "16", "18")) { continue; }
                if (IsRestriction(image->filename, option->filename, "14", "13", "14", "16", "18")) { continue; }
                if (IsRestriction(image->filename, option->filename, "16", "13", "14", "16", "18")) { continue; }
                if (IsRestriction(image->filename, option->filename, "18", "13", "14", "16", "18")) { continue; }

                if (LineMatchPercent(image->surface, option->surface, image->surface->h - 1, 0) >= match_percent) {
                    image->down_images.push_back(option);
                }
                if (LineMatchPercent(image->surface, option->surface, 0, image->surface->h - 1) >= match_percent) {
                    image->top_images.push_back(option);
                }
                if (ColumnMatchPercent(image->surface, option->surface, image->surface->w - 1, 0) >= match_percent) {
                    image->right_images.push_back(option);
                }
                if (ColumnMatchPercent(image->surface, option->surface, 0, image->surface->w - 1) >= match_percent) {
                    image->left_images.push_back(option);
                }
            }
        }
    }

    bool IsRestriction(Image *image, Image *option, string id)
    {
        if (image->filename.find(id) != string::npos && option->filename.find(id) != string::npos) {
            if (image->rotation == 0 && option->rotation == 180) { return true; }
            if (image->rotation == 90 && option->rotation == 270) { return true; }
            if (image->rotation == 180 && option->rotation == 0) { return true; }
            if (image->rotation == 270 && option->rotation == 90) { return true; }
        }
        return false;
    }

    bool IsRestriction(string image_name, string option_name, string id, string o1, string o2, string o3, string o4)
    {
        if (image_name.find(id) != string::npos) {
            if (option_name.find(o1) != string::npos) { return true; }
            if (option_name.find(o2) != string::npos) { return true; }
            if (option_name.find(o3) != string::npos) { return true; }
            if (option_name.find(o4) != string::npos) { return true; }
        }
        return false;
    }

    float LineMatchPercent(SDL_Surface *surface1, SDL_Surface *surface2, int y1, int y2)
    {
        float match_count = 0;
        float pixel_count = 0;
        for (int x = 0; x < surface1->w; x++)
        {
            Uint8 *source_index = (Uint8*)surface1->pixels + y1 * surface1->pitch + x * surface1->format->BytesPerPixel;
            Uint8 *target_index = (Uint8*)surface2->pixels + y2 * surface2->pitch + x * surface2->format->BytesPerPixel;
            for (int i = 0; i < surface1->format->BytesPerPixel; i++) {
                pixel_count++;
                if (*target_index++ == *source_index++) {
                    match_count++;
                }
            }
        }
        float percent = match_count / pixel_count * 100;
        return percent;
    }

    float ColumnMatchPercent(SDL_Surface *surface1, SDL_Surface *surface2, int x1, int x2)
    {
        float match_count = 0;
        float pixel_count = 0;
        for (int y = 0; y < surface1->h; y++)
        {
            Uint8 *source_index = (Uint8*)surface1->pixels + y * surface1->pitch + x1 * surface1->format->BytesPerPixel;
            Uint8 *target_index = (Uint8*)surface2->pixels + y * surface2->pitch + x2 * surface2->format->BytesPerPixel;
            for (int i = 0; i < surface1->format->BytesPerPixel; i++) {
                pixel_count++;
                if (*target_index++ == *source_index++) {
                    match_count++;
                }
            }
        }
        float percent = match_count / pixel_count * 100;
        return percent;
    }

    bool LoadImagesFromFolder()
    {
        int image_width = 0;
        int image_height = 0;
        
        all_images_.clear();

        for (const auto & entry : std::filesystem::directory_iterator(folder_name_))
        {
            auto image = new Image();
            image->filename = entry.path().string();
            image->surface = IMG_Load(image->filename.c_str());
            if (!image->surface) {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load image %s, error: %s", image->filename, IMG_GetError());
                return false;
            }
            image->texture = SDL_CreateTextureFromSurface(Renderer(), image->surface);
            if (!image->texture) {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't texture from image %s, error: %s", image->filename, IMG_GetError());
                return false;
            }
            // validate all images have the same width/height
            if (image_width == 0) {
                image_width = image->surface->w;
                image_height = image->surface->h;
            }
            if (image_width != image->surface->w || image_height != image->surface->h) {
                cout << "Image Width " << image_width << endl;
                cout << "Image Height " << image_height << endl;
                cout << "Image " << image->filename << " does not have the same dimensions: ";
                cout << "(" << image->surface->w << ", " << image->surface->h << ")" << endl;
                return false;
            }
            // Add each image and a copy for each possible rotation
            image->rotation = 0;
            all_images_.push_back(image);
            SDL_Surface *previous_surface = image->surface;
            for (int rotation = 90; rotation <= 270; rotation += 90) {
                auto rotated_image = new Image();
                rotated_image->filename = image->filename;
                rotated_image->surface = RotateSurface(previous_surface);
                if (!rotated_image->surface) {
                    return false;
                }
                rotated_image->texture = SDL_CreateTextureFromSurface(Renderer(), rotated_image->surface);
                if (!rotated_image->texture) {
                    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't texture from image %s, error: %s", image->filename, IMG_GetError());
                    return false;
                }
                rotated_image->rotation = rotation;
                all_images_.push_back(rotated_image);
                previous_surface = rotated_image->surface;
            }
        }
        cout << "all images size: " << all_images_.size() << endl;
        return true;
    }
};

void RunWaveFunctionCollapse(void)
{
    SDL_WaveFunctionCollapse wfc("Images\\Circuit");
    if (wfc.Init("Wave Function Collapse", 400, 100, 1200, 800, 0)) {
        wfc.Run();
    }
}


