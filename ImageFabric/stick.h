#pragma once

#include "point.h"

class Stick
{
    private:
        Point *start;
        Point *end;
        float length;

    public:
        Stick(Point *newStart, Point *newEnd);
        void constrain(float deltaTime);
};

