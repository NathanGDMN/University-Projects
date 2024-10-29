// Created by Etan Ossip on 2022-11-02.
//

#ifndef PROJECT_PROJECTILE_H
#define PROJECT_PROJECTILE_H

#include "GameObject.h"
#include <SFML/Graphics.hpp>

/**
 * Class that represents a Projectile fired by a Player
 */
class Projectile: public GameObject {
    // Might want to consider making Player a friend class, if it turns out to be useful
private:
    /// Damage projectile deals
    float damage;
public:
    /**
     * Projectile constructor
     * @param sprite The Projectile's sprite
     * @param position The Projectile's initial position
     * @param velocity The Projectile's initial velocity
     */
    Projectile(const sf::Sprite &sprite, sf::Vector2f position, sf::Vector2f velocity, float damage);

    /// Gets the damage dealt by this projectile
    float getDamage() const { return damage; }
    /// Sets the damage dealt by this projectile
    void setDamage(float d) { this->damage = d; }

    void handleEvents(sf::Event) override;
};


#endif //PROJECT_PROJECTILE_H