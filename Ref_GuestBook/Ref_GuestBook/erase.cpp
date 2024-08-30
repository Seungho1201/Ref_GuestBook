#include <iostream>
#include "framework.h"
#include "Pen_Str.h"

// 전역변수 정의

/**
 * @brief       화면 지우기 함수
 */
void erase(HWND hWnd)
{
    // 벡터 변수 초기화
    penMemory.clear();
    // 윈도우의 클라이언트 영역을 무효화하여 다시 그리기 요청
    InvalidateRect(hWnd, NULL, TRUE);
}