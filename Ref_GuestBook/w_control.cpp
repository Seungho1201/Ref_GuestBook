#include "w_control.h"

PenWidthControl::PenWidthControl() {
    this->textRect = { WIDTH_R_LEFT, 
                       WIDTH_R_TOP, 
                       WIDTH_R_RIGHT,
                       WIDTH_R_BOTTOM };
}

void PenWidthControl::widthControl(HWND g_Hwnd, int func, int* pen_Width, int* stamp_Size, bool* stampActive)
{
    switch (func)
    {
    case W_UP:
        // 펜 최대 굵기는 20
        if (*pen_Width == 20)   { break; }
        if (*stamp_Size == 100) { break; }

        if (*stampActive == true) { 
            *stamp_Size += 10; 
        } else { 
            *pen_Width += 1; 
        }

        InvalidateRect(g_Hwnd, &this->textRect, TRUE);  // 텍스트 영역만 무효화
        UpdateWindow(g_Hwnd);

        break;

    case W_DOWN:
        // 펜 최소 굵기는 1
        if (*pen_Width == 1)   { break; }
        if (*stamp_Size == 10) { break; }

        if (*stampActive == true) { 
            *stamp_Size -= 10; 
        } else {
            *pen_Width -= 1; 
        }
        InvalidateRect(g_Hwnd, &this->textRect, TRUE);  // 텍스트 영역만 무효화
        UpdateWindow(g_Hwnd);
        break;
    }
}