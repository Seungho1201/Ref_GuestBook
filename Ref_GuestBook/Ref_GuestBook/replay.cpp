#include <iostream>
#include <windows.h>
#include "framework.h"
#include "Pen_Str.h"

// 스레드는 인자를 하나밖에 못받기에 HWND 전역변수는 스레드 항목에서 할당
extern HWND g_Hwnd;

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

    // 벡터 변수 penMemory를 반복
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

        // 벡터 변수 반복 중단점
        if (i + 1 < penMemory.size() && penMemory[i + 1].penState == WM_MOUSEMOVE)
        {
            Sleep(penMemory[i + 1].penTime - penMemory[i].penTime);
        }

        
        SelectObject(hdc, osP);
        DeleteObject(myP);          // 리소스 자원 확보 위해 삭제
    }

    ReleaseDC(g_Hwnd, hdc);
    return 0;
}