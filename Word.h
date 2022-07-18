#pragma once

class Text : public Texture
{
private:
    SDL_Color textColor = { 0, 0, 0, 255 };
    TTF_Font *font = TTF_OpenFont( "SnakeChan.ttf", 30 );
    SDL_Texture* textTexture = NULL;
public:
    SDL_Rect textSize = {0, 0, 0, 0};

    Text()
    {

    }

    ~Text()
    {
        free();
        TTF_CloseFont( font );
        font = NULL;
    }

    Text(string text, int fontSize)
    {
        font = TTF_OpenFont( "SnakeChan.ttf", fontSize );
        SDL_Surface* textSurface = TTF_RenderText_Solid( font, text.c_str(), textColor );
        textTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
        SDL_FreeSurface(textSurface);
        TTF_SizeText(font, text.c_str(), &textSize.w, &textSize.h);
        rect.w = textSize.w;
        rect.h = textSize.h;
    }

    void loadTextureFromText(string text, int fontSize)
    {
        font = TTF_OpenFont( "SnakeChan.ttf", fontSize );
        SDL_Surface* textSurface = TTF_RenderText_Solid( font, text.c_str(), textColor );
        textTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
        SDL_FreeSurface(textSurface);
        TTF_SizeText(font, text.c_str(), &textSize.w, &textSize.h);
        rect.w = textSize.w;
        rect.h = textSize.h;
    }

    void loadTextureFromText()
    {
        textTexture = NULL;
        rect.x = SCREEN_WIDTH;
    }

    void textRender(int _x, int _y)
    {
        rect.x = _x;
        rect.y = _y;
        SDL_RenderCopy(renderer, textTexture, &textSize, &rect);
    }
};
