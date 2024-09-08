#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include<vector>
#include<Windows.h>

using namespace std;

/**
 * @brief       �� ���� ������ ����ü
 * (��ǥ, �� ����, ����, �ð�, ����(LBUTTON))
*/
typedef struct Pen_Info
{
    LPARAM      penCoordinate;     // ��ǥ
    int         penWidth;          // �� ����
    COLORREF    penColor;          // �� ����
    DWORD       penTime;           // �ð�
    UINT        penState;          // ���� (LBUTTON)
    bool        test;
    int         stampImg;          // ������ �̹���
    int         stampSize;         // ������ ������
} PEN_INFO;


/**
 * @brief       Pen_Info ����ü�� ���� �ڷᱸ���� �����ϱ� ���� ���� ����ü
 * ���÷��� ������� ���
*/
extern vector<PEN_INFO> penMemory;

extern PEN_INFO g_Pen_Info;     // �� ����ü �������� ���� (extern)
extern COLORREF pen_Color;      // �� ���� �������� ���� (extern)
extern int pen_Width;           // �� ���� �������� ���� (ectern)

