#include <windows.h>
#include "paint_area.h"

void Square(HDC hdc) {

     ///사각형 그리기위한 펜 설정 PS_SOLID(선 종류 선택),두께,색상(RGB)값
     HPEN MyPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
     HPEN OldPen = (HPEN)SelectObject(hdc, MyPen);

     ///사각형 (hdc,left, top, right, bottom)
     Rectangle(hdc, Rectangle_left, Rectangle_top, Rectangle_right, Rectangle_bottom);
     SelectObject(hdc, OldPen);

     DeleteObject(MyPen);
}