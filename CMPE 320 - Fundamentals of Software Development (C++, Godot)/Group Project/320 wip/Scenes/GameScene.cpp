//
// Created by sgsg1 on 2022-11-20.
//

#include "GameScene.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


GameScene::GameScene(sf::RenderWindow *window){
    plane1.loadFromFile("GameAssets/plane1.png");
    plane2.loadFromFile("GameAssets/plane2.png");
    button.loadFromFile("GameAssets/buttonimagesmall.png");

    backgroundTexture.loadFromFile("GameAssets/gameplacebackground.png");
    font.loadFromFile("TOP GUN.ttf");

    // setting the texture as a sprite
    background.setTexture(backgroundTexture);

    // Player sprites
    sf::Sprite leftSprite, rightSprite;

    leftSprite.setTexture(plane1);
    rightSprite.setTexture(plane2);

    // Initialize players and player fields, could be made neater with time
    leftPlayer = Player(), rightPlayer = Player();
    leftPlayer.enemy = &rightPlayer;
    rightPlayer.enemy = &leftPlayer;
    leftPlayer.setSprite(leftSprite);
    rightPlayer.setSprite(rightSprite);
    leftPlayer.setUpKey(sf::Keyboard::W);
    leftPlayer.setDownKey(sf::Keyboard::S);
    leftPlayer.setFireKey(sf::Keyboard::D);
    leftPlayer.setFireMissileKey(sf::Keyboard::C);
    rightPlayer.setFireMissileKey(sf::Keyboard::RShift);
    rightPlayer.setPosition(sf::Vector2f(window->getSize().x - 200, 100));
    rightPlayer.setFireDirection(sf::Vector2f(-1, 0));

    //Initialize Obstacle
    blimb.loadFromFile("GameAssets/blimb1.png");
    sf::Sprite bouncySprite;
    bouncySprite.setTexture(blimb);
    bouncy = Obstacle();
    bouncy.setSprite(bouncySprite);

    //Initialize GUI
    leftGUI = PlayerGUI(leftPlayer, window);    //Added
    rightGUI = PlayerGUI(rightPlayer, window);

    //loading font and setting the player titles at top of the screen
    leftPlayerLabel.setFont(font);
    rightPlayerLabel.setFont(font);
    pauseLabel.setFont(font);
    leftPlayerLabel.setString("Player One");
    rightPlayerLabel.setString("Player Two");
    pauseLabel.setString("Paused");
    leftPlayerLabel.setCharacterSize(20);
    rightPlayerLabel.setCharacterSize(20);
    pauseLabel.setCharacterSize(50);
    leftPlayerLabel.setFillColor(sf::Color::Black);
    rightPlayerLabel.setFillColor(sf::Color::Black);
    pauseLabel.setFillColor(sf::Color::Black);
    leftPlayerLabel.setPosition(70, 5);
    rightPlayerLabel.setPosition(750, 5);
    pauseLabel.setPosition(
            (window->getSize().x - pauseLabel.getGlobalBounds().width) / 2.0,
            (window->getSize().y - pauseLabel.getGlobalBounds().height) / 2.0
        );

    //setting plane and backgroundTexture image placement
    background.setPosition(0, 0);
}

void GameScene::update(sf::RenderWindow *window) {
    if (!paused) {
        leftPlayer.update(window);
        rightPlayer.update(window);

        leftPlayer.checkHits(&rightPlayer);
        rightPlayer.checkHits(&leftPlayer);

        //Obstacle Handling:
        bouncy.update(window);
        leftPlayer.checkHits(&bouncy);
        rightPlayer.checkHits(&bouncy);

        //GUI Handling
        leftGUI.update(leftPlayer);
        rightGUI.update(rightPlayer);

        gameOver = leftPlayer.getHealth() <= 0 || rightPlayer.getHealth() <= 0;
        playerOneVictory = gameOver && rightPlayer.getHealth() <= 0;
    } else {
        leftPlayer.setVelocity(sf::Vector2f(0, 0));
        rightPlayer.setVelocity(sf::Vector2f(0, 0));
    }
}

void GameScene::handleEvents(sf::Event event, sf::RenderWindow* unused) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
        paused = !paused;
    if (!paused) {
        leftPlayer.handleEvents(event);
        rightPlayer.handleEvents(event);
    }
}

void GameScene::display(sf::RenderWindow *window) {
    window->draw(leftPlayerLabel);
    window->draw(rightPlayerLabel);
    window->draw(background);
    if (paused) window->draw(pauseLabel);

    leftPlayer.display(window);
    rightPlayer.display(window);
    bouncy.display(window);
    leftGUI.display(window);
    rightGUI.display(window);
}

void GameScene::reset(sf::RenderWindow* window) {
    leftPlayer.setHealth(100), rightPlayer.setHealth(100);
    leftPlayer.setVelocity(sf::Vector2f(0, 0)), rightPlayer.setVelocity(sf::Vector2f(0, 0));
    rightPlayer.setPosition(sf::Vector2f(window->getSize().x - 200, 100));
    leftPlayer.setPosition(sf::Vector2f(100, 100));
    leftPlayer.clearProjectiles();
    rightPlayer.clearProjectiles();
}
