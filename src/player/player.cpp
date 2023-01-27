#include "player.h"

bool Player::Init(SDL_Renderer* renderer,const Uint8* keyboard_state) {
    KeyboardState = keyboard_state;
    InitAnimation(renderer);
    Velocity = 10;
    return true;
}

void Player::Control(SDL_Event *event) {
    if(event->type == SDL_KEYDOWN || event->type == SDL_KEYUP)
    {
        if (KeyboardState[SDL_SCANCODE_A] && !(KeyboardState[SDL_SCANCODE_D])) {
            CurrentAnimation = Walking_Left;
            CurrentMotion = Walking_Left;
        } else if (!KeyboardState[SDL_SCANCODE_A] && KeyboardState[SDL_SCANCODE_D]) {
            CurrentAnimation = Walking_Right;
            CurrentMotion = Walking_Right;
        } else if (!KeyboardState[SDL_SCANCODE_A] && !KeyboardState[SDL_SCANCODE_D]) {
            switch (CurrentMotion) {
                case Walking_Left:
                    CurrentAnimation = Standing_Left;
                    CurrentMotion = Standing_Left;
                    break;
                case Walking_Right:
                    CurrentAnimation = Standing_Right;
                    CurrentMotion = Standing_Right;
                    break;
            }
        }
    }
}

void Player::Update(int delta_time){
    int distance = (int)((delta_time*1.0/20)*Velocity);
    if (CurrentMotion == Walking_Right){
        SetPosition(Rect.x+distance,Rect.y);
    } else if (CurrentMotion == Walking_Left){
        SetPosition(Rect.x-distance,Rect.y);
    }
}