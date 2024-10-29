//
// Created by sgsg1 on 2022-11-23.
//

#ifndef GAMETEST_ENDSCREEN_H
#define GAMETEST_ENDSCREEN_H
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "../Buttons/Button.h"

class EndScene: public Scene {
private:
    // Textures
    sf::Texture backgroundTexture;
    sf::Texture buttonTexture;
    sf::Texture buttonClickedTexture;

    sf::Sprite background;

    // Buttons
    Button* playAgainButton;
    Button* quitButton;

    sf::Font font;

    sf::Text congrats;
    sf::Text winner;
    sf::Text playAgain;
    sf::Text quit;
public:
    EndScene();

    enum Action { NONE, PLAY_AGAIN, QUIT };

    Action action = NONE;

    void display(sf::RenderWindow *) override;
    void handleEvents(sf::Event, sf::RenderWindow *) override;
};


#endif //GAMETEST_ENDSCREEN_H
