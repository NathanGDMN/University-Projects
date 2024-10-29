//
// Created by sgsg1 on 2022-11-23.
//

#include "highscoreScreen.h"


highscoreScreen::highscoreScreen(const std::string &fontfile, const std::string &backgroundfile, const std::string &buttonfilesm) {
    background.loadFromFile(backgroundfile);
    buttonsm.loadFromFile(buttonfilesm);
    font.loadFromFile(fontfile);

    spriteBG.setTexture(background);
    spritebs.setTexture(buttonsm);
    highscore.setFont(font);
    back.setFont(font);

    highscore.setCharacterSize(70);
    back.setCharacterSize(15);
    highscore.setFillColor(sf::Color::Black);
    back.setFillColor(sf::Color::Black);
    highscore.setString("High Scores");
    back.setString("Back");

    spriteBG.setPosition(0,0);
    spritebs.setPosition(-40,950);
    highscore.setPosition(410,85);
    back.setPosition(70,1080);


}