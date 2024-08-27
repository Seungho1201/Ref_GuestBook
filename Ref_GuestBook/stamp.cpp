#include <iostream>
#include "framework.h"

void stamp(HWND hWnd, UINT message, LPARAM lParam) {
    static int stampX, stampY;
    int x, y;
    HDC hdc;

    x = LOWORD(lParam);
    y = HIWORD(lParam);
    hdc = GetDC(hWnd);

    // ������ �ε�
    HICON hIcon = (HICON)LoadImage(NULL, L"heart.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
    if (!hIcon) {
        MessageBox(hWnd, L"Failed to load icon!", L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    switch (message)
    {
    case WM_LBUTTONDOWN:
        stampX = x;
        stampY = y;

        // �������� Ư�� ������ �׸���
        DrawIconEx(hdc, stampX - 32, stampY - 32, hIcon, 64, 64, 0, NULL, DI_NORMAL);
        break;

    case WM_MOUSEMOVE:
        stampX = x;
        stampY = y;
        break;

    case WM_LBUTTONUP:
        break;
    }
}
