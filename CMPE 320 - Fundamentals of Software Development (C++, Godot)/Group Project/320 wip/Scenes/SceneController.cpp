//
// Created by Etan Ossip on 2022-11-29.
//

#include "SceneController.h"

SceneController::SceneController(sf::RenderWindow *renderWindow) : game(renderWindow) {
    this->window = renderWindow;
}

Scene *SceneController::getCurrentScene() {
    switch (currentScene) {
        case MENU:
            return reinterpret_cast<Scene *>(&menu);
        case GAME:
            return reinterpret_cast<Scene *>(&game);
        case END:
            return reinterpret_cast<Scene *>(&end);
    }
}

void SceneController::update() {
    getCurrentScene()->update(window);

    switch (currentScene) {
        case MENU:
            return;
        case GAME:
            if (game.isOver()) currentScene = END;
            return;
        case END:
            switch (end.action) {
                case EndScene::NONE:
                    return;
                case EndScene::PLAY_AGAIN:
                    game.reset(window);
                    currentScene = GAME;
                    end.action = EndScene::NONE;
                    return;
                case EndScene::QUIT:
                    window->close();
                    return;
            }
            return;
    }
}

void SceneController::runGame() {
    while (window->isOpen()) {
        sf::Event event;

        while(window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }

            getCurrentScene()->handleEvents(event, window);
        }

        window->clear();

        update();
        getCurrentScene()->display(window);
        window->display();
    }
}