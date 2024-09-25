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

void PaintAreaSquare::makeSquare(HDC hdc, int rt_right, int rt_bottom) 
{
    this->OldPen = (HPEN)SelectObject(hdc, MyPen);

    ///사각형 (hdc,left, top, right, bottom)
    Rectangle(hdc, PAINT_R_LEFT, PAINT_R_TOP, rt_right-10 , rt_bottom-10);


    SelectObject(hdc, OldPen);   
}
