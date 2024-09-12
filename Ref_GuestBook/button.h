/**
@file button.h
@brief 버튼 관련 클래스 멤버 정의 파일
*/
#pragma once
#include <windows.h>  /// CreateWindow에 필요한 헤더

class MakeButton {
private:
    int x;                /// 버튼의 x 위치
    int y;                /// 버튼의 y 위치
    int width;            /// 버튼의 폭
    int height;           /// 버튼의 높이
    int func;             /// 버튼의 ID
    LPCWSTR text;         /// 버튼 텍스트
    HWND hButton;

public:
    MakeButton(int x, int y, int width, int height, int func, LPCWSTR text);

    void mkButton(HWND g_Hwnd);
    void mkButton(HWND g_Hwnd, int path);

private:
    void insertIconImg(LPCWSTR text, int path, HINSTANCE hInst);
};
