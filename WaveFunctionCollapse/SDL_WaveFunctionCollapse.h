#ifndef SDL_WAVE_FUNCTION_COLLAPSE_H
#define SDL_WAVE_FUNCTION_COLLAPSE_H

#include "../SDL_Framework.h"

#include <filesystem>

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
public:
    SDL_WaveFunctionCollapse(string pFolderName) :
        SDL_Framework("Wave Function Collapse", 400, 100, 1200, 800, 0)
    {
        folder_name_ = pFolderName;
    }

    bool UserInit() override;
    void CreateTiles();
    bool UserRender(int elapsed_time) override;
    void DrawTiles();
    void UpdateTiles();
    void Propagate(Tile *tile);
    void ReduceTile(Tile *tile);
    void ReduceOptions(Tile *tile, vector<Image *>& options);
    void Backtrack(Tile *tile);
    void Undo(Tile *tile);
    Tile *GetTileWithFewestOptions();
    bool IsUpdateTime();
    void DrawDebug();
    void ShowImage(int row, int col, Image *image);
    SDL_Surface* RotateSurface(SDL_Surface* surface);
    void GenerateImageOptions();
    bool IsRestriction(Image *image, Image *option, string id);
    bool IsRestriction(string image_name, string option_name, string id, string o1, string o2, string o3, string o4);
    float LineMatchPercent(SDL_Surface *surface1, SDL_Surface *surface2, int y1, int y2);
    float ColumnMatchPercent(SDL_Surface *surface1, SDL_Surface *surface2, int x1, int x2);
    bool LoadImagesFromFolder();
private:
    int             kTileWidth = 20;
    int             kTileHeight = 20;
    int             kTileRows;
    int             kTileColumns;
    int             kTotalOptions;
    int             kUpdateTimeMs = 25;
    string          folder_name_;
    vector<Image *> all_images_;
    vector<Tile *>  all_tiles_;
    bool            debug_images_ = false;
    int             current_index_ = 0;
    Uint32          start_time_ = 0;
};

#endif
