#pragma once

#include<SDL.h>
#include<SDL_image.h>
#include <string>

class Image{
private:
    SDL_Surface* surface;
public:
    SDL_Rect rect;

    Image(){
        surface = NULL;
    }

    Image(string path){
        surface = IMG_Load(path.c_str());
    }

    void loadImage(string path){
        surface = IMG_Load(path.c_str());
    }

    void display(int x, int y){
        rect = {x, y, 200, 200};
        SDL_BlitSurface( surface, NULL, gScreenSurface, &rect);
    }

    void display(){
        SDL_BlitSurface( surface, NULL, gScreenSurface, &rect);
    }
};
