#include "image_sprite.h"

using namespace std;

ImageSprite::ImageSprite() {
    Visible = true;
    Scale = 5;
    SetPosition(10,10);
};

void ImageSprite::InitImage(SDL_Renderer *renderer) {
    Renderer = renderer;
}

bool ImageSprite::LoadImage(const std::string &name) {
    return LoadImage(name,SDL_FLIP_NONE);
}

bool ImageSprite::LoadImage(const string& name,SDL_RendererFlip flip) {
    SDL_RWops* rw = Assets::GetInstance()->GetAsset(name);
    SDL_Surface * img = IMG_LoadPNG_RW(rw);
    if (!img) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Couldn't load %s: %s\n", name.c_str(), SDL_GetError());
        return false;
    }
    SetBox(img->w,img->h);
    SDL_Texture** texture = (SDL_Texture **)SDL_calloc(1, sizeof(*texture));
    if (!texture) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Couldn't allocate textures\n");
        SDL_FreeSurface(img);
        return false;
    }
    Image->texture = SDL_CreateTextureFromSurface(Renderer, img);
    Image->flip = flip;
    SDL_FreeRW(rw);
    SDL_FreeSurface(img);
    return true;
}

ImageSprite* ImageSprite::GetImageSprite() {
    return this;
}