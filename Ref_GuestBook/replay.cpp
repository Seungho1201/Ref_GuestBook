#include <iostream>
#include <windows.h>
#include "framework.h"
#include "Pen_Str.h"
#include "stamp.h"
#include "resource.h"

// ������� ���ڸ� �ϳ��ۿ� ���ޱ⿡ HWND ���������� ������ �׸񿡼� �Ҵ�
extern HWND g_Hwnd;

DWORD WINAPI replay(LPVOID points)
{
    HDC hdc;
    HPEN myP, osP;

    hdc = GetDC(g_Hwnd);
    int x, y;

    // ��û�� �ٷ� ó������ �ʰ� �޼��� ť�� ���� �� ��� �۾��� ���� �� ����
    InvalidateRect(g_Hwnd, NULL, TRUE);

    // ��� ������Ʈ ��û�� ������ ��� �۾��� ������ ����Ǵ� InvalidateRect �Լ��� ��� ȣ��
    UpdateWindow(g_Hwnd);

    // ���� ���� penMemory�� �ݺ�
    for (size_t i = 0; i < (int)penMemory.size(); i++)
    {

        myP = CreatePen(PS_SOLID, penMemory[i].penWidth, penMemory[i].penColor);
        osP = (HPEN)SelectObject(hdc, myP);

        switch (penMemory[i].penState)
        {
        case WM_LBUTTONDOWN:
            x = LOWORD(penMemory[i].penCoordinate);
            y = HIWORD(penMemory[i].penCoordinate);

            // pen_str ����ü ���Ͽ��� ���� �ΰ��� �߰�����
            // ��ƼĿ �׸��� ����, � ��ƼĿ���� �� ���� ���� �ΰ�

            // stamp ���Ͽ��� ���� test(������ �׸�����)������ true�� �ϰ�
            // stampImg ������ �ش� Ŭ���� �̹���(int)�� ����ü�� ���� �� PUSH
            // ���� �� ��ư �߰��ؼ� ��ȯ�� �����Ӱ� �����ϸ� �ɵ� ��
            if (penMemory[i].test == true) {
                int stampX = x;
                int stampY = y;
                int stampIcon = penMemory[i].stampImg;
                int stampWidth = penMemory[i].stampSize;  // ���ϴ� ������ �ʺ�
                int stampHeight = penMemory[i].stampSize; // ���ϴ� ������ ����

                Sleep(100);

                HICON hIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(stampIcon), IMAGE_ICON, stampWidth, stampHeight, 0);
                DrawIconEx(hdc, stampX - stampWidth / 2, stampY - stampHeight / 2, hIcon, stampWidth, stampHeight, 0, NULL, DI_NORMAL);
                break;
            }

            MoveToEx(hdc, x, y, NULL);
            LineTo(hdc, x, y);  //�����
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

        // ���� ���� �ݺ� �ߴ���
        if (i + 1 < penMemory.size() && penMemory[i + 1].penState == WM_MOUSEMOVE)
        {
            Sleep(penMemory[i + 1].penTime - penMemory[i].penTime);
        }


        SelectObject(hdc, osP);
        DeleteObject(myP);          // ���ҽ� �ڿ� Ȯ�� ���� ����
    }

    ReleaseDC(g_Hwnd, hdc);
    return 0;
}
