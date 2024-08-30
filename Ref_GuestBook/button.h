#pragma once
#include <windows.h>  // CreateWindow에 필요한 헤더


class MakeButton {
private:
    int x;                // 버튼의 x 위치
    int y;                // 버튼의 y 위치
    int width;            // 버튼의 폭
    int height;           // 버튼의 높이
    int func;             // 버튼의 ID
    LPCWSTR text;         // 버튼 텍스트
    HWND hButton;

public:
    /**
    * @brief       버튼 구현 생성자 (x, y, 너비, 높이, 기능, 버튼 안 텍스트)
    */
    MakeButton(int x, int y, int width, int height, int func, LPCWSTR text);


    // 버튼 생성 메서드
    // g_Hwnd 전역 변수를 선언함으로인해 인자 X
    void mkButton();

    // 이미지 경로 상수 인자값
    void mkButton(int path);

private:
    void insertIconImg(LPCWSTR text, int path, HINSTANCE hInst);
};
