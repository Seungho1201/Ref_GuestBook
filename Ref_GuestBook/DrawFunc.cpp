/**
@file DrawFunc.cpp
@brief 그리기 관련  코드
*/
#include "DrawFunc.h"

/*
@fn  PenDraw::PenDraw()
@brief 그리기 기능 코드 생성자
*/
PenDraw::PenDraw() {
    this->x = 0;
    this->y = 0;
    this->preX = 0;
    this->preY = 0;
    this->hdc = nullptr;
    this->myP = nullptr;
    this->osP = nullptr;
    this->drawStart = false;
    this->s_Hdc = nullptr;
    this->penStay = true;
    this->paint_area = { PAINT_R_LEFT,
                         PAINT_R_TOP,
                         PAINT_R_RIGHT, 
                         PAINT_R_BOTTOM };
}

bool PenDraw::isReplay = false;     /// static 변수 외부 초기화

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
void PenDraw::drawLine(int* pen_Width, HWND hWnd, UINT message, LPARAM lParam, COLORREF* pen_Color, PEN_INFO* g_Pen_Info, std::vector<PEN_INFO>* penMemory)
{
    /// 리플레이 스레드 작동시 그리기 기능을 정지
    if (this->isReplay) { return; }

    x = LOWORD(lParam);
    y = HIWORD(lParam);
    hdc = GetDC(hWnd);

    myP = CreatePen(PS_SOLID, *pen_Width, *pen_Color);
    osP = (HPEN)SelectObject(hdc, myP);

    switch (message)
    {
    case WM_LBUTTONDOWN:
        /// 그리기 영역이 아닐 시 break
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
        g_Pen_Info->penCoordinate = lParam;              /// 마우스 x, y 좌표 (lParam) 
        g_Pen_Info->penWidth = *pen_Width;               /// 펜 굵기 (기본 값 10)
        g_Pen_Info->penColor = *pen_Color;               /// 펜 색상 (기본 값 RGB(0, 0, 0))
        g_Pen_Info->penTime = (DWORD)GetTickCount64();   /// 그리기 시간
        g_Pen_Info->penState = message;                  /// 상태 (ex WM_LBUTTONDOWN)

        /// 펜 모드일 때 스탬프 관련 벡터 데이터는 0(false)로 초기화
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
            || LOWORD(lParam) > PAINT_R_RIGHT   - 5) {
            /// 그리기 영역을 넘어가는 순간 그리기 체크용 변수(drawStart) false
            drawStart = false;
            break;
        }

        if (drawStart)
        {   
            MoveToEx(hdc, this->preX, this->preY, NULL);
            LineTo(hdc, x, y);

            /// 이전 좌표 갱신
            this->preX = x;
            this->preY = y;

            // 각 LBUTTON state 별 데이터 구조체에 저장
            g_Pen_Info->penCoordinate = lParam;              /// 마우스 x, y 좌표 (lParam) 
            g_Pen_Info->penWidth = *pen_Width;               /// 펜 굵기 (기본 값 10)
            g_Pen_Info->penColor = *pen_Color;               /// 펜 색상 (기본 값 RGB(0, 0, 0))
            g_Pen_Info->penTime = (DWORD)GetTickCount64();   /// 그리기 시간
            g_Pen_Info->penState = message;                  /// 상태 (ex WM_LBUTTONDOWN)

            g_Pen_Info->stampOn = false;
            g_Pen_Info->stampImg = 0;
            g_Pen_Info->stampSize = 0;

            /// 벡터 변수에 위 구조체 데이터 PUSH
            penMemory->emplace_back(std::move(*g_Pen_Info));
        }
        break;

    case WM_LBUTTONUP:
        if (this->drawStart)
        {
            // 각 LBUTTON state 별 데이터 구조체에 저장
            g_Pen_Info->penCoordinate = lParam;              // 마우스 x, y 좌표 (lParam) 
            g_Pen_Info->penWidth = *pen_Width;               // 펜 굵기 (기본 값 10)
            g_Pen_Info->penColor = *pen_Color;               // 펜 색상 (기본 값 RGB(0, 0, 0))
            g_Pen_Info->penTime = (DWORD)GetTickCount64();   // 그리기 시간
            g_Pen_Info->penState = message;                  // 상태 (ex WM_LBUTTONDOWN)

            g_Pen_Info->stampOn = false;
            g_Pen_Info->stampImg = 0;
            g_Pen_Info->stampSize = 0;

            /// 벡터 변수에 위 구조체 데이터 PUSH
            penMemory->emplace_back(std::move(*g_Pen_Info));

            /// 좌클릭 상태가 아닐시 그리기 여부 변수를 false로 함
            this->drawStart = false;
            break;
        }
        break;
    }
    SelectObject(hdc, osP);
    DeleteObject(myP);      
    ReleaseDC(hWnd, hdc);  
}

