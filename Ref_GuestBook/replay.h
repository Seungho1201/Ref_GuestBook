#pragma once

#include <iostream>
#include <windows.h>
#include <vector>
#include "framework.h"
#include "stamp.h"
#include "resource.h"
#include "Ref_GuestBook.h"

using namespace std;

class DrawReplay {
private:
    vector<Pen_Info>* penMemory;
    RECT paintArea;
    HPEN myP;
    HPEN osP;
    HDC hdc;
    HWND g_Hwnd;
    int x;
    int y;

public:
    DrawReplay();

    // �����带 �����ϴ� �Լ�
    void replayThread(HWND g_Hwnd, vector<Pen_Info>* penMemory);

private:
    // �����忡�� ������ �Լ� 
    static DWORD WINAPI ThreadFunc(LPVOID lpParam);

    // �����忡�� ȣ���� ���� ��� �Լ�
    DWORD drawReplay();
};
