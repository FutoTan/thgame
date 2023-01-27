#include "animated_sprite.h"

using namespace std;

AnimatedSprite::AnimatedSprite() : Sprite() {
    Visible = true;
    Scale = 5;
    SetPosition(10,10);
};

void AnimatedSprite::InitAnimation(SDL_Renderer* renderer) {
    Renderer = renderer;
}

bool AnimatedSprite::LoadAnimation(const string& name){
    return LoadAnimation(name,SDL_FLIP_NONE);
}

bool AnimatedSprite::LoadAnimation(const string& name,SDL_RendererFlip flip){
    SDL_RWops* rw = Assets::GetInstance()->GetAsset(name);
    IMG_Animation* anim = IMG_LoadGIFAnimation_RW(rw);
    if (!anim) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Couldn't load %s: %s\n", name.c_str(), SDL_GetError());
        return false;
    }
    SetBox(anim->w,anim->h);
    LoadAnimationTexture(anim,flip);
    SDL_FreeRW(rw);
    IMG_FreeAnimation(anim);
    return true;
}

bool AnimatedSprite::LoadAnimationTexture(IMG_Animation* anim,SDL_RendererFlip flip){
    SDL_Texture** texture = (SDL_Texture **)SDL_calloc(anim->count, sizeof(*texture));
    if (!texture) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Couldn't allocate textures\n");
        IMG_FreeAnimation(anim);
        return false;
    }
    for (int j = 0; j < anim->count; j++) {
        texture[j] = SDL_CreateTextureFromSurface(Renderer, anim->frames[j]);
    }
    auto animation_texture = AnimationTexture{texture,0,anim->count,flip};
    Animations.push_back(animation_texture);
    return true;
}

AnimatedSprite* AnimatedSprite::GetAnimatedSprite() {
    return this;
}