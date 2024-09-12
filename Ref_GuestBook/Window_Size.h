#pragma once
#include "Ref_GuestBook.h"


/**
* @WM_GETMINMAXINFO 창의 크기 조절 메세지
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