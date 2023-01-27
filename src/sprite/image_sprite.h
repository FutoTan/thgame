#include <SDL_image.h>
#include "sprite.h"
#include "../game/assets.h"

#ifndef THGAME_IMAGE_SPRITE_H
#define THGAME_IMAGE_SPRITE_H


class ImageSprite:public Sprite {
private:
    static ImageSprite Instance;

private:
    SDL_Renderer* Renderer;

    typedef struct {
        SDL_Texture* texture;
        SDL_RendererFlip flip;
    } ImageTexture;

public:
    ImageTexture* Image;

public:
    ImageSprite();
    void InitImage(SDL_Renderer* renderer);
    bool LoadImage(const string& name);
    bool LoadImage(const string& name,SDL_RendererFlip flip);

    ImageSprite* GetImageSprite();
};


#endif //THGAME_IMAGE_SPRITE_H
