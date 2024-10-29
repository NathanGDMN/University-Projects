//
// Created by Etan Ossip on 2022-11-26.
//

#ifndef FIGHTNFLIGHT_SCENE_H
#define FIGHTNFLIGHT_SCENE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class Scene {
private:
    bool active = false;
public:
    virtual void update(sf::RenderWindow *) { }
    virtual void display(sf::RenderWindow *) { }
    virtual void handleEvents(sf::Event, sf::RenderWindow *) { }
};

#endif //FIGHTNFLIGHT_SCENE_H
