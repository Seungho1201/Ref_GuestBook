/**
@file button.cpp
@brief 버튼 생성 관련 클래스 외부 정의 파일
*/
#include "button.h"

/*
@fn  MakeButton::MakeButton(int x, int y, int width, int height, int func, LPCWSTR text)
@brief 버튼 클래스 생성자
@param x 버튼의 x 좌표
@param y 버튼의 y좌표
@param width 버튼의 폭
@param height 버튼의 너비
@param func COMMAND에서 작동할 기능 상수
@param text 버튼에 그려지는 텍스트
*/
MakeButton::MakeButton(int x, int y, int width, int height, int func, LPCWSTR text) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->func = func;
    this->text = text;
    this->hButton = nullptr;
}


/// <summary>
/// 버튼 구현은 두가지로 나뉜다
/// 1. 텍스트로 버튼 구현 - 인자 값 X
/// 2. 파일 경로 상수로 구현 - 아이콘 인자 값 1개
/// 
/// 만일 아이콘을 추가하거나 수정하고픈 팀원이 있을 수 있으니 
/// 아이콘은 비트맵 확장자(bmp)의 파일이여야 하고 "리소스 폴더" 안에 존재해야 함
/// 아이콘은 Ref_GuestBook.rc 파일에서 정의 한다 (ex: IDI_ERASE_ICON    ICON    "..\..\icon\Pen.ico")
/// rc 파일에서 정의 후 Resource.h 파일에서 상수로 재정의 한다 (ex: #define IDI_ERASE_ICON     130)
/// 이제 아이콘 이미지를 넣을 인스턴스의 mkButton(int path) 메서드의 인자로 Resource.h 파일에서 정의한 상수를 넣는다.
/// </summary>


/**
@fn  MakeButton::mkButton()
@brief 버튼 클래스의 버튼 생성 메서드
@param g_Hwnd 윈도우 핸들
*/
void MakeButton::mkButton(HWND g_Hwnd) {
    this->hButton = g_Hwnd;

    /// CreateWindow 함수로 버튼 생성
    CreateWindow(
        L"BUTTON",                                                          // 버튼 클래스 이름
        text,                                                               // 버튼 텍스트
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_FLAT,       // 버튼 스타일
        x,                                                                  // 버튼의 x 위치
        y,                                                                  // 버튼의 y 위치
        width,                                                              // 버튼의 폭
        height,                                                             // 버튼의 높이
        this->hButton,                                                             // 부모 윈도우 핸들
        (HMENU)func,                                                        // 버튼의 ID
        (HINSTANCE)GetWindowLongPtr(this->hButton, GWLP_HINSTANCE),                // 인스턴스 핸들
        NULL                                                                // 추가 매개변수
    );
}

/**
@fn   MakeButton::mkButton(int path)
@brief 버튼 클래스의 이미지 버튼 생성 메서드
@details 이 메서드는 지정된 리소스 경로의 이미지를 사용하여 버튼을 생성
@param g_Hwnd 윈도우 핸들
@param path 버튼에 삽입될 비트맵 이미지 경로 (resource.h)
*/
void MakeButton::mkButton(HWND g_Hwnd, int path) {
    this->hButton = g_Hwnd;

    CreateWindow(
        L"BUTTON",                                                          // 버튼 클래스 이름
        text,                                                               // 버튼 텍스트
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_ICON | BS_FLAT,             // 버튼 스타일
        x,                                                                  // 버튼의 x 위치
        y,                                                                  // 버튼의 y 위치
        width,                                                              // 버튼의 폭
        height,                                                             // 버튼의 높이
        this->hButton,                                                             // 부모 윈도우 핸들
        (HMENU)func,                                                        // 버튼의 ID
        (HINSTANCE)GetWindowLongPtr(this->hButton, GWLP_HINSTANCE),                // 인스턴스 핸들
        NULL                                                                // 추가 매개변수
    );

    insertIconImg(text, path, (HINSTANCE)GetWindowLongPtr(this->hButton, GWLP_HINSTANCE));
}

/**
@fn  MakeButton::insertIconImg(LPCWSTR text, int path, HINSTANCE hInst)
@brief 이미지 버튼 생성 메서드의 이미지 전송 메서드 (private)
@param text 버튼 텍스트
@param path 버튼에 삽입될 비트맵 이미지 경로 (resource.h)
@param hInst 인스턴스 핸들
*/
void MakeButton::insertIconImg(LPCWSTR text, int path, HINSTANCE hInst)
{
    /// 버튼의 크기에 맞는 아이콘을 불러오기 위해 LoadImage를 사용.
    HICON hIcon = (HICON)LoadImage(
        hInst,                        /// 인스턴스 핸들
        MAKEINTRESOURCE(path),        /// 리소스 경로
        IMAGE_ICON,                   /// 아이콘 유형
        width,                        /// 아이콘의 가로 크기
        height,                       /// 아이콘의 세로 크기
        LR_DEFAULTCOLOR               /// 기본 색상 로드 플래그
    );

    /// 버튼에 아이콘 설정 함수
    SendMessageW(
        FindWindowExW(this->hButton, NULL, L"BUTTON", text),   /// 버튼의 핸들을 찾습니다.
        BM_SETIMAGE,                                    /// 버튼에 이미지를 설정하는 메시지
        IMAGE_ICON,                                     /// 이미지 유형이 아이콘임을 지정
        (LPARAM)hIcon                                   /// 설정할 아이콘
    );
}
