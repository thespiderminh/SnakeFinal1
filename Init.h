#pragma once

#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<vector>
#include<string>
#include<fstream>

using namespace std;

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;
int SCREEN_FPS;
int SCREEN_TICK_PER_FRAME;
const int snakeWidth = 20;
int snakeLength = 2;

int snk[100][2] = {{0, 0}};

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;

static SDL_Renderer* renderer;
static SDL_Event event;

bool quit = false, border, again = false;

namespace start{
    void logSDLError(ostream& os, const string& msg, bool fatal){
        os << msg << " Error: " << SDL_GetError() << endl;
        if(fatal){
            SDL_Quit();
            exit(1);
        }
    }

    void initSDL(SDL_Window*& window, SDL_Renderer*& renderer){
        if(SDL_Init(SDL_INIT_EVERYTHING) < 0) logSDLError(cout, "SDL_Init", true);
        gWindow = SDL_CreateWindow("Min's Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        gScreenSurface = SDL_GetWindowSurface( gWindow );
        if(window == nullptr) logSDLError(cout, "CreateWindow", true);

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if(renderer  == nullptr) logSDLError(cout, "CreateRenderer", true);
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

        Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );

        TTF_Init();
    }

    void quitSDL(SDL_Window* window, SDL_Renderer* renderer){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }

    SDL_Texture* loadTexture(SDL_Renderer* renderer, string path){
        SDL_Texture* newTexture = NULL;
        SDL_Surface* loadedSurface = IMG_Load(path.c_str());
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        SDL_FreeSurface(loadedSurface);
        return newTexture;
    }
}
