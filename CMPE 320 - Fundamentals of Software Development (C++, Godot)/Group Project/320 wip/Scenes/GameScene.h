//
// Created by sgsg1 on 2022-11-20.
//

#ifndef GAMETEST_PLAYSCREEN_H
#define GAMETEST_PLAYSCREEN_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "Scene.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/Obstacle.h"
#include "../GameObjects/PlayerGUI.h"

class GameScene: public Scene {
private:
    /// Background
    sf::Sprite background;
    sf::Texture backgroundTexture;
    sf::Texture plane1;
    sf::Texture plane2;
    sf::Texture button;
    sf::Texture blimb;

    sf::Text leftPlayerLabel;
    sf::Text rightPlayerLabel;
    sf::Text pauseLabel;

    sf::Font font;
    /// Boolean indicating whether game is paused
    bool paused = false;
    /// Boolean indicating whether game is over
    bool gameOver = false;
    /// Boolean indicating whether player 1 has won. If this is false but gameOver is true, then player 2 won.
    bool playerOneVictory = false;
    /// Players in the scene
    Player leftPlayer, rightPlayer;
    /// Obstacles in scene
    Obstacle bouncy;

    ///GUI Objects
    PlayerGUI leftGUI;
    PlayerGUI rightGUI;

public:
    explicit GameScene(sf::RenderWindow *);

    enum Victor { NONE, PLAYER_ONE, PLAYER_TWO };

    bool isOver() const { return gameOver; }

    Victor winner() const {
        return gameOver ? (playerOneVictory ? PLAYER_ONE : PLAYER_TWO) : NONE;
    }

    void reset(sf::RenderWindow *);

    void update(sf::RenderWindow *) override;
    void display(sf::RenderWindow *) override;
    void handleEvents(sf::Event, sf::RenderWindow *) override;
};



#endif //GAMETEST_PLAYSCREEN_H
