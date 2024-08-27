#include <iostream>
#include "framework.h"
#include "Pen_Str.h"
#include "c_color.h"

    /*
    펜 색상 변경 함수
    */
void Change_Color(int color) {

    
    switch (color)
    {
    case C_RED:
        pen_Color = RGB(255, 0, 0);
        break;
    case C_ORANGE:
        pen_Color = RGB(255, 165, 0);
        break;
    case C_YELLOW:
        pen_Color = RGB(255, 255, 0);
        break;
    case C_GREEN:
        pen_Color = RGB(0, 128, 0);
        break;
    case C_BLUE:
        pen_Color = RGB(0, 0, 255);
        break;
    case C_NAVY:
        pen_Color = RGB(0, 0, 128);
        break;
    case C_PURPLE:
        pen_Color = RGB(128, 0, 128);
        break;
    case C_BLACK:
        pen_Color = RGB(0, 0, 0);
        break;
    default:
        break;
    }

}