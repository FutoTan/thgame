#include "title_scene.h"

bool TitleScene::Init(SDL_Renderer *renderer, const Uint8 *keyboard_state, class Font *font) {
    bool flag = true;

    Player = &reimu;

    flag &= Scene::Init(renderer,keyboard_state,font);

    auto text_style = RenderingText::TextStyle{75,
                                               "unifont.ttf",
                                               {0, 0, 0, 255}};
    RenderingText t;
    t.Init(Renderer,text_style,{50,700});
    t.SetText("Start");
    TextList.push_back(t);
    t.SetPosition(100,800);
    t.SetText("Continue");
    TextList.push_back(t);
    for (auto &text : TextList){
        Font->AddText(&text);
    }
    return flag;
}

void TitleScene::OnEvent(SDL_Event *event) {
    Scene::OnEvent(event);
}

void TitleScene::Update(int delta_time) {
    Scene::Update(delta_time);
}