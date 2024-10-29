//
// Created by jmowo on 2022-11-14.
//

#ifndef CMPE320_FIGHTNFLIGHT_PROJECTILEMISSILE_H
#define CMPE320_FIGHTNFLIGHT_PROJECTILEMISSILE_H

#include "Projectile.h"

/**
 * Class that represents a Missile Projectile fired by a Player
 */
class ProjectileMissile: public Projectile {

private:
    /// Damage projectile deals
    float speed = 1.0;
    float steer_force = 0.8;
    sf::Vector2f target;
    GameObject* enemy;
    sf::Vector2f acceleration = sf::Vector2f(0, 0);

public:
    /**
     * Projectile constructor
     * @param sprite The Projectile's sprite
     * @param position The Projectile's initial position
     * @param velocity The Projectile's initial velocity
     */
    ProjectileMissile(const sf::Sprite &sprite, sf::Vector2f position, sf::Vector2f velocity, GameObject* enemy);

    sf::Vector2f seek(sf::Vector2f position, sf::Vector2f velocity);

    static sf::Vector2f normalize(sf::Vector2f source);

    void handleEvents(sf::Event) override;
    void update(sf::RenderWindow *) override;
    void display(sf::RenderWindow*) override;
};



#endif //CMPE320_FIGHTNFLIGHT_PROJECTILEMISSILE_H
