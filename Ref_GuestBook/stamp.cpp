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

    // 아이콘 로드 및 크기 조정
    int stampWidth = 80;  // 원하는 아이콘 너비
    int stampHeight = 80; // 원하는 아이콘 높이

    HICON hIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(stampIcon), IMAGE_ICON, stampWidth, stampHeight, 0);
    if (!hIcon) {
        MessageBox(hWnd, L"아이콘을 로드할 수 없습니다.", L"Error", MB_OK | MB_ICONERROR);
        ReleaseDC(hWnd, hdc);
        return;
    }

    // 아이콘을 커서로 사용
    HCURSOR hCursor = CopyIcon(hIcon);
    if (!hCursor) {
        MessageBox(hWnd, L"커서를 복사할 수 없습니다.", L"Error", MB_OK | MB_ICONERROR);
        DestroyIcon(hIcon);
        ReleaseDC(hWnd, hdc);
        return;
    }

    SetCursor(hCursor);  // 커서 변경

    switch (message)
    {
    case WM_LBUTTONDOWN:
        stampX = x;
        stampY = y;

        // 아이콘을 특정 영역에 그리기
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

    // 리소스 해제
    DestroyCursor(hCursor);  // 커서 해제
    DestroyIcon(hIcon);      // 아이콘 해제
}
