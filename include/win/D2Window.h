#ifndef D2WINDOW_H
#define D2WINDOW_H

#include <SFML/Graphics.hpp>

class D2Window
{
    public:
        sf::RenderWindow &window;

        D2Window(sf::RenderWindow &window);
        virtual ~D2Window();

        // virtual int load() =0;
        // virtual int run();
        // virtual void show() =0;
        // virtual int OnEvent(sf::Event event) =0;
    protected:
        bool running = true;
    private:
};

#endif // D2WINDOW_H
