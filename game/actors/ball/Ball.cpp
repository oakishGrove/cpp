//
// Created by oak on 2021-12-20.
//

#include "Ball.h"

void Ball::visit(Pad *pad) {
    if (SDL_HasIntersection(&this->form, pad->getRect())) {
        this->x_direction *= -1;

        if (pad->getRect()->x < 100) {
            this->form.x = pad->getRect()->x + pad->getRect()->w;
        } else if (pad->getRect()->x > windowHeight - 100) {
            this->form.x = pad->getRect()->x - form.w;
        }
    }
}

void Ball::draw(SDL_Renderer *renderer) {
    Actor::draw(renderer);
    SDL_SetRenderDrawColor(renderer, 100, 200, 0, 255);
    SDL_RenderFillRect(renderer, &form);
}

void Ball::update(float deltaTime) {
    form.x += static_cast<int>(120 * deltaTime * x_direction);
    if (form.y < 0 && y_direction < 1) {
        y_direction = 1;
    } else if (form.y + form.h > windowHeight && y_direction > -1) {
        y_direction = -1;
    }
    form.y += static_cast<int>(120 * deltaTime * y_direction);
}
