#include "Init.h"
#include "Music.h"
#include "Chunk.h"
#include "Image.h"
#include "Texture.h"
#include "Word.h"

#include "Snake.h"
#include "Fruit.h"

#include "GameProcess.h"

using namespace start;

int main(int argc, char *argv[])
{
    srand(time(0));
    initSDL(gWindow, renderer);
    Music ThemeSong("Music/Theme_Song.mp3"); ThemeSong.playinfi();

game:
    preGame();
    inGame();
    outGame();

    if(again == true)
    {
        again = false;
        score = 0;
        snakeLength = 2;
        goto game;
    }

    quitSDL(gWindow, renderer);
    return 0;
}
