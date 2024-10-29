//
// Created by sgsg1 on 2022-11-23.
//

#include "EndScene.h"

EndScene::EndScene() {
    // Loading in textures.
    backgroundTexture.loadFromFile("GameAssets/endscreenbackground.png");
    buttonTexture.loadFromFile("GameAssets/buttonimage.png");
    buttonClickedTexture.loadFromFile("GameAssets/buttonclicked.png");

    // Setting up buttons.
    playAgainButton = new Button({200, 800}, buttonTexture, buttonClickedTexture);
    quitButton = new Button({650,800}, buttonTexture, buttonClickedTexture);

    // Loading in font.
    font.loadFromFile("TOP GUN.ttf");

    // Set background & static items.
    background.setTexture(backgroundTexture);
    background.setPosition(0, 0);

    congrats.setFont(font);
    congrats.setString("Congratulations");
    congrats.setFillColor(sf::Color::Black);
    congrats.setCharacterSize(45);
    congrats.setPosition(380,350);

    playAgain.setFont(font);
    playAgain.setString("Play Again");
    playAgain.setFillColor(sf::Color::Black);
    playAgain.setCharacterSize(31);
    playAgain.setPosition(290,820);

    quit.setFont(font);
    quit.setString("Quit");
    quit.setFillColor(sf::Color::Black);
    quit.setCharacterSize(31);
    quit.setPosition(790,820);

    winner.setFont(font);
    winner.setString("You are the champion!");
    winner.setFillColor(sf::Color::Black);
    winner.setCharacterSize(45);
    winner.setPosition(340,700);
}

void EndScene::display(sf::RenderWindow *window) {
    window->draw(background);
    window->draw(winner);

    playAgainButton->drawTo(window);
    quitButton->drawTo(window);

    window->draw(playAgain);
    window->draw(quit);
}

void EndScene::handleEvents(sf::Event event, sf::RenderWindow* window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (playAgainButton->checkClick(window)) action = PLAY_AGAIN;
        if (quitButton->checkClick(window)) action = QUIT;
    }
}
