#include "c_color.h"

/*
@fn  PenColorManager::Change_Color(int color, COLORREF* penColor)
@brief �� ���� ��� �ڵ�
@param color ����cpp ���Ͽ��� �޾ƿ��� wmId ��
@param penColor �� ���� ������ ����
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