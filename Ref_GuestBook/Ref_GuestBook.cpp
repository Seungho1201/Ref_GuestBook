/// Ref_GuestBook.cpp : 애플리케이션에 대한 진입점을 정의합니다.

#include "framework.h"
#include "Ref_GuestBook.h"

#define MAX_LOADSTRING 100

/// 전역 변수:
HINSTANCE hInst;                                /// 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  /// 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            /// 기본 창 클래스 이름입니다.

/// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow){
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    /// TODO: 여기에 코드를 입력합니다.

    /// 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_REFGUESTBOOK, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    /// 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_REFGUESTBOOK));

    MSG msg;

    /// 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return (int)msg.wParam;
}

///  함수: MyRegisterClass()
///  용도: 창 클래스를 등록합니다.
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_REFGUESTBOOK));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_REFGUESTBOOK);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

///   함수: InitInstance(HINSTANCE, int)
///   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
///   주석:
///        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
///        주 프로그램 창을 만든 다음 표시합니다.

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

///  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
///  용도: 주 창의 메시지를 처리합니다.

///  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
///  WM_PAINT    - 주 창을 그립니다.
///  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.

/// 전역변수 정의
std::vector<PEN_INFO> penMemory;        /// 펜 구조체 정보 저장 벡터 변수 전역변수 정의
PEN_INFO g_Pen_Info;                    /// 펜 정보 구조체 전역변수 정의
COLORREF pen_Color = RGB(0, 0, 0);      /// 펜 기본 색상 BLACK, RGB(0, 0, 0)
ColorPalette g_colorPalette;

extern int preview_Icon = 132;

///  윈도우 핸들 전역변수
HWND g_Hwnd;                            /// HWND 전역변수 정의
PenDraw drawInstance;                   /// 그리기 관련 클래스 인스턴스 선언
/// 펜 색상 관련 클래스 인스턴스 선언
PaintAreaSquare paintSquare;            /// 그리기 영역 사각형 인스턴스 선언
PenWidthControl penWidthControl;        /// 펜 굵기 조절 관련 인스턴스 선언
File_Manager fileManager;               /// File_Manager 클래스의 인스턴스 선언
Eraser eraser;                          /// Eraser 클래스의 인스턴스 선언
ShowStatus statusInstance;              /// 스테이터스 관련 인스턴스 선언

int pen_Width = 10;                     /// 펜 기본 굵기 10으로 정의

int stamp_Size = 200;                   /// 스탬프 크기 가로, 세로 80으로 정의
int stampIcon = 140;                    /// 스탬프 아이콘 초기값
bool stampActive = false;               /// 스탬프 버튼 활성화 확인
static Stamp* stampInfo = nullptr;      /// Stamp 객체를 저장할 포인터

/// 버튼 변경 버튼
int bt_X = 625;
int bt_Y = 10;
int bt_Size = 45;
int bt_Side = 5;
int bt_Array = bt_Size + bt_Side;


/// 기능 기본 버튼
MakeButton bt_Clear(120, 10, 100, 100, ERASE, L"ERASE");
MakeButton bt_Replay(10, 10, 100, 100, REPLAY, L"REPLAY");
MakeButton bt_SAVE(230, 10, 100, 45, SAVE, L"SAVE");
MakeButton bt_Load(230, 65, 100, 45, LOAD, L"LOAD");
MakeButton bt_Widthup(375, 10, 45, 45, W_DOWN, L"-");
MakeButton bt_Widthdown(470, 10, 45, 45, W_UP, L"+");


MakeButton bt_Change_Pen(375, 60, 140, 45, CHANGE_PEN, L"PEN");

/// 펜 미리보기
MakeButton bt_Preview(525, 10, 95, 95, PREVIEW, L"미리보기");

/// 사용자 지정 색 버튼
MakeButton bt_ColorPalette(bt_X, 10, bt_Size, bt_Size + bt_Array, PALETTE, L"PALETTE");

MakeButton bt_ColorRed(bt_X + bt_Array, bt_Y, bt_Size, bt_Size, C_RED, L"빨");
MakeButton bt_ColorOrange(bt_X + bt_Array * 2, bt_Y, bt_Size, bt_Size, C_ORANGE, L"주");
MakeButton bt_ColorYellow(bt_X + bt_Array * 3, bt_Y, bt_Size, bt_Size, C_YELLOW, L"노");
MakeButton bt_ColorGreen(bt_X + bt_Array * 4, bt_Y, bt_Size, bt_Size, C_GREEN, L"초");

