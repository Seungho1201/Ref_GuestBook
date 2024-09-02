#pragma once

#include <windef.h>
#include <wingdi.h>

void Square(HDC hdc) {

    ///사각형 그리기위한 펜 설정 PS_SOLID(선 종류 선택),두께,색상(RGB)값
    HPEN MyPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
    HPEN OldPen = (HPEN)SelectObject(hdc, MyPen);

    ///사각형 (hdc,left, top, right, bottom)
    Rectangle(hdc, 10, 120, 1000, 700);
    SelectObject(hdc, OldPen);

    DeleteObject(MyPen);
}
