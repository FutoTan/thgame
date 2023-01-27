#include "font.h"

Font::Font() = default;

bool Font::Init(SDL_Renderer *renderer) {
    Renderer = renderer;
    return true;
}

void Font::AddText(RenderingText *text_to_render) {
    RenderingTexts.push_back(text_to_render);
}

void Font::Render() {
    for (auto text_to_render : RenderingTexts)
    {
        if (!text_to_render->Enabled) continue;
        SDL_RenderCopy(Renderer, text_to_render->Texture, nullptr,&text_to_render->Rect);
    }
}