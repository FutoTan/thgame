#include <iostream>
#include <thread>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "assets.h"
#include "../scene/title_scene.h"
#include "font.h"

#ifndef THGAME_GAME_H
#define THGAME_GAME_H

class Game {
private:
    static Game Instance;

    bool Running = true;
    SDL_Window* Window = nullptr;
    SDL_Renderer* Renderer = nullptr;

    Scene* Scene;

    TitleScene title_scene;

    Font Font;

    const Uint8* KeyboardState = SDL_GetKeyboardState(nullptr);

    RenderingText FPSText;

    thread AnimationUpdateThread;
    thread RenderThread;

    const int WIDTH = 800;
    const int HEIGHT = 600;

private:
    Game();

    void OnEvent(SDL_Event* event);

    bool Init();

    void Update(int delta_time);

    void AnimationUpdate();

    void Render(SDL_Renderer *renderer);

    void Cleanup();

public:
    int Execute(int argc, char* argv[]);

public:
    static Game* GetInstance();

    int GetWindowWidth();

    int GetWindowHeight();

};
#endif