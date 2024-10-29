#include <SFML/Graphics.hpp>
#include "Scenes/SceneController.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(1200,1200), "SFML App");
    window.setKeyRepeatEnabled(false);

    SceneController player = SceneController(&window);
    player.runGame();
}
