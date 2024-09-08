#include <iostream>
#include "framework.h"
#include "Pen_Str.h"
#include "paint_area.h"

// 전역변수 정의
extern vector<PEN_INFO> penMemory;
extern PEN_INFO g_Pen_Info;
extern COLORREF pen_Color;
extern int pen_Width;
RECT pentext = { 310 + 100, 15, 340 + 100, 45 };

void drawLine(HWND hWnd, UINT message, LPARAM lParam)
{
    static int preX, preY;
    static bool drawStart = false;
    int x, y;
    HDC hdc;
    HPEN myP, osP;

    InvalidateRect(hWnd, &pentext, TRUE);  // 텍스트 영역만 무효화
    UpdateWindow(hWnd);

    x = LOWORD(lParam);
    y = HIWORD(lParam);
    hdc = GetDC(hWnd);

    myP = CreatePen(PS_SOLID, pen_Width, pen_Color);
    osP = (HPEN)SelectObject(hdc, myP);

    switch (message)
    {
    case WM_LBUTTONDOWN:

        ///x,y마우스 이전 좌표 저장 변수
        preX = x;
        preY = y;
    
            ///WM_MOUSEMOVE 그리기 조건 변수
           drawStart = true;


           // 각 LBUTTON state 별 데이터 구조체에 저장
           g_Pen_Info.penCoordinate = lParam;              // 마우스 x, y 좌표 (lParam) 
           g_Pen_Info.penWidth = pen_Width;                // 펜 굵기 (기본 값 10)
           g_Pen_Info.penColor = pen_Color;                // 펜 색상 (기본 값 RGB(0, 0, 0))
           g_Pen_Info.penTime = (DWORD)GetTickCount64();   // 그리기 시간
           g_Pen_Info.penState = message;                  // 상태 (ex WM_LBUTTONDOWN)

           // 벡터 변수에 위 구조체 데이터 PUSH
           penMemory.push_back(g_Pen_Info);
        
        break;

    case WM_MOUSEMOVE:

        ///마우스 x,y 좌표기준 그리기 영역지정
        if (HIWORD(lParam) <= Rectangle_top+5 || HIWORD(lParam) >= Rectangle_bottom-5 || LOWORD(lParam) < (Rectangle_left+5) || LOWORD(lParam) > Rectangle_right-5) {
            drawStart = false;
        }

        if (drawStart)
        {   
            MoveToEx(hdc, preX, preY, NULL);
            LineTo(hdc, x, y);

            preX = x;
            preY = y;

            // 각 LBUTTON state 별 데이터 구조체에 저장
            g_Pen_Info.penCoordinate = lParam;
            g_Pen_Info.penWidth = pen_Width;
            g_Pen_Info.penColor = pen_Color;
            g_Pen_Info.penTime = (DWORD)GetTickCount64();
            g_Pen_Info.penState = message;

            // 벡터 변수에 위 구조체 데이터 PUSH
            penMemory.push_back(g_Pen_Info);
        }
        break;

    case WM_LBUTTONUP:
        if (drawStart)
        {
            // 각 LBUTTON state 별 데이터 구조체에 저장
            g_Pen_Info.penCoordinate = lParam;
            g_Pen_Info.penWidth = pen_Width;
            g_Pen_Info.penColor = pen_Color;
            g_Pen_Info.penTime = (DWORD)GetTickCount64();
            g_Pen_Info.penState = message;

            // 벡터 변수에 위 구조체 데이터 PUSH
            penMemory.push_back(g_Pen_Info);

            drawStart = false;
            break;
        }
        break;
    }

    SelectObject(hdc, osP);
    DeleteObject(myP);  // 펜을 삭제

    ReleaseDC(hWnd, hdc);  // HDC 자원 해제
}