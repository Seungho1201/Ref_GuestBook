/**
@file button.h
@brief ��ư ���� Ŭ���� ��� ���� ����
*/
#pragma once
#include <windows.h>  /// CreateWindow�� �ʿ��� ���

class MakeButton {
private:
    int x;                /// ��ư�� x ��ġ
    int y;                /// ��ư�� y ��ġ
    int width;            /// ��ư�� ��
    int height;           /// ��ư�� ����
    int func;             /// ��ư�� ID
    LPCWSTR text;         /// ��ư �ؽ�Ʈ
    COLORREF buttonColor; /// ��ư ������
    HWND hButton;


public:
    MakeButton(int x, int y, int width, int height, int func, LPCWSTR text);

    void mkButton(HWND g_Hwnd);
    void mkButton(HWND g_Hwnd, int path);
    void mkButton(HWND g_Hwnd, COLORREF color);

private:
    void insertIconImg(LPCWSTR text, int path, HINSTANCE hInst);
};
