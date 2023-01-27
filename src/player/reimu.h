#include "player.h"
#ifndef THGAME_REIMU_H
#define THGAME_REIMU_H


class Reimu: public Player{
public:
    bool Init(SDL_Renderer* renderer,const Uint8* keyboard_state) override;

    void Control(SDL_Event* event) override;

    void Update(int delta_time) override;
};


#endif //THGAME_REIMU_H
