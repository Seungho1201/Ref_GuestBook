#include "erase.h"

// �������� ����

/**
 * @brief       ȭ�� ����� �Լ�
 */
void Eraser::erase(HWND hWnd)
{
    /// ���� ���� �ʱ�ȭ
    penMemory.clear();
    /// �������� Ŭ���̾�Ʈ ������ ��ȿȭ�Ͽ� �ٽ� �׸��� ��û

    InvalidateRect(hWnd, NULL, TRUE);
}