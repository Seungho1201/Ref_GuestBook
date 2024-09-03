#include <iostream>
#include <windows.h>
#include "framework.h"
#include "Pen_Str.h"
#include "stamp.h"

// 전역변수 정의
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

    // 아이콘 로드 및 크기 조정
    int stampWidth = stamp_Size;  // 원하는 아이콘 너비
    int stampHeight = stamp_Size; // 원하는 아이콘 높이

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

        //replay cpp 확인 바람
        g_Pen_Info.penCoordinate = lParam;              // 마우스 x, y 좌표 (lParam) 
        //g_Pen_Info.penWidth = pen_Width;                // 펜 굵기 (기본 값 10)
        //g_Pen_Info.penColor = pen_Color;                // 펜 색상 (기본 값 RGB(0, 0, 0))
        g_Pen_Info.penTime = (DWORD)GetTickCount64();   // 그리기 시간
        g_Pen_Info.penState = message;                  // 상태 (ex WM_LBUTTONDOWN)
        g_Pen_Info.test = true;
        g_Pen_Info.img = stampIcon;
        // 벡터 변수에 위 구조체 데이터 PUSH
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

    // 리소스 해제
    DestroyCursor(hCursor);  // 커서 해제
    DestroyIcon(hIcon);      // 아이콘 해제
}

