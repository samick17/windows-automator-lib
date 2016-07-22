#pragma once

typedef struct Point {
    int x;
    int y;
    Point() : Point(0, 0) {}
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
} Point;