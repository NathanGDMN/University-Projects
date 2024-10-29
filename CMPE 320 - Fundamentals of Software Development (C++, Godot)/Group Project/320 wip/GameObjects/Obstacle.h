//
// Created by Nathan Goodman on 2022-11-24.
//

#ifndef INC_320_ASSIGNMENT_OBSTACLE_H
#define INC_320_ASSIGNMENT_OBSTACLE_H

#include <SFML/Graphics/Texture.hpp>
#include "Destructible.h"
class Obstacle: public Destructible {
    /**
     * @param sprite the Obstacle's sprite
     * @param position the Obstacle's initial position
     * @param velocity the Obstacle's velocity
     * @param path the path that the Obstacle will follow
     * @param health the Obstacle's initial health
     */
private:
    char path;
    sf::Texture blimb;
public:
    //-----Constructors
    Obstacle();   //No arg
    Obstacle(   //All arg
        const sf::Sprite &sprite,
        sf::Vector2f position,
        sf::Vector2f velocity,
        char path,
        float health
    );

    //-----Methods (Match Player)
    void update(sf::RenderWindow *);
    /*Update:
    *   -Triggers event when health  <= 0
    *       -Explodes
    *       -Drops Power Up
    *   -Adjusts obstacles position
    */

    void display(sf::RenderWindow *);
    /*Display:
    *   -To be used if obstacle releases projectiles
    *       -Such as upon death
    *       -Or maybe its just an ai enemy
    */
    void handleEvents(sf::Event) override; //Wont be used but gives error if not overwritten

    //-----Methods(exclusive to obstacle)
    void setPath (char c);

private:    //Obstacle Paths
    void bouncePath(sf::RenderWindow *);
    void circlePath(sf::RenderWindow *);    //-UNFINISHED-
};



#endif //INC_320_ASSIGNMENT_OBSTACLE_H
