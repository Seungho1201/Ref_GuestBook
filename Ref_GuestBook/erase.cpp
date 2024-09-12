/**
@file erase.cpp
@brief ����� ��� Ŭ���� �ܺ� ���� ����
*/
#include "erase.h"

/**
@fn  Eraser::Eraser()
@brief ����� ���� �ʱ�ȭ�� ���� ������
*/
Eraser::Eraser() {
    this->paintArea = { PAINT_R_LEFT, 
                        PAINT_R_TOP, 
                        PAINT_R_RIGHT, 
                        PAINT_R_BOTTOM };
}

/**
@fn   Eraser::erase(HWND hWnd, vector<Pen_Info>* penMemory)
@brief ����� ��� �޼���
@param hWnd ������ �ڵ�
@param penMemory ����� ��ɰ� ���ÿ� ���ͺ��� �ʱ�ȭ�� ���� ������ ����
*/
void Eraser::erase(HWND hWnd, vector<Pen_Info>* penMemory)
{
    /// ���� ���� �ʱ�ȭ
    penMemory->clear();

    /// �������� Ŭ���̾�Ʈ ������ ��ȿȭ�Ͽ� �ٽ� �׸��� ��û
    InvalidateRect(hWnd, &this->paintArea, TRUE);
}