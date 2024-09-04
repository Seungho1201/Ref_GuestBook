#pragma once
/**
* @Window_Size_Width 윈도우 넓이
* @Window_Size_Height 윈도우 높이
*/
#define Window_Size_Width 1450  
#define Window_Size_Height 900  
/**
* @WM_GETMINMAXINFO 창의 크기 조절 메세지
*/
class WindowSizeManager
{
public:
    /** 
    *생성자: 윈도우의 넓이와 높이를 초기화
    */ 
    WindowSizeManager(int width, int height)
        : m_width(width), m_height(height) {}

    /** 
    *창 크기 고정을 처리하는 함수
    */ 
    void HandleMinMaxInfo(LPARAM lParam) const
    {
        MINMAXINFO* minMaxInfo = reinterpret_cast<MINMAXINFO*>(lParam);
        minMaxInfo->ptMinTrackSize.x = m_width;
        minMaxInfo->ptMinTrackSize.y = m_height;
    }
    /**
    * @m_width 창의 넓이
    * @m_height 창의 높이
    */

private:
    int m_width;  
    int m_height; 
};