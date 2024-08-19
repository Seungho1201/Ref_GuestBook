#include "Button.h"

extern HWND g_Hwnd;

// �����ڿ� �̹��� ��� ���� �߰� ����
MakeButton::MakeButton(int x, int y, int width, int height, int func, LPCWSTR text) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->func = func;
    this->text = text;
    // �̹��� ��� ���� �߰� ����
}

/// <summary>
/// ��ư ������ �ΰ����� ������
/// 1. �ؽ�Ʈ�� ��ư ���� - ���� �� X
/// 2. ���� ��� ����� ���� - ������ ���� �� 1��
/// 
/// ���� �������� �߰��ϰų� �����ϰ��� ������ ���� �� ������ 
/// �������� ��Ʈ�� Ȯ����(bmp)�� �����̿��� �ϰ� "���ҽ� ����" �ȿ� �����ؾ� ��
/// �������� Ref_GuestBook.rc ���Ͽ��� ���� �Ѵ� (ex: IDI_ERASE_ICON    ICON    "..\..\icon\Pen.ico")
/// rc ���Ͽ��� ���� �� Resource.h ���Ͽ��� ����� ������ �Ѵ� (ex: #define IDI_ERASE_ICON     130)
/// ���� ������ �̹����� ���� �ν���Ʈ�� mkButton(int path) �޼����� ���ڷ� Resource.h ���Ͽ��� ������ ����� �ִ´�.
/// </summary>
void MakeButton::mkButton() {
    CreateWindow(
        L"BUTTON",                                              // ��ư Ŭ���� �̸�
        text,                                                   // ��ư �ؽ�Ʈ
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,     // ��ư ��Ÿ��
        x,                                                      // ��ư�� x ��ġ
        y,                                                      // ��ư�� y ��ġ
        width,                                                  // ��ư�� ��
        height,                                                 // ��ư�� ����
        g_Hwnd,                                                 // �θ� ������ �ڵ�
        (HMENU)func,                                            // ��ư�� ID
        (HINSTANCE)GetWindowLongPtr(g_Hwnd, GWLP_HINSTANCE),    // �ν��Ͻ� �ڵ�
        NULL                                                    // �߰� �Ű�����
    );
}

void MakeButton::mkButton(int path) {
    CreateWindow(
        L"BUTTON",                                              // ��ư Ŭ���� �̸�
        text,                                                   // ��ư �ؽ�Ʈ
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_ICON,           // ��ư ��Ÿ��
        x,                                                      // ��ư�� x ��ġ
        y,                                                      // ��ư�� y ��ġ
        width,                                                  // ��ư�� ��
        height,                                                 // ��ư�� ����
        g_Hwnd,                                                 // �θ� ������ �ڵ�
        (HMENU)func,                                            // ��ư�� ID
        (HINSTANCE)GetWindowLongPtr(g_Hwnd, GWLP_HINSTANCE),    // �ν��Ͻ� �ڵ�
        NULL                                                    // �߰� �Ű�����
    );

    insertIconImg(text, path, (HINSTANCE)GetWindowLongPtr(g_Hwnd, GWLP_HINSTANCE));
}

// ������ ���� �޼���
void MakeButton::insertIconImg(LPCWSTR text, int path, HINSTANCE hInst)
{
    HICON hIcon = LoadIcon(hInst, MAKEINTRESOURCE(path));
    SendMessageW(FindWindowExW(g_Hwnd, NULL, L"button", text), BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon);
}