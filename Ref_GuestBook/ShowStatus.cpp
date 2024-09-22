#include "ShowStatus.h"

ShowStatus::ShowStatus()
{
    this->status_Hdc = nullptr;

    // std::fill�� ����� �迭�� 0���� �ʱ�ȭ
    std::fill(std::begin(this->modeStatus), std::end(this->modeStatus), 0);
    std::fill(std::begin(this->nowStatus), std::end(this->nowStatus), 0);
    wsprintf(nowStatus, L"�� ���");
}


void ShowStatus::setStatus(int wmId, HWND g_Hwnd)
{
    switch (wmId)
    {
    case REPLAY:
        wsprintf(nowStatus, L"���÷��� ���");
        InvalidateRect(g_Hwnd, NULL, TRUE);
        break;

    case ERASE:
        wsprintf(nowStatus, L"���찳 ���");
        InvalidateRect(g_Hwnd, NULL, TRUE);
        break;

        /// SAVE, LOAD ��� 
    case SAVE:
        wsprintf(nowStatus, L"���� ����");
        InvalidateRect(g_Hwnd, NULL, TRUE);
        break;

    case LOAD:
        wsprintf(nowStatus, L"���� �ε�");
        InvalidateRect(g_Hwnd, NULL, TRUE);
        break;

        /// �� ���� ���� ���
    case W_DOWN:
        wsprintf(nowStatus, L"������ ����");
        InvalidateRect(g_Hwnd, NULL, TRUE);
        break;

    case W_UP:
        wsprintf(nowStatus, L"������ ����");            /// �� ���� ����
        InvalidateRect(g_Hwnd, NULL, TRUE);
        break;

        /// ������ ���� case 
    case HEART_STAMP:
    case UH_STAMP:
    case YUHAN_STAMP:
    case YONGBIN_STAMP:
        wsprintf(nowStatus, L"������ ����");
        InvalidateRect(g_Hwnd, NULL, TRUE);
        break;


    case C_RED:
    case C_ORANGE:
    case C_YELLOW:
    case C_GREEN:
    case C_BLUE:
    case C_NAVY:
    case C_PURPLE:
    case C_BLACK:
        wsprintf(nowStatus, L"���� ����");
        InvalidateRect(g_Hwnd, NULL, TRUE);
        break;

    default:
        wsprintf(nowStatus, L"��� �߰��ض�");
        InvalidateRect(g_Hwnd, NULL, TRUE);
        break;
    }
}


void ShowStatus::showDisplay(HDC hdc, HWND g_Hwnd)
{
    this->status_Hdc = hdc;

    wsprintf(modeStatus, L"���� ��� : ");
    TextOut(status_Hdc, 15, 845, modeStatus, lstrlen(modeStatus));

   
    TextOut(status_Hdc, 100, 845, nowStatus, lstrlen(nowStatus));
}