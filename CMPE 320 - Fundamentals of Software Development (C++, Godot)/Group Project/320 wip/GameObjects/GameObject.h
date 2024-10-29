//
// Created by Etan Ossip on 2022-10-31.
//

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#ifndef PROJECT_GAMEOBJECT_H
#define PROJECT_GAMEOBJECT_H

/**
 * Abstract class that represents a general object in a game. Contains a position, velocity, sprite, and
 * methods to handle motion and indicate collisions between GameObjects.
 */
class GameObject {
private:
    sf::Sprite sprite;
    sf::Vector2f position;
    sf::Vector2f velocity;
public:
    /**
     * GameObject Constructor
     * @param sprite The object's sprite
     * @param position The object's initial position
     * @param velocity The object's initial velocity
     */
    GameObject(const sf::Sprite& sprite, sf::Vector2f position, sf::Vector2f velocity);
    /**
     * GameObject Constructor
     * @param sprite The object's sprite
     * @param x The object's initial x position
     * @param y The object's initial y position
     * @param vx The object's initial x velocity
     * @param vy The object's initial y velocity
     */
    GameObject(const sf::Sprite& sprite, float x, float y, float vx, float vy);

    /// Gets the object's sprite
    sf::Sprite getSprite() { return sprite; }
    /// Sets the object's sprite
    void setSprite(const sf::Sprite& sp) { this->sprite = sp; }

    /// Gets the object's position
    sf::Vector2f getPosition() { return position; }
    /// Gets the object's velocity
    sf::Vector2f getVelocity() { return velocity; }

    /// Sets the object's position
    void setPosition(sf::Vector2f p) { position = p; }
    /// Sets the object's velocity
    void setVelocity(sf::Vector2f v) { velocity = v; }
    /// Sets sprite rotation
    void setRotation(float angle) { sprite.setRotation(angle); }

    /**
     * Indicates whether two objects are colliding
     *
     * @param other A pointer to a GameObject that may be colliding with this
     *
     * @return a bool indicating whether the objects are colliding
     */
    bool isColliding(GameObject*);

    /**
     * Updates the object's position, intended use is to be called before drawing each frame.
     * @param window a pointer to the game window
     */
    virtual void update(sf::RenderWindow*);
    /**
     * Displays the object to the game window
     * @param window a pointer to the game window
     */
    virtual void display(sf::RenderWindow*);

    /**
     * Handles input events from the user. Overwritten by subclasses.
     */
    virtual void handleEvents(sf::Event) = 0;
};


#endif //PROJECT_GAMEOBJECT_H