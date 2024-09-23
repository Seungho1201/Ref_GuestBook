#pragma once

#include "Ref_GuestBook.h"
#include "framework.h"
#include "Resource.h"

class Eraser {
public:
    Eraser();
    void erase(HWND hWnd, std::vector<Pen_Info>* penMemory);

private:
    RECT paintArea;
};



