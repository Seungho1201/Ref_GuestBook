#include "FileManager.h"

void File_Manager::selectFileMode(int wmId, HWND g_Hwnd, vector<Pen_Info>* penMemory)
{
    switch (wmId)
    {
    case SAVE:
        SaveFile(g_Hwnd, penMemory);                                /// ���� ���� �Լ� ȣ��
        break;
    case LOAD:
        LoadFile(g_Hwnd, penMemory);                                /// ���� �ε� �Լ� ȣ��
        break;
    }
}


bool File_Manager::SaveFile(HWND hWnd, vector<Pen_Info>* penMemory)
{
    /// ���� ���� ��ȭ���� ���� �� ��ΰ� ��ȿ�ϸ� ����
    if (ConfigureDialog(hWnd, OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT, fileName, sizeof(fileName))) {
        wsprintf(str, L"%s", OFN.lpstrFile);
        if (save(str, penMemory)) {            /// FileOperations�� save �޼��� ȣ��
            WCHAR successMessage[512];
            wsprintf(successMessage, L"������ ���������� ����Ǿ����ϴ�.\n���: %s", str);
            MessageBox(hWnd, successMessage, L"���� ���� ����", MB_OK);     /// ���� �޽��� �ڽ� ǥ��
            return true;        /// ���� ����
        }
        else {
            MessageBox(hWnd, L"���� ���� ����", L"����", MB_OK);            /// ���� �޽��� �ڽ� ǥ��
            return false;       /// ���� ����
        }
    }
    return false;           /// ��ȭ���� ���� ����
}

bool File_Manager::LoadFile(HWND hWnd, vector<Pen_Info>* penMemory)
{
    /// ���� ���� ��ȭ���� ���� �� ��ΰ� ��ȿ�ϸ� ����
    if (ConfigureDialog(hWnd, OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST, fileOpenName, sizeof(fileOpenName))) {
        wsprintf(str, L"%s", OFN.lpstrFile);        /// ������ ���� ��θ� str�� ����
        if (load(str, penMemory, hWnd)) {           /// FileOperations�� load �޼��� ȣ��
            return true;            /// �ε� ����
        }
        else {
            MessageBox(hWnd, L"���� ���� ����", L"����", MB_OK);            /// ���� �޽��� �ڽ� ǥ��
            return false;           /// �ε� ����
        }
    }
    return false;           /// ��ȭ���� ���� ����
}

bool File_Manager::ConfigureDialog(HWND hWnd, DWORD flags, WCHAR* fileBuffer, DWORD bufferSize) 
{
    /// OPENFILENAME ����ü ����
    OFN.lStructSize = sizeof(OPENFILENAME);
    OFN.hwndOwner = hWnd;
    OFN.lpstrFilter = L"��� ����(*.*)\0*.*\0";
    OFN.lpstrFile = fileBuffer;
    OFN.nMaxFile = bufferSize / sizeof(fileBuffer[0]);
    OFN.Flags = flags;

    /// ��ȭ���� ǥ�� �� ����� �۾� ó��
    return (flags & OFN_OVERWRITEPROMPT ? GetSaveFileName(&OFN) : GetOpenFileName(&OFN)) != 0;
}
