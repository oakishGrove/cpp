#ifndef GAMEDEV_BALL_H
#define GAMEDEV_BALL_H

#include "../actor/Actor.h"
#include "../actor/Visitor.h"
#include "../pad/Pad.h"


class Ball: public Visitor, public Actor {
public:
    Ball(int x, int y, int w, int h, int windowHeight_):
            form{x, y, w, h},
            x_direction{-1},
            y_direction{1},
            windowHeight{windowHeight_}
    {}
    void visit(Pad *pad);
    void draw(SDL_Renderer *renderer) override;
    void update(float deltaTime);
    int getX() { return form.x; }
private:
    SDL_Rect form;
    int8_t x_direction;
    int8_t y_direction;
    int windowHeight;
};

#endif //FRAMEWORK_BALL_H
