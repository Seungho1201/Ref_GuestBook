#pragma once

#include <thread>
#include <iostream>
#include "framework.h"
#include "Pen_Str.h"
#include "Resource.h"

class PenDraw {

private:
    int x;                              /// 좌클릭 x좌표
    int y;                              /// 좌클릭 y좌표
    int preX;                           /// 현재 좌표 기준 이전 x좌표 저장용 변수
    int preY;                           /// 현재 좌표 기준 이전 y좌표 저장용 변수
    bool penStay;                       /// 화면 그리기 유지 상태 확인 변수 (리플레이시 작동 X)
    bool drawStart;                     /// 그리기 확인 변수
   
    HDC hdc;                            /// hdc
    HDC s_Hdc;                          /// WM_PAINT 메세지 전용 hdc
    HPEN myP;                           /// 색상 선택
    HPEN osP;
    RECT paint_area;                    /// 그리기 영역
    
    std::thread startReplayThread;      /// 스레드 변수
    std::vector<Pen_Info> copiedMemory; /// 외부 접근 위한 벡터 포인터 변수
    
public:
    static bool isReplay;               /// 현재 리플레이 상태 확인 체크용 변수

    PenDraw();
    void drawLine(int* pen_Width, HWND hWnd, UINT message, LPARAM lParam, COLORREF* pen_Color, PEN_INFO* g_Pen_Info, std::vector<PEN_INFO>* penMemory);
    void drawStay(HDC hdc, HWND hWnd, std::vector<PEN_INFO>* penMemory);

    void replayThread(HWND g_Hwnd, std::vector<Pen_Info>* penMemory);
    void drawReplay(HWND g_Hwnd);
};