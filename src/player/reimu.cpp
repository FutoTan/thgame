#include "reimu.h"

bool Reimu::Init(SDL_Renderer *renderer, const Uint8 *keyboard_state) {
    bool flag = true;
    flag &= Player::Init(renderer,keyboard_state);
    flag &= LoadAnimation("/sprite/reimu/stand.gif");
    flag &= LoadAnimation("/sprite/reimu/stand.gif",SDL_FLIP_HORIZONTAL);
    flag &= LoadAnimation("/sprite/reimu/walk.gif");
    flag &= LoadAnimation("/sprite/reimu/walk.gif",SDL_FLIP_HORIZONTAL);
    return flag;
}

void Reimu::Control(SDL_Event *event) {
    Player::Control(event);
}

void Reimu::Update(int delta_time) {
    Player::Update(delta_time);
}