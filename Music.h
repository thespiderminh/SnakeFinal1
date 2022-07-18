#pragma once

class Music{
private:
    Mix_Music* music;
public:
    Music(){
        music = NULL;
    }

    Music(string path){
        music = Mix_LoadMUS(path.c_str());
    }

    ~Music()
    {
        Mix_FreeMusic( music );
        music = NULL;
    }

    void playinfi(){
        Mix_PlayMusic(music, -1);
    }

    void playonce(){
        Mix_PlayMusic(music, 0);
    }
};
