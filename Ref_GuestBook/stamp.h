#pragma once
#include <windows.h>
#include <vector>
#include "Pen_Str.h"

class Stamp {
private:
    int stampSize;                 // ������ ũ��
    int stampIcon;                 // ������ ������ ID
    int stampX, stampY;            // �������� x, y ��ǥ
    RECT stamptext = { 310 + 100, 15, 340 + 100, 45 };
    std::vector<PEN_INFO>& penMemory; // �ܺο��� �����ϴ� �� ���� ����

public:
    Stamp(int size, int icon, std::vector<PEN_INFO>& memory);
    void handleStamp(HWND hWnd, UINT message, LPARAM lParam);

private:
    void drawIcon(HDC hdc, int x, int y, HICON hIcon); // ������ �������� �׸��� �޼���
};
