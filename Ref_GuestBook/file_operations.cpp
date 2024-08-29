#include <windows.h>
#include <commdlg.h>

#include "file_operations.h"
#include "Pen_Str.h"  
#include "file_io.h"

bool SaveFile(HWND hWnd, SPINFO penInfo) {
    OPENFILENAME OFN = { 0 };
    WCHAR fileName[256] = { 0 };
    WCHAR str[256] = { 0 };

    OFN.lStructSize = sizeof(OPENFILENAME);
    OFN.hwndOwner = hWnd;
    OFN.lpstrFilter = L"��� ����(*.*)\0*.*\0";
    OFN.lpstrFile = fileName;
    OFN.nMaxFile = sizeof(fileName) / sizeof(fileName[0]);

    if (GetSaveFileName(&OFN) != 0) {
        wsprintf(str, L"%s", OFN.lpstrFile);
        if (file_save(penInfo, str)) {
            MessageBox(hWnd, str, L"���� ���� ����", MB_OK);
            return true;
        }
        else {
            MessageBox(hWnd, L"����", L"���� ���� ����", MB_OK);
            return false;
        }
    }
    return false;
}

bool LoadFile(HWND hWnd, SPINFO penInfo) {
    OPENFILENAME OFN = { 0 };
    WCHAR fileOpenName[256] = { 0 };
    WCHAR str[256] = { 0 };

    OFN.lStructSize = sizeof(OPENFILENAME);
    OFN.hwndOwner = hWnd;
    OFN.lpstrFilter = L"��� ����(*.*)\0*.*\0";
    OFN.lpstrFile = fileOpenName;
    OFN.nMaxFile = sizeof(fileOpenName) / sizeof(fileOpenName[0]);

    if (GetOpenFileName(&OFN) != 0) {
        wsprintf(str, L"%s", OFN.lpstrFile);
        if (file_load(penInfo, str)) {
            return true;
        }
        else {
            MessageBox(hWnd, L"����", L"���� ���� ����", MB_OK);
            return false;
        }
    }
    return false;
}
