//
// Created by Etan Ossip on 2022-11-02.
//

#include "Projectile.h"
#include <SFML/Window/Event.hpp>

Projectile::Projectile(const sf::Sprite &sprite, sf::Vector2f position, sf::Vector2f velocity, float damage) : GameObject(sprite, position, velocity) {
    this->damage = damage;
}

void Projectile::handleEvents(sf::Event) { }
