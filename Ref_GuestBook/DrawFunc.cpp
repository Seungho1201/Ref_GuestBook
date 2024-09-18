/**
@file DrawFunc.cpp
@brief �׸��� ����  �ڵ�
*/
#include "DrawFunc.h"

/*
@fn  PenDraw::PenDraw()
@brief �׸��� ��� �ڵ� ������
*/
PenDraw::PenDraw() {
    this->x = 0;
    this->y = 0;
    this->preX = 0;
    this->preY = 0;
    this->hdc = nullptr;
    this->myP = nullptr;
    this->osP = nullptr;
    this->drawStart = false;
    this->s_Hdc = nullptr;
    this->penStay = true;
    this->paint_area = { PAINT_R_LEFT,
                         PAINT_R_TOP,
                         PAINT_R_RIGHT, 
                         PAINT_R_BOTTOM };
}

bool PenDraw::isReplay = false;     /// static ���� �ܺ� �ʱ�ȭ

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
void PenDraw::drawLine(int* pen_Width, HWND hWnd, UINT message, LPARAM lParam, COLORREF* pen_Color, PEN_INFO* g_Pen_Info, std::vector<PEN_INFO>* penMemory)
{
    /// ���÷��� ������ �۵��� �׸��� ����� ����
    if (this->isReplay) { return; }

    x = LOWORD(lParam);
    y = HIWORD(lParam);
    hdc = GetDC(hWnd);

    myP = CreatePen(PS_SOLID, *pen_Width, *pen_Color);
    osP = (HPEN)SelectObject(hdc, myP);

    switch (message)
    {
    case WM_LBUTTONDOWN:
        /// �׸��� ������ �ƴ� �� break
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
        g_Pen_Info->penCoordinate = lParam;              /// ���콺 x, y ��ǥ (lParam) 
        g_Pen_Info->penWidth = *pen_Width;               /// �� ���� (�⺻ �� 10)
        g_Pen_Info->penColor = *pen_Color;               /// �� ���� (�⺻ �� RGB(0, 0, 0))
        g_Pen_Info->penTime = (DWORD)GetTickCount64();   /// �׸��� �ð�
        g_Pen_Info->penState = message;                  /// ���� (ex WM_LBUTTONDOWN)

        /// �� ����� �� ������ ���� ���� �����ʹ� 0(false)�� �ʱ�ȭ
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
            || LOWORD(lParam) > PAINT_R_RIGHT   - 5) {
            /// �׸��� ������ �Ѿ�� ���� �׸��� üũ�� ����(drawStart) false
            drawStart = false;
            break;
        }

        if (drawStart)
        {   
            MoveToEx(hdc, this->preX, this->preY, NULL);
            LineTo(hdc, x, y);

            /// ���� ��ǥ ����
            this->preX = x;
            this->preY = y;

            // �� LBUTTON state �� ������ ����ü�� ����
            g_Pen_Info->penCoordinate = lParam;              /// ���콺 x, y ��ǥ (lParam) 
            g_Pen_Info->penWidth = *pen_Width;               /// �� ���� (�⺻ �� 10)
            g_Pen_Info->penColor = *pen_Color;               /// �� ���� (�⺻ �� RGB(0, 0, 0))
            g_Pen_Info->penTime = (DWORD)GetTickCount64();   /// �׸��� �ð�
            g_Pen_Info->penState = message;                  /// ���� (ex WM_LBUTTONDOWN)

            g_Pen_Info->stampOn = false;
            g_Pen_Info->stampImg = 0;
            g_Pen_Info->stampSize = 0;

            /// ���� ������ �� ����ü ������ PUSH
            penMemory->emplace_back(std::move(*g_Pen_Info));
        }
        break;

    case WM_LBUTTONUP:
        if (this->drawStart)
        {
            // �� LBUTTON state �� ������ ����ü�� ����
            g_Pen_Info->penCoordinate = lParam;              // ���콺 x, y ��ǥ (lParam) 
            g_Pen_Info->penWidth = *pen_Width;               // �� ���� (�⺻ �� 10)
            g_Pen_Info->penColor = *pen_Color;               // �� ���� (�⺻ �� RGB(0, 0, 0))
            g_Pen_Info->penTime = (DWORD)GetTickCount64();   // �׸��� �ð�
            g_Pen_Info->penState = message;                  // ���� (ex WM_LBUTTONDOWN)

            g_Pen_Info->stampOn = false;
            g_Pen_Info->stampImg = 0;
            g_Pen_Info->stampSize = 0;

            /// ���� ������ �� ����ü ������ PUSH
            penMemory->emplace_back(std::move(*g_Pen_Info));

            /// ��Ŭ�� ���°� �ƴҽ� �׸��� ���� ������ false�� ��
            this->drawStart = false;
            break;
        }
        break;
    }
    SelectObject(hdc, osP);
    DeleteObject(myP);      
    ReleaseDC(hWnd, hdc);  
}

