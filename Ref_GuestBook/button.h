#pragma once
#include <windows.h>  // CreateWindow�� �ʿ��� ���


class MakeButton {
private:
    int x;                // ��ư�� x ��ġ
    int y;                // ��ư�� y ��ġ
    int width;            // ��ư�� ��
    int height;           // ��ư�� ����
    int func;             // ��ư�� ID
    LPCWSTR text;         // ��ư �ؽ�Ʈ
    HWND hButton;

public:
    /**
    * @brief       ��ư ���� ������ (x, y, �ʺ�, ����, ���, ��ư �� �ؽ�Ʈ)
    */
    MakeButton(int x, int y, int width, int height, int func, LPCWSTR text);


    // ��ư ���� �޼���
    // g_Hwnd ���� ������ �������������� ���� X
    void mkButton();

    // �̹��� ��� ��� ���ڰ�
    void mkButton(int path);

private:
    void insertIconImg(LPCWSTR text, int path, HINSTANCE hInst);
};
