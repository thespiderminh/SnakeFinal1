#pragma once

class Chunk{
private:
    Mix_Chunk* chunk;
public:
    Chunk(){
        chunk = NULL;
    }

    Chunk(string path){
        chunk = Mix_LoadWAV(path.c_str());
    }

    ~Chunk()
    {
        Mix_FreeChunk( chunk );
        chunk = NULL;
    }

    void loadSoundFromFile(string path)
    {
        chunk = Mix_LoadWAV(path.c_str());
    }

    void playinfi(){
        Mix_PlayChannel(-1, chunk, -1);
    }

    void playonce(){
        Mix_PlayChannel(-1, chunk, 0);
    }
};
