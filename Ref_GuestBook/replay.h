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

    // 스레드를 생성하는 함수
    void replayThread(HWND g_Hwnd, vector<Pen_Info>* penMemory);

private:
    // 스레드에서 실행할 함수 
    static DWORD WINAPI ThreadFunc(LPVOID lpParam);

    // 스레드에서 호출할 실제 멤버 함수
    DWORD drawReplay();
};
