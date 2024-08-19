#include <iostream>
#include "framework.h"
#include "Pen_Str.h"
#include "Ref_GuestBook.h"

// 변경시 갱신되는 영역 지정
RECT textRect = { 310, 15, 340, 45 };
extern int pen_Width;

// 펜 굵기 변경 함수 (HWND, 실행 값)
void w_Control(HWND g_Hwnd, int con)
{
    switch (con)
    {
    case W_UP:
        // 펜 최대 굵기는 20
        if (pen_Width == 20) { break; }

        pen_Width += 1;

        InvalidateRect(g_Hwnd, &textRect, TRUE);  // 텍스트 영역만 무효화
        UpdateWindow(g_Hwnd);
        break;

    case W_DOWN:
        // 펜 최소 굵기는 1
        if (pen_Width == 1) { break; }

        pen_Width -= 1;

        InvalidateRect(g_Hwnd, &textRect, TRUE);  // 텍스트 영역만 무효화
        UpdateWindow(g_Hwnd);
        break;
    }
}