//
// Created by Nathan Goodman on 2022-11-28.
//

#ifndef INC_320_ASSIGNMENT_PLAYERGUI_H
#define INC_320_ASSIGNMENT_PLAYERGUI_H

#include "Player.h"
#include <SFML/Graphics/RectangleShape.hpp>

class PlayerGUI{
private:
    Player* player;
    //Health Bar Fields:
    sf::RectangleShape healthBarFrame;
    sf::RectangleShape barBackground;
    sf::RectangleShape healthBar;
    int maxHealth;
    float maxHealthBarWidth;

public:
    //Constructor and Destructor
    PlayerGUI();
    PlayerGUI(Player player, sf::RenderWindow *window);
    virtual ~PlayerGUI();

    //-----Class Functions
    void update(Player player);
    void display(sf::RenderWindow *window);

    //-----Health Bar Functions
    void updateHealthBar(Player player);
    void renderHealthBar(sf::RenderWindow *window);
private:
    void initializeHealthBar(sf::RenderWindow *window);

};

#endif //INC_320_ASSIGNMENT_PLAYERGUI_H
