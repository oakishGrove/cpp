//
// Created by oak on 2021-12-20.
//

#include "Pad.h"
#include <iostream>

Pad::Pad(int x, int y, int width_, int height_, int windowHeight)
: form({x, y, width_, height_}), direction{0}, windowHeight{windowHeight}
{}

void Pad::accept(Visitor *visitor) {
    visitor->visit(this);
}

void Pad::draw(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 100, 200, 0, 255);
    SDL_RenderFillRect(renderer, &form);
}

void Pad::update(float deltaTime) {
    form.y += static_cast<int>(500 * deltaTime * direction);
    if (form.y < 0) {
        form.y = 0;
    }
    if (form.y + form.h > windowHeight) {
       form.y = windowHeight - form.h;
    }
}

void Pad::setDirection(int8_t new_direction) {
//    std::cout << "set new pad direction: " << (int ) new_direction << '\n';
    direction = new_direction;
}

