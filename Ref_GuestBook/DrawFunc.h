#pragma once

#include <thread>
#include <iostream>
#include "framework.h"
#include "Pen_Str.h"
#include "Ref_GuestBook.h"
#include <vector>

class PenDraw {

private:
    int preX, preY;
    bool drawStart;
    int x, y;
    HDC hdc;
    HDC s_Hdc;          /// WM_PAINT 메세지 전용 hdc
    HPEN myP, osP;
    RECT paint_area;
    thread startReplayThread;
    vector<Pen_Info> copiedMemory;

    bool penStay;

public:
    PenDraw();
    void drawLine(int* pen_Width, HWND hWnd, UINT message, LPARAM lParam, COLORREF* pen_Color, PEN_INFO* g_Pen_Info, vector<PEN_INFO>* penMemory);
    void drawStay(HDC hdc, HWND hWnd, vector<PEN_INFO>* penMemory);

    void replayThread(HWND g_Hwnd, vector<Pen_Info>* penMemory);
    void drawReplay(HWND g_Hwnd);

    //void test;
};