//
// Created by Etan Ossip on 2022-11-02.
//

#include "Destructible.h"

Destructible::Destructible(const sf::CircleShape &sprite,
            sf::Vector2f position,
            sf::Vector2f velocity,
            float health
        ) : GameObject(sprite, position, velocity) {
    this->health = health;
}

float Destructible::getHealth() const { return health; }
void Destructible::setHealth(float newHealth)  { health = newHealth; }
void Destructible::takeDamage(float damage) { setHealth(health - damage); }
