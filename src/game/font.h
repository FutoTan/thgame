#include <SDL_ttf.h>
#include "../game/assets.h"
#include "../ui/rendering_text.h"

using namespace std;

#ifndef THGAME_FONT_H
#define THGAME_FONT_H


class Font {

private:
    vector<RenderingText*> RenderingTexts;
    SDL_Renderer* Renderer;

public:
    Font();

    bool Init(SDL_Renderer* renderer);

    bool LoadFont(RenderingText* text_to_render);

    void AddText(RenderingText* text_to_render);

    void Render();
};

#endif //THGAME_FONT_H
