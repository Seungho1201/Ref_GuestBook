#include "c_color.h"

/*
@fn  PenColorManager::Change_Color(int color, COLORREF* penColor)
@brief 색 변경 기능 코드
@param color 메인cpp 파일에서 받아오는 wmId 값
@param penColor 펜 색상 포인터 변수
*/
void PenColorManager::Change_Color(int color, COLORREF* penColor) {

    switch (color) 
    {
    case C_RED:
        *penColor = RGB(255, 0, 0);
        break;

    case C_ORANGE:
        *penColor = RGB(255, 165, 0);
        break;

    case C_YELLOW:
        *penColor = RGB(255, 255, 0);
        break;

    case C_GREEN:
        *penColor = RGB(0, 128, 0);
        break;

    case C_BLUE:
        *penColor = RGB(0, 0, 255);
        break;

    case C_NAVY:
        *penColor = RGB(0, 0, 128);
        break;

    case C_PURPLE:
        *penColor = RGB(128, 0, 128);
        break;

    case C_BLACK:
        *penColor = RGB(0, 0, 0);
        break;

    default:
        break;
    }
}