#include "FileManager.h"

void File_Manager::selectFileMode(int wmId, HWND g_Hwnd, vector<Pen_Info>* penMemory)
{
    switch (wmId)
    {
    case SAVE:
        SaveFile(g_Hwnd, penMemory);                                /// 파일 저장 함수 호출
        break;
    case LOAD:
        LoadFile(g_Hwnd, penMemory);                                /// 파일 로드 함수 호출
        break;
    }
}


bool File_Manager::SaveFile(HWND hWnd, vector<Pen_Info>* penMemory)
{
    /// 파일 저장 대화상자 설정 후 경로가 유효하면 저장
    if (ConfigureDialog(hWnd, OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT, fileName, sizeof(fileName))) {
        wsprintf(str, L"%s", OFN.lpstrFile);
        if (save(str, penMemory)) {            /// FileOperations의 save 메서드 호출
            WCHAR successMessage[512];
            wsprintf(successMessage, L"파일이 성공적으로 저장되었습니다.\n경로: %s", str);
            MessageBox(hWnd, successMessage, L"파일 저장 성공", MB_OK);     /// 성공 메시지 박스 표시
            return true;        /// 저장 성공
        }
        else {
            MessageBox(hWnd, L"파일 저장 실패", L"실패", MB_OK);            /// 실패 메시지 박스 표시
            return false;       /// 저장 실패
        }
    }
    return false;           /// 대화상자 설정 실패
}

bool File_Manager::LoadFile(HWND hWnd, vector<Pen_Info>* penMemory)
{
    /// 파일 열기 대화상자 설정 후 경로가 유효하면 저장
    if (ConfigureDialog(hWnd, OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST, fileOpenName, sizeof(fileOpenName))) {
        wsprintf(str, L"%s", OFN.lpstrFile);        /// 선택한 파일 경로를 str에 저장
        if (load(str, penMemory, hWnd)) {           /// FileOperations의 load 메서드 호출
            return true;            /// 로드 성공
        }
        else {
            MessageBox(hWnd, L"파일 열기 실패", L"실패", MB_OK);            /// 실패 메시지 박스 표시
            return false;           /// 로드 실패
        }
    }
    return false;           /// 대화상자 설정 실패
}

bool File_Manager::ConfigureDialog(HWND hWnd, DWORD flags, WCHAR* fileBuffer, DWORD bufferSize) 
{
    /// OPENFILENAME 구조체 설정
    OFN.lStructSize = sizeof(OPENFILENAME);
    OFN.hwndOwner = hWnd;
    OFN.lpstrFilter = L"모든 파일(*.*)\0*.*\0";
    OFN.lpstrFile = fileBuffer;
    OFN.nMaxFile = bufferSize / sizeof(fileBuffer[0]);
    OFN.Flags = flags;

    /// 대화상자 표시 및 사용자 작업 처리
    return (flags & OFN_OVERWRITEPROMPT ? GetSaveFileName(&OFN) : GetOpenFileName(&OFN)) != 0;
}
