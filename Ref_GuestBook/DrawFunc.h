#pragma once

#include <thread>
#include <iostream>
#include "framework.h"
#include "Pen_Str.h"
#include "Resource.h"

class PenDraw {

private:
    int x;                              /// ��Ŭ�� x��ǥ
    int y;                              /// ��Ŭ�� y��ǥ
    int preX;                           /// ���� ��ǥ ���� ���� x��ǥ ����� ����
    int preY;                           /// ���� ��ǥ ���� ���� y��ǥ ����� ����
    bool penStay;                       /// ȭ�� �׸��� ���� ���� Ȯ�� ���� (���÷��̽� �۵� X)
    bool drawStart;                     /// �׸��� Ȯ�� ����
   
    HDC hdc;                            /// hdc
    HDC s_Hdc;                          /// WM_PAINT �޼��� ���� hdc
    HPEN myP;                           /// ���� ����
    HPEN osP;
    RECT paint_area;                    /// �׸��� ����
    
    std::thread startReplayThread;      /// ������ ����
    std::vector<Pen_Info> copiedMemory; /// �ܺ� ���� ���� ���� ������ ����
    
public:
    static bool isReplay;               /// ���� ���÷��� ���� Ȯ�� üũ�� ����

    PenDraw();
    void drawLine(int* pen_Width, HWND hWnd, UINT message, LPARAM lParam, COLORREF* pen_Color, PEN_INFO* g_Pen_Info, std::vector<PEN_INFO>* penMemory);
    void drawStay(HDC hdc, HWND hWnd, std::vector<PEN_INFO>* penMemory);

    void replayThread(HWND g_Hwnd, std::vector<Pen_Info>* penMemory);
    void drawReplay(HWND g_Hwnd);
};