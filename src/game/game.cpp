#include "game.h"

using namespace std;

Game Game::Instance;

Game::Game() = default;

bool Game::Init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"SDL_Init error: %s",SDL_GetError());
        return false;
    }

    if (TTF_Init() < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"TTF_Init error: %s",SDL_GetError());
        return false;
    }

    Window = SDL_CreateWindow("TH19", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH,
                              HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    if (Window == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"SDL_CreateWindow error: %s",SDL_GetError());
        return false;
    }

    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if (Renderer == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"SDL_CreateRenderer error: %s",SDL_GetError());
        return false;
    }

    if (!Assets::GetInstance()->GetAssetsList()) return false;

    if (!Font.Init(Renderer)) return false;

    if (!FPSText.Init(Renderer,
                      RenderingText::TextStyle{45,
                                               "unifont.ttf",
                                               {0, 0, 0, 255}},
                      {10, 10})) return false;
    Font.AddText(&FPSText);

    Scene = &title_scene;

    if (!Scene->Init(Renderer,KeyboardState,&Font)) return false;

    return true;
}

void Game::OnEvent(SDL_Event* event) {
    switch (event->type) {
        case SDL_QUIT:
            Running = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            int x = event->button.x;
            int y = event->button.y;
            SDL_Log("(%d,%d) %d",x,y,event->button.button);
            break;
    }
    Scene->OnEvent(event);
}

void Game::Update(int delta_time) {
    Scene->Update(delta_time);
}

void Game::AnimationUpdate() {
    Uint32 last_tick = 0;
    int limitedFPS = 8;
    int delta_time;
    while (Running) {
        delta_time = (int)(SDL_GetTicks()-last_tick);

        Scene->AnimationUpdate();

        last_tick=SDL_GetTicks();
        if(delta_time<1000/limitedFPS){
            SDL_Delay(1000/limitedFPS-delta_time);
        }
    }
}

void Game::Render(SDL_Renderer* renderer) {
    Uint32 last_tick = 0;

    int counted_frame=0;
    int FPS_timer=0;

    while (Running) {
        counted_frame++;
        FPS_timer+=(int)(SDL_GetTicks()-last_tick);
        if(FPS_timer>1000){
            char buf[11];
            double t = counted_frame*1.0/(FPS_timer*1.0/1000);
            snprintf(buf, 11, "FPS:%.1f", t);
            FPSText.SetText(buf);
            FPS_timer=counted_frame=0;
        }

        Update((int)(SDL_GetTicks()-last_tick));

        last_tick=SDL_GetTicks();

        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
        Scene->Render();
        Font.Render();
        SDL_RenderPresent(renderer);
    }
}

void Game::Cleanup() {
    if (Renderer) {
        SDL_DestroyRenderer(Renderer);
        Renderer = nullptr;
    }
    if (Window) {
        SDL_DestroyWindow(Window);
        Window = nullptr;
    }

    SDL_Quit();

    Assets::GetInstance()->CleanUp();

    cout << "Quit!" << endl;
}

int Game::Execute(int argc, char** argv) {
    if (!Init()) {
        return 1;
    }

    SDL_Event event;

    AnimationUpdateThread = thread([this]{AnimationUpdate();});
    RenderThread = thread([this]{Render(Renderer);});

    while (SDL_WaitEvent(&event)) {
        OnEvent(&event);
        if(!Running)break;
    }

    AnimationUpdateThread.join();
    RenderThread.join();

    SDL_PushEvent(&event);

    Cleanup();
    return 0;
}

Game* Game::GetInstance() {
    return &Game::Instance;
}

int Game::GetWindowWidth() {
    return WIDTH;
}

int Game::GetWindowHeight() {
    return HEIGHT;
}