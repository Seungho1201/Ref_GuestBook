#include "file_operations.h"

bool File_Manager::SaveFile(HWND hWnd, SPINFO penInfo) {

    // OPENFILENAME 구조체 설정
    OFN.lStructSize = sizeof(OPENFILENAME);
    OFN.hwndOwner = hWnd;
    OFN.lpstrFilter = L"모든 파일(*.*)\0*.*\0";
    OFN.lpstrFile = fileName;
    OFN.nMaxFile = sizeof(fileName) / sizeof(fileName[0]);

    if (GetSaveFileName(&OFN) != 0) {
        wsprintf(str, L"%s", OFN.lpstrFile);
        if (fileOps.save(penInfo, str)) {                       /// FileOperations의 save 메서드 호출
            return true;
        }
        else {
            MessageBox(hWnd, L"실패", L"파일 저장 실패", MB_OK);
            return false;
        }
    }
    return false;
}

bool File_Manager::LoadFile(HWND hWnd, SPINFO penInfo) {

    // OPENFILENAME 구조체 설정
    OFN.lStructSize = sizeof(OPENFILENAME);
    OFN.hwndOwner = hWnd;
    OFN.lpstrFilter = L"모든 파일(*.*)\0*.*\0";
    OFN.lpstrFile = fileOpenName;
    OFN.nMaxFile = sizeof(fileOpenName) / sizeof(fileOpenName[0]);

    if (GetOpenFileName(&OFN) != 0) {
        wsprintf(str, L"%s", OFN.lpstrFile);
        if (fileOps.load(penInfo, str)) {                       /// FileOperations의 load 메서드 호출
            return true;
        }
        else {
            MessageBox(hWnd, L"실패", L"파일 열기 실패", MB_OK);
            return false;
        }
    }
    return false;
}