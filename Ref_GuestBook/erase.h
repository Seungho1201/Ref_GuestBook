#pragma once

#include <iostream>
#include "framework.h"
#include "Ref_GuestBook.h"

class Eraser {
public:
    Eraser();
    void erase(HWND hWnd, vector<Pen_Info>* penMemory);

private:
    RECT paintArea;
};



