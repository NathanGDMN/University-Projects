//
// Created by nmgoo on 2022-11-24.
//

#include <SFML/Window/Event.hpp>
#include <string.h>
#include "Obstacle.h"

//-----Constructors

/*
 * Can play around with obstacle position and health.
 * -Health is currently set to 20 so standard projectile one-shots it
 */
Obstacle::Obstacle():Destructible(sf::CircleShape(40), sf::Vector2f(100, 100), sf::Vector2f(2, 2), 20.f){
    path = 'b';
};
Obstacle::Obstacle(const sf::CircleShape &sprite,sf::Vector2f position,sf::Vector2f velocity, char path, float health) : Destructible(sprite, position, velocity, health){
    setSprite(sprite);
    setPosition(position);
    setVelocity(velocity);
    setPath(path);
    setHealth(health);
};

void Obstacle::update(sf::RenderWindow *window){
    //Events if hit:
    sf::CircleShape sprite = getSprite();

    if (getHealth() < 20) sprite.setFillColor(sf::Color::Red);
    else sprite.setFillColor(sf::Color::Green);

    setSprite(sprite);

    //Adjust position:
    //The following code will vertically bounce obstacle between sides of screen until removed

    switch(path){
        case 'b':
            bouncePath(window);
            break;
    }
};

//-----Methods

void Obstacle::display(sf::RenderWindow *window){
    GameObject::display(window);
};
void Obstacle::handleEvents(sf::Event event) {}

void Obstacle::bouncePath(sf::RenderWindow *window){
    //The following code will spawn obstacle at given position and bounce obstacle between sides of screen

    float minX = 200, maxX = window->getSize().x-200; //Set so obstacle is always inbetween players
    float minY = 0, maxY = window->getSize().y - 2 * getSprite().getRadius();
    sf::Vector2f newPos = sf::Vector2f(maxX+1, maxY+1);

    while(newPos.y > maxY) {
        newPos = getVelocity() + getPosition();

        if ((newPos.y < minY || newPos.y > maxY) && (newPos.x < minX || newPos.x > maxX)){
            //If newPos.y and newPos.x is out of bounds
            setVelocity(sf::Vector2f(0-getVelocity().x, 0 - getVelocity().y));
            //*this will only occur if obstacle hits corner
        }else if (newPos.y < minY || newPos.y > maxY) {
            //If newPos.y is out of bounds
            setVelocity(sf::Vector2f(getVelocity().x, 0 - getVelocity().y));
        } else if (newPos.x < minX || newPos.x > maxX){
            //If newPos.x is out of bounds
            setVelocity(sf::Vector2f(0-getVelocity().x, getVelocity().y));
        }else{
            //If newPos is inbounds
            GameObject::update(window);
        }
    }
}

void Obstacle::circlePath(sf::RenderWindow *window) {   //-UNFINISHED-
    sf::Vector2f center = sf::Vector2f(window->getSize().x/2, window->getSize().y/2);
    float radius = 150;

    std::string rotation;
    if (getVelocity().y >= 0){
        //If Velocity is positive in x and y or
        rotation = "counterCW";
    }else{
        rotation = "clockwise";
    }

    sf::Vector2f newPos = sf::Vector2f(center.x+radius, center.y);



}

void Obstacle::setPath(char c) { path = c;}