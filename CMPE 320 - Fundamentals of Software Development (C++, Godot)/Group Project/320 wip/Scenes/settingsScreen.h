//
// Created by sgsg1 on 2022-11-26.
//

#ifndef GAMETEST_SETTINGSSCREEN_H
#define GAMETEST_SETTINGSSCREEN_H
#include <SFML/Graphics.hpp>


class settingsScreen {
public:
    settingsScreen(const std::string &fontfile, const std::string &backgroundfile, const std::string &buttonfilesm);
    sf::Texture background;
    sf::Texture buttonsm;

    sf::Sprite spriteBG;
    sf::Sprite spritebs;

    sf::Font font;

    sf::Text settings;
    sf::Text back;


};


#endif //GAMETEST_SETTINGSSCREEN_H
