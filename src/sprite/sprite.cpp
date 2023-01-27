#include "sprite.h"

Sprite::Sprite() = default;

void Sprite::SetBox(int width, int height) {
    Rect.w = width*Scale;
    Rect.h = height*Scale;
}

void Sprite::SetPosition(int x, int y) {
    Rect.x = x;
    Rect.y = y;
    Center = {x+Rect.w/2,y+Rect.h/2};
}