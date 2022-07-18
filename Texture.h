#pragma once

#include "Chunk.h"

using namespace start;

class Texture
{
private:

public:
    SDL_Rect rect;
    SDL_Texture *texture;

    Texture()
    {
        texture = NULL;
    }

    ~Texture()
    {
        free();
    }

    void free()
    {
        if( texture != NULL )
        {
            SDL_DestroyTexture( texture );
            texture = NULL;
        }
    }

    Texture(string path)
    {
        texture = loadTexture(renderer, path.c_str());
    }

    void loadTextureFromFile()
    {
        texture = NULL;
    }

    void loadTextureFromFile(string path)
    {
        texture = loadTexture(renderer, path.c_str());
    }

    void render(int x, int y, int w, int h)
    {
        rect = {x, y, w, h};
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }

    void render()
    {
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }

    void render(int x, int y, int w, int h, double angle, SDL_Point* center, SDL_RendererFlip flip)
    {
        rect = {x, y, w, h};
        SDL_RenderCopyEx( renderer, texture, NULL, &rect, angle, center, flip );
    }

    void render(double angle, SDL_Point* center, SDL_RendererFlip flip)
    {
        SDL_RenderCopyEx( renderer, texture, NULL, &rect, angle, center, flip );
    }

    void setRect(int x, int y, int w, int h)
    {
        rect = {x, y, w, h};
    }

    void render(Uint8 r)
    {
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(texture, r);
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }
};
