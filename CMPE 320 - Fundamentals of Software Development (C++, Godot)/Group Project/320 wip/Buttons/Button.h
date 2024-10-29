//
// Created by Carl on 23-Nov-22.
//

#ifndef FIGHTANDFLIGHT_BUTTON_H
#define FIGHTANDFLIGHT_BUTTON_H

#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
/**
 * Class to act as button for the game.
 */
class Button {
public:
    /**
     * Constructor for the button.
     * @param position Vector2f for positioning on the screen.
     * @param baseButtonPath Texture for idle button.
     * @param hoverButtonPath Texture for hover button.
     */
    Button(sf::Vector2f position, const sf::Texture& baseButton, const sf::Texture& hoverButton);

    /**
     * Draw button to targetted window.
     * @param window Pointer to game window holding button
     */
    void drawTo(sf::RenderWindow*);

    /**
     * Check of button is clicked or not.
     * @param window Pointer to game window holding button
     * @return bool indicating if the button was clicked or not
     *
     * Example Usage (code to be contained inside window polling loop):
     * sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::MouseButtonPressed:
                    if(button1.checkClick(window))
                    {
                        cout << "Desired button output..." << endl;
                    }
            }
        }
     */
    bool checkClick(sf::RenderWindow*);

private:
    sf::Texture baseButtonTexture;
    sf::Texture hoverButtonTexture;
    sf::Sprite curButtonSprite;
    sf::Vector2f pos;
    bool isMouseOver(sf::RenderWindow*);
};


#endif //FIGHTANDFLIGHT_BUTTON_H
