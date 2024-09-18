#pragma once

#include <iostream>
#include "framework.h"
#include "Resource.h"


class PenWidthControl {

private:
    RECT textRect;
    HDC wc_Hdc;

public:
    PenWidthControl();
 
    void widthControl(HWND g_Hwnd, int func, int* pen_Width, int* stamp_size, bool* stampActive);

    void penWidthDisplay(HDC Hdc, bool* stampActive, int* stamp_Size, int* pen_Width);
    
};