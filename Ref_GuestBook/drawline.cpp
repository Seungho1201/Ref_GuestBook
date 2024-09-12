/**
@file drawline.cpp
@brief �׸��� ����  �ڵ�
*/
#include "drawline.h"

/*
@fn  PenDraw::PenDraw()
@brief �׸��� ��� �ڵ� ������
*/
PenDraw::PenDraw() {
    this->hdc = nullptr;
    this->myP = nullptr;
    this->osP = nullptr;
    this->drawStart = false;
    this->preX = 0;
    this->preY = 0;
    this->x = 0;
    this->y = 0;
    this->s_Hdc = nullptr;

}

/*
@fn  PenDraw::drawLine(int* pen_Width, HWND hWnd, UINT message, LPARAM lParam, COLORREF* pen_Color, PEN_INFO* g_Pen_Info, vector<PEN_INFO>* penMemory)
@brief �׸��� ��� �ڵ�
@param pen_Width �� ���� �����ͷ� �޴� ����
@param hWnd ������ �ڵ�
@param message �Է� ���� ó�� (ex WM_LBUTTONDOWN)
@param lParam ���콺 ��ǥ
@param pen_Color �� ������ �����ͷ� �޴� ����
@param g_Pen_Info ����ü ���� ������ ����
@param penMemory ����ü �����͸� ������ ���� ����
*/
void PenDraw::drawLine(int* pen_Width, HWND hWnd, UINT message, LPARAM lParam, COLORREF* pen_Color, PEN_INFO* g_Pen_Info, vector<PEN_INFO>* penMemory)
{

    x = LOWORD(lParam);
    y = HIWORD(lParam);
    hdc = GetDC(hWnd);

    myP = CreatePen(PS_SOLID, *pen_Width, *pen_Color);
    osP = (HPEN)SelectObject(hdc, myP);

    switch (message)
    {
    case WM_LBUTTONDOWN:

        if (HIWORD(lParam)    <= PAINT_R_TOP    + 5
            || HIWORD(lParam) >= PAINT_R_BOTTOM - 5
            || LOWORD(lParam) <  PAINT_R_LEFT   + 5
            || LOWORD(lParam) >  PAINT_R_RIGHT  - 5) 
        {
            break;
        }

        ///x,y���콺 ���� ��ǥ ���� ����
        this->preX = x;
        this->preY = y;
    
        ///WM_MOUSEMOVE �׸��� ���� ����
        this->drawStart = true;

        // �� LBUTTON state �� ������ ����ü�� ����
        g_Pen_Info->penCoordinate = lParam;              // ���콺 x, y ��ǥ (lParam) 
        g_Pen_Info->penWidth = *pen_Width;                // �� ���� (�⺻ �� 10)
        g_Pen_Info->penColor = *pen_Color;               // �� ���� (�⺻ �� RGB(0, 0, 0))
        g_Pen_Info->penTime = (DWORD)GetTickCount64();   // �׸��� �ð�
        g_Pen_Info->penState = message;                  // ���� (ex WM_LBUTTONDOWN)

        g_Pen_Info->stampOn = false;
        g_Pen_Info->stampImg = 0;
        g_Pen_Info->stampSize = 0;

        // ���� ������ �� ����ü ������ PUSH
        // emplace_back�� ��ü�� ������ ���� ���� �����ϴ� �Լ�
        // std::move�� �̵� �ø�ƽ�� ����Ͽ� ��ü�� �������� �ʰ� �̵�
        penMemory->emplace_back(std::move(*g_Pen_Info));

    break;

    case WM_MOUSEMOVE:

        ///���콺 x,y ��ǥ���� �׸��� ��������
        if (HIWORD(lParam) <= PAINT_R_TOP       + 5
            || HIWORD(lParam) >= PAINT_R_BOTTOM - 5
            || LOWORD(lParam) < PAINT_R_LEFT    + 5
            || LOWORD(lParam) > PAINT_R_RIGHT   - 5)
        {

            drawStart = false;
            break;
        }

        if (drawStart)
        {   
            MoveToEx(hdc, this->preX, this->preY, NULL);
            LineTo(hdc, x, y);

            this->preX = x;
            this->preY = y;

            // �� LBUTTON state �� ������ ����ü�� ����
            g_Pen_Info->penCoordinate = lParam;              // ���콺 x, y ��ǥ (lParam) 
            g_Pen_Info->penWidth = *pen_Width;                // �� ���� (�⺻ �� 10)
            g_Pen_Info->penColor = *pen_Color;               // �� ���� (�⺻ �� RGB(0, 0, 0))
            g_Pen_Info->penTime = (DWORD)GetTickCount64();   // �׸��� �ð�
            g_Pen_Info->penState = message;                  // ���� (ex WM_LBUTTONDOWN)

            g_Pen_Info->stampOn = false;
            g_Pen_Info->stampImg = 0;
            g_Pen_Info->stampSize = 0;
            // ���� ������ �� ����ü ������ PUSH
            //penMemory->push_back(*g_Pen_Info);
            penMemory->emplace_back(std::move(*g_Pen_Info));
           
        }
        break;

    case WM_LBUTTONUP:
        if (this->drawStart)
        {
            // �� LBUTTON state �� ������ ����ü�� ����
            g_Pen_Info->penCoordinate = lParam;              // ���콺 x, y ��ǥ (lParam) 
            g_Pen_Info->penWidth = *pen_Width;                // �� ���� (�⺻ �� 10)
            g_Pen_Info->penColor = *pen_Color;               // �� ���� (�⺻ �� RGB(0, 0, 0))
            g_Pen_Info->penTime = (DWORD)GetTickCount64();   // �׸��� �ð�
            g_Pen_Info->penState = message;                  // ���� (ex WM_LBUTTONDOWN)

            g_Pen_Info->stampOn = false;
            g_Pen_Info->stampImg = 0;
            g_Pen_Info->stampSize = 0;

            // ���� ������ �� ����ü ������ PUSH
            //penMemory->push_back(*g_Pen_Info);
            penMemory->emplace_back(std::move(*g_Pen_Info));

            this->drawStart = false;
            break;
        }
        break;
    }
    SelectObject(hdc, osP);

    DeleteObject(myP);      // ���� ����
    ReleaseDC(hWnd, hdc);  // HDC �ڿ� ����
}

