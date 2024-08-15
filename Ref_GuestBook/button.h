#pragma once
#include <windows.h>  // CreateWindow에 필요한 헤더


class MakeButton {
private:
    int x;                // 버튼의 x 위치
    int y;                // 버튼의 y 위치
    int weight;           // 버튼의 폭
    int height;           // 버튼의 높이
    int func;             // 버튼의 ID
    LPCWSTR text;         // 버튼 텍스트
    HWND c_Hwnd;          // 부모 윈도우 핸들

public:

    /**
    * @brief       버튼 구현 생성자 (x, y, 너비, 높이, 기능, 버튼 안 텍스트)
    */
    MakeButton(int x, int y, int weight, int height, int func, LPCWSTR text);

    // 버튼 생성 메서드
    // 전역 변수로 생성 된 g_Hwnd 변수를 사용해야 하지만 
    // WM_CREATE 부분에서 초기화가 들어가니 인자로  HWND 타입 변수 사용
    void mkButton(HWND g_Hwnd);
};
