#pragma once

#include <iostream>
#include "framework.h"
#include "Pen_Str.h"

class Eraser {

public:
    Eraser() = default;
    ~Eraser() = default;

    Eraser(const Eraser&) = delete;
    Eraser& operator=(const Eraser&) = delete;

    void erase(HWND hWnd);
};

