//
// Created by sgsg1 on 2022-11-26.
//

#include "settingsScreen.h"


settingsScreen::settingsScreen(const std::string &fontfile, const std::string &backgroundfile, const std::string &buttonfilesm) {
    background.loadFromFile(backgroundfile);
    buttonsm.loadFromFile(buttonfilesm);
    font.loadFromFile(fontfile);

    spriteBG.setTexture(background);
    spritebs.setTexture(buttonsm);
    settings.setFont(font);
    back.setFont(font);

    settings.setCharacterSize(70);
    back.setCharacterSize(15);
    settings.setFillColor(sf::Color::Black);
    back.setFillColor(sf::Color::Black);
    settings.setString("Settings");
    back.setString("Back");

    spriteBG.setPosition(0,0);
    spritebs.setPosition(-40,950);
    settings.setPosition(455,30);
    back.setPosition(70,1080);


}