#pragma once
#include <windows.h>  // CreateWindow�� �ʿ��� ���


class MakeButton {
private:
    int x;                // ��ư�� x ��ġ
    int y;                // ��ư�� y ��ġ
    int weight;           // ��ư�� ��
    int height;           // ��ư�� ����
    int func;             // ��ư�� ID
    LPCWSTR text;         // ��ư �ؽ�Ʈ
    HWND c_Hwnd;          // �θ� ������ �ڵ�

public:

    /**
    * @brief       ��ư ���� ������ (x, y, �ʺ�, ����, ���, ��ư �� �ؽ�Ʈ)
    */
    MakeButton(int x, int y, int weight, int height, int func, LPCWSTR text);

    // ��ư ���� �޼���
    // ���� ������ ���� �� g_Hwnd ������ ����ؾ� ������ 
    // WM_CREATE �κп��� �ʱ�ȭ�� ���� ���ڷ�  HWND Ÿ�� ���� ���
    void mkButton(HWND g_Hwnd);
};
