/**
@file button.h
@brief 버튼 관련 클래스 멤버 정의 파일
*/
#pragma once
#include <windows.h>  /// CreateWindow에 필요한 헤더
#include "framework.h"
#include "Resource.h"

class MakeButton {
private:
    int x;                /// 버튼의 x 위치
    int y;                /// 버튼의 y 위치
    int width;            /// 버튼의 폭
    int height;           /// 버튼의 높이
    int func;             /// 버튼의 ID
    LPCWSTR text;         /// 버튼 텍스트
    COLORREF buttonColor; /// 버튼 색지정
    HWND hButton;


public:
    static int buttonHighlight;                     /// 버튼 ID 구분 위한 변수
    static RECT buttonRect;                         /// 클릭한 버튼 저장용 변수
    static RECT buttonRectBefore;                   /// 이전 클릭된 버튼 저장용 변수
    static std::vector<MakeButton*> buttonList;     /// 버튼을 저장할 벡터 변수

    MakeButton(int x, int y, int width, int height, int func, LPCWSTR text);

    void mkButton(HWND g_Hwnd);
    void mkButton(HWND g_Hwnd, int path);
    void mkButton(HWND g_Hwnd, COLORREF color);

    static void getClickHighlight(int wmId, HWND g_Hwnd);
    static void setClickHighlight(HDC hdc);

private:
    void insertIconImg(LPCWSTR text, int path, HINSTANCE hInst);
};
