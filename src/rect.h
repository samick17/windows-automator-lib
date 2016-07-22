#pragma once

#include "point.h"
#include "size.h"

typedef struct Rect {
    Point position;
    Size size;
    Rect() :Rect(0, 0, 0, 0) {
    }
    Rect(int x, int y, int w, int h) {
        this->position = Point(x, y);
        this->size = Size(w, h);
    }
} Rect;