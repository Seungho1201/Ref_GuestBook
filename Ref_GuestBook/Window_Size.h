#pragma once
/**
* @Window_Size_Width ������ ����
* @Window_Size_Height ������ ����
*/
#define Window_Size_Width 1450  
#define Window_Size_Height 900  
/**
* @WM_GETMINMAXINFO â�� ũ�� ���� �޼���
*/
class WindowSizeManager
{
public:
    
    //������: �������� ���̿� ���̸� �ʱ�ȭ
    
    WindowSizeManager(int width, int height)
        : m_width(width), m_height(height) {}

   
    //â ũ�� ������ ó���ϴ� �Լ�
   
    void HandleMinMaxInfo(LPARAM lParam) const
    {   
        //�ּ� ũ�� ����
        MINMAXINFO* minMaxInfo = reinterpret_cast<MINMAXINFO*>(lParam);
        minMaxInfo->ptMinTrackSize.x = m_width;
        minMaxInfo->ptMinTrackSize.y = m_height;

        
        //�ִ� ũ�� ����
         

        minMaxInfo->ptMaxTrackSize.x = m_width;
        minMaxInfo->ptMaxTrackSize.y = m_height;

        
        //�ִ�ȭ �Ҷ� ũ�� ����
        
        minMaxInfo->ptMaxSize.x = m_width;
        minMaxInfo->ptMaxSize.y = m_height;
    }

    /**
    * @m_width â�� ����
    * @m_height â�� ����
    */

public:
    int m_width;  
    int m_height; 

   void HandleWMSize(HWND hWnd, WPARAM wParam) const
{
    if (wParam == SIZE_MAXIMIZED)
    {
        // â�� �ִ�ȭ�� ��, ũ��� �ڵ����� �����ϰ� ��ġ�� ����
        RECT rect;
        GetWindowRect(hWnd, &rect);

        // SetWindowPos�� ȣ���ϵ�, SWP_NOMOVE �÷��׸� ����Ͽ� ��ġ�� �����ϵ��� ��.
        SetWindowPos(hWnd, NULL, rect.left, rect.top, m_width, m_height, SWP_NOMOVE | SWP_NOZORDER);
    }
}


    
};