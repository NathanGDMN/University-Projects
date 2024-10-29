//
// Created by Etan Ossip on 2022-11-02.
//

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Missile.h"
#include <iostream>

Player::Player(const sf::Sprite &sprite,
               sf::Vector2f position,
               sf::Vector2f velocity,
               float health,
               sf::Keyboard::Key up,
               sf::Keyboard::Key down,
               sf::Keyboard::Key fire
) : Destructible(sprite, position, velocity, health) {
    this->up = up;
    this->down = down;
    this->fire = fire;
    this->projTexture.loadFromFile("GameAssets/bulletimage.png");
    this->missileTexture.loadFromFile("GameAssets/missile.png");
}

Player::Player() : Destructible(sf::Sprite(), sf::Vector2f(100, 100), sf::Vector2f(0, 0), 100.f) {
    this->up = sf::Keyboard::Up;
    this->down = sf::Keyboard::Down;
    this->fire = sf::Keyboard::Space;
    this->projTexture.loadFromFile("GameAssets/bulletimage.png");
    this->missileTexture.loadFromFile("GameAssets/missile.png");
}

void Player::handleEvents(sf::Event event) {
    float vy = getVelocity().y;

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == up) vy = -SPEED;
        if (event.key.code == down) vy = SPEED;
        if (event.key.code == fire) fireProjectile(false);
        if (event.key.code == fireMissile) fireProjectile(true);
    }

    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == up) vy = std::max(0.0f, vy);
        if (event.key.code == down) vy = std::min(0.0f, vy);
    }

    float vx = this->getVelocity().x;
    setVelocity(sf::Vector2f(vx, vy));
}

void Player::fireProjectile(bool missile) {
    sf::Sprite projSprite;
    projSprite.setTexture(missile ? missileTexture : projTexture);
    if (missile) projSprite.setScale(sf::Vector2f(0.4, 0.4));

    sf::FloatRect bounds = getSprite().getGlobalBounds();
    sf::FloatRect projBounds = projSprite.getGlobalBounds();
    float startX = bounds.left + 0.5 * bounds.width;
    float startY = bounds.top + 0.5 * bounds.height - 0.5 * projBounds.height;
    sf::Vector2f start = sf::Vector2f(startX, startY);

    if (missile) {
        ProjectileMissile proj = ProjectileMissile(projSprite, start, fireDirection, enemy);
        missiles.push_back(proj);
    } else {
        Projectile proj = Projectile(projSprite, start, fireDirection, 20);
        projectiles.push_back(proj);
    }
}

void Player::update(sf::RenderWindow *window) {
    sf::Sprite sprite = getSprite();

    setSprite(sprite);
    sf::FloatRect bounds = getSprite().getGlobalBounds();

    sf::Vector2f newPos = getVelocity() + getPosition();
    float minX = 0, maxX = window->getSize().x;
    float minY = 0, maxY = window->getSize().y - bounds.height;


    if (newPos.x > minX && newPos.x < maxX && newPos.y > minY && newPos.y < maxY)
        GameObject::update(window);

    sf::FloatRect windowRect = sf::FloatRect(0, 0, window->getSize().x, window->getSize().y);

    for (int i = 0; i < projectiles.size(); i++) {
        sf::FloatRect projRect = projectiles[i].getSprite().getGlobalBounds();
        if (windowRect.intersects(projRect))
            projectiles[i].update(window);
        else
            projectiles.erase(projectiles.begin() + i);
    }

    for (int i = 0; i < missiles.size(); i++) {
        sf::FloatRect missileRect = missiles[i].getSprite().getGlobalBounds();
        if (windowRect.intersects(missileRect))
            missiles[i].update(window);
        else {
            missiles.erase(missiles.begin() + i);
        }
    }
}

void Player::display(sf::RenderWindow *window) {
    GameObject::display(window);
    for (int i = 0; i < projectiles.size(); i++) {
        projectiles[i].display(window);
    }

    for (int i = 0; i < missiles.size(); i++) {
        missiles[i].display(window);
    }
}

void Player::checkHits(Destructible *target) {
    for (int i = 0; i < projectiles.size(); i++) {
        if (projectiles[i].isColliding(target)) {
            target->takeDamage(projectiles[i].getDamage());
            projectiles.erase(projectiles.begin() + i);
        }
    }

    for (int i = 0; i < missiles.size(); i++) {
        if (missiles[i].isColliding(target)) {
            target->takeDamage(missiles[i].getDamage());
            missiles.erase(missiles.begin() + i);
        }
    }
}

