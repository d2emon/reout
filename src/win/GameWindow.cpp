#include "GameWindow.h"
#include <time.h>
#include "settings.h"

GameWindow::GameWindow(sf::RenderWindow &window): D2Window(window)
{
    // srand(time(0));
    window.setFramerateLimit(60);
}

GameWindow::~GameWindow()
{
    //dtor
}

int GameWindow::load()
{
    if (!texture.loadFromFile("res/1.png"))
        return EXIT_FAILURE;

    for (int i=0; i < 1600; i++)
    {
        Line line;
        line.z = i * segL;

        lines.push_back(line);
    }

    N = lines.size();
    pos = 0;

    return 1;
}

int GameWindow::run()
{
    load();

	// Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up  )) pos += 200;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) pos -= 200;

        startPos = pos / segL;

        show();
    }

    return 1;
}

void GameWindow::show()
{
    // Clear screen
    window.clear();
    // window.draw(bg);

    // drawQuad(sf::Color::Green, 500, 500, 200, 500, 300, 100);

    for (int n=startPos; n < startPos + 300; n++)
    {
        Line &l = lines[n % N];
        l.project(0, 1500, pos);

        sf::Color grass  = (n/3) % 2 ? sf::Color( 16, 200,  16) : sf::Color(  0, 154,   0);
        sf::Color rumble = (n/3) % 2 ? sf::Color(255, 255, 255) : sf::Color(  0,   0,   0);
        sf::Color road   = (n/3) % 2 ? sf::Color(107, 107, 107) : sf::Color(105, 105, 105);

        Line p = lines[(n-1) % N];

        drawQuad(grass,  0,   p.Y, winSize[0],   0, l.Y, winSize[0]);
        drawQuad(rumble, p.X, p.Y, p.W * 1.2,  l.X, l.Y, l.W * 1.2 );
        drawQuad(road,   p.X, p.Y, p.W,        l.X, l.Y, l.W       );
    }

    // Update the window
    window.display();

}

void GameWindow::drawQuad(sf::Color c, int x1, int y1, int w1, int x2, int y2, int w2)
{
    sf::ConvexShape shape(4);
    shape.setFillColor(c);
    shape.setPoint(0, sf::Vector2f(x1 - w1, y1));
    shape.setPoint(1, sf::Vector2f(x2 - w2, y2));
    shape.setPoint(2, sf::Vector2f(x2 + w2, y2));
    shape.setPoint(3, sf::Vector2f(x1 + w1, y1));
    window.draw(shape);
}