/*
@fn  PenDraw::stayPaint(HDC hdc, HWND hWnd, vector<PEN_INFO>* penMemory)
@brief 그리기 유지 메서드
@param hdc WM_PAINT: 레이블의 hdc를 받음
@param hWnd 윈도우 핸들
@param penMemory 벡터 변수
*/
void PenDraw::drawStay(HDC hdc, HWND hWnd, std::vector<PEN_INFO>* penMemory) {

    /// 그리기 유지 조건이 false일 때 return
    if (!penStay) { return; }


    /// WM_PAINT 의 hdc를 받아옴
    this->s_Hdc = hdc;

    /// 벡터 데이터 크기 만큼 반복
    for (size_t i = 0; i < penMemory->size(); i++) {

        /// 포인터를 역참조하여 PEN_INFO 객체에 접근
        PEN_INFO& penInfo = (*penMemory)[i];

        myP = CreatePen(PS_SOLID, penInfo.penWidth, penInfo.penColor);
        osP = (HPEN)SelectObject(s_Hdc, myP);

        /// 좌클릭 상태(state)
        switch (penInfo.penState) {

        case WM_LBUTTONDOWN:
            x = LOWORD(penInfo.penCoordinate);
            y = HIWORD(penInfo.penCoordinate);

            /// 펜 모드가 아닌 스탬프 모드일 때 스탬프를 그리기 위한 조건문
            if (penInfo.stampOn == true) {
                int stampX = x;
                int stampY = y;
                int stampIcon = penInfo.stampImg;
                int stampWidth = penInfo.stampSize;  
                int stampHeight = penInfo.stampSize;  

                HICON hIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(stampIcon), IMAGE_ICON, stampWidth, stampHeight, 0);
                DrawIconEx(hdc, stampX - stampWidth / 2, stampY - stampHeight / 2, hIcon, stampWidth, stampHeight, 0, NULL, DI_NORMAL);
                break;
            }

            MoveToEx(hdc, x, y, NULL);
            LineTo(hdc, x, y);  // 점찍기
            break;

        case WM_MOUSEMOVE:
        case WM_LBUTTONUP:
            LineTo(hdc, LOWORD(penInfo.penCoordinate), HIWORD(penInfo.penCoordinate));
            break;

        default:
            break;
        }
        SelectObject(s_Hdc, osP);
        DeleteObject(myP);  
    }
    ReleaseDC(hWnd, s_Hdc);
}

/*
@fn PenDraw::replaythread(HWND g_Hwnd, vector<Pen_Info>* penMemory)
@brief 리플레이 스레드 호출 메서드
@param g_Hwnd: 윈도우 핸들
@param penMemory: main에서 사용되는 벡터 변수에 대한 포인터
*/
void PenDraw::replayThread(HWND g_Hwnd, std::vector<Pen_Info>* penMemory)
{
    /// 리플레이 실행 중일땐 스레드 생성을 막음
    if (this->isReplay) { return; }

    /// 메인 접근이 아닌 스레드 접근을 위해 벡터 복사
    copiedMemory = *penMemory;

    /// 람다식 사용
    /// [this, g_Hwnd] : 람다식의 캡처리스트 (함수 내에서 사용할 외부변수 캡쳐)
    /// 포인터 사용하여 drwaReplay 실행 
    startReplayThread = std::thread([this, g_Hwnd]() { this->drawReplay(g_Hwnd); });

    /// 스레드 반환
    startReplayThread.detach();
}

/*
@fn PenDraw::drawReplay(HWND g_Hwnd)
@brief 리플레이 스레드로 호출되는 메서드
@param g_Hwnd: 윈도우 핸들
*/
void PenDraw::drawReplay(HWND g_Hwnd)
{


    /// WM_PAINT 에서 그리기 유지하는 조건을 리플레이 실행 동안 비활성화
    this->penStay = false;
    PenDraw::isReplay = true;

    HDC hdc;
    hdc = GetDC(g_Hwnd);
  
    /// 윈도우 그리기 영역(&paint_area) 초기화
    InvalidateRect(g_Hwnd, &paint_area, TRUE);
    UpdateWindow(g_Hwnd);

    // 벡터 변수 penMemory를 반복
    for (size_t i = 0; i < copiedMemory.size(); i++) {
        myP = CreatePen(PS_SOLID, copiedMemory[i].penWidth, copiedMemory[i].penColor);
        osP = (HPEN)SelectObject(hdc, myP);

        switch (copiedMemory[i].penState)
        {
        case WM_LBUTTONDOWN:
            x = LOWORD(copiedMemory[i].penCoordinate);
            y = HIWORD(copiedMemory[i].penCoordinate);

            if (copiedMemory[i].stampOn == true) {
                int stampX = x;
                int stampY = y;
                int stampIcon = copiedMemory[i].stampImg;
                int stampWidth = copiedMemory[i].stampSize;   // 원하는 아이콘 너비
                int stampHeight = copiedMemory[i].stampSize;  // 원하는 아이콘 높이

                HICON hIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(stampIcon), IMAGE_ICON, stampWidth, stampHeight, 0);
                DrawIconEx(hdc, stampX - stampWidth / 2, stampY - stampHeight / 2, hIcon, stampWidth, stampHeight, 0, NULL, DI_NORMAL);
                Sleep(100);
                break;
            }

            MoveToEx(hdc, x, y, NULL);
            LineTo(hdc, x, y);  // 점찍기
            break;

        case WM_MOUSEMOVE:
            LineTo(hdc, LOWORD(copiedMemory[i].penCoordinate), HIWORD(copiedMemory[i].penCoordinate));
            break;

        case WM_LBUTTONUP:
            LineTo(hdc, LOWORD(copiedMemory[i].penCoordinate), HIWORD(copiedMemory[i].penCoordinate));
            break;

        default:
            break;
        }

        // 벡터 변수 반복 중단점
        if (i + 1 < copiedMemory.size() && copiedMemory[i + 1].penState == WM_MOUSEMOVE) {
            Sleep(copiedMemory[i + 1].penTime - copiedMemory[i].penTime);
        }

        SelectObject(hdc, osP);
        DeleteObject(myP);  // 리소스 자원 확보 위해 삭제
    }
    /// 리플레이 기능 종료 시 그리기 유지 활성화
    this->penStay = true;
    PenDraw::isReplay = false;

    ReleaseDC(g_Hwnd, hdc);
    //return 0;
}