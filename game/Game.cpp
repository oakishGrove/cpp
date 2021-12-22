//
// Created by oak on 2021-12-20.
//

#include "Game.h"
#include "actors/pad/Pad.h"
#include "actors/ball/Ball.h"

void Game::init_actors() {
    using std::make_shared;
    int padWith = 20;
    int padHeight = 100;
    pad1 = make_shared<Pad>(0, 0, padWith, padHeight, this->height);
    pad2 = make_shared<Pad>(width-padWith, 0, padWith, padHeight, this->height);
    actors.push_back(pad1);
    actors.push_back(pad2);
    ball = make_shared<Ball>(200, 300, padWith, padWith, this->height);
    actors.push_back(ball);
}

void Game::draw_circle(int center_x, int center_y, int radius_){
    // Setting the color to be RED with 100% opaque (0% trasparent).
    SDL_SetRenderDrawColor(renderer, 100, 200, 0, 255);

    // Drawing circle
    for(int x=center_x-radius_; x<=center_x+radius_; x++){
        for(int y=center_y-radius_; y<=center_y+radius_; y++){
            if((std::pow(center_y-y,2)+std::pow(center_x-x,2)) <=
               std::pow(radius_,2)){
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
}

void Game::RunLoop()
{
    while (isRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            // If we get an SDL_QUIT event, end loop
            case SDL_QUIT:
                isRunning = false;
                break;
        }
    }

    // Get state of keyboard
    const Uint8* state = SDL_GetKeyboardState(NULL);
    // If escape is pressed, also end loop
    if (state[SDL_SCANCODE_ESCAPE]) {
        isRunning = false;
    }

    // Update paddle direction based on W/S keys
    if (state[SDL_SCANCODE_W]) {
        pad1->setDirection(-1);
    } else if (state[SDL_SCANCODE_S]) {
        pad1->setDirection(1);
    } else {
        pad1->setDirection(0);
    }

    // Update paddle direction based on W/S keys
    if (state[SDL_SCANCODE_I]) {
        pad2->setDirection(-1);
    } else if (state[SDL_SCANCODE_K]) {
        pad2->setDirection(1);
    } else {
        pad2->setDirection(0);
    }
}

void Game::UpdateGame() {
    // Wait until 16ms has elapsed since last frame
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16))
        ;

    // Delta time is the difference in ticks from last frame
    // (converted to seconds)
    float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;

    // Clamp maximum delta time value
    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }

    // Update tick counts (for next frame)
    ticksCount = SDL_GetTicks();

    pad1->update(deltaTime);
    pad2->update(deltaTime);

    for (auto& actor : actors) {
        actor->accept(ball.get());
    }
    ball->update(deltaTime);

    if (ball->getX() < 0 || ball->getX() > width) {
        isRunning = false;
    }
}

void Game::GenerateOutput() {
    SDL_RenderClear(renderer);// Clear back buffer

    SDL_SetRenderDrawColor(renderer, 100, 50, 50, 255);
    SDL_Rect screen { 0,  0, width, height };
    SDL_RenderFillRect(renderer, &screen);

    for (auto& actor: actors) {
        actor->draw(renderer);
    }

    // Swap front buffer and back buffer
    SDL_RenderPresent(renderer);
}
