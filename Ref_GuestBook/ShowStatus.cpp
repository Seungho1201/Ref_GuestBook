#include "ShowStatus.h"

ShowStatus::ShowStatus()
{
    this->status_Hdc = nullptr;

    // std::fill을 사용해 배열을 0으로 초기화
    std::fill(std::begin(this->modeStatus), std::end(this->modeStatus), 0);
    std::fill(std::begin(this->nowStatus), std::end(this->nowStatus), 0);
    wsprintf(nowStatus, L"펜 모드");
}


void ShowStatus::setStatus(int wmId, HWND g_Hwnd)
{
    switch (wmId)
    {
    case REPLAY:
        wsprintf(nowStatus, L"리플레이 모드");
        InvalidateRect(g_Hwnd, NULL, TRUE);
        break;

    case ERASE:
        wsprintf(nowStatus, L"지우개 모드");
        InvalidateRect(g_Hwnd, NULL, TRUE);
        break;

        /// SAVE, LOAD 기능 
    case SAVE:
        wsprintf(nowStatus, L"파일 저장");
        InvalidateRect(g_Hwnd, NULL, TRUE);
        break;

    case LOAD:
        wsprintf(nowStatus, L"파일 로드");
        InvalidateRect(g_Hwnd, NULL, TRUE);
        break;

        /// 펜 굵기 관련 기능
    case W_DOWN:
        wsprintf(nowStatus, L"사이즈 감소");
        InvalidateRect(g_Hwnd, NULL, TRUE);
        break;

    case W_UP:
        wsprintf(nowStatus, L"사이즈 증가");            /// 펜 굵기 조절
        InvalidateRect(g_Hwnd, NULL, TRUE);
        break;

        /// 스탬프 관련 case 
    case HEART_STAMP:
    case UH_STAMP:
    case YUHAN_STAMP:
    case YONGBIN_STAMP:
        wsprintf(nowStatus, L"사이즈 감소");
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
        wsprintf(nowStatus, L"색상 선택");
        InvalidateRect(g_Hwnd, NULL, TRUE);
        break;

    default:
        wsprintf(nowStatus, L"모드 추가해라");
        InvalidateRect(g_Hwnd, NULL, TRUE);
        break;
    }
}


void ShowStatus::showDisplay(HDC hdc, HWND g_Hwnd)
{
    this->status_Hdc = hdc;

    wsprintf(modeStatus, L"실행 모드 : ");
    TextOut(status_Hdc, 15, 845, modeStatus, lstrlen(modeStatus));

   
    TextOut(status_Hdc, 100, 845, nowStatus, lstrlen(nowStatus));
}