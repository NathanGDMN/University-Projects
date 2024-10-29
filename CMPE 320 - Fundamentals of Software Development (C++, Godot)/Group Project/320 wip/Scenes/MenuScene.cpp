//
// Created by sgsg1 on 2022-11-21.
//

#include "MenuScene.h"
#include <SFML/Graphics.hpp>

//MenuScene screen(,,,);

MenuScene::MenuScene() {
    backgroundTexture.loadFromFile("GameAssets/titlescreenbackground.png");
    button.loadFromFile("GameAssets/buttonimage.png");
    buttonsmall.loadFromFile("GameAssets/buttonimagesmall.png");
    font.loadFromFile("TOP GUN.ttf");

    background.setTexture(backgroundTexture);
    spriteb1.setTexture(button);
    spriteb2.setTexture(button);
    spriteb3.setTexture(button);
    spritebs.setTexture(buttonsmall);

    title.setFont(font);
    quit.setFont(font);
    newgame.setFont(font);
    highscore.setFont(font);
    settings.setFont(font);
    title.setString("Fight N Flight");
    quit.setString("Quit Game");
    newgame.setString("New Game");
    highscore.setString("High Scores");
    settings.setString("Settings");
    title.setCharacterSize(120);
    quit.setCharacterSize(15);
    newgame.setCharacterSize(31);
    highscore.setCharacterSize(31);
    settings.setCharacterSize(31);
    title.setFillColor(sf::Color::Black);
    quit.setFillColor(sf::Color::Black);
    newgame.setFillColor(sf::Color::Black);
    highscore.setFillColor(sf::Color::Black);
    settings.setFillColor(sf::Color::Black);
    title.setPosition(230, 450);
    quit.setPosition(50, 1080);

    spriteb1.setPosition(180,250);
    newgame.setPosition(515,658);
    spriteb2.setPosition(180,350);
    highscore.setPosition(495,758);
    spriteb3.setPosition(180,450);
    settings.setPosition(515,858);
    spritebs.setPosition(-40,950);
}


