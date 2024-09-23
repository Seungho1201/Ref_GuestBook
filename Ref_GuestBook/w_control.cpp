/**
@file w_control.cpp
@brief 굵기(스탬프 사이즈) 조절 관련 클래스 외부 정의 파일
*/

#include "w_control.h"

/*
@fn PenWidthControl::PenWidthControl()
@brief 굵기(스탬프 사이즈) 조절 클래스 생성자
*/
PenWidthControl::PenWidthControl() {
    this->textRect = { WIDTH_R_LEFT, 
                       WIDTH_R_TOP, 
                       WIDTH_R_RIGHT,
                       WIDTH_R_BOTTOM };

    this->wc_Hdc = nullptr;
}

/*
@fn PenWidthControl::widthControl(HWND g_Hwnd, int func, int* pen_Width, int* stamp_Size, bool* stampActive)
@brief 굵기(스탬프 사이즈) 조절 메서드
@param g_Hwnd 윈도우 핸들
@param func 실행할 기능 메서드 WM_COMMAND에서 (wmId) 인자
@param penWidth 펜 굵기 조절 위한 포인터 변수
@param stamp_Size 스탬프 사이즈 조절 위한 포인터 변수
@param stampActive 스탬프 활성화 여부 확인 위한 포인터 변수
*/
void PenWidthControl::widthControl(HWND g_Hwnd, int func, int* pen_Width, int* stamp_Size, bool* stampActive)
{
    /// WM_COMMAND 에서 wmId변수 인자
    switch (func)
    {
    /// 펜(스탬프) 사이즈 UP
    case W_UP:
        /// 스탬프 모드일 떄
        if (*stampActive) {  
            /// 스탬프 크기의 최대 사이즈는 100으로 지정
            if (*stamp_Size < 100) { *stamp_Size += 10; }

        /// 펜 모드일 때
        } else {  
            /// 펜 최대 굵기 사이즈는 20
            if (*pen_Width < 20) { *pen_Width += 1; }
        }
        break;

    /// 펜(스탬프) 사이즈 DOWN
    case W_DOWN:
        /// 스탬프 모드일 떄
        if (*stampActive) {  
            if (*stamp_Size > 10) { *stamp_Size -= 10; }

        /// 펜 모드일 때
        } else {  
            if (*pen_Width > 1) {   // 펜 최소 굵기 제한
                *pen_Width -= 1;
            }
        }
        break;
    }

    // 변경된 값에 따라 텍스트 영역을 무효화하고 갱신
    InvalidateRect(g_Hwnd, &this->textRect, TRUE);
    UpdateWindow(g_Hwnd);
}

/*
@fn  PenWidthControl::penWidthDisplay(HDC Hdc, bool* stampActive, int* stamp_Size, int* pen_Width)
@brief 굵기(스탬프 사이즈) 출력 메서드
@param hdc WM_PAINT에서 받을 hdc
*/
void PenWidthControl::penWidthDisplay(HDC Hdc, bool* stampActive, int* stamp_Size, int* pen_Width)
{
    wc_Hdc = Hdc;

    WCHAR szPenWidth[10] = {};

    if (*stampActive) {
        // 스탬프 사이즈 출력 (10 단위로 나누어서 출력)
        wsprintf(szPenWidth, L"%2d", *stamp_Size / 10);
    }
    else {
        // 펜 굵기 출력
        wsprintf(szPenWidth, L"%2d", *pen_Width);
    }

    // 폰트 설정
    HFONT hFont, hOldFont;
    hFont = CreateFont(
        30,                // 글자 크기 (높이)
        0,                 // 글자 너비 (0은 자동으로 설정)
        0,                 // 문자 각도
        0,                 // 기준선 각도
        FW_THIN,           // 얇은 글자 두께
        FALSE,             // 이탤릭체 여부
        FALSE,             // 밑줄 여부
        FALSE,             // 취소선 여부
        DEFAULT_CHARSET,   // 문자 세트
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS,
        L"Arial"           // 폰트 이름
    );

    // 새로운 폰트를 HDC에 선택하고 이전 폰트를 저장
    hOldFont = (HFONT)SelectObject(wc_Hdc, hFont);

    // 텍스트 출력
    TextOut(wc_Hdc, 430, 15, szPenWidth, lstrlen(szPenWidth));

    // 원래 폰트로 복원
    SelectObject(wc_Hdc, hOldFont);

    // 새로 생성한 폰트 삭제
    DeleteObject(hFont);
}
