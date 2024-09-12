#pragma once
#include "Ref_GuestBook.h"


/**
* @WM_GETMINMAXINFO â�� ũ�� ���� �޼���
*/
class WindowSizeManager
{
public:

    WindowSizeManager(int width, int height);
    void HandleMinMaxInfo(LPARAM lParam) const;

private:
    int m_width;
    int m_height;
};