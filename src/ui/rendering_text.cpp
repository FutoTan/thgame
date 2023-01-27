#include "rendering_text.h"

#include <utility>

RenderingText::RenderingText() = default;

bool RenderingText::Init(SDL_Renderer *renderer, RenderingText::TextStyle style, SDL_Point position,
                         const std::string &text) {
    bool flag = true;
    Renderer = renderer;
    Style = std::move(style);
    Position = position;
    Enabled = true;
    flag &= LoadFont();
    flag &= SetText(text);
    return flag;
}

bool RenderingText::LoadFont() {
    SDL_RWops* rw = Assets::GetInstance()->GetAsset("/font/"+Style.fontName);
    TTF_Font* font = TTF_OpenFontRW(rw,true,Style.fontSize);
    if (!font)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Couldn't load %s: %s\n",
                     ("/font/"+Style.fontName).c_str(),TTF_GetError());
        return false;
    }
    Font = font;
    return true;
}

bool RenderingText::SetText(string text) {
    Text = std::move(text);
    return RenderText();
}

bool RenderingText::RenderText() {
    SDL_Surface *text_surface;

    text_surface = TTF_RenderUTF8_Solid(Font, Text.c_str(), Style.color);

    if (!text_surface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Rendering Text error: %s",TTF_GetError());
        return false;
    }

    SDL_Texture* text_texture;
    text_texture = SDL_CreateTextureFromSurface(Renderer, text_surface);
    if (!text_texture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Rendering Text error: %s",SDL_GetError());
        return false;
    }
    SDL_Rect dest = {Position.x, Position.y, text_surface->w, text_surface->h};
    Texture = text_texture;
    Rect = dest;

    SDL_FreeSurface(text_surface);
    return true;
}

void RenderingText::SetPosition(int x, int y) {
    Position = {x,y};
}