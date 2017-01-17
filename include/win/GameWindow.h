#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <math.h>

#include "D2Window.h"
#include "Background.h"
#include "settings.h"

struct Line
{
    float x, y, z;
    float X, Y, W;
    float scale;

    Line() {x=y=z=0;}

    void project(int camX, int camY, int camZ)
    {
        scale = camD / (z-camZ);
        X = (1 + scale * (x - camX)) * winSize[0]/2;
        Y = (1 - scale * (y - camY)) * winSize[1]/2;
        W = scale * roadW * winSize[0]/2;
    }
};

class GameWindow : public D2Window
{
    public:
        GameWindow(sf::RenderWindow &window);
        virtual ~GameWindow();

        Background bg;
        sf::Texture texture;
        sf::Sprite carSprite;

        int grid[6][6];
        std::vector<Line> lines;
        int N;
        int pos;
        int startPos;

        int load();
        int run();
        void show();

        void drawQuad(sf::Color c, int x1, int y1, int w1, int x2, int y2, int w2);
    protected:
    private:
};

#endif // GAMEWINDOW_H
