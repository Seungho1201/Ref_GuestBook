#include "file_operations.h"

bool File_Manager::SaveFile(HWND hWnd) {
    if (ConfigureDialog(hWnd, OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT, fileName, sizeof(fileName))) {
        wsprintf(str, L"%s", OFN.lpstrFile);
        if (fileOps.save(str)) {            /// FileOperations의 save 메서드 호출
            WCHAR successMessage[512];
            wsprintf(successMessage, L"파일이 성공적으로 저장되었습니다.\n경로: %s", str);
            MessageBox(hWnd, successMessage, L"파일 저장 성공", MB_OK);
            return true;
        }
        else {
            MessageBox(hWnd, L"파일 저장 실패", L"실패", MB_OK);
            return false;
        }
    }
    return false;
}

bool File_Manager::LoadFile(HWND hWnd) {
    if (ConfigureDialog(hWnd, OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST, fileOpenName, sizeof(fileOpenName))) {
        wsprintf(str, L"%s", OFN.lpstrFile);
        if (fileOps.load(str)) {            /// FileOperations의 load 메서드 호출
            return true;
        }
        else {
            MessageBox(hWnd, L"파일 열기 실패", L"실패", MB_OK);
            return false;
        }
    }
    return false;
}

bool File_Manager::ConfigureDialog(HWND hWnd, DWORD flags, WCHAR* fileBuffer, DWORD bufferSize) {

    /// OPENFILENAME 구조체 설정
    OFN.lStructSize = sizeof(OPENFILENAME);
    OFN.hwndOwner = hWnd;
    OFN.lpstrFilter = L"모든 파일(*.*)\0*.*\0";
    OFN.lpstrFile = fileBuffer;
    OFN.nMaxFile = bufferSize / sizeof(fileBuffer[0]);
    OFN.Flags = flags;

    return (flags & OFN_OVERWRITEPROMPT ? GetSaveFileName(&OFN) : GetOpenFileName(&OFN)) != 0;
}
