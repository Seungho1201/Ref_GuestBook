/**
@file button.h
@brief ��ư ���� Ŭ���� ��� ���� ����
*/
#pragma once
#include <windows.h>  /// CreateWindow�� �ʿ��� ���
#include "framework.h"
#include "Resource.h"

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
    static int buttonHighlight;                     /// ��ư ID ���� ���� ����
    static RECT buttonRect;                         /// Ŭ���� ��ư ����� ����
    static RECT buttonRectBefore;                   /// ���� Ŭ���� ��ư ����� ����
    static std::vector<MakeButton*> buttonList;     /// ��ư�� ������ ���� ����

    MakeButton(int x, int y, int width, int height, int func, LPCWSTR text);

    void mkButton(HWND g_Hwnd);
    void mkButton(HWND g_Hwnd, int path);
    void mkButton(HWND g_Hwnd, COLORREF color);

    static void getClickHighlight(int wmId, HWND g_Hwnd);
    static void setClickHighlight(HDC hdc);

private:
    void insertIconImg(LPCWSTR text, int path, HINSTANCE hInst);
};
