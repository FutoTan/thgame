#include "../sprite/animated_sprite.h"

#ifndef THGAME_PLAYER_H
#define THGAME_PLAYER_H


class Player:public AnimatedSprite {

private:
    const Uint8 *KeyboardState = nullptr;

public:
    int Hp = 0;
    int MaxHp = 0;
    enum Motion{Standing_Right,Standing_Left,Walking_Right,Walking_Left};
    int CurrentMotion = Standing_Right;

public:
    virtual bool Init(SDL_Renderer* renderer,const Uint8* keyboard_state);

    virtual void Control(SDL_Event* event);

    virtual void Update(int delta_time);
};


#endif //THGAME_PLAYER_H
