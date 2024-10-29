#include <C:/Users/nmgoo/OneDrive/Documents/SFML-2.5.1/include/SFML/Graphics.hpp>
#include "Player.h"
#include "Obstacle.h"
#include "PlayerGUI.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Application");
    window.setKeyRepeatEnabled(false);

    Player left = Player('l'), right = Player('r'); //Adjusted

    sf::CircleShape leftCircle = sf::CircleShape(40);
    leftCircle.setFillColor(sf::Color::Cyan);
    left.setSprite(leftCircle);

    sf::CircleShape rightCircle = sf::CircleShape(40);
    rightCircle.setFillColor(sf::Color::Green);
    right.setSprite(rightCircle);

    right.setUpKey(sf::Keyboard::W);
    right.setDownKey(sf::Keyboard::S);
    right.setFireKey(sf::Keyboard::D);

    right.setPosition(sf::Vector2f(window.getSize().x - 100, 100));
    right.setFireDirection(sf::Vector2f(-1, 0));

    PlayerGUI leftGUI = PlayerGUI(left);    //Added
    PlayerGUI rightGUI = PlayerGUI(right);  //Added

    Obstacle bouncy = Obstacle();   //Added
    bouncy.setSprite(leftCircle);   //Added
    bouncy.setPosition(sf::Vector2f(window.getSize().x/2, 100)); //Puts obstacle in middle of screen

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) { //Gets input
            left.handleEvents(event);
            right.handleEvents(event);
        }

        left.checkHits(&right);
        right.checkHits(&left);

        left.checkHits(&bouncy);    //Added
        right.checkHits(&bouncy);   //Added

        //--Update Game Objects
        left.update(&window);
        right.update(&window);
        bouncy.update(&window);            //Added
        leftGUI.update(left);        //Added
        rightGUI.update(right);      //Added

        //--Display Game Objects (generate new frame)
        window.clear(); //Clear old frame

        //Add Game Objects to new frame
        left.display(&window);
        right.display(&window);
        bouncy.display(&window);           //Added
        leftGUI.display(&window);        //Added
        rightGUI.display(&window);       //Added

        window.display();   //Push new frame to window
    }
}
