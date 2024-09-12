/**
@file drawline.cpp
@brief 그리기 관련  코드
*/
#include "drawline.h"

/*
@fn  PenDraw::PenDraw()
@brief 그리기 기능 코드 생성자
*/
PenDraw::PenDraw() {
    this->hdc = nullptr;
    this->myP = nullptr;
    this->osP = nullptr;
    this->drawStart = false;
    this->preX = 0;
    this->preY = 0;
    this->x = 0;
    this->y = 0;
    this->s_Hdc = nullptr;

}

/*
@fn  PenDraw::drawLine(int* pen_Width, HWND hWnd, UINT message, LPARAM lParam, COLORREF* pen_Color, PEN_INFO* g_Pen_Info, vector<PEN_INFO>* penMemory)
@brief 그리기 기능 코드
@param pen_Width 펜 굵기 포인터로 받는 변수
@param hWnd 윈도우 핸들
@param message 입력 상태 처리 (ex WM_LBUTTONDOWN)
@param lParam 마우스 좌표
@param pen_Color 펜 색상을 포인터로 받는 변수
@param g_Pen_Info 구조체 관련 포인터 변수
@param penMemory 구조체 데이터를 저장할 벡터 변수
*/
void PenDraw::drawLine(int* pen_Width, HWND hWnd, UINT message, LPARAM lParam, COLORREF* pen_Color, PEN_INFO* g_Pen_Info, vector<PEN_INFO>* penMemory)
{

    x = LOWORD(lParam);
    y = HIWORD(lParam);
    hdc = GetDC(hWnd);

    myP = CreatePen(PS_SOLID, *pen_Width, *pen_Color);
    osP = (HPEN)SelectObject(hdc, myP);

    switch (message)
    {
    case WM_LBUTTONDOWN:

        if (HIWORD(lParam)    <= PAINT_R_TOP    + 5
            || HIWORD(lParam) >= PAINT_R_BOTTOM - 5
            || LOWORD(lParam) <  PAINT_R_LEFT   + 5
            || LOWORD(lParam) >  PAINT_R_RIGHT  - 5) 
        {
            break;
        }

        ///x,y마우스 이전 좌표 저장 변수
        this->preX = x;
        this->preY = y;
    
        ///WM_MOUSEMOVE 그리기 조건 변수
        this->drawStart = true;

        // 각 LBUTTON state 별 데이터 구조체에 저장
        g_Pen_Info->penCoordinate = lParam;              // 마우스 x, y 좌표 (lParam) 
        g_Pen_Info->penWidth = *pen_Width;                // 펜 굵기 (기본 값 10)
        g_Pen_Info->penColor = *pen_Color;               // 펜 색상 (기본 값 RGB(0, 0, 0))
        g_Pen_Info->penTime = (DWORD)GetTickCount64();   // 그리기 시간
        g_Pen_Info->penState = message;                  // 상태 (ex WM_LBUTTONDOWN)

        g_Pen_Info->stampOn = false;
        g_Pen_Info->stampImg = 0;
        g_Pen_Info->stampSize = 0;

        // 벡터 변수에 위 구조체 데이터 PUSH
        // emplace_back은 객체를 벡터의 끝에 직접 생성하는 함수
        // std::move는 이동 시멘틱을 사용하여 객체를 복사하지 않고 이동
        penMemory->emplace_back(std::move(*g_Pen_Info));

    break;

    case WM_MOUSEMOVE:

        ///마우스 x,y 좌표기준 그리기 영역지정
        if (HIWORD(lParam) <= PAINT_R_TOP       + 5
            || HIWORD(lParam) >= PAINT_R_BOTTOM - 5
            || LOWORD(lParam) < PAINT_R_LEFT    + 5
            || LOWORD(lParam) > PAINT_R_RIGHT   - 5)
        {

            drawStart = false;
            break;
        }

        if (drawStart)
        {   
            MoveToEx(hdc, this->preX, this->preY, NULL);
            LineTo(hdc, x, y);

            this->preX = x;
            this->preY = y;

            // 각 LBUTTON state 별 데이터 구조체에 저장
            g_Pen_Info->penCoordinate = lParam;              // 마우스 x, y 좌표 (lParam) 
            g_Pen_Info->penWidth = *pen_Width;                // 펜 굵기 (기본 값 10)
            g_Pen_Info->penColor = *pen_Color;               // 펜 색상 (기본 값 RGB(0, 0, 0))
            g_Pen_Info->penTime = (DWORD)GetTickCount64();   // 그리기 시간
            g_Pen_Info->penState = message;                  // 상태 (ex WM_LBUTTONDOWN)

            g_Pen_Info->stampOn = false;
            g_Pen_Info->stampImg = 0;
            g_Pen_Info->stampSize = 0;
            // 벡터 변수에 위 구조체 데이터 PUSH
            //penMemory->push_back(*g_Pen_Info);
            penMemory->emplace_back(std::move(*g_Pen_Info));
           
        }
        break;

    case WM_LBUTTONUP:
        if (this->drawStart)
        {
            // 각 LBUTTON state 별 데이터 구조체에 저장
            g_Pen_Info->penCoordinate = lParam;              // 마우스 x, y 좌표 (lParam) 
            g_Pen_Info->penWidth = *pen_Width;                // 펜 굵기 (기본 값 10)
            g_Pen_Info->penColor = *pen_Color;               // 펜 색상 (기본 값 RGB(0, 0, 0))
            g_Pen_Info->penTime = (DWORD)GetTickCount64();   // 그리기 시간
            g_Pen_Info->penState = message;                  // 상태 (ex WM_LBUTTONDOWN)

            g_Pen_Info->stampOn = false;
            g_Pen_Info->stampImg = 0;
            g_Pen_Info->stampSize = 0;

            // 벡터 변수에 위 구조체 데이터 PUSH
            //penMemory->push_back(*g_Pen_Info);
            penMemory->emplace_back(std::move(*g_Pen_Info));

            this->drawStart = false;
            break;
        }
        break;
    }
    SelectObject(hdc, osP);

    DeleteObject(myP);      // 펜을 삭제
    ReleaseDC(hWnd, hdc);  // HDC 자원 해제
}

