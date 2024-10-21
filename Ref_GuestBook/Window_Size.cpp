#include "Window_Size.h"


WindowSizeManager::WindowSizeManager(int width, int height)
{
    this->m_width = width;
    this->m_height = height;
}
 
void WindowSizeManager::HandleMinMaxInfo(LPARAM lParam) const
{
    MINMAXINFO* minMaxInfo = reinterpret_cast<MINMAXINFO*>(lParam);
    
    minMaxInfo->ptMinTrackSize.x = m_width;
    minMaxInfo->ptMinTrackSize.y = m_height;
}