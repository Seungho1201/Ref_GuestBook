#include "Stamp.h"
#include <iostream>

Stamp::Stamp(int size, int icon, std::vector<PEN_INFO>& memory)
    : stampSize(size), stampIcon(icon), penMemory(memory), stampX(0), stampY(0) {}

void Stamp::handleStamp(HWND hWnd, UINT message, LPARAM lParam) {
    int x = LOWORD(lParam);
    int y = HIWORD(lParam);
    HDC hdc = GetDC(hWnd);

    InvalidateRect(hWnd, &stamptext, TRUE);  // 텍스트 영역만 무효화
    UpdateWindow(hWnd);

    // 아이콘 로드 및 크기 조정
    HICON hIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(stampIcon), IMAGE_ICON, stampSize, stampSize, 0);
    if (!hIcon) {
        MessageBox(hWnd, L"아이콘을 로드할 수 없습니다.", L"Error", MB_OK | MB_ICONERROR);
        ReleaseDC(hWnd, hdc);
        return;
    }

    switch (message) {
    case WM_LBUTTONDOWN:
        stampX = x;
        stampY = y;

        // 아이콘을 그리기
        drawIcon(hdc, stampX, stampY, hIcon);

        // 그리기 정보 저장
        PEN_INFO g_Pen_Info;
        g_Pen_Info.penCoordinate = lParam;
        g_Pen_Info.penTime = (DWORD)GetTickCount64();
        g_Pen_Info.penState = message;
        g_Pen_Info.stampImg = stampIcon;
        g_Pen_Info.stampSize = stampSize;
        g_Pen_Info.test = true;

        // 펜 정보 벡터에 저장
        penMemory.push_back(g_Pen_Info);
        break;

    case WM_MOUSEMOVE:
        stampX = x;
        stampY = y;
        break;

    case WM_LBUTTONUP:
        // 여기서 추가 기능을 구현할 수 있습니다.
        break;
    }

    ReleaseDC(hWnd, hdc);
    DestroyIcon(hIcon);
}

void Stamp::drawIcon(HDC hdc, int x, int y, HICON hIcon) {
    // 아이콘을 중심으로 그리기
    DrawIconEx(hdc, x - stampSize / 2, y - stampSize / 2, hIcon, stampSize, stampSize, 0, NULL, DI_NORMAL);
}
