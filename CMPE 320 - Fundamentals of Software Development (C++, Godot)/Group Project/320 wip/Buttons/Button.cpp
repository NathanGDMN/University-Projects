//
// Created by Carl on 23-Nov-22.
//

#include <SFML/Graphics.hpp>
#include "Button.h"
using namespace std;

Button::Button(const sf::Vector2f position, const sf::Texture& baseButton, const sf::Texture& hoverButton)
{
    this->pos = position;
    this->baseButtonTexture = baseButton;
    this->hoverButtonTexture = hoverButton;
    this->curButtonSprite.setTexture(baseButtonTexture);
    this->curButtonSprite.setPosition(pos);
}


void Button::drawTo(sf::RenderWindow *window) {
    if (isMouseOver(window))
        curButtonSprite.setTexture(baseButtonTexture);
    else
        curButtonSprite.setTexture(hoverButtonTexture);

    curButtonSprite.setPosition(pos);
    window->draw(curButtonSprite);
}

bool Button::isMouseOver(sf::RenderWindow *window){
    float mouseX = sf::Mouse::getPosition(*window).x;
    float mouseY = sf::Mouse::getPosition(*window).y;
    float leftX = curButtonSprite.getPosition().x;
    float topY = curButtonSprite.getPosition().y;
    float rightX = leftX + curButtonSprite.getGlobalBounds().width;
    float bottomY = topY + curButtonSprite.getGlobalBounds().height;

    return mouseX < rightX && mouseX > leftX && mouseY < bottomY && mouseY > topY;
}

bool Button::checkClick(sf::RenderWindow *window) {
    if (isMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        while (sf::Mouse::isButtonPressed(sf::Mouse::Left));
        return true;
    }
    return false;
}