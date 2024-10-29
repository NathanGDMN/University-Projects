//
// Created by Etan Ossip on 2022-11-29.
//

#ifndef FIGHTNFLIGHT_SCENECONTROLLER_H
#define FIGHTNFLIGHT_SCENECONTROLLER_H


#include "Scene.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "EndScene.h"

class SceneController {
private:
    enum SceneType { MENU, GAME, END };

    SceneType currentScene = GAME;

    MenuScene menu;
    GameScene game;
    EndScene end;

    sf::RenderWindow *window;
public:
    explicit SceneController(sf::RenderWindow *);
    Scene *getCurrentScene();

    void update();

    void runGame();
};


#endif //FIGHTNFLIGHT_SCENECONTROLLER_H
