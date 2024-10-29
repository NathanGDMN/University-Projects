//
// Created by Etan Ossip on 2022-11-02.
//

#include "Projectile.h"
#include <SFML/Window/Event.hpp>

Projectile::Projectile(const sf::CircleShape &sprite, sf::Vector2f position, sf::Vector2f velocity) : GameObject(sprite, position, velocity) {
    this->damage = 20; // sample value to be changed later
}

void Projectile::handleEvents(sf::Event) { }
