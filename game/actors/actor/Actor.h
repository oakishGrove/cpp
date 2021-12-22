//
// Created by oak on 2021-12-20.
//

#ifndef GAMEDEV_ACTOR_H
#define GAMEDEV_ACTOR_H

#include <SDL_render.h>

class Visitor;

class Actor {
public:
    virtual void accept(Visitor *visitor) {};
    virtual void draw(SDL_Renderer* renderer){}
};


#endif //FRAMEWORK_ACTOR_H