MakeButton bt_ColorBlue(bt_X + bt_Array, bt_Y + bt_Size + bt_Side, bt_Size, bt_Size, C_BLUE, L"파");
MakeButton bt_ColorNavy(bt_X + bt_Array * 2, bt_Y + bt_Size + bt_Side, bt_Size, bt_Size, C_NAVY, L"남");
MakeButton bt_ColorPurple(bt_X + bt_Array * 3, bt_Y + bt_Size + bt_Side, bt_Size, bt_Size, C_PURPLE, L"보");
MakeButton bt_ColorBlack(bt_X + bt_Array * 4, bt_Y + bt_Size + bt_Side, bt_Size, bt_Size, C_BLACK, L"검");

/// 스탬프 변경 버튼
MakeButton bt_Heart_Stamp(bt_X + bt_Array * 5, bt_Y, bt_Size, bt_Size, HEART_STAMP, L"하트");
MakeButton bt_Uh_Stamp(bt_X + bt_Array * 6, bt_Y, bt_Size, bt_Size, UH_STAMP, L"어?");
MakeButton bt_Yuhan_Stamp(bt_X + bt_Array * 7, bt_Y, bt_Size, bt_Size, YUHAN_STAMP, L"유한대마크");
MakeButton bt_Yongbin_Stamp(bt_X + bt_Array * 8, bt_Y, bt_Size, bt_Size, YONGBIN_STAMP, L"김용빈");
MakeButton bt_what_Stamp(bt_X + bt_Array * 9, bt_Y, bt_Size, bt_Size, WHAT_STAMP, L"뭐어쩌라고");

