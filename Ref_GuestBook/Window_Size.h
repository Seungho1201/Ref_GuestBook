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
    /** 
    *������: �������� ���̿� ���̸� �ʱ�ȭ
    */ 
    WindowSizeManager(int width, int height)
        : m_width(width), m_height(height) {}

    /** 
    *â ũ�� ������ ó���ϴ� �Լ�
    */ 
    void HandleMinMaxInfo(LPARAM lParam) const
    {
        MINMAXINFO* minMaxInfo = reinterpret_cast<MINMAXINFO*>(lParam);
        minMaxInfo->ptMinTrackSize.x = m_width;
        minMaxInfo->ptMinTrackSize.y = m_height;
    }
    /**
    * @m_width â�� ����
    * @m_height â�� ����
    */

private:
    int m_width;  
    int m_height; 
};