#pragma once

#include "point.h"

// A Stick is a constraint between two points. This prevents the distance
// between two points from being different than a certain length.
class Stick {
    private:
        // The endpoints of the stick.
        Point *start;
        Point *end;

        // The desired length between the endpoints.
        float length;

    public:
        // Stick constructor.
        Stick(Point *newStart, Point *newEnd);

        // Constrains the endpoint distance to the desired length.
        void constrain();
};