#include "scene.h"

Scene::Scene() = default;

bool Scene::Init(SDL_Renderer* renderer,const Uint8* keyboard_state, class Font* font) {
    bool flag = true;
    Font = font;
    Renderer = renderer;

    flag &= Player->Init(Renderer, keyboard_state);
    AnimatedSprites.push_back(Player->GetAnimatedSprite());

    return flag;
}

void Scene::OnEvent(SDL_Event *event) {
    Player->Control(event);
}

void Scene::Update(int delta_time) {
    Player->Update(delta_time);
}

void Scene::AnimationUpdate() {
    for (auto sprite : AnimatedSprites)
    {
        if(!&sprite->Visible) continue;
        auto texture = &sprite->Animations[sprite->CurrentAnimation];
        texture->currentFrame = (texture->currentFrame + 1) % texture->count;
    }
}

void Scene::Render() {
    for (auto sprite : AnimatedSprites)
    {
        if(!&sprite->Visible) continue;
        auto texture = &sprite->Animations[sprite->CurrentAnimation];
        SDL_RenderCopyEx(Renderer, texture->texture[texture->currentFrame], nullptr, &sprite->Rect,sprite->Angle,&sprite->Center,texture->flip);
    }
}