#pragma once

#include <iostream>
#include "framework.h"
#include "Ref_GuestBook.h"


class PenWidthControl {

private:
    RECT textRect;

public:
    PenWidthControl();
  

    void widthControl(HWND g_Hwnd, int func, int* pen_Width, int* stamp_size, bool* stampActive);

    
};