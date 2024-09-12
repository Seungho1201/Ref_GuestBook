/**
@file button.cpp
@brief ��ư ���� ���� Ŭ���� �ܺ� ���� ����
*/
#include "button.h"

/*
@fn  MakeButton::MakeButton(int x, int y, int width, int height, int func, LPCWSTR text)
@brief ��ư Ŭ���� ������
@param x ��ư�� x ��ǥ
@param y ��ư�� y��ǥ
@param width ��ư�� ��
@param height ��ư�� �ʺ�
@param func COMMAND���� �۵��� ��� ���
@param text ��ư�� �׷����� �ؽ�Ʈ
*/
MakeButton::MakeButton(int x, int y, int width, int height, int func, LPCWSTR text) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->func = func;
    this->text = text;
    this->hButton = nullptr;
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
/// ���� ������ �̹����� ���� �ν��Ͻ��� mkButton(int path) �޼����� ���ڷ� Resource.h ���Ͽ��� ������ ����� �ִ´�.
/// </summary>


/**
@fn  MakeButton::mkButton()
@brief ��ư Ŭ������ ��ư ���� �޼���
@param g_Hwnd ������ �ڵ�
*/
void MakeButton::mkButton(HWND g_Hwnd) {
    this->hButton = g_Hwnd;

    /// CreateWindow �Լ��� ��ư ����
    CreateWindow(
        L"BUTTON",                                                          // ��ư Ŭ���� �̸�
        text,                                                               // ��ư �ؽ�Ʈ
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_FLAT,       // ��ư ��Ÿ��
        x,                                                                  // ��ư�� x ��ġ
        y,                                                                  // ��ư�� y ��ġ
        width,                                                              // ��ư�� ��
        height,                                                             // ��ư�� ����
        this->hButton,                                                             // �θ� ������ �ڵ�
        (HMENU)func,                                                        // ��ư�� ID
        (HINSTANCE)GetWindowLongPtr(this->hButton, GWLP_HINSTANCE),                // �ν��Ͻ� �ڵ�
        NULL                                                                // �߰� �Ű�����
    );
}

/**
@fn   MakeButton::mkButton(int path)
@brief ��ư Ŭ������ �̹��� ��ư ���� �޼���
@details �� �޼���� ������ ���ҽ� ����� �̹����� ����Ͽ� ��ư�� ����
@param g_Hwnd ������ �ڵ�
@param path ��ư�� ���Ե� ��Ʈ�� �̹��� ��� (resource.h)
*/
void MakeButton::mkButton(HWND g_Hwnd, int path) {
    this->hButton = g_Hwnd;

    CreateWindow(
        L"BUTTON",                                                          // ��ư Ŭ���� �̸�
        text,                                                               // ��ư �ؽ�Ʈ
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_ICON | BS_FLAT,             // ��ư ��Ÿ��
        x,                                                                  // ��ư�� x ��ġ
        y,                                                                  // ��ư�� y ��ġ
        width,                                                              // ��ư�� ��
        height,                                                             // ��ư�� ����
        this->hButton,                                                             // �θ� ������ �ڵ�
        (HMENU)func,                                                        // ��ư�� ID
        (HINSTANCE)GetWindowLongPtr(this->hButton, GWLP_HINSTANCE),                // �ν��Ͻ� �ڵ�
        NULL                                                                // �߰� �Ű�����
    );

    insertIconImg(text, path, (HINSTANCE)GetWindowLongPtr(this->hButton, GWLP_HINSTANCE));
}

/**
@fn  MakeButton::insertIconImg(LPCWSTR text, int path, HINSTANCE hInst)
@brief �̹��� ��ư ���� �޼����� �̹��� ���� �޼��� (private)
@param text ��ư �ؽ�Ʈ
@param path ��ư�� ���Ե� ��Ʈ�� �̹��� ��� (resource.h)
@param hInst �ν��Ͻ� �ڵ�
*/
void MakeButton::insertIconImg(LPCWSTR text, int path, HINSTANCE hInst)
{
    /// ��ư�� ũ�⿡ �´� �������� �ҷ����� ���� LoadImage�� ���.
    HICON hIcon = (HICON)LoadImage(
        hInst,                        /// �ν��Ͻ� �ڵ�
        MAKEINTRESOURCE(path),        /// ���ҽ� ���
        IMAGE_ICON,                   /// ������ ����
        width,                        /// �������� ���� ũ��
        height,                       /// �������� ���� ũ��
        LR_DEFAULTCOLOR               /// �⺻ ���� �ε� �÷���
    );

    /// ��ư�� ������ ���� �Լ�
    SendMessageW(
        FindWindowExW(this->hButton, NULL, L"BUTTON", text),   /// ��ư�� �ڵ��� ã���ϴ�.
        BM_SETIMAGE,                                    /// ��ư�� �̹����� �����ϴ� �޽���
        IMAGE_ICON,                                     /// �̹��� ������ ���������� ����
        (LPARAM)hIcon                                   /// ������ ������
    );
}
