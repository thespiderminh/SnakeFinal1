int multiply;
int highScore, score = 0;

void preGame()
{
    Texture Title("Image/Title.png");
    Texture background("Image/PreGame_Background.png"), start("Image/PlayButton1.png");
    Title.setRect(700, 100, 300, 150);

    while(Title.rect.x >= 300 - Title.rect.w / 2)
    {
        while(SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quitSDL(gWindow, renderer);
                return;
            }
        }
        Title.rect.x -= 2;

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        Title.render();

        SDL_RenderPresent(renderer);
    }

    bool checkCollision = 0, oldCollision = 0;
    Chunk Button("Music/Button.mp3"), Click("Music/Click.mp3");

    while(!quit)
    {
        while(SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quitSDL(gWindow, renderer);
                return;
            }
            else if (event.type == SDL_MOUSEMOTION)
            {
                oldCollision = checkCollision;
                if ((event.motion.x > start.rect.x && event.motion.x < (start.rect.x + start.rect.w)) && (event.motion.y > start.rect.y && event.motion.y < (start.rect.y + start.rect.h)))
                    checkCollision = 1;
                else
                    checkCollision = 0;
                if(oldCollision != checkCollision)
                    Button.playonce();
                if (checkCollision == 0)
                    start.loadTextureFromFile("Image/PlayButton1.png");
                else
                    start.loadTextureFromFile("Image/PlayButton2.png");
            }
            if (checkCollision == 1 && event.type == SDL_MOUSEBUTTONDOWN)
            {
                Click.playonce();
                quit = true;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        background.render(0, 0, 600, 600);
        Title.render();
        start.render(350, 300, 225, 60);

        SDL_RenderPresent(renderer);
    }

    quit = false;
    Text ChooseGamemode("Do you want border or not", 30);
    Text ChooseGamemode2("Press Y or N", 30);
    Text Pressing("Y : Border           N : No border", 25);

    while(!quit)
    {
        while(SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quitSDL(gWindow, renderer);
                return;
            }
            else if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_y && event.key.repeat == 0)
                {
                    border = true;
                    quit = true;
                }
                else if(event.key.keysym.sym == SDLK_n && event.key.repeat == 0)
                {
                    border = false;
                    quit = true;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        background.render(0, 0, 600, 600);
        ChooseGamemode.textRender(0, 20);
        ChooseGamemode2.textRender(60, 70);
        Pressing.textRender(30, 200);

        SDL_RenderPresent(renderer);
    }

    quit = false;
    ChooseGamemode.loadTextureFromText("Choose difficulty", 50);
    ChooseGamemode2.loadTextureFromText("Press E, N or D", 50);
    Pressing.loadTextureFromText("E:Easy     N:Normal   D:Difficult", 25);

    while(!quit)
    {
        while(SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quitSDL(gWindow, renderer);
                return;
            }
            else if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_e && event.key.repeat == 0)
                {
                    SCREEN_FPS = 5; multiply = 1;
                }
                else if(event.key.keysym.sym == SDLK_n && event.key.repeat == 0)
                {
                    SCREEN_FPS = 8; multiply = 2;
                }
                else if(event.key.keysym.sym == SDLK_d && event.key.repeat == 0)
                {
                    SCREEN_FPS = 11; multiply = 3;
                }
                SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;
                return;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        background.render(0, 0, 600, 600);
        ChooseGamemode.textRender(0, 20);
        ChooseGamemode2.textRender(60, 100);
        Pressing.textRender(30, 200);

        SDL_RenderPresent(renderer);
    }
}

void checkEat(Snake &snake, Fruit &fruit, int &Score)
{
    if(snake.getHeadX() < fruit.rect.x + fruit.rect.w && snake.getHeadX() + snakeWidth > fruit.rect.x)
    {
        if(snake.getHeadY() < fruit.rect.y + fruit.rect.h && snake.getHeadY() + snakeWidth > fruit.rect.y)
        {
            if(fruit.type == 1) Score += 1 * multiply;
            else if(fruit.type == 2) Score += 2 * multiply;
            else if(fruit.type == 3) Score += 5 * multiply;

            fruit.loadTextureFromFile();
            fruit.setRect(-100, -100, 30, 30);
            fruit.dissappearTime = SDL_GetTicks();
            fruit.isOnTheScreen = false;
            fruit.createFruit();
            snake.lengthUp();
        }
    }
}

