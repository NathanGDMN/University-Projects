//
// Created by Etan Ossip on 2022-11-16.
//

#ifndef FIGHTNFLIGHT_SCENE_H
#define FIGHTNFLIGHT_SCENE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class Scene {
    // To be added later
    // friend class SceneController
private:
    /// boolean indicating whether the scene is being displayed
    bool active;
public:
    /**
     * Displays the scene's contents to the game window
     * @param window a pointer to the game window
     */
    virtual void display(sf::RenderWindow* window) { };
    /**
     * Updates the contents of the scene
     * @param window a pointer to the game window
     */
    virtual void update(sf::RenderWindow* window) { };
    /**
     * Handles events and directs contents to register events
     * @param event an event registered by the game window
     */
    virtual void handleEvents(sf::Event event) { };
};


#endif //FIGHTNFLIGHT_SCENE_H
