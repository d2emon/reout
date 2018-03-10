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
    float curve;

    float spriteX;
    float clip;

    sf::Sprite sprite;

    Line() {curve=x=y=z=0;}

    void project(int camX, int camY, int camZ)
    {
        scale = camD / (z-camZ);
        X = (1 + scale * (x - camX)) * winSize[0]/2;
        Y = (1 - scale * (y - camY)) * winSize[1]/2;
        W = scale * roadW * winSize[0]/2;
    }

    void drawSprite(sf::RenderWindow &window)
    {
        sf::Sprite s = sprite;
        int w = s.getTextureRect().width;
        int h = s.getTextureRect().height;

        float destX = X + scale * spriteX * winSize[0]/2;
        float destY = Y + 4;
        float destW = w * W / 266;
        float destH = h * W / 266;

        // printf("%f\n", destX);

        destX += destW * spriteX;
        destY += destH * (-1);

        float clipH = destY + destH - clip;

        if (clipH<0)
            clipH = 0;
        if (clipH >= destH)
            return;

        if (!w)
        {
            printf("No sprite\n");
            return;
        }

        printf("Rect %f, %f\n", w, h-h * clipH/destH);
        // s.setTextureRect(sf::IntRect(0, 0, w, h-h * clipH/destH));
        // s.setTextureRect(sf::IntRect(0, 0, w, h-h * clipH/destH));
        printf("Scale %f, %f\n", destW/w, destH/h);
        // s.setScale(destW/w, destH/h);
        // s.setScale(1, 1);
        printf("Pos %f, %f\n", destX, destY);
        s.setPosition(destX, destY); //destX, destY

        window.draw(s);

    }

};

class GameWindow : public D2Window
{
    public:
        GameWindow(sf::RenderWindow &window);
        virtual ~GameWindow();

        Background bg;
        sf::Texture texture;
        sf::Sprite treeSprite;

        int grid[6][6];
        std::vector<Line> lines;
        int N;
        int pos;
        int startPos;
        int playerX;

        int camH;
        int maxy;

        float x;
        float dx;

        int load();
        int run();
        void show();

        void drawQuad(sf::Color c, int x1, int y1, int w1, int x2, int y2, int w2);
    protected:
    private:
};

#endif // GAMEWINDOW_H