/*
@fn  PenDraw::stayPaint(HDC hdc, HWND hWnd, vector<PEN_INFO>* penMemory)
@brief �׸��� ���� �޼���
@param hdc WM_PAINT: ���̺��� hdc�� ����
@param hWnd ������ �ڵ�
@param penMemory ���� ����
*/
void PenDraw::drawStay(HDC hdc, HWND hWnd, std::vector<PEN_INFO>* penMemory) {

    /// �׸��� ���� ������ false�� �� return
    if (!penStay) { return; }


    /// WM_PAINT �� hdc�� �޾ƿ�
    this->s_Hdc = hdc;

    /// ���� ������ ũ�� ��ŭ �ݺ�
    for (size_t i = 0; i < penMemory->size(); i++) {

        /// �����͸� �������Ͽ� PEN_INFO ��ü�� ����
        PEN_INFO& penInfo = (*penMemory)[i];

        myP = CreatePen(PS_SOLID, penInfo.penWidth, penInfo.penColor);
        osP = (HPEN)SelectObject(s_Hdc, myP);

        /// ��Ŭ�� ����(state)
        switch (penInfo.penState) {

        case WM_LBUTTONDOWN:
            x = LOWORD(penInfo.penCoordinate);
            y = HIWORD(penInfo.penCoordinate);

            /// �� ��尡 �ƴ� ������ ����� �� �������� �׸��� ���� ���ǹ�
            if (penInfo.stampOn == true) {
                int stampX = x;
                int stampY = y;
                int stampIcon = penInfo.stampImg;
                int stampWidth = penInfo.stampSize;  
                int stampHeight = penInfo.stampSize;  

                HICON hIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(stampIcon), IMAGE_ICON, stampWidth, stampHeight, 0);
                DrawIconEx(hdc, stampX - stampWidth / 2, stampY - stampHeight / 2, hIcon, stampWidth, stampHeight, 0, NULL, DI_NORMAL);
                break;
            }

            MoveToEx(hdc, x, y, NULL);
            LineTo(hdc, x, y);  // �����
            break;

        case WM_MOUSEMOVE:
        case WM_LBUTTONUP:
            LineTo(hdc, LOWORD(penInfo.penCoordinate), HIWORD(penInfo.penCoordinate));
            break;

        default:
            break;
        }
        SelectObject(s_Hdc, osP);
        DeleteObject(myP);  
    }
    ReleaseDC(hWnd, s_Hdc);
}

/*
@fn PenDraw::replaythread(HWND g_Hwnd, vector<Pen_Info>* penMemory)
@brief ���÷��� ������ ȣ�� �޼���
@param g_Hwnd: ������ �ڵ�
@param penMemory: main���� ���Ǵ� ���� ������ ���� ������
*/
void PenDraw::replayThread(HWND g_Hwnd, std::vector<Pen_Info>* penMemory)
{
    /// ���÷��� ���� ���϶� ������ ������ ����
    if (this->isReplay) { return; }

    /// ���� ������ �ƴ� ������ ������ ���� ���� ����
    copiedMemory = *penMemory;

    /// ���ٽ� ���
    /// [this, g_Hwnd] : ���ٽ��� ĸó����Ʈ (�Լ� ������ ����� �ܺκ��� ĸ��)
    /// ������ ����Ͽ� drwaReplay ���� 
    startReplayThread = std::thread([this, g_Hwnd]() { this->drawReplay(g_Hwnd); });

    /// ������ ��ȯ
    startReplayThread.detach();
}

/*
@fn PenDraw::drawReplay(HWND g_Hwnd)
@brief ���÷��� ������� ȣ��Ǵ� �޼���
@param g_Hwnd: ������ �ڵ�
*/
void PenDraw::drawReplay(HWND g_Hwnd)
{


    /// WM_PAINT ���� �׸��� �����ϴ� ������ ���÷��� ���� ���� ��Ȱ��ȭ
    this->penStay = false;
    this->isReplay = true;

    HDC hdc;
    hdc = GetDC(g_Hwnd);
  
    /// ������ �׸��� ����(&paint_area) �ʱ�ȭ
    InvalidateRect(g_Hwnd, &paint_area, TRUE);
    UpdateWindow(g_Hwnd);

    // ���� ���� penMemory�� �ݺ�
    for (size_t i = 0; i < copiedMemory.size(); i++) {
        myP = CreatePen(PS_SOLID, copiedMemory[i].penWidth, copiedMemory[i].penColor);
        osP = (HPEN)SelectObject(hdc, myP);

        switch (copiedMemory[i].penState)
        {
        case WM_LBUTTONDOWN:
            x = LOWORD(copiedMemory[i].penCoordinate);
            y = HIWORD(copiedMemory[i].penCoordinate);

            if (copiedMemory[i].stampOn == true) {
                int stampX = x;
                int stampY = y;
                int stampIcon = copiedMemory[i].stampImg;
                int stampWidth = copiedMemory[i].stampSize;   // ���ϴ� ������ �ʺ�
                int stampHeight = copiedMemory[i].stampSize;  // ���ϴ� ������ ����

                HICON hIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(stampIcon), IMAGE_ICON, stampWidth, stampHeight, 0);
                DrawIconEx(hdc, stampX - stampWidth / 2, stampY - stampHeight / 2, hIcon, stampWidth, stampHeight, 0, NULL, DI_NORMAL);
                Sleep(100);
                break;
            }

            MoveToEx(hdc, x, y, NULL);
            LineTo(hdc, x, y);  // �����
            break;

        case WM_MOUSEMOVE:
            LineTo(hdc, LOWORD(copiedMemory[i].penCoordinate), HIWORD(copiedMemory[i].penCoordinate));
            break;

        case WM_LBUTTONUP:
            LineTo(hdc, LOWORD(copiedMemory[i].penCoordinate), HIWORD(copiedMemory[i].penCoordinate));
            break;

        default:
            break;
        }

        // ���� ���� �ݺ� �ߴ���
        if (i + 1 < copiedMemory.size() && copiedMemory[i + 1].penState == WM_MOUSEMOVE) {
            Sleep(copiedMemory[i + 1].penTime - copiedMemory[i].penTime);
        }

        SelectObject(hdc, osP);
        DeleteObject(myP);  // ���ҽ� �ڿ� Ȯ�� ���� ����
    }
    /// ���÷��� ��� ���� �� �׸��� ���� Ȱ��ȭ
    this->penStay = true;
    this->isReplay = false;
    ReleaseDC(g_Hwnd, hdc);
    //return 0;
}