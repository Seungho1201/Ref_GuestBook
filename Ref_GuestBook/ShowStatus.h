#pragma once
#include <windows.h>  /// CreateWindow�� �ʿ��� ���
#include "framework.h"
#include <algorithm> // std::fill

class ShowStatus 
{
private:
    HDC status_Hdc;
    WCHAR modeStatus[20];

    WCHAR nowStatus[30];
    
public:
    ShowStatus();
    void showDisplay(HDC hdc, HWND g_Hwnd);

    void setStatus(int wmId, HWND g_Hwnd);
    
};