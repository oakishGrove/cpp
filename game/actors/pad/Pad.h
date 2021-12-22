//
// Created by oak on 2021-12-20.
//
#ifndef GAMESDEV_PAD_H
#define GAMESDEV_PAD_H

#include "../actor/Actor.h"
#include "../actor/Visitor.h"
#include <SDL_render.h>
#include <array>

class Pad: public Actor {
public:
    Pad(int x, int y, int width, int height, int windowHeight);
    void accept(Visitor *visitor) override;
    void draw(SDL_Renderer *) override;
    void setDirection(int8_t new_direction);
    void update(float deltaTime);
    SDL_Rect* getRect() { return &form; }
private:
    SDL_Rect form;
    int8_t direction;
    int windowHeight;
};

#endif //GAMESDEV_PAD_H