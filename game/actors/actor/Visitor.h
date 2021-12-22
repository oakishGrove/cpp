#ifndef GAMEDEV_VISITOR_H
#define GAMEDEV_VISITOR_H

class Pad;

class Visitor {
public:
    virtual void visit(Pad *pad) = 0;
};

#endif //FRAMEWORK_VISITOR_H