/*
@fn  PenDraw::stayPaint(HDC hdc, HWND hWnd, vector<PEN_INFO>* penMemory)
@brief �׸��� ���� �޼���
@param hdc WM_PAINT: ���̺��� hdc�� ����
@param hWnd ������ �ڵ�
@param penMemory ���� ����
*/
void PenDraw::stayPaint(HDC hdc, HWND hWnd, vector<PEN_INFO>* penMemory) {

    this->s_Hdc = hdc;

    for (size_t i = 0; i < penMemory->size(); i++) {

        // �����͸� �������Ͽ� PEN_INFO ��ü�� ����
        PEN_INFO& penInfo = (*penMemory)[i];

        myP = CreatePen(PS_SOLID, penInfo.penWidth, penInfo.penColor);
        osP = (HPEN)SelectObject(s_Hdc, myP);

        switch (penInfo.penState) {
        case WM_LBUTTONDOWN:
            x = LOWORD(penInfo.penCoordinate);
            y = HIWORD(penInfo.penCoordinate);

            if (penInfo.stampOn == true) {
                int stampX = x;
                int stampY = y;
                int stampIcon = penInfo.stampImg;
                int stampWidth = penInfo.stampSize;   // ���ϴ� ������ �ʺ�
                int stampHeight = penInfo.stampSize;  // ���ϴ� ������ ����

                HICON hIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(stampIcon), IMAGE_ICON, stampWidth, stampHeight, 0);
                DrawIconEx(hdc, stampX - stampWidth / 2, stampY - stampHeight / 2, hIcon, stampWidth, stampHeight, 0, NULL, DI_NORMAL);
                break;
            }

            MoveToEx(hdc, x, y, NULL);
            LineTo(hdc, x, y);  // �����
            break;

        case WM_MOUSEMOVE:
            LineTo(hdc, LOWORD(penInfo.penCoordinate), HIWORD(penInfo.penCoordinate));
            break;

        case WM_LBUTTONUP:
            LineTo(hdc, LOWORD(penInfo.penCoordinate), HIWORD(penInfo.penCoordinate));
            break;

        default:
            break;
        }
        SelectObject(s_Hdc, osP);
        DeleteObject(myP);  // ���ҽ� �ڿ� Ȯ�� ���� ����
    }

    ReleaseDC(hWnd, s_Hdc);
}
