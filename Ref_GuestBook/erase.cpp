#include <iostream>
#include "Pen_Str.h"
#include "erase.h"

void Eraser::erase(HWND hWnd)
{
    /// ���� ���� �ʱ�ȭ
    penMemory.clear();

    /// �������� Ŭ���̾�Ʈ ������ ��ȿȭ�Ͽ� �ٽ� �׸��� ��û
    InvalidateRect(hWnd, NULL, TRUE);
}