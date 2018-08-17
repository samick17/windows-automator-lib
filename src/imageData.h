#pragma once

#include <string.h>

typedef struct ImageData {
    int width;
    int height;
    std::vector<BYTE> data;
} ImageData;
