#include <iostream>
#include "framework.h"
#include "Pen_Str.h"

// �������� ����
extern vector<PEN_INFO> penMemory;
extern PEN_INFO g_Pen_Info;
extern COLORREF pen_Color;
extern int pen_Width;

void drawLine(HWND hWnd, UINT message, LPARAM lParam)
{
    static int preX, preY;
    static bool drawStart = false;
    int x, y;
    HDC hdc;
    HPEN myP, osP;

    x = LOWORD(lParam);
    y = HIWORD(lParam);
    hdc = GetDC(hWnd);

    myP = CreatePen(PS_SOLID, pen_Width, pen_Color);
    osP = (HPEN)SelectObject(hdc, myP);

    switch (message)
    {
    case WM_LBUTTONDOWN:
        drawStart = true;

        MoveToEx(hdc, x, y, NULL);
        LineTo(hdc, x, y);

        preX = x;
        preY = y;

        // �� LBUTTON state �� ������ ����ü�� ����
        g_Pen_Info.penCoordinate = lParam;              // ���콺 x, y ��ǥ (lParam) 
        g_Pen_Info.penWidth = pen_Width;                // �� ���� (�⺻ �� 10)
        g_Pen_Info.penColor = pen_Color;                // �� ���� (�⺻ �� RGB(0, 0, 0))
        g_Pen_Info.penTime = (DWORD)GetTickCount64();   // �׸��� �ð�
        g_Pen_Info.penState = message;                  // ���� (ex WM_LBUTTONDOWN)

        // ���� ������ �� ����ü ������ PUSH
        penMemory.push_back(g_Pen_Info);
        break;

    case WM_MOUSEMOVE:

        if (drawStart)  
        {
            MoveToEx(hdc, preX, preY, NULL);
            LineTo(hdc, x, y);

            preX = x;
            preY = y;

            // �� LBUTTON state �� ������ ����ü�� ����
            g_Pen_Info.penCoordinate = lParam;
            g_Pen_Info.penWidth = pen_Width;
            g_Pen_Info.penColor = pen_Color;
            g_Pen_Info.penTime = (DWORD)GetTickCount64();
            g_Pen_Info.penState = message;

            // ���� ������ �� ����ü ������ PUSH
            penMemory.push_back(g_Pen_Info);
            break;
        }
        break;

    case WM_LBUTTONUP:
        if (drawStart)
        {
            // �� LBUTTON state �� ������ ����ü�� ����
            g_Pen_Info.penCoordinate = lParam;
            g_Pen_Info.penWidth = pen_Width;
            g_Pen_Info.penColor = pen_Color;
            g_Pen_Info.penTime = (DWORD)GetTickCount64();
            g_Pen_Info.penState = message;

            // ���� ������ �� ����ü ������ PUSH
            penMemory.push_back(g_Pen_Info);

            drawStart = false;
            break;
        }
        break;
    }

    SelectObject(hdc, osP);
    DeleteObject(myP);  // ���� ����

    ReleaseDC(hWnd, hdc);  // HDC �ڿ� ����
}