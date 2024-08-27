#include <iostream>
#include "framework.h"

extern bool stampActive;

void stamp(HWND hWnd, UINT message, LPARAM lParam, INT stampIcon) {
    static int stampX, stampY;
    int x, y;
    HDC hdc;

    x = LOWORD(lParam);
    y = HIWORD(lParam);
    hdc = GetDC(hWnd);

    // ������ �ε� �� ũ�� ����
    int stampWidth = 80;  // ���ϴ� ������ �ʺ�
    int stampHeight = 80; // ���ϴ� ������ ����

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
