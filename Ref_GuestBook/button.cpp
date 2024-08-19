#include "Button.h"

extern HWND g_Hwnd;

// 생성자에 이미지 경로 변수 추가 예정
MakeButton::MakeButton(int x, int y, int width, int height, int func, LPCWSTR text) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->func = func;
    this->text = text;
    // 이미지 경로 변수 추가 예정
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
/// 이제 아이콘 이미지를 넣을 인스턴트의 mkButton(int path) 메서드의 인자로 Resource.h 파일에서 정의한 상수를 넣는다.
/// </summary>
void MakeButton::mkButton() {
    CreateWindow(
        L"BUTTON",                                              // 버튼 클래스 이름
        text,                                                   // 버튼 텍스트
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,     // 버튼 스타일
        x,                                                      // 버튼의 x 위치
        y,                                                      // 버튼의 y 위치
        width,                                                  // 버튼의 폭
        height,                                                 // 버튼의 높이
        g_Hwnd,                                                 // 부모 윈도우 핸들
        (HMENU)func,                                            // 버튼의 ID
        (HINSTANCE)GetWindowLongPtr(g_Hwnd, GWLP_HINSTANCE),    // 인스턴스 핸들
        NULL                                                    // 추가 매개변수
    );
}

void MakeButton::mkButton(int path) {
    CreateWindow(
        L"BUTTON",                                              // 버튼 클래스 이름
        text,                                                   // 버튼 텍스트
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_ICON,           // 버튼 스타일
        x,                                                      // 버튼의 x 위치
        y,                                                      // 버튼의 y 위치
        width,                                                  // 버튼의 폭
        height,                                                 // 버튼의 높이
        g_Hwnd,                                                 // 부모 윈도우 핸들
        (HMENU)func,                                            // 버튼의 ID
        (HINSTANCE)GetWindowLongPtr(g_Hwnd, GWLP_HINSTANCE),    // 인스턴스 핸들
        NULL                                                    // 추가 매개변수
    );

    insertIconImg(text, path, (HINSTANCE)GetWindowLongPtr(g_Hwnd, GWLP_HINSTANCE));
}

// 아이콘 삽입 메서드
void MakeButton::insertIconImg(LPCWSTR text, int path, HINSTANCE hInst)
{
    HICON hIcon = LoadIcon(hInst, MAKEINTRESOURCE(path));
    SendMessageW(FindWindowExW(g_Hwnd, NULL, L"button", text), BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon);
}