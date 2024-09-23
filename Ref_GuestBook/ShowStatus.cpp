#include "ShowStatus.h"

ShowStatus::ShowStatus()
{
    this->status_Hdc = nullptr;

    /// std::fill�� ����� �迭�� 0���� �ʱ�ȭ
    std::fill(std::begin(this->modeStatus), std::end(this->modeStatus), 0);

    /// �⺻ ���´� "�� ���"�� ����
    wsprintf(nowStatus, L"�� ���");
}

WCHAR ShowStatus::nowStatus[30] = {};
WCHAR ShowStatus::playingStatus[30] = {};
RECT ShowStatus::status_Rect = { 50, 830, 1500, 900 };

void ShowStatus::setStatus(int wmId, HWND g_Hwnd)
{
    switch (wmId)
    {
    case REPLAY:
        //wsprintf(ShowStatus::playingStatus, L"");
        wsprintf(ShowStatus::nowStatus, L"���÷��� ���");
        InvalidateRect(g_Hwnd, &ShowStatus::status_Rect, TRUE);
        break;

    case ERASE:
        wsprintf(ShowStatus::nowStatus, L"���찳 ���");
        InvalidateRect(g_Hwnd, &ShowStatus::status_Rect, TRUE);
        break;

        /// SAVE, LOAD ��� 
    case SAVE:
        wsprintf(ShowStatus::nowStatus, L"���� ����");
        InvalidateRect(g_Hwnd, &ShowStatus::status_Rect, TRUE);
        break;

    case LOAD:
        wsprintf(ShowStatus::nowStatus, L"���� �ε�");
        InvalidateRect(g_Hwnd, &ShowStatus::status_Rect, TRUE);
        break;

        /// �� ���� ���� ���
    case W_DOWN:
        wsprintf(ShowStatus::nowStatus, L"������ ����");
        InvalidateRect(g_Hwnd, &ShowStatus::status_Rect, TRUE);
        break;

    case W_UP:
        wsprintf(ShowStatus::nowStatus, L"������ ����");           
        InvalidateRect(g_Hwnd, &ShowStatus::status_Rect, TRUE);
        break;

    case CHANGE_PEN:
        wsprintf(ShowStatus::nowStatus, L"�� ���");          
        InvalidateRect(g_Hwnd, &ShowStatus::status_Rect, TRUE);
        break;
        
    case HEART_STAMP:
    case UH_STAMP:
    case YUHAN_STAMP:;
    case YONGBIN_STAMP:
        wsprintf(ShowStatus::nowStatus, L"������ ���");
        InvalidateRect(g_Hwnd, &ShowStatus::status_Rect, TRUE);
        break;


    case C_RED:
    case C_ORANGE:
    case C_YELLOW:
    case C_GREEN:
    case C_BLUE:
    case C_NAVY:
    case C_PURPLE:
    case C_BLACK:
        wsprintf(ShowStatus::nowStatus, L"���� ����");
        InvalidateRect(g_Hwnd, &ShowStatus::status_Rect, TRUE);
        break;

    default:
        wsprintf(ShowStatus::nowStatus, L"��� �߰��ض�");
        InvalidateRect(g_Hwnd, &ShowStatus::status_Rect, TRUE);
        break;
    }
}


void ShowStatus::showDisplay(HDC hdc, HWND g_Hwnd)
{
    this->status_Hdc = hdc;

    wsprintf(modeStatus, L"���� ��� : ");
    TextOut(status_Hdc, 15, 845, modeStatus, lstrlen(modeStatus));

   
    TextOut(status_Hdc, 100, 845, nowStatus, lstrlen(nowStatus));

    /// ������ ���� �� ��� �ؽ�Ʈ�� ���� �۾�
    SetTextColor(hdc, RGB(255, 0, 0));
    TextOut(status_Hdc, 660, 845, playingStatus, lstrlen(playingStatus));
}