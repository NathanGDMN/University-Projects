//
// Created by sgsg1 on 2022-11-21.
//

#ifndef GAMETEST_MAINSCREEN_H
#define GAMETEST_MAINSCREEN_H
#include <string>
#include <SFML/Graphics.hpp>
#include "Scene.h"

class MenuScene: public Scene {
private:
    sf::Texture backgroundTexture;
    sf::Texture button;
    sf::Texture buttonsmall;

    sf::Sprite background;
    sf::Sprite spriteb1;
    sf::Sprite spriteb2;
    sf::Sprite spriteb3;
    sf::Sprite spritebs;

    sf::Font font;

    sf::Text title;
    sf::Text quit;
    sf::Text newgame;
    sf::Text highscore;
    sf::Text settings;
public:
    MenuScene();
};


#endif //GAMETEST_MAINSCREEN_H
