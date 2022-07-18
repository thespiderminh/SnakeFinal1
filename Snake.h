#pragma once

int X[5] = {0, 0, snakeWidth, 0, -snakeWidth};
int Y[5] = {0, -snakeWidth, 0, snakeWidth, 0};
int i = 1, preDirection, nextDirection;

class Snake : public Texture
{
private:
    int x = SCREEN_WIDTH/2/snakeWidth*snakeWidth, y = SCREEN_HEIGHT/2/snakeWidth*snakeWidth;
    Texture Head;
    bool isDead = false;
public:
    Snake()
    {
        Texture();
        loadTextureFromFile("Image/SnakeBody_1_1.png");
        Head.loadTextureFromFile("Image/Black" + to_string(i) + ".png");
    }

    ~Snake()
    {
        free();
    }

    void renderSnake()
    {
        Head.loadTextureFromFile("Image/Black" + to_string(i) + ".png");

        for(int j = 1; j < snakeLength - 1; j++)
        {
            int xx2 = snk[j-1][0] - snk[j][0];
            int yy2 = snk[j-1][1] - snk[j][1];
            int xx1 = snk[j][0] - snk[j+1][0];
            int yy1 = snk[j][1] - snk[j+1][1];
            int i1, i2;
            for(int k = 0; k < 5; k++)
            {
                if(X[k] == xx1 && Y[k] == yy1) i1 = k;
                if(X[k] == xx2 && Y[k] == yy2) i2 = k;
            }
            loadTextureFromFile("Image/SnakeBody_" + to_string(i1) + "_" + to_string(i2) + ".png");
            render(snk[j][0], snk[j][1], snakeWidth, snakeWidth);
        }

        int xx2 = snk[snakeLength - 2][0] - snk[snakeLength - 1][0];
        int yy2 = snk[snakeLength - 2][1] - snk[snakeLength - 1][1];
        int i2;
        for(int k = 0; k < 5; k++)
        {
            if(X[k] == xx2 && Y[k] == yy2) i2 = k;
        }
        loadTextureFromFile("Image/SnakeTail_" + to_string(i2) + ".png");
        render(snk[snakeLength - 1][0], snk[snakeLength - 1][1], snakeWidth, snakeWidth);

        Head.render(snk[0][0], snk[0][1], snakeWidth, snakeWidth);
    }

    void handleMove()
    {
        if(i == 1)
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_RIGHT:
                i = 2;
                break;
            case SDLK_LEFT:
                i = 4;
                break;
            }
        }
        else if(i == 2)
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_UP:
                i = 1;
                break;
            case SDLK_DOWN:
                i = 3;
                break;
            }
        }
        else if(i == 3)
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_RIGHT:
                i = 2;
                break;
            case SDLK_LEFT:
                i = 4;
                break;
            }
        }
        else if(i == 4)
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_UP:
                i = 1;
                break;
            case SDLK_DOWN:
                i = 3;
                break;
            }
        }
    }

    void snakeMove()
    {
        x += X[i];
        y += Y[i];

        if(x + snakeWidth >= SCREEN_WIDTH)
        {
            if(border == false) x = snakeWidth;
            if(border == true) isDead = true;
        }
        else if(x <= 0)
        {
            if(border == false) x = SCREEN_WIDTH - 2 * snakeWidth;
            else if(border == true) isDead = true;
        }

        if(y + snakeWidth >= SCREEN_HEIGHT)
        {
            if(border == false) y = 100 + snakeWidth;
            if(border == true) isDead = true;
        }
        else if(y <= 100)
        {
            if(border == false) y = SCREEN_HEIGHT - 2 *snakeWidth;
            if(border == true) isDead = true;
        }
        for(int j = snakeLength - 1; j >= 0; j--)
        {
            snk[j+1][0] = snk[j][0];
            snk[j+1][1] = snk[j][1];
        }
        snk[0][0] = x;
        snk[0][1] = y;

        for(int j = snakeLength - 1; j > 0; j--)
        {
            if(snk[j][0] == snk[0][0] && snk[j][1] == snk[0][1])
            {
                isDead = true;
            }
        }
    }

    int getLength()
    {
        return snakeLength;
    }

    int getHeadX()
    {
        return snk[0][0];
    }

    int getHeadY()
    {
        return snk[0][1];
    }

    void lengthUp()
    {
        snakeLength++;
    }

    bool checkDead()
    {
        return isDead;
    }
};
