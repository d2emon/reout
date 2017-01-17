#include <SFML/Graphics.hpp>
#include "GameWindow.h"
#include "settings.h"

int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(winSize[0], winSize[1]), gameTitle);

    GameWindow win(app);
    win.run();
    return EXIT_SUCCESS;
}
