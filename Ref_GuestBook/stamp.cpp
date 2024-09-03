#include <iostream>
#include <windows.h>
#include "framework.h"
#include "Pen_Str.h"
#include "stamp.h"

// �������� ����
extern int stamp_Size;
extern int stampIcon;

extern bool stampActive;
extern vector<PEN_INFO> penMemory;

void stamp(HWND hWnd, UINT message, LPARAM lParam, INT stampIcon) {
    static int stampX, stampY;
    int x, y;
    HDC hdc;

    x = LOWORD(lParam);
    y = HIWORD(lParam);
    hdc = GetDC(hWnd);

    // ������ �ε� �� ũ�� ����
    int stampWidth = stamp_Size;  // ���ϴ� ������ �ʺ�
    int stampHeight = stamp_Size; // ���ϴ� ������ ����

    HICON hIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(stampIcon), IMAGE_ICON, stampWidth, stampHeight, 0);
    if (!hIcon) {
        MessageBox(hWnd, L"�������� �ε��� �� �����ϴ�.", L"Error", MB_OK | MB_ICONERROR);
        ReleaseDC(hWnd, hdc);
        return;
    }

    // �������� Ŀ���� ���
    HCURSOR hCursor = CopyIcon(hIcon);
    if (!hCursor) {
        MessageBox(hWnd, L"Ŀ���� ������ �� �����ϴ�.", L"Error", MB_OK | MB_ICONERROR);
        DestroyIcon(hIcon);
        ReleaseDC(hWnd, hdc);
        return;
    }

    SetCursor(hCursor);  // Ŀ�� ����

    switch (message)
    {
    case WM_LBUTTONDOWN:
        stampX = x;
        stampY = y;

        // �������� Ư�� ������ �׸���
        DrawIconEx(hdc, stampX - stampWidth / 2, stampY - stampHeight / 2, hIcon, stampWidth, stampHeight, 0, NULL, DI_NORMAL);

        //replay cpp Ȯ�� �ٶ�
        g_Pen_Info.penCoordinate = lParam;              // ���콺 x, y ��ǥ (lParam) 
        //g_Pen_Info.penWidth = pen_Width;                // �� ���� (�⺻ �� 10)
        //g_Pen_Info.penColor = pen_Color;                // �� ���� (�⺻ �� RGB(0, 0, 0))
        g_Pen_Info.penTime = (DWORD)GetTickCount64();   // �׸��� �ð�
        g_Pen_Info.penState = message;                  // ���� (ex WM_LBUTTONDOWN)
        g_Pen_Info.test = true;
        g_Pen_Info.img = stampIcon;
        // ���� ������ �� ����ü ������ PUSH
        penMemory.push_back(g_Pen_Info);

        break;

    case WM_MOUSEMOVE:
        stampX = x;
        stampY = y;
        break;

    case WM_LBUTTONUP:
        break;
    }

    ReleaseDC(hWnd, hdc);

    // ���ҽ� ����
    DestroyCursor(hCursor);  // Ŀ�� ����
    DestroyIcon(hIcon);      // ������ ����
}

