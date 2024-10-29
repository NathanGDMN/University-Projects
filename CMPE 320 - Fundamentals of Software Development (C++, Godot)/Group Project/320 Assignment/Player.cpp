//
// Created by Etan Ossip on 2022-11-02.
//

#include <SFML/Window/Event.hpp>
#include "Player.h"
#include <iostream>

Player::Player(char pl, //Player label
        const sf::CircleShape &sprite,
        sf::Vector2f position,
        sf::Vector2f velocity,
        float health,
        sf::Keyboard::Key up,
        sf::Keyboard::Key down,
        sf::Keyboard::Key fire
    ) : Destructible(sprite, position, velocity, health) {
    this->playerLabel = pl;
    this->up = up;
    this->down = down;
    this->fire = fire;
}

Player::Player(char pl) : Destructible(sf::CircleShape(40), sf::Vector2f(100, 100), sf::Vector2f(0, 0), 100.f) {
    this->playerLabel = pl;
    this->up = sf::Keyboard::Up;
    this->down = sf::Keyboard::Down;
    this->fire = sf::Keyboard::Space;
}

void Player::handleEvents(sf::Event event) {
    float vy = getVelocity().y;

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == up) vy = -SPEED;
        if (event.key.code == down) vy = SPEED;
        if (event.key.code == fire) fireProjectile();
    }

    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == up) vy = std::max(0.0f, vy);
        if (event.key.code == down) vy = std::min(0.0f, vy);
    }

    float vx = this->getVelocity().x;
    setVelocity(sf::Vector2f(vx, vy));
}

void Player::fireProjectile() {
    sf::CircleShape projSprite = sf::CircleShape(5);
    projSprite.setFillColor(sf::Color::Red);

    sf::Vector2f start = getPosition() + sf::Vector2f(getSprite().getRadius(), getSprite().getRadius());

    Projectile proj = Projectile(projSprite, start, fireDirection);
    projectiles.push_back(proj);
}

void Player::update(sf::RenderWindow *window) {
    sf::CircleShape sprite = getSprite();

    if (getHealth() < 40) sprite.setFillColor(sf::Color::Red);
    else if (getHealth() < 80) sprite.setFillColor(sf::Color::Yellow);
    else sprite.setFillColor(sf::Color::Green);

    setSprite(sprite);

    sf::Vector2f newPos = getVelocity() + getPosition();
    float minX = 0, maxX = window->getSize().x;
    float minY = 0, maxY = window->getSize().y - 2 * getSprite().getRadius();

    if (newPos.x > minX && newPos.x < maxX && newPos.y > minY && newPos.y < maxY)
        GameObject::update(window);

    for (int i = 0; i < projectiles.size(); i++) {
        projectiles[i].update(window);
    }
}

void Player::display(sf::RenderWindow *window) {
    GameObject::display(window);
    for (int i = 0; i < projectiles.size(); i++) {
        projectiles[i].display(window);
    }
}

void Player::checkHits(Destructible *enemy) {
    for (int i = 0; i < projectiles.size(); i++) {
        if (projectiles[i].isColliding(enemy)) {
            enemy->takeDamage(projectiles[i].getDamage());
            projectiles.erase(projectiles.begin() + i);
        }
    }
}
