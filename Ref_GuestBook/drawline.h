#pragma once
#include <iostream>
#include "framework.h"
#include "Pen_Str.h"
#include "Ref_GuestBook.h"


class PenDraw {

private:
    int preX, preY;
    bool drawStart;
    int x, y;
    HDC hdc;
    HDC s_Hdc;
    HPEN myP, osP;
   

public:
    PenDraw();
    void drawLine(int* pen_Width, HWND hWnd, UINT message, LPARAM lParam, COLORREF* pen_Color, PEN_INFO* g_Pen_Info, vector<PEN_INFO>* penMemory);
    void stayPaint(HDC hdc, HWND hWnd, vector<PEN_INFO>* penMemory);
};