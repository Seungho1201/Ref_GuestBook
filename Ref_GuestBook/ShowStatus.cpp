#include "ShowStatus.h"

ShowStatus::ShowStatus()
{
    this->status_Hdc = nullptr;

    /// std::fill을 사용해 배열을 0으로 초기화
    std::fill(std::begin(this->modeStatus), std::end(this->modeStatus), 0);

    /// 기본 상태는 "펜 모드"로 지정
    wsprintf(nowStatus, L"펜 모드");
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
        wsprintf(ShowStatus::nowStatus, L"리플레이 모드");
        InvalidateRect(g_Hwnd, &ShowStatus::status_Rect, TRUE);
        break;

    case ERASE:
        wsprintf(ShowStatus::nowStatus, L"지우개 모드");
        InvalidateRect(g_Hwnd, &ShowStatus::status_Rect, TRUE);
        break;

        /// SAVE, LOAD 기능 
    case SAVE:
        wsprintf(ShowStatus::nowStatus, L"파일 저장");
        InvalidateRect(g_Hwnd, &ShowStatus::status_Rect, TRUE);
        break;

    case LOAD:
        wsprintf(ShowStatus::nowStatus, L"파일 로드");
        InvalidateRect(g_Hwnd, &ShowStatus::status_Rect, TRUE);
        break;

        /// 펜 굵기 관련 기능
    case W_DOWN:
        wsprintf(ShowStatus::nowStatus, L"사이즈 감소");
        InvalidateRect(g_Hwnd, &ShowStatus::status_Rect, TRUE);
        break;

    case W_UP:
        wsprintf(ShowStatus::nowStatus, L"사이즈 증가");           
        InvalidateRect(g_Hwnd, &ShowStatus::status_Rect, TRUE);
        break;

    case CHANGE_PEN:
        wsprintf(ShowStatus::nowStatus, L"펜 모드");          
        InvalidateRect(g_Hwnd, &ShowStatus::status_Rect, TRUE);
        break;
        
    case HEART_STAMP:
        wsprintf(ShowStatus::nowStatus, L"스탬프 모드 [하트]");
        InvalidateRect(g_Hwnd, &ShowStatus::status_Rect, TRUE);
        break;
    case UH_STAMP:
        wsprintf(ShowStatus::nowStatus, L"스탬프 모드 [어?]");
        InvalidateRect(g_Hwnd, &ShowStatus::status_Rect, TRUE);
        break;
    case YUHAN_STAMP:
        wsprintf(ShowStatus::nowStatus, L"스탬프 모드 [유한 마크]");
        InvalidateRect(g_Hwnd, &ShowStatus::status_Rect, TRUE);
        break;
    case YONGBIN_STAMP:
        wsprintf(ShowStatus::nowStatus, L"스탬프 모드 [김용반]");
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
        wsprintf(ShowStatus::nowStatus, L"색상 선택");
        InvalidateRect(g_Hwnd, &ShowStatus::status_Rect, TRUE);
        break;

    default:
        wsprintf(ShowStatus::nowStatus, L"모드 추가해라");
        InvalidateRect(g_Hwnd, &ShowStatus::status_Rect, TRUE);
        break;
    }
}


void ShowStatus::showDisplay(HDC hdc, HWND g_Hwnd)
{
    this->status_Hdc = hdc;

    wsprintf(modeStatus, L"실행 모드 : ");
    TextOut(status_Hdc, 15, 845, modeStatus, lstrlen(modeStatus));

   
    TextOut(status_Hdc, 100, 845, nowStatus, lstrlen(nowStatus));

    /// 스레드 실행 중 출력 텍스트는 빨간 글씨
    SetTextColor(hdc, RGB(255, 0, 0));
    TextOut(status_Hdc, 660, 845, playingStatus, lstrlen(playingStatus));
}