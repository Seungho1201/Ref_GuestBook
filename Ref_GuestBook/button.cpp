/**
@file button.cpp
@brief ��ư ���� ���� Ŭ���� �ܺ� ���� ����
*/
#include "button.h"

/// static ��� ����
std::vector<MakeButton*> MakeButton::buttonList;

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
MakeButton::MakeButton(int x, int y, int width, int height, int func, LPCWSTR text) 
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->func = func;
    this->text = text;
    this->hButton = nullptr;

    /// ��ư ���� �� ����Ʈ�� �ٷ� PUSH
    buttonList.push_back(this);
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
void MakeButton::mkButton(HWND g_Hwnd) 
{
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
    /// ���� �׵θ� ���� �޼��� ����
    SendMessage(g_Hwnd, WM_UPDATEUISTATE, MAKELONG(UIS_SET, UISF_HIDEFOCUS), 0);
}

/**
@fn   MakeButton::mkButton(int path)
@brief ��ư Ŭ������ �̹��� ��ư ���� �޼���
@details �� �޼���� ������ ���ҽ� ����� �̹����� ����Ͽ� ��ư�� ����
@param g_Hwnd ������ �ڵ�
@param path ��ư�� ���Ե� ��Ʈ�� �̹��� ��� (resource.h)
*/
void MakeButton::mkButton(HWND g_Hwnd, int path) 
{
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

    /// ���� �׵θ� ���� �޼��� ����
    SendMessage(g_Hwnd, WM_UPDATEUISTATE, MAKELONG(UIS_SET, UISF_HIDEFOCUS), 0);
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

int MakeButton::buttonHighlight = 0;
RECT MakeButton::buttonRect = { 0, 0, 0, 0 };
RECT MakeButton::buttonRectBefore = { 0, 0, 0, 0 };

void MakeButton::getClickHighlight(int wmId, HWND g_Hwnd)
{
    RECT test = { 0, 0, 1450, 120 };

    /// Ŭ���� ��ư�� func�� ��, ID�� ����
    MakeButton::buttonHighlight = wmId;

    /// ��ư ����Ʈ(std::vector<MakeButton*>)�� �ݺ� 
    for (auto button : buttonList) {
        /// ��ư ����Ʈ�� �� Ŭ���� ��ư�� ID�� ��ġ�ϴ� ������ ���� ���� if��
        if (button->func == MakeButton::buttonHighlight) 
        {
            /// ���� ��ư�� ��ǥ �����͸� ����
            MakeButton::buttonRectBefore = MakeButton::buttonRect;

            /// ���� Ŭ���� ��ư�� �����ͷ� ���� ����
            MakeButton::buttonRect.left = button->x - 4;
            MakeButton::buttonRect.top = button->y - 4;
            MakeButton::buttonRect.right = button->x + button->width + 4;
            MakeButton::buttonRect.bottom = button->y + button->height + 4;

            break;
        }
    }
    /// ���� �ܰ��� ����� �� �� �ܰ��� �׸��� ��û
    InvalidateRect(g_Hwnd, &MakeButton::buttonRectBefore, TRUE);  
    InvalidateRect(g_Hwnd, &MakeButton::buttonRect, TRUE); 

    // WM_PAINT�� ������ ȣ��
    UpdateWindow(g_Hwnd);
}

void MakeButton::setClickHighlight(HDC hdc)
{
    /// ���� 2�� �簢������ �ܰ��� ����
    HPEN hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0)); 
    HPEN oldPen = (HPEN)SelectObject(hdc, hPen);

    /// Ŭ���� ��ư �ܰ��� �׸���
    Rectangle(hdc, MakeButton::buttonRect.left,
                   MakeButton::buttonRect.top, 
                   MakeButton::buttonRect.right,
                   MakeButton::buttonRect.bottom);         

    SelectObject(hdc, oldPen);
    DeleteObject(hPen);            
}
