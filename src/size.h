#pragma once

typedef struct Size {
    int w;
    int h;
    Size() :Size(0, 0) {
    }
    Size(int w, int h) {
        this->w = w;
        this->h = h;
    }
} Size;