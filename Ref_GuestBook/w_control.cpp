/**
@file w_control.cpp
@brief ����(������ ������) ���� ���� Ŭ���� �ܺ� ���� ����
*/

#include "w_control.h"

/*
@fn PenWidthControl::PenWidthControl()
@brief ����(������ ������) ���� Ŭ���� ������
*/
PenWidthControl::PenWidthControl() {
    this->textRect = { WIDTH_R_LEFT, 
                       WIDTH_R_TOP, 
                       WIDTH_R_RIGHT,
                       WIDTH_R_BOTTOM };

    this->wc_Hdc = nullptr;
}

/*
@fn PenWidthControl::widthControl(HWND g_Hwnd, int func, int* pen_Width, int* stamp_Size, bool* stampActive)
@brief ����(������ ������) ���� �޼���
@param g_Hwnd ������ �ڵ�
@param func ������ ��� �޼��� WM_COMMAND���� (wmId) ����
@param penWidth �� ���� ���� ���� ������ ����
@param stamp_Size ������ ������ ���� ���� ������ ����
@param stampActive ������ Ȱ��ȭ ���� Ȯ�� ���� ������ ����
*/
void PenWidthControl::widthControl(HWND g_Hwnd, int func, int* pen_Width, int* stamp_Size, bool* stampActive)
{
    /// WM_COMMAND ���� wmId���� ����
    switch (func)
    {
    /// ��(������) ������ UP
    case W_UP:
        /// ������ ����� ��
        if (*stampActive) {  
            /// ������ ũ���� �ִ� ������� 100���� ����
            if (*stamp_Size < 100) { *stamp_Size += 10; }

        /// �� ����� ��
        } else {  
            /// �� �ִ� ���� ������� 20
            if (*pen_Width < 20) { *pen_Width += 1; }
        }
        break;

    /// ��(������) ������ DOWN
    case W_DOWN:
        /// ������ ����� ��
        if (*stampActive) {  
            if (*stamp_Size > 10) { *stamp_Size -= 10; }

        /// �� ����� ��
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

/*
@fn  PenWidthControl::penWidthDisplay(HDC Hdc, bool* stampActive, int* stamp_Size, int* pen_Width)
@brief ����(������ ������) ��� �޼���
@param hdc WM_PAINT���� ���� hdc
*/
void PenWidthControl::penWidthDisplay(HDC Hdc, bool* stampActive, int* stamp_Size, int* pen_Width)
{
    wc_Hdc = Hdc;

    WCHAR szPenWidth[10] = {};

    if (*stampActive) {
        // ������ ������ ��� (10 ������ ����� ���)
        wsprintf(szPenWidth, L"%2d", *stamp_Size / 10);
    }
    else {
        // �� ���� ���
        wsprintf(szPenWidth, L"%2d", *pen_Width);
    }

    // ��Ʈ ����
    HFONT hFont, hOldFont;
    hFont = CreateFont(
        30,                // ���� ũ�� (����)
        0,                 // ���� �ʺ� (0�� �ڵ����� ����)
        0,                 // ���� ����
        0,                 // ���ؼ� ����
        FW_THIN,           // ���� ���� �β�
        FALSE,             // ���Ÿ�ü ����
        FALSE,             // ���� ����
        FALSE,             // ��Ҽ� ����
        DEFAULT_CHARSET,   // ���� ��Ʈ
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS,
        L"Arial"           // ��Ʈ �̸�
    );

    // ���ο� ��Ʈ�� HDC�� �����ϰ� ���� ��Ʈ�� ����
    hOldFont = (HFONT)SelectObject(wc_Hdc, hFont);

    // �ؽ�Ʈ ���
    TextOut(wc_Hdc, 430, 15, szPenWidth, lstrlen(szPenWidth));

    // ���� ��Ʈ�� ����
    SelectObject(wc_Hdc, hOldFont);

    // ���� ������ ��Ʈ ����
    DeleteObject(hFont);
}
