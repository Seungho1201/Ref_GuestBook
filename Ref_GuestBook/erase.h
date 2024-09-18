#pragma once

#include <vector>
#include <iostream>
#include "framework.h"
#include "Resource.h"

class Eraser {
public:
    Eraser();
    void erase(HWND hWnd, std::vector<Pen_Info>* penMemory);

private:
    RECT paintArea;
};