void inGame()
{
    Snake snake;
    Fruit fruit;
    Texture background("Image/Ingame_Background.png");
    Chunk Button("Music/Button.mp3"), Click("Music/Click.mp3");
    bool isPaused = false, oldCollision = 0, checkCollision = 0;
    Texture pauseButton("Image/Pause.png");
    pauseButton.setRect(SCREEN_WIDTH - 50, 0, 50, 50);
    Texture playButton("Image/Play.png");
    playButton.setRect(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 150, 300, 300);
    fstream fileIn;
    fstream fileOut;
    fileIn.open("HighScore.txt", ios::in);
    if(fileIn.is_open())
    {
        fileIn >> highScore;
    }

    while(!quit)
    {
        Text Score("Score : " + to_string(score), 40);
        Text HighScore("Highscore: " + to_string(highScore), 40);
        Uint32 oldTick = SDL_GetTicks();
        while(SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quitSDL(gWindow, renderer);
                return;
            }
            if (event.type == SDL_KEYDOWN)
            {
                snake.handleMove();
                while(SDL_PollEvent(&event) != 0);
            }
            if(event.type == SDL_MOUSEMOTION)
            {
                oldCollision = checkCollision;
                if(event.motion.x >= SCREEN_WIDTH - 50 && event.motion.y <= 50)
                {
                    pauseButton.setRect(SCREEN_WIDTH - 45, 5, 40, 40);
                    checkCollision = true;
                }
                else
                {
                    pauseButton.setRect(SCREEN_WIDTH - 50, 0, 50, 50);
                    checkCollision = false;
                }
                if(oldCollision != checkCollision)
                {
                    Button.playonce();
                }
            }

            if((event.type == SDL_MOUSEBUTTONDOWN && pauseButton.rect.w == 40) || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p && event.key.repeat == 0))
            {
                Mix_PauseMusic();
                isPaused = true;
                Click.playonce();
                checkCollision = false;
                oldCollision = false;
                while(isPaused)
                {
                    while (SDL_PollEvent(&event) != 0)
                    {
                        if (event.type == SDL_QUIT)
                        {
                            quit = true;
                            quitSDL(gWindow, renderer);
                            return;
                        }
                        if(event.type == SDL_MOUSEMOTION)
                        {
                            oldCollision = checkCollision;
                            if(event.motion.x >= SCREEN_WIDTH / 2 - 150 && event.motion.y >= SCREEN_HEIGHT / 2 - 150 && event.motion.x <= SCREEN_WIDTH / 2 + 150 && event.motion.y <= SCREEN_HEIGHT / 2 + 150)
                            {
                                playButton.setRect(SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT / 2 - 120, 240, 240);
                                checkCollision = true;
                            }
                            else
                            {
                                playButton.setRect(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 150, 300, 300);
                                checkCollision = false;
                            }
                            if(oldCollision != checkCollision)
                            {
                                    Button.playonce();
                            }
                        }
                        if((event.type == SDL_MOUSEBUTTONDOWN && playButton.rect.w == 240) || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p && event.key.repeat == 0))
                        {
                            isPaused = false;
                            break;
                            playButton.setRect(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 150, 300, 300);
                        }
                    }
                    if(isPaused == false)
                    {
                        checkCollision = false;
                        oldCollision = false;
                        Click.playonce();
                        break;
                    }
                    playButton.render();

                    SDL_RenderPresent(renderer);
                }
                pauseButton.setRect(SCREEN_WIDTH - 50, 0, 50, 50);
                Mix_ResumeMusic();
            }
        }

        if(snake.checkDead() == true) quit = true;
        snake.snakeMove();
        fruit.moveFruit();

        checkEat(snake, fruit, score);

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        background.render(0, 0, 600, 600);
        snake.renderSnake();
        pauseButton.render();
        fruit.renderFruit();
        Score.textRender(0, 0);
        HighScore.textRender(0, 50);

        SDL_RenderPresent(renderer);

        Uint32 frameTicks = SDL_GetTicks() - oldTick;

        if( frameTicks < SCREEN_TICK_PER_FRAME )
        {
            SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks );
        }
    }

    quit = false;

    if(score > highScore)
    {
        highScore = score;
        fileOut.open("HighScore.txt", ios::out);
        fileOut << highScore;
    }
}

void outGame()
{
    Texture background("Image/OutGame_Background.png");
    Text Score("Score : " + to_string(score), 40);
    Text HighScore("Highscore: " + to_string(highScore), 40);
    Text Again("Press R to restart game", 30);

    while(!quit)
    {
        while(SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quitSDL(gWindow, renderer);
                return;
            }
            else if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_r)
                {
                    again = true;
                    return;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        background.render(0, 0, 600, 600);
        Score.textRender(200, 350);
        HighScore.textRender(160, 400);
        Again.textRender(50, 500);

        SDL_RenderPresent(renderer);
    }
}
