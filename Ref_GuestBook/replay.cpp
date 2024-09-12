#include "replay.h"

DrawReplay::DrawReplay() {
    this->penMemory = nullptr;
    this->g_Hwnd = nullptr;
    this->paintArea = { PAINT_R_LEFT, PAINT_R_TOP, PAINT_R_RIGHT, PAINT_R_BOTTOM };
    this->myP = nullptr;
    this->osP = nullptr;
    this->hdc = nullptr;
    this->x = 0;
    this->y = 0;
}

// ������ ����
void DrawReplay::replayThread(HWND g_Hwnd, vector<Pen_Info>* penMemory)
{
    this->g_Hwnd = g_Hwnd;
    this->penMemory = penMemory;

    // this �����͸� �����Ͽ� �����忡�� �ش� ��ü�� ��� �Լ� ȣ��
    CreateThread(NULL, 0, ThreadFunc, (LPVOID)this, 0, NULL);
}

// �����忡�� ����� ���� �Լ�
DWORD WINAPI DrawReplay::ThreadFunc(LPVOID lpParam) 
{
    DrawReplay* pThis = (DrawReplay*)lpParam;
    return pThis->drawReplay();
}

// ���� �۾��� ����
DWORD DrawReplay::drawReplay()
{
    hdc = GetDC(this->g_Hwnd);

    // ��û�� �ٷ� ó������ �ʰ� �޼��� ť�� ���� �� ��� �۾��� ���� �� ����
    InvalidateRect(this->g_Hwnd, &paintArea, TRUE);

    // ��� ������Ʈ ��û�� ������ ��� �۾��� ������ ����Ǵ� InvalidateRect �Լ��� ��� ȣ��
    UpdateWindow(this->g_Hwnd);

    // ���� ���� penMemory�� �ݺ�
    for (size_t i = 0; i < penMemory->size(); i++) {
        myP = CreatePen(PS_SOLID, (*penMemory)[i].penWidth, (*penMemory)[i].penColor);
        osP = (HPEN)SelectObject(hdc, myP);

        switch ((*penMemory)[i].penState) {
        case WM_LBUTTONDOWN:
            x = LOWORD((*penMemory)[i].penCoordinate);
            y = HIWORD((*penMemory)[i].penCoordinate);

            if ((*penMemory)[i].stampOn == true) {
                int stampX = x;
                int stampY = y;
                int stampIcon = (*penMemory)[i].stampImg;
                int stampWidth = (*penMemory)[i].stampSize;   // ���ϴ� ������ �ʺ�
                int stampHeight = (*penMemory)[i].stampSize;  // ���ϴ� ������ ����


                HICON hIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(stampIcon), IMAGE_ICON, stampWidth, stampHeight, 0);
                DrawIconEx(hdc, stampX - stampWidth / 2, stampY - stampHeight / 2, hIcon, stampWidth, stampHeight, 0, NULL, DI_NORMAL);
                Sleep(100);
                break;
            }

            MoveToEx(hdc, x, y, NULL);
            LineTo(hdc, x, y);  // �����
            break;

        case WM_MOUSEMOVE:
            LineTo(hdc, LOWORD((*penMemory)[i].penCoordinate), HIWORD((*penMemory)[i].penCoordinate));
            break;

        case WM_LBUTTONUP:
            LineTo(hdc, LOWORD((*penMemory)[i].penCoordinate), HIWORD((*penMemory)[i].penCoordinate));
            break;

        default:
            break;
        }

        // ���� ���� �ݺ� �ߴ���
        if (i + 1 < penMemory->size() && (*penMemory)[i + 1].penState == WM_MOUSEMOVE) {
            Sleep((*penMemory)[i + 1].penTime - (*penMemory)[i].penTime);
        }

        SelectObject(hdc, osP);
        DeleteObject(myP);  // ���ҽ� �ڿ� Ȯ�� ���� ����
    }

    ReleaseDC(this->g_Hwnd, hdc);
    return 0;
}
