//
// Created by oak on 2021-12-20.
//

#ifndef GAMEDEV_GAME_H
#define GAMEDEV_GAME_H

#include <SDL.h>
#include <vector>
#include <memory>

#include "actors/actor/Actor.h"
#include "actors/pad/Pad.h"
#include "actors/ball/Ball.h"

struct Vector2 {
    float x, y;
};

class Game {
public:
    // Contructor which initialize the parameters.
    Game(int height_, int width_)
    : height(height_), width(width_)
    {
        // Initializing SDL as Video
        if (int sdlResult = SDL_Init(SDL_INIT_VIDEO)) {
            SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
            exit(1);
        }


        // Create an SDL Window
        if (!(this->window = SDL_CreateWindow(
                "Game Programming in C++ (Chapter 1)", // Window title
                100,	// Top left x-coordinate of window
                100,	// Top left y-coordinate of window
                width_,	// Width of window
                height_,	// Height of window
                0		// Flags (0 for no flags set)
        ))) {
            SDL_Log("Failed to create window: %s", SDL_GetError());
            exit(1);
        }

//        //// Create SDL renderer
        if (!(renderer = SDL_CreateRenderer(
                window, // Window to create renderer for
                -1,		 // Usually -1
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
        ))) {
            SDL_Log("Failed to create renderer: %s", SDL_GetError());
            exit(1);
        }
        isRunning = true;

//        SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);      // setting draw color
        SDL_RenderClear(renderer);      // Clear the newly created window
        SDL_RenderPresent(renderer);    // Reflects the changes done in the
        //  window.

        init_actors();
    }

    // Destructor
    ~Game(){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void draw_circle(int center_x, int center_y, int radius_);

//    bool Initialize();
    // Runs the game loop until the game is over
    void RunLoop();
    // Shutdown the game
//    void Shutdown();
    int getHeight() { return height; }
    int getWidth() { return width; }
private:
    // Helper functions for the game loop
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    int height;     // Height of the window
    int width;      // Width of the window
    SDL_Renderer *renderer = NULL;      // Pointer for the renderer
    SDL_Window *window = NULL;      // Pointer for the window
    uint32_t ticksCount = 0;
    bool isRunning;
    std::vector<std::shared_ptr<Actor>> actors;
    std::shared_ptr<Pad> pad1;
    std::shared_ptr<Pad> pad2;
    std::shared_ptr<Ball> ball;

    void init_actors();
};

#endif //FRAMEWORK_GAME_H
