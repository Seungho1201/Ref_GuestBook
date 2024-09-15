#include "w_control.h"

PenWidthControl::PenWidthControl() {
    this->textRect = { WIDTH_R_LEFT, 
                       WIDTH_R_TOP, 
                       WIDTH_R_RIGHT,
                       WIDTH_R_BOTTOM };

    this->wc_Hdc = nullptr;
}

void PenWidthControl::widthControl(HWND g_Hwnd, int func, int* pen_Width, int* stamp_Size, bool* stampActive)
{
    switch (func)
    {
    case W_UP:
        if (*stampActive) {  // 스탬프 모드일 때
            // 스탬프 최대 크기 제한
            if (*stamp_Size < 100) {
                *stamp_Size += 10;
            }

        // 펜 모드일 때
        } else {  
            if (*pen_Width < 20) {  // 펜 최대 굵기 제한
                *pen_Width += 1;
            }
        }
        break;

    case W_DOWN:
        // 스탬프 모드일 때
        if (*stampActive) {  
            if (*stamp_Size > 10) {   // 스탬프 최소 굵기 제한
                *stamp_Size -= 10;
            }

        // 펜 모드일 때
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

void PenWidthControl::penWidthDisplay(HDC Hdc, bool* stampActive, int* stamp_Size, int* pen_Width)
{
    wc_Hdc = Hdc;

    WCHAR szPenWidth[10] = {};

    if (*stampActive) {
        // 스탬프 사이즈 출력 (10 단위로 나누어서 출력)
        wsprintf(szPenWidth, L"%d", *stamp_Size / 10);
    } else {
        // 펜 굵기 출력
        wsprintf(szPenWidth, L" %d", *pen_Width);
    }
    /// 출력
    TextOut(wc_Hdc, 420, 15, szPenWidth, lstrlen(szPenWidth)); 

}