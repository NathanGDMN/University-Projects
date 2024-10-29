//
// Created by Etan Ossip on 2022-11-02.
//

#ifndef PROJECT_DESTRUCTIBLE_H
#define PROJECT_DESTRUCTIBLE_H

#include "GameObject.h"

/**
 * Abstract class that represents a destructible object, ie a GameObject that has health and can take damage
 */
class Destructible: public GameObject {
private:
    /// The object's health
    float health;
public:
    /**
     * Constructs a Destructible object
     *
     * @param sprite The object's sprite
     * @param position The object's initial position
     * @param velocity The object's initial velocity
     * @param health The object's initial health
     */
    Destructible(
        const sf::CircleShape &sprite,
        sf::Vector2f position,
        sf::Vector2f velocity,
        float health
    );


    /// Gets the current health of the object
    float getHealth() const;
    /// Sets the object's health
    void setHealth(float newHealth);
    /**
     * Deals a specified amount of damage to the object (passing a negative value will heal the object)
     *
     * @param damage The amount to subtract from the object's current health
     */
    void takeDamage(float damage);
};


#endif //PROJECT_DESTRUCTIBLE_H
