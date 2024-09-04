#include <windows.h>
#include "paint_area.h"

void Square(HDC hdc) {

     ///�簢�� �׸������� �� ���� PS_SOLID(�� ���� ����),�β�,����(RGB)��
     HPEN MyPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
     HPEN OldPen = (HPEN)SelectObject(hdc, MyPen);

     ///�簢�� (hdc,left, top, right, bottom)
     Rectangle(hdc, Rectangle_left, Rectangle_top, Rectangle_right, Rectangle_bottom);
     SelectObject(hdc, OldPen);

     DeleteObject(MyPen);
}