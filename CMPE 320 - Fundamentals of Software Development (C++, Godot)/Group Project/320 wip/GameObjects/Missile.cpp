//
// Created by jmowo on 2022-11-14.
//

#include "Missile.h"

#include <SFML/Window/Event.hpp>
#include <cmath>
#include <iostream>


ProjectileMissile::ProjectileMissile(const sf::Sprite &sprite, sf::Vector2f position, sf::Vector2f velocity, GameObject* enemy) : Projectile(sprite, position, velocity, 40.0) {
    this->enemy = enemy;
}

sf::Vector2f ProjectileMissile::seek(sf::Vector2f position, sf::Vector2f velocity) {
    sf::Vector2f steer;
    sf::Vector2f desired = sf::Vector2f((target.x - position.x), target.y - position.y);
    desired = normalize(desired);
    desired = desired * speed;
    steer = (desired - velocity);
    normalize(steer);
    steer = steer * steer_force;
    return steer;
}

sf::Vector2f ProjectileMissile::normalize(const sf::Vector2f source) {
    float length = sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0) {
        sf::Vector2f newSource = sf::Vector2f(source.x / length, source.y / length);
        return newSource;
    }
    else
        return source;
}

void ProjectileMissile::handleEvents(sf::Event) { }

void ProjectileMissile::update(sf::RenderWindow *window) {
    target = enemy->getPosition();
    acceleration += seek(getPosition(), getVelocity());
    // Distance To Target
    sf::Vector2f disp = sf::Vector2f((target.x - getPosition().x), target.y - getPosition().y);
    float xToTarget = disp.x < 0 ? -disp.x : disp.x;
    float minAdjustX = (window->getSize().x) * 0.3;

    if (xToTarget < minAdjustX)
        acceleration = sf::Vector2f(0,0);

    sf::Vector2f newVelocity  = normalize(getVelocity() + acceleration);
    setVelocity(newVelocity);
    setRotation(180 * std::atan2(newVelocity.y, newVelocity.x) / M_PI);

    GameObject::update(window);
}

void ProjectileMissile::display(sf::RenderWindow *window) {
    GameObject::display(window);
}
