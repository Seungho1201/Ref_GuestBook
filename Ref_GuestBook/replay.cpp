#include "replay.h"

DrawReplay::DrawReplay() {
    this->penMemory = nullptr;
    this->g_Hwnd = nullptr;
    this->paintArea = { PAINT_R_LEFT, PAINT_R_TOP, PAINT_R_RIGHT, PAINT_R_BOTTOM };
    this->myP = nullptr;
    this->osP = nullptr;
    this->hdc = nullptr;
    this->x = 0;
    this->y = 0;
}

// 스레드 시작
void DrawReplay::replayThread(HWND g_Hwnd, vector<Pen_Info>* penMemory)
{
    this->g_Hwnd = g_Hwnd;
    this->penMemory = penMemory;

    // this 포인터를 전달하여 스레드에서 해당 객체의 멤버 함수 호출
    CreateThread(NULL, 0, ThreadFunc, (LPVOID)this, 0, NULL);
}

// 스레드에서 실행될 정적 함수
DWORD WINAPI DrawReplay::ThreadFunc(LPVOID lpParam) 
{
    DrawReplay* pThis = (DrawReplay*)lpParam;
    return pThis->drawReplay();
}

// 실제 작업을 수행
DWORD DrawReplay::drawReplay()
{
    hdc = GetDC(this->g_Hwnd);

    // 요청이 바로 처리되지 않고 메세지 큐에 저장 즉 모든 작업이 끝난 후 실행
    InvalidateRect(this->g_Hwnd, &paintArea, TRUE);

    // 즉시 업데이트 요청을 보내어 모든 작업이 끝나고 실행되는 InvalidateRect 함수를 즉시 호출
    UpdateWindow(this->g_Hwnd);

    // 벡터 변수 penMemory를 반복
    for (size_t i = 0; i < penMemory->size(); i++) {
        myP = CreatePen(PS_SOLID, (*penMemory)[i].penWidth, (*penMemory)[i].penColor);
        osP = (HPEN)SelectObject(hdc, myP);

        switch ((*penMemory)[i].penState) {
        case WM_LBUTTONDOWN:
            x = LOWORD((*penMemory)[i].penCoordinate);
            y = HIWORD((*penMemory)[i].penCoordinate);

            if ((*penMemory)[i].stampOn == true) {
                int stampX = x;
                int stampY = y;
                int stampIcon = (*penMemory)[i].stampImg;
                int stampWidth = (*penMemory)[i].stampSize;   // 원하는 아이콘 너비
                int stampHeight = (*penMemory)[i].stampSize;  // 원하는 아이콘 높이


                HICON hIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(stampIcon), IMAGE_ICON, stampWidth, stampHeight, 0);
                DrawIconEx(hdc, stampX - stampWidth / 2, stampY - stampHeight / 2, hIcon, stampWidth, stampHeight, 0, NULL, DI_NORMAL);
                Sleep(100);
                break;
            }

            MoveToEx(hdc, x, y, NULL);
            LineTo(hdc, x, y);  // 점찍기
            break;

        case WM_MOUSEMOVE:
            LineTo(hdc, LOWORD((*penMemory)[i].penCoordinate), HIWORD((*penMemory)[i].penCoordinate));
            break;

        case WM_LBUTTONUP:
            LineTo(hdc, LOWORD((*penMemory)[i].penCoordinate), HIWORD((*penMemory)[i].penCoordinate));
            break;

        default:
            break;
        }

        // 벡터 변수 반복 중단점
        if (i + 1 < penMemory->size() && (*penMemory)[i + 1].penState == WM_MOUSEMOVE) {
            Sleep((*penMemory)[i + 1].penTime - (*penMemory)[i].penTime);
        }

        SelectObject(hdc, osP);
        DeleteObject(myP);  // 리소스 자원 확보 위해 삭제
    }

    ReleaseDC(this->g_Hwnd, hdc);
    return 0;
}
