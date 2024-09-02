#pragma once

#include <windef.h>
#include <wingdi.h>

void Square(HDC hdc) {

    ///�簢�� �׸������� �� ���� PS_SOLID(�� ���� ����),�β�,����(RGB)��
    HPEN MyPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
    HPEN OldPen = (HPEN)SelectObject(hdc, MyPen);

    ///�簢�� (hdc,left, top, right, bottom)
    Rectangle(hdc, 10, 120, 1000, 700);
    SelectObject(hdc, OldPen);

    DeleteObject(MyPen);
}
