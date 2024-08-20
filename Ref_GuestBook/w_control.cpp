#include <iostream>
#include "framework.h"
#include "Pen_Str.h"
#include "Ref_GuestBook.h"

// ����� ���ŵǴ� ���� ����
RECT textRect = { 310 + 100, 15, 340 + 100, 45 };
extern int pen_Width;

// �� ���� ���� �Լ� (HWND, ���� ��)
void w_Control(HWND g_Hwnd, int con)
{
    switch (con)
    {
    case W_UP:
        // �� �ִ� ����� 20
        if (pen_Width == 20) { break; }

        pen_Width += 1;

        InvalidateRect(g_Hwnd, &textRect, TRUE);  // �ؽ�Ʈ ������ ��ȿȭ
        UpdateWindow(g_Hwnd);
        break;

    case W_DOWN:
        // �� �ּ� ����� 1
        if (pen_Width == 1) { break; }

        pen_Width -= 1;

        InvalidateRect(g_Hwnd, &textRect, TRUE);  // �ؽ�Ʈ ������ ��ȿȭ
        UpdateWindow(g_Hwnd);
        break;
    }
}