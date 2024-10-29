//
// Created by Etan Ossip on 2022-11-02.
//

#include "GameObject.h"

void GameObject::update(sf::RenderWindow* = nullptr) {
    position += velocity;
    sprite.setPosition(position);
}

void GameObject::display(sf::RenderWindow *window) {
    window->draw(sprite);
}

GameObject::GameObject(const sf::Sprite &sprite, sf::Vector2f position, sf::Vector2f velocity = sf::Vector2f(0, 0)) {
    this->sprite = sprite;
    this->position = position;
    this->velocity = velocity;
}

GameObject::GameObject(const sf::Sprite& sprite, float x, float y, float vx = 0, float vy = 0) {
    this->sprite = sprite;
    this->position = sf::Vector2f(x, y);
    this->velocity = sf::Vector2f(vx, vy);
}

bool GameObject::isColliding(GameObject *other) {
    return sprite.getGlobalBounds().intersects(other->sprite.getGlobalBounds());
}