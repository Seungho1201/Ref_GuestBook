#include "Button.h"

// 생성자에 이미지 경로 변수 추가 예정
MakeButton::MakeButton(int x, int y, int weight, int height, int func, LPCWSTR text) {
    this->x = x;
    this->y = y;
    this->weight = weight;
    this->height = height;
    this->c_Hwnd = NULL;
    this->func = func;
    this->text = text;
    // 이미지 경로 변수 추가 예정
}

void MakeButton::mkButton(HWND g_Hwnd) {
    this->c_Hwnd = g_Hwnd;

    CreateWindow(
        L"BUTTON",                                              // 버튼 클래스 이름
        text,                                                   // 버튼 텍스트
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // 버튼 스타일
        x,                                                      // 버튼의 x 위치
        y,                                                      // 버튼의 y 위치
        weight,                                                 // 버튼의 폭
        height,                                                 // 버튼의 높이
        c_Hwnd,                                                 // 부모 윈도우 핸들
        (HMENU)func,                                            // 버튼의 ID
        (HINSTANCE)GetWindowLongPtr(c_Hwnd, GWLP_HINSTANCE),    // 인스턴스 핸들
        NULL                                                    // 추가 매개변수
    );
}
