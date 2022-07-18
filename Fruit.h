#pragma once

int fruitType[20] = {1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,3,3,3};
Uint32 timeOnScreen[4] = {0, 8000, 6000, 4000};

class Fruit : public Texture
{
private:
    int x, y;
    const int maxPosition = SCREEN_WIDTH - 100;
public:
    int type;
    Uint32 appearTime = 0, dissappearTime = 0;
    bool isOnTheScreen = false;

    Fruit()
    {
        createFruit();
    }

    ~Fruit()
    {
        free();
    }

    void checkCollision()
    {
        for(int i = 0; i < snakeLength; i++)
        {
            if(snk[i][0] == x && snk[i][1] == y)
            {
                createFruit();
                break;
            }
        }
    }

    void createFruit()
    {
        type = fruitType[rand() % 20];
        y = (rand()%23 + 6)*snakeWidth;
        x = (rand()%28 + 1)*snakeWidth;
        checkCollision();
        loadTextureFromFile("Image/Fruit" + to_string(type) + ".png");
        appearTime = SDL_GetTicks();
        setRect(x, y, snakeWidth, snakeWidth);
        isOnTheScreen = true;
    }

    void moveFruit()
    {
        if(SDL_GetTicks() - appearTime >= timeOnScreen[type] && isOnTheScreen == true)
        {
            loadTextureFromFile();
            rect.x = -999;
            dissappearTime = SDL_GetTicks();
            isOnTheScreen = false;
        }
        if(isOnTheScreen == false)
        {
            createFruit();
        }
    }

    void renderFruit()
    {
        if(isOnTheScreen == true)
        {
            render();
        }
    }
};
