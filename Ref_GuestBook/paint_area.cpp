#include <windows.h>

const int left = 10, top = 120, right = 1000, bottom = 700;


void Square(HDC hdc) {

     ///�簢�� �׸������� �� ���� PS_SOLID(�� ���� ����),�β�,����(RGB)��
     HPEN MyPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
     HPEN OldPen = (HPEN)SelectObject(hdc, MyPen);

     ///�簢�� (hdc,left, top, right, bottom)
     Rectangle(hdc, left, top, right, bottom);
     SelectObject(hdc, OldPen);

     DeleteObject(MyPen);
}