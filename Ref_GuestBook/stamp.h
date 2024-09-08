#pragma once
#include <windows.h>
#include <vector>
#include "Pen_Str.h"

class Stamp {
private:
    int stampSize;                 // 스탬프 크기
    int stampIcon;                 // 스탬프 아이콘 ID
    int stampX, stampY;            // 스탬프의 x, y 좌표
    RECT stamptext = { 310 + 100, 15, 340 + 100, 45 };
    std::vector<PEN_INFO>& penMemory; // 외부에서 참조하는 펜 정보 벡터

public:
    Stamp(int size, int icon, std::vector<PEN_INFO>& memory);
    void handleStamp(HWND hWnd, UINT message, LPARAM lParam);

private:
    void drawIcon(HDC hdc, int x, int y, HICON hIcon); // 스탬프 아이콘을 그리는 메서드
};
