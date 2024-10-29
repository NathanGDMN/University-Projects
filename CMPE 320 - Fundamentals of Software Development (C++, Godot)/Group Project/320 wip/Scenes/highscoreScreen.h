//
// Created by sgsg1 on 2022-11-23.
//

#ifndef GAMETEST_HIGHSCORESCREEN_H
#define GAMETEST_HIGHSCORESCREEN_H
#include "SFML/Graphics.hpp"

class highscoreScreen {
public:
    highscoreScreen(const std::string &fontfile, const std::string &backgroundfile, const std::string &buttonfilesm);
    sf::Texture background;
    sf::Texture buttonsm;

    sf::Sprite spriteBG;
    sf::Sprite spritebs;

    sf::Font font;

    sf::Text highscore;
    sf::Text back;


};


#endif //GAMETEST_HIGHSCORESCREEN_H