/*
@fn  PenDraw::stayPaint(HDC hdc, HWND hWnd, vector<PEN_INFO>* penMemory)
@brief 그리기 유지 메서드
@param hdc WM_PAINT: 레이블의 hdc를 받음
@param hWnd 윈도우 핸들
@param penMemory 벡터 변수
*/
void PenDraw::stayPaint(HDC hdc, HWND hWnd, vector<PEN_INFO>* penMemory) {

    this->s_Hdc = hdc;

    for (size_t i = 0; i < penMemory->size(); i++) {

        // 포인터를 역참조하여 PEN_INFO 객체에 접근
        PEN_INFO& penInfo = (*penMemory)[i];

        myP = CreatePen(PS_SOLID, penInfo.penWidth, penInfo.penColor);
        osP = (HPEN)SelectObject(s_Hdc, myP);

        switch (penInfo.penState) {
        case WM_LBUTTONDOWN:
            x = LOWORD(penInfo.penCoordinate);
            y = HIWORD(penInfo.penCoordinate);

            if (penInfo.stampOn == true) {
                int stampX = x;
                int stampY = y;
                int stampIcon = penInfo.stampImg;
                int stampWidth = penInfo.stampSize;   // 원하는 아이콘 너비
                int stampHeight = penInfo.stampSize;  // 원하는 아이콘 높이

                HICON hIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(stampIcon), IMAGE_ICON, stampWidth, stampHeight, 0);
                DrawIconEx(hdc, stampX - stampWidth / 2, stampY - stampHeight / 2, hIcon, stampWidth, stampHeight, 0, NULL, DI_NORMAL);
                break;
            }

            MoveToEx(hdc, x, y, NULL);
            LineTo(hdc, x, y);  // 점찍기
            break;

        case WM_MOUSEMOVE:
            LineTo(hdc, LOWORD(penInfo.penCoordinate), HIWORD(penInfo.penCoordinate));
            break;

        case WM_LBUTTONUP:
            LineTo(hdc, LOWORD(penInfo.penCoordinate), HIWORD(penInfo.penCoordinate));
            break;

        default:
            break;
        }
        SelectObject(s_Hdc, osP);
        DeleteObject(myP);  // 리소스 자원 확보 위해 삭제
    }

    ReleaseDC(hWnd, s_Hdc);
}
