#include <SDL_image.h>
#include "sprite.h"
#include "../game/assets.h"

#ifndef THGAME_ANIMATED_SPRITE_H
#define THGAME_ANIMATED_SPRITE_H

class AnimatedSprite:public Sprite{

private:
    SDL_Renderer* Renderer;

    typedef struct {
        SDL_Texture** texture;
        int currentFrame;
        int count;
        SDL_RendererFlip flip;
        bool enabled;
    } AnimationTexture;

public:
    vector<AnimationTexture> Animations;
    int CurrentAnimation = 0;

public:
    AnimatedSprite();
    void InitAnimation(SDL_Renderer* renderer);
    bool LoadAnimation(const string& name);
    bool LoadAnimation(const string& name,SDL_RendererFlip flip);
    bool LoadAnimationTexture(IMG_Animation* anim,SDL_RendererFlip flip);

    AnimatedSprite* GetAnimatedSprite();
};

#endif //THGAME_Sprite_H
