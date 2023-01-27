#include "scene.h"
#include "../player/reimu.h"

#ifndef THGAME_TITLE_SCENE_H
#define THGAME_TITLE_SCENE_H


class TitleScene: public Scene {
private:
    Reimu reimu;
public:
    bool Init(SDL_Renderer* renderer,const Uint8* keyboard_state, class Font* font) override;

    void OnEvent(SDL_Event* Event) override;

    void Update(int delta_time) override;
};


#endif //THGAME_TITLE_SCENE_H
