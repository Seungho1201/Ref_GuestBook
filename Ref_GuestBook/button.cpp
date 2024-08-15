#include "Button.h"

// �����ڿ� �̹��� ��� ���� �߰� ����
MakeButton::MakeButton(int x, int y, int weight, int height, int func, LPCWSTR text) {
    this->x = x;
    this->y = y;
    this->weight = weight;
    this->height = height;
    this->c_Hwnd = NULL;
    this->func = func;
    this->text = text;
    // �̹��� ��� ���� �߰� ����
}

void MakeButton::mkButton(HWND g_Hwnd) {
    this->c_Hwnd = g_Hwnd;

    CreateWindow(
        L"BUTTON",                                              // ��ư Ŭ���� �̸�
        text,                                                   // ��ư �ؽ�Ʈ
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // ��ư ��Ÿ��
        x,                                                      // ��ư�� x ��ġ
        y,                                                      // ��ư�� y ��ġ
        weight,                                                 // ��ư�� ��
        height,                                                 // ��ư�� ����
        c_Hwnd,                                                 // �θ� ������ �ڵ�
        (HMENU)func,                                            // ��ư�� ID
        (HINSTANCE)GetWindowLongPtr(c_Hwnd, GWLP_HINSTANCE),    // �ν��Ͻ� �ڵ�
        NULL                                                    // �߰� �Ű�����
    );
}
