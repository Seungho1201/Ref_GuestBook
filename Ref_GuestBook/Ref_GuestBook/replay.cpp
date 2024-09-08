#include <iostream>
#include <windows.h>
#include "framework.h"
#include "Pen_Str.h"

// ������� ���ڸ� �ϳ��ۿ� ���ޱ⿡ HWND ���������� ������ �׸񿡼� �Ҵ�
extern HWND g_Hwnd;

DWORD WINAPI replay(LPVOID points)
{
    HDC hdc;
    HPEN myP, osP;

    hdc = GetDC(g_Hwnd);
    int x, y;

    // ��û�� �ٷ� ó������ �ʰ� �޼��� ť�� ���� �� ��� �۾��� ���� �� ����
    InvalidateRect(g_Hwnd, NULL, TRUE);

    // ��� ������Ʈ ��û�� ������ ��� �۾��� ������ ����Ǵ� InvalidateRect �Լ��� ��� ȣ��
    UpdateWindow(g_Hwnd);

    // ���� ���� penMemory�� �ݺ�
    for (size_t i = 0; i < (int)penMemory.size(); i++)
    {

        myP = CreatePen(PS_SOLID, penMemory[i].penWidth, penMemory[i].penColor);
        osP = (HPEN)SelectObject(hdc, myP);

        switch (penMemory[i].penState)
        {
        case WM_LBUTTONDOWN:
            x = LOWORD(penMemory[i].penCoordinate);
            y = HIWORD(penMemory[i].penCoordinate);

            MoveToEx(hdc, x, y, NULL);
            LineTo(hdc, x, y);  //�����
            break;

        case WM_MOUSEMOVE:
            LineTo(hdc, LOWORD(penMemory[i].penCoordinate), HIWORD(penMemory[i].penCoordinate));
            break;

        case WM_LBUTTONUP:
            LineTo(hdc, LOWORD(penMemory[i].penCoordinate), HIWORD(penMemory[i].penCoordinate));
            break;

        default:
            break;
        }

        // ���� ���� �ݺ� �ߴ���
        if (i + 1 < penMemory.size() && penMemory[i + 1].penState == WM_MOUSEMOVE)
        {
            Sleep(penMemory[i + 1].penTime - penMemory[i].penTime);
        }

        
        SelectObject(hdc, osP);
        DeleteObject(myP);          // ���ҽ� �ڿ� Ȯ�� ���� ����
    }

    ReleaseDC(g_Hwnd, hdc);
    return 0;
}