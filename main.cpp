#include <iostream>
#include "game/Game.h"
#include "game/actors/ball/Ball.h"
#include "game/actors/pad/Pad.h"

//https://refactoring.guru/design-patterns/visitor/cpp/example
//https://github.com/gameprogcpp/code/blob/master/Chapter01/Game.cpp

int main() {
    // Creating the object by passing Height and Width value.
    Game game(600, 1024);
    game.RunLoop();

//    SDL_Event event;    // Event variable

    // Below while loop checks if the window has terminated using close in the
    //  corner.
//    game.draw_circle(200, 100, 50);

//    while(!(event.type == SDL_QUIT)){
//        SDL_Delay(10);  // setting some Delay
//        SDL_PollEvent(&event);  // Catching the poll event.
//    }

//    auto ball = new Ball();
//    auto pad = new Pad();
//
//    pad->accept(ball);
    return 0;
}
