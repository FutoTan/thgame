#include "../sprite/animated_sprite.h"
#include "../player/player.h"
#include "../ui/rendering_text.h"
#include "../game/font.h"

#ifndef THGAME_SCENE_H
#define THGAME_SCENE_H


class Scene {

public:

    SDL_Renderer* Renderer;

    Font* Font;

    vector<RenderingText> TextList;

    Player* Player;

    vector<AnimatedSprite*> AnimatedSprites;

public:

    Scene();

    virtual bool Init(SDL_Renderer* renderer,const Uint8* keyboard_state, class Font* font);

    virtual void OnEvent(SDL_Event* event);

    virtual void Update(int delta_time);

    void AnimationUpdate();

    void Render();

};


#endif //THGAME_SCENE_H
