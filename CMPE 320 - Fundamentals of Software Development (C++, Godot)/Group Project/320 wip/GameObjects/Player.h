//
// Created by Etan Ossip on 2022-11-02.
//

#ifndef PROJECT_PLAYER_H
#define PROJECT_PLAYER_H

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#include "Destructible.h"
#include "Projectile.h"
#include "Missile.h"
#include <vector>

/**
 * Class that represents a player in the game. Inherits from Destructible and therefore GameObject,
 * and contains a vector of Projectiles as well as methods to control player movement and behaviour.
 */
class Player: public Destructible {
private:
    // Key codes that correspond to moving up, moving down, and firing, respectively
    sf::Keyboard::Key up, down, fire, fireMissile;
    /// Vector of projectiles that have been fired by the Player
    std::vector<Projectile> projectiles;
    /// Vector of missiles that have been fired by the Player
    std::vector<ProjectileMissile> missiles;
    /// Initial velocity of launched projectile
    sf::Vector2f fireDirection = sf::Vector2f(1, 0);
    /// Texture for projectiles
    sf::Texture projTexture;
    /// Texture for missiles
    sf::Texture missileTexture;
public:
    /// Pointer to the enemy player
    GameObject* enemy = nullptr;

    /// Gets the key that moves the player up when pressed
    sf::Keyboard::Key getUpKey() { return up; }
    /// Gets the key that moves the player down when pressed
    sf::Keyboard::Key getDownKey() { return down; }
    /// Gets the key that causes the player to fire when pressed
    sf::Keyboard::Key getFireKey() { return fire; }
    /// Gets the key that causes the player to fire a missile when pressed
    sf::Keyboard::Key getFireMissileKey() { return fireMissile; }

    /// Sets the key that moves the player up when pressed
    void setUpKey(sf::Keyboard::Key key) { up = key; }
    /// Sets the key that moves the player down when pressed
    void setDownKey(sf::Keyboard::Key key) { down = key; }
    /// Sets the key that causes the player to fire when pressed
    void setFireKey(sf::Keyboard::Key key) { fire = key; }
    /// Sets the key that causes the player to fire a missile when pressed
    void setFireMissileKey(sf::Keyboard::Key key) { fireMissile = key; }

    sf::Vector2f getFireDirection() { return fireDirection; }
    void setFireDirection(sf::Vector2f dir) { fireDirection = dir; }

    /**
     * Constructor for Player class
     * @param sprite the Player's sprite
     * @param position the Player's initial position
     * @param velocity the Player's initial velocity
     * @param health the Player's initial health
     * @param up the key that will move the player up
     * @param down the key that will move the player down
     * @param fire the key that will cause the player to fire
     * @param fireMissile the key that will cause the player to fire a missile
     */
    Player(
            const sf::Sprite &sprite,
            sf::Vector2f position,
            sf::Vector2f velocity,
            float health,
            sf::Keyboard::Key up,
            sf::Keyboard::Key down,
            sf::Keyboard::Key fire
    );

    /// No argument constructor
    Player();

    /**
     * The speed of a Player object
     */
    constexpr static const float SPEED = 1;

    /**
     * Fires a projectile
     * @param missile boolean indicating whether to fire a missile or regular projectile
     */
    void fireProjectile(bool missile);

    /**
     * Removes all fired projectiles
     */
    void clearProjectiles() {
        projectiles.clear();
        missiles.clear();
    }

    /** Checks to see if any of this Player's projectiles have hit a Destructible object
     *  and handles removing the projectile and dealing the damage to the target.
     *  TODO: reasonable place to handle animation as well
     *
     * @param enemy a pointer to the Destructible object that this Player's Projectiles may have hit
     */
    void checkHits(Destructible *enemy); // check if projectiles have hit other player

    void handleEvents(sf::Event) override;
    void update(sf::RenderWindow *) override;
    void display(sf::RenderWindow *) override;
};


#endif //PROJECT_PLAYER_H