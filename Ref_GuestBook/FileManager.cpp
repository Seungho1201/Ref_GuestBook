#include "FileManager.h"

/// 파일 저장 또는 로드를 처리하는 함수
bool File_Manager::HandleFileOperation(HWND hWnd, std::vector<Pen_Info>* penMemory, bool isSave) {
    DWORD flags = isSave ? (OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT) : (OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST);
    WCHAR* filePath = isSave ? fileName : fileOpenName;
    const wchar_t* operation = isSave ? L"저장" : L"열기";

    /// 파일 대화상자를 설정하고 경로가 유효하면 처리
    if (ConfigureDialog(hWnd, flags, filePath, sizeof(fileName))) {
        wsprintf(str, L"%s", OFN.lpstrFile);
        bool result = isSave ? save(str, penMemory) : load(str, penMemory, hWnd);

        if (result) {
            if (isSave) {  /// 저장시 경로 표시
                WCHAR successMessage[512];
                wsprintf(successMessage, L"파일이 성공적으로 %s되었습니다.\n경로: %s", operation, str);
                MessageBox(hWnd, successMessage, L"파일 성공", MB_OK); /// 성공 메시지 표시
            }
        }
        else {
            MessageBox(hWnd, L"파일 작업 실패", L"실패", MB_OK); /// 실패 메시지 표시
        }
        return result;
    }
    return false; /// 대화상자 실패
}

/// 파일 모드를 선택하여 저장 또는 로드 작업을 수행하는 함수
void File_Manager::selectFileMode(int wmId, HWND g_Hwnd, std::vector<Pen_Info>* penMemory) {
    switch (wmId) {
    case SAVE:
        HandleFileOperation(g_Hwnd, penMemory, true); /// 저장
        break;
    case LOAD:
        HandleFileOperation(g_Hwnd, penMemory, false); /// 로드
        break;
    }
}

/// 파일을 저장하는 함수
bool File_Manager::save(const wchar_t* path, std::vector<Pen_Info>* penMemory) {
    if (penMemory->size() < 80 || !openForWrite(path)) {
        return false;
    }

    /// penMemory의 데이터를 파일에 기록
    for (const auto& i : *penMemory) {
        this->fs << i.penCoordinate << ' '
            << i.penWidth << ' '
            << i.penColor << ' '
            << i.penTime << ' '
            << i.penState << ' '
            << i.stampOn << ' '
            << i.stampImg << ' '
            << i.stampSize << '\n';
    }

    this->fs.close(); /// 파일을 닫음
    return true;
}

/// 파일을 로드하는 함수
bool File_Manager::load(const wchar_t* path, std::vector<Pen_Info>* penMemory, HWND g_Hwnd) {
    if (!openForRead(path)) {
        return false;
    }

    penMemory->clear();
    PEN_INFO pen_info;

    /// 파일에서 데이터를 읽어와 penMemory에 추가
    while (this->fs >> pen_info.penCoordinate
        >> pen_info.penWidth
        >> pen_info.penColor
        >> pen_info.penTime
        >> pen_info.penState
        >> pen_info.stampOn
        >> pen_info.stampImg
        >> pen_info.stampSize) {
        penMemory->push_back(pen_info);
    }

    this->fs.close(); /// 파일을 닫음

    /// 화면 갱신을 위해 무효화 영역 설정
    RECT paintAreaLoad = { PAINT_R_LEFT, PAINT_R_TOP, PAINT_R_RIGHT, PAINT_R_BOTTOM };
    InvalidateRect(g_Hwnd, &paintAreaLoad, TRUE); /// 화면 갱신
    return true;
}

/// 파일 대화상자를 설정하는 함수
bool File_Manager::ConfigureDialog(HWND hWnd, DWORD flags, WCHAR* fileBuffer, DWORD bufferSize) {
    OFN.lStructSize = sizeof(OPENFILENAME);
    OFN.hwndOwner = hWnd;
    OFN.lpstrFilter = L"모든 파일(*.*)\0*.*\0";
    OFN.lpstrFile = fileBuffer;
    OFN.nMaxFile = bufferSize / sizeof(fileBuffer[0]);
    OFN.Flags = flags;

    /// 저장 또는 열기 대화상자를 실행
    return (flags & OFN_OVERWRITEPROMPT ? GetSaveFileName(&OFN) : GetOpenFileName(&OFN)) != 0;
}

/// 파일을 쓰기 모드로 여는 함수
bool File_Manager::openForWrite(const wchar_t* path) {
    fs.open(path, std::ios::out | std::ios::trunc);
    return !fs.fail();
}

/// 파일을 읽기 모드로 여는 함수
bool File_Manager::openForRead(const wchar_t* path) {
    fs.open(path, std::ios::in);
    return !fs.fail();
}
