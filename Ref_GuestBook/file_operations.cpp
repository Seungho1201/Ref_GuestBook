#include "file_operations.h"

bool File_Manager::SaveFile(HWND hWnd) {
    if (ConfigureDialog(hWnd, OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT, fileName, sizeof(fileName))) {
        wsprintf(str, L"%s", OFN.lpstrFile);
        if (fileOps.save(str)) {            /// FileOperations�� save �޼��� ȣ��
            WCHAR successMessage[512];
            wsprintf(successMessage, L"������ ���������� ����Ǿ����ϴ�.\n���: %s", str);
            MessageBox(hWnd, successMessage, L"���� ���� ����", MB_OK);
            return true;
        }
        else {
            MessageBox(hWnd, L"���� ���� ����", L"����", MB_OK);
            return false;
        }
    }
    return false;
}

bool File_Manager::LoadFile(HWND hWnd) {
    if (ConfigureDialog(hWnd, OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST, fileOpenName, sizeof(fileOpenName))) {
        wsprintf(str, L"%s", OFN.lpstrFile);
        if (fileOps.load(str)) {            /// FileOperations�� load �޼��� ȣ��
            return true;
        }
        else {
            MessageBox(hWnd, L"���� ���� ����", L"����", MB_OK);
            return false;
        }
    }
    return false;
}

bool File_Manager::ConfigureDialog(HWND hWnd, DWORD flags, WCHAR* fileBuffer, DWORD bufferSize) {

    /// OPENFILENAME ����ü ����
    OFN.lStructSize = sizeof(OPENFILENAME);
    OFN.hwndOwner = hWnd;
    OFN.lpstrFilter = L"��� ����(*.*)\0*.*\0";
    OFN.lpstrFile = fileBuffer;
    OFN.nMaxFile = bufferSize / sizeof(fileBuffer[0]);
    OFN.Flags = flags;

    return (flags & OFN_OVERWRITEPROMPT ? GetSaveFileName(&OFN) : GetOpenFileName(&OFN)) != 0;
}
