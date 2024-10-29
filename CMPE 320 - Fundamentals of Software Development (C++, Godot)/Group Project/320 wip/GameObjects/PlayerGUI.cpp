//
// Created by Nathan Goodman on 2022-11-28.
//

#include "PlayerGUI.h"

//-----Constructor
PlayerGUI::PlayerGUI() {}
PlayerGUI::PlayerGUI(Player player, sf::RenderWindow *window) {
    this->player = &player;
    this->initializeHealthBar(window);
}

PlayerGUI::~PlayerGUI() {}

//----- Class Methods
void PlayerGUI::update(Player player) {
    this->updateHealthBar(player);
}

void PlayerGUI::display(sf::RenderWindow *window) {
    this->renderHealthBar(window);
}

//-----Health Bar Stuff
void PlayerGUI::updateHealthBar(Player player) {
    float percentHealthRemaining = static_cast<float>(player.getHealth())/static_cast<float>(maxHealth); //Static casts are used to avoid truncation
    float newWidth = maxHealthBarWidth*percentHealthRemaining;
    this->healthBar.setSize(sf::Vector2f(newWidth,this->healthBar.getSize().y));

    //Change Colour
    /// -Health bar starts blue
    /// -percentHealthRemaining is between 1 and 0
    if(percentHealthRemaining < 1){
        this->healthBar.setFillColor(sf::Color(100,252,100,200)); //Green
    }
    if(percentHealthRemaining < 0.75){
        this->healthBar.setFillColor(sf::Color(255,225,55,200)); //Yellow
    }
    if(percentHealthRemaining < 0.25){
        this->healthBar.setFillColor(sf::Color(255,50,50,200)); //Red
    }
}

void PlayerGUI::renderHealthBar(sf::RenderWindow *window) {
    window->draw(this->healthBarFrame);
    window->draw(this->barBackground);
    window->draw(this->healthBar);
}

void PlayerGUI::initializeHealthBar(sf::RenderWindow *window) {
    float width = 400;
    float height = 30;
    float distanceFromCenter = 40;
    float x;
    float y = 20;          //Height of Healthbar
    float frameOffset = 3; //Thickness of the frame around healthbar;

    //Change healthbar position depending on whether its right or left player
    if (this->player->getPosition().x < window->getSize().x/2){
        //If left player
        x = (window->getSize().x/2) - distanceFromCenter - width;
    }else{
        //If right player
        x = (window->getSize().x/2) + distanceFromCenter;
    }

    //Initializing HealthBar Frame
    this->healthBarFrame.setSize(sf::Vector2f(width+(2*frameOffset),height+(2*frameOffset)));
    this->healthBarFrame.setFillColor(sf::Color(195,195,195,150));
    this->healthBarFrame.setPosition(x - frameOffset, y - frameOffset);

    //Initializing HealthBar:
    this->barBackground.setSize(sf::Vector2f(width,height));                        //Size
    this->barBackground.setFillColor(sf::Color(50,50,50,200));  //Colour
    this->barBackground.setPosition(x,y);                                                 //Position

    this->healthBar.setSize(sf::Vector2f(width,height));                            //Size
    this->healthBar.setFillColor(sf::Color(50,180,255,200));     //Colour
    this->healthBar.setPosition(x,y);                                                     //Position

    this->maxHealthBarWidth = width;
    this->maxHealth = this->player->getHealth();    //Set maxHealth to player's health value when healthBar is initialized
}