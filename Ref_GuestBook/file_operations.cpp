#include "file_operations.h"

bool File_Manager::SaveFile(HWND hWnd, SPINFO penInfo) {

    // OPENFILENAME ����ü ����
    OFN.lStructSize = sizeof(OPENFILENAME);
    OFN.hwndOwner = hWnd;
    OFN.lpstrFilter = L"��� ����(*.*)\0*.*\0";
    OFN.lpstrFile = fileName;
    OFN.nMaxFile = sizeof(fileName) / sizeof(fileName[0]);

    if (GetSaveFileName(&OFN) != 0) {
        wsprintf(str, L"%s", OFN.lpstrFile);
        if (fileOps.save(penInfo, str)) {                       /// FileOperations�� save �޼��� ȣ��
            return true;
        }
        else {
            MessageBox(hWnd, L"����", L"���� ���� ����", MB_OK);
            return false;
        }
    }
    return false;
}

bool File_Manager::LoadFile(HWND hWnd, SPINFO penInfo) {

    // OPENFILENAME ����ü ����
    OFN.lStructSize = sizeof(OPENFILENAME);
    OFN.hwndOwner = hWnd;
    OFN.lpstrFilter = L"��� ����(*.*)\0*.*\0";
    OFN.lpstrFile = fileOpenName;
    OFN.nMaxFile = sizeof(fileOpenName) / sizeof(fileOpenName[0]);

    if (GetOpenFileName(&OFN) != 0) {
        wsprintf(str, L"%s", OFN.lpstrFile);
        if (fileOps.load(penInfo, str)) {                       /// FileOperations�� load �޼��� ȣ��
            return true;
        }
        else {
            MessageBox(hWnd, L"����", L"���� ���� ����", MB_OK);
            return false;
        }
    }
    return false;
}