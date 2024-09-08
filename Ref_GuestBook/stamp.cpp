#include "Stamp.h"
#include <iostream>

Stamp::Stamp(int size, int icon, std::vector<PEN_INFO>& memory)
    : stampSize(size), stampIcon(icon), penMemory(memory), stampX(0), stampY(0) {}

void Stamp::handleStamp(HWND hWnd, UINT message, LPARAM lParam) {
    int x = LOWORD(lParam);
    int y = HIWORD(lParam);
    HDC hdc = GetDC(hWnd);

    InvalidateRect(hWnd, &stamptext, TRUE);  // �ؽ�Ʈ ������ ��ȿȭ
    UpdateWindow(hWnd);

    // ������ �ε� �� ũ�� ����
    HICON hIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(stampIcon), IMAGE_ICON, stampSize, stampSize, 0);
    if (!hIcon) {
        MessageBox(hWnd, L"�������� �ε��� �� �����ϴ�.", L"Error", MB_OK | MB_ICONERROR);
        ReleaseDC(hWnd, hdc);
        return;
    }

    switch (message) {
    case WM_LBUTTONDOWN:
        stampX = x;
        stampY = y;

        // �������� �׸���
        drawIcon(hdc, stampX, stampY, hIcon);

        // �׸��� ���� ����
        PEN_INFO g_Pen_Info;
        g_Pen_Info.penCoordinate = lParam;
        g_Pen_Info.penTime = (DWORD)GetTickCount64();
        g_Pen_Info.penState = message;
        g_Pen_Info.stampImg = stampIcon;
        g_Pen_Info.stampSize = stampSize;
        g_Pen_Info.test = true;

        // �� ���� ���Ϳ� ����
        penMemory.push_back(g_Pen_Info);
        break;

    case WM_MOUSEMOVE:
        stampX = x;
        stampY = y;
        break;

    case WM_LBUTTONUP:
        // ���⼭ �߰� ����� ������ �� �ֽ��ϴ�.
        break;
    }

    ReleaseDC(hWnd, hdc);
    DestroyIcon(hIcon);
}

void Stamp::drawIcon(HDC hdc, int x, int y, HICON hIcon) {
    // �������� �߽����� �׸���
    DrawIconEx(hdc, x - stampSize / 2, y - stampSize / 2, hIcon, stampSize, stampSize, 0, NULL, DI_NORMAL);
}
