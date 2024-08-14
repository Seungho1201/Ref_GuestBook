﻿// Ref_GuestBook.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Ref_GuestBook.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_REFGUESTBOOK, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_REFGUESTBOOK));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_REFGUESTBOOK));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_REFGUESTBOOK);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

extern HWND g_Hwnd;

// 전역 변수 사용 위해 임시 선언
HWND g_Hwnd;


DWORD WINAPI replay(LPVOID points)
{
    HDC hdc;
    HPEN myP, osP;

    hdc = GetDC(g_Hwnd);
    int x, y;

    // 요청이 바로 처리되지 않고 메세지 큐에 저장 즉 모든 작업이 끝난 후 실행
    InvalidateRect(g_Hwnd, NULL, TRUE);
    // 즉시 업데이트 요청을 보내어 모든 작업이 끝나고 실행되는 InvalidateRect 함수를 즉시 호출
    UpdateWindow(g_Hwnd);


    for (size_t i = 0; i < (int)penMemory.size(); i++)
    {

        myP = CreatePen(PS_SOLID, penMemory[i].penWidth, penMemory[i].penColor);
        osP = (HPEN)SelectObject(hdc, myP);

        switch (penMemory[i].penState)
        {
        case WM_LBUTTONDOWN:
            x = LOWORD(penMemory[i].penCoordinate);
            y = HIWORD(penMemory[i].penCoordinate);

            MoveToEx(hdc, x, y, NULL);
            LineTo(hdc, x, y);  //점찍기
            break;

        case WM_MOUSEMOVE:
            LineTo(hdc, LOWORD(penMemory[i].penCoordinate), HIWORD(penMemory[i].penCoordinate));
            break;

        case WM_LBUTTONUP:
            LineTo(hdc, LOWORD(penMemory[i].penCoordinate), HIWORD(penMemory[i].penCoordinate));
            break;

        default:
            break;
        }

        if (i + 1 < penMemory.size() && penMemory[i + 1].penState == WM_MOUSEMOVE)
        {
            Sleep(penMemory[i + 1].penTime - penMemory[i].penTime);
        }

        // 리소스 자원 확보 위해 삭제
        SelectObject(hdc, osP);
        DeleteObject(myP);  // 펜을 삭제
    }

    ReleaseDC(g_Hwnd, hdc);
    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {

    case WM_CREATE:

        g_Hwnd = hWnd;

        // 버튼 생성 임시 구현 클래스로 분할 예정
        CreateWindow(
            L"BUTTON",                                               // 버튼 클래스 이름
            L"REPLAY",                                               // 버튼 텍스트
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,   // 버튼 스타일
            10,                                                      // 버튼의 x 위치
            10,                                                      // 버튼의 y 위치
            100,                                                     // 버튼의 폭
            30,                                                      // 버튼의 높이
            g_Hwnd,                                                  // 부모 윈도우 핸들
            (HMENU)REPLAY,                                           // 버튼의 ID
            (HINSTANCE)GetWindowLongPtr(g_Hwnd, GWLP_HINSTANCE),     // 인스턴스 핸들
            NULL                                                     // 추가 매개변수
        );

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;

            case REPLAY:
                // 리플레이 기능은 스레드화
                CreateThread(NULL, 0, replay, (LPVOID)lParam, 0, NULL);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_MOUSEMOVE:
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
        // 그리기 함수
        drawLine(hWnd, message, lParam);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

