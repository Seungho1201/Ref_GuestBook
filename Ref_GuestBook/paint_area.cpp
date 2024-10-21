#include "paint_area.h"

PaintAreaSquare::PaintAreaSquare() 
{
    this->MyPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
    this->OldPen = nullptr;
}

PaintAreaSquare::~PaintAreaSquare() 
{
    if (this->MyPen) {
        DeleteObject(this->MyPen);  // 소멸자에서 펜 삭제
    }
}

void PaintAreaSquare::makeSquare(HDC hdc) 
{
    this->OldPen = (HPEN)SelectObject(hdc, MyPen);

    ///사각형 (hdc,left, top, right, bottom)
    Rectangle(hdc, PAINT_R_LEFT, PAINT_R_TOP, PAINT_R_RIGHT, PAINT_R_BOTTOM);
    SelectObject(hdc, OldPen);   
}
