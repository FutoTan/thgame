#include <SDL_ttf.h>
#include <string>
#include "../game/assets.h"

using namespace std;

#ifndef THGAME_RENDERING_TEXT_H
#define THGAME_RENDERING_TEXT_H


class RenderingText {
private:
    SDL_Renderer* Renderer;
public:
    typedef struct {
        int fontSize;
        string fontName;
        SDL_Color color;
    } TextStyle;

    SDL_Point Position{};

    TextStyle Style;
    string Text;
    bool Enabled = false;

    TTF_Font* Font{};
    SDL_Texture* Texture{};
    SDL_Rect Rect{};

public:

    RenderingText();

    bool Init(SDL_Renderer* renderer,TextStyle style,SDL_Point position,const string& text = "Loading");

    bool SetText(string text);

    bool LoadFont();

    bool RenderText();

    void SetPosition(int x, int y);
};


#endif //THGAME_RENDERING_TEXT_H
