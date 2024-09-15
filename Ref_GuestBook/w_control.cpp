#include "w_control.h"

PenWidthControl::PenWidthControl() {
    this->textRect = { WIDTH_R_LEFT, 
                       WIDTH_R_TOP, 
                       WIDTH_R_RIGHT,
                       WIDTH_R_BOTTOM };

    this->wc_Hdc = nullptr;
}

void PenWidthControl::widthControl(HWND g_Hwnd, int func, int* pen_Width, int* stamp_Size, bool* stampActive)
{
    switch (func)
    {
    case W_UP:
        if (*stampActive) {  // ������ ����� ��
            // ������ �ִ� ũ�� ����
            if (*stamp_Size < 100) {
                *stamp_Size += 10;
            }

        // �� ����� ��
        } else {  
            if (*pen_Width < 20) {  // �� �ִ� ���� ����
                *pen_Width += 1;
            }
        }
        break;

    case W_DOWN:
        // ������ ����� ��
        if (*stampActive) {  
            if (*stamp_Size > 10) {   // ������ �ּ� ���� ����
                *stamp_Size -= 10;
            }

        // �� ����� ��
        } else {  
            if (*pen_Width > 1) {   // �� �ּ� ���� ����
                *pen_Width -= 1;
            }
        }
        break;
    }

    // ����� ���� ���� �ؽ�Ʈ ������ ��ȿȭ�ϰ� ����
    InvalidateRect(g_Hwnd, &this->textRect, TRUE);
    UpdateWindow(g_Hwnd);
}

void PenWidthControl::penWidthDisplay(HDC Hdc, bool* stampActive, int* stamp_Size, int* pen_Width)
{
    wc_Hdc = Hdc;

    WCHAR szPenWidth[10] = {};

    if (*stampActive) {
        // ������ ������ ��� (10 ������ ����� ���)
        wsprintf(szPenWidth, L"%d", *stamp_Size / 10);
    } else {
        // �� ���� ���
        wsprintf(szPenWidth, L" %d", *pen_Width);
    }
    /// ���
    TextOut(wc_Hdc, 420, 15, szPenWidth, lstrlen(szPenWidth)); 

}