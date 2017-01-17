#include "Background.h"
#include <time.h>

int backgroundsCount = 10;
sf::String background = "res/bg.png";

sf::String bgFile()
{
    return background;
}

Background::Background()
{
    if (texture.loadFromFile(bgFile()))
    {
        texture.setRepeated(true);
        setTexture(texture);
    }
}