MakeButton bt_Why_Stamp(bt_X + bt_Array * 5, bt_Y + bt_Size + bt_Side, bt_Size, bt_Size, WHY_STAMP, L"왜?");
MakeButton bt_Gu_Stamp(bt_X + bt_Array * 6, bt_Y + bt_Size + bt_Side, bt_Size, bt_Size, GU_STAMP, L"비둘기");
MakeButton bt_pf_Stamp(bt_X + bt_Array * 7, bt_Y + bt_Size + bt_Side, bt_Size, bt_Size, PF_STAMP, L"교수님");
MakeButton bt_f_Stamp(bt_X + bt_Array * 8, bt_Y + bt_Size + bt_Side, bt_Size, bt_Size, F_STAMP, L"내성적F");
MakeButton bt_hate_Stamp(bt_X + bt_Array * 9, bt_Y + bt_Size + bt_Side, bt_Size, bt_Size, HATE_STAMP, L"엉엉");



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    /// 윈도우 크기 고정 정적 변수로 선언
    static WindowSizeManager windowSizeManager(Window_Size_Width, Window_Size_Height);

    switch (message)
    {
    case WM_DRAWITEM:
    {
        LPDRAWITEMSTRUCT lpDrawItemStruct = (LPDRAWITEMSTRUCT)lParam;

        // 버튼 핸들 확인
        if (lpDrawItemStruct->CtlType == ODT_BUTTON)
        {
            HBRUSH hBrush = CreateSolidBrush(currentColor);  // 버튼의 배경색을 설정
            FillRect(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, hBrush);// 생성된 브러시로 버튼 영역을 채움

            DeleteObject(hBrush);
            return TRUE;
        }
    }
    break;

    case WM_GETMINMAXINFO:
        // 창 크기 고정을 위해 HandleMinMaxInfo 호출
        windowSizeManager.HandleMinMaxInfo(lParam);
        break;

    case WM_CREATE:
        g_Hwnd = hWnd;

        /// stamp 관련 객체 초기화
        stampInfo = new Stamp(NULL, NULL);

        /// 윈도우 창 생성시 버튼 생성 메서드 실행
        /// 인자 관련 설명은 button.cpp 파일 주석 참고
        /// 리플레이, 지우개 버튼 생성
        bt_Replay.mkButton(g_Hwnd, IDI_REPLAY_ICON);
        bt_Clear.mkButton(g_Hwnd, IDI_ERASE_ICON);

        /// 세이브 로드 버튼 생성
        bt_SAVE.mkButton(g_Hwnd);
        bt_Load.mkButton(g_Hwnd);

        /// 굵기 조절 버튼 생성
        bt_Widthup.mkButton(g_Hwnd);
        bt_Widthdown.mkButton(g_Hwnd);

        /// 펜 미리보기
        bt_Preview.mkButton(g_Hwnd, stampIcon);

        /// 색상 변경 버튼 생성
        bt_Change_Pen.mkButton(g_Hwnd);

        bt_ColorRed.mkButton(g_Hwnd, IDI_RED_ICON);
        bt_ColorOrange.mkButton(g_Hwnd, IDI_ORANGE_ICON);
        bt_ColorYellow.mkButton(g_Hwnd, IDI_YELLOW_ICON);
        bt_ColorGreen.mkButton(g_Hwnd, IDI_GREEN_ICON);
        bt_ColorBlue.mkButton(g_Hwnd, IDI_BLUE_ICON);
        bt_ColorNavy.mkButton(g_Hwnd, IDI_NAVY_ICON);
        bt_ColorPurple.mkButton(g_Hwnd, IDI_PURPLE_ICON);
        bt_ColorBlack.mkButton(g_Hwnd, IDI_BLACK_ICON);
        bt_ColorPalette.mkButton(g_Hwnd, currentColor);

        /// 스탬프 관련 버튼 생성
        bt_Heart_Stamp.mkButton(g_Hwnd, IDI_BT_HEART_ICON);
        bt_Uh_Stamp.mkButton(g_Hwnd, IDI_BT_UH_ICON);
        bt_Yuhan_Stamp.mkButton(g_Hwnd, IDI_BT_YUHAN_ICON);
        bt_Yongbin_Stamp.mkButton(g_Hwnd, IDI_BT_YONGBIN_ICON);
        bt_Why_Stamp.mkButton(g_Hwnd, IDI_BT_WHY_ICON);
        bt_Gu_Stamp.mkButton(g_Hwnd, IDI_BT_GU_ICON);
        bt_what_Stamp.mkButton(g_Hwnd, IDI_BT_WHAT_ICON);
        bt_pf_Stamp.mkButton(g_Hwnd, IDI_BT_PF_ICON);
        bt_f_Stamp.mkButton(g_Hwnd, IDI_BT_F_ICON);
        bt_hate_Stamp.mkButton(g_Hwnd, IDI_BT_HATE_ICON);


    /// 그리기 관련 분기
    case WM_MOUSEMOVE:
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
        /// 스탬프 버튼이 활성화 되어있을시 스탬프 기능 실행
        if (stampActive) {
            stampInfo = new Stamp(stamp_Size, stampIcon);
            stampInfo->handleStamp(hWnd, message, lParam, &penMemory);

        /// 버튼 비활성화시 그리기 함수 실행
        } else {
            drawInstance.drawLine(&pen_Width, g_Hwnd, message, lParam, &pen_Color, &penMemory);
        }
        break;

    /// 버튼으로 구현한 func 기능은 COMMAND 에서 정의한다.
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);

        /// 클릭된 버튼 하이라이트 설정
        MakeButton::getClickHighlight(wmId, g_Hwnd);
        /// 스테이터스 기능
        statusInstance.setStatus(wmId, g_Hwnd);

        /// 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        /// 지우기 기능
        case ERASE:
            eraser.erase(hWnd, &penMemory);
            break;

        /// 리플레이 기능 
        case REPLAY:
            drawInstance.replayThread(g_Hwnd, &penMemory);
            break;

        /// SAVE, LOAD 기능 
        case SAVE:
        case LOAD:
            fileManager.selectFileMode(wmId, g_Hwnd, &penMemory);
            break;

        /// 펜 굵기 관련 기능
        case W_DOWN:
        case W_UP:
            penWidthControl.widthControl(g_Hwnd, wmId, &pen_Width, &stamp_Size, &stampActive);           
            break;

        /// 펜 모드 (펜, 스탬프) 
        case CHANGE_PEN:
            stampInfo->changeModeToPen(g_Hwnd, &stampActive);
            break;

        ///펜 색상 및 미리보기 색 변경 기능
        case C_RED: 

        case C_ORANGE:
        case C_YELLOW:
        case C_GREEN:
        case C_BLUE:
        case C_NAVY:
        case C_PURPLE:
        case C_BLACK:
            g_colorPalette.Change_Color(wmId, &pen_Color);
            break;

         /// 사용자 지정 색
        case PALETTE:
            g_colorPalette.colorSelect(g_Hwnd, 0);
            pen_Color = g_colorPalette.getColor(0);
                currentColor = pen_Color;               // 현재 색상 업데이트
                break;

        /// 스탬프 관련 case 
        case HEART_STAMP:
        case UH_STAMP:
        case YUHAN_STAMP:
        case YONGBIN_STAMP:
        case WHY_STAMP:
        case GU_STAMP:
        case WHAT_STAMP:
        case PF_STAMP:
        case F_STAMP:
        case HATE_STAMP:
            stampInfo->changeModeToStamp(&stampActive, g_Hwnd, &stampIcon, wParam);
            InvalidateRect(g_Hwnd, NULL, TRUE);
            UpdateWindow(g_Hwnd);
            break;

        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        MakeButton::setClickHighlight(hdc);

        /// 펜 굵기 표시 메서드
        penWidthControl.penWidthDisplay(hdc, &stampActive, &stamp_Size, &pen_Width);

        /// 그리기 영역 사각형 그리기
        paintSquare.makeSquare(hdc);

        /// 현재 스테이터스 출력
        statusInstance.showDisplay(hdc, g_Hwnd);
        
        /// 그리기 한 벡터 데이터 그리기 유지 메서드
        drawInstance.drawStay(hdc, g_Hwnd, &penMemory);
       
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}
/// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

