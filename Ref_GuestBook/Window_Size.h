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
    
    //생성자: 윈도우의 넓이와 높이를 초기화
    
    WindowSizeManager(int width, int height)
        : m_width(width), m_height(height) {}

   
    //창 크기 고정을 처리하는 함수
   
    void HandleMinMaxInfo(LPARAM lParam) const
    {   
        //최소 크기 설정
        MINMAXINFO* minMaxInfo = reinterpret_cast<MINMAXINFO*>(lParam);
        minMaxInfo->ptMinTrackSize.x = m_width;
        minMaxInfo->ptMinTrackSize.y = m_height;

        
        //최대 크기 설정
         

        minMaxInfo->ptMaxTrackSize.x = m_width;
        minMaxInfo->ptMaxTrackSize.y = m_height;

        
        //최대화 할때 크기 설정
        
        minMaxInfo->ptMaxSize.x = m_width;
        minMaxInfo->ptMaxSize.y = m_height;
    }

    /**
    * @m_width 창의 넓이
    * @m_height 창의 높이
    */

public:
    int m_width;  
    int m_height; 

   void HandleWMSize(HWND hWnd, WPARAM wParam) const
{
    if (wParam == SIZE_MAXIMIZED)
    {
        // 창이 최대화될 때, 크기는 자동으로 조정하고 위치는 유지
        RECT rect;
        GetWindowRect(hWnd, &rect);

        // SetWindowPos를 호출하되, SWP_NOMOVE 플래그를 사용하여 위치를 고정하도록 함.
        SetWindowPos(hWnd, NULL, rect.left, rect.top, m_width, m_height, SWP_NOMOVE | SWP_NOZORDER);
    }
}


    
};