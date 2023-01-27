#include <SDL.h>

#ifndef THGAME_SPRITE_H
#define THGAME_SPRITE_H


class Sprite{
public:
    SDL_Rect Rect{0,0,0,0};
    int Scale = 1;
    double Angle = 0;
    SDL_Point Center{0,0};
    int Velocity = 0;
    unsigned char Opacity = 255;
    bool Visible = false;
public:
    Sprite();

    void SetBox(int width,int height);

    void SetPosition(int x, int y);
};


#endif
