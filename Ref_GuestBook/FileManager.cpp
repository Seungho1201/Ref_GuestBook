#include "FileManager.h"

/// ���� ���� �Ǵ� �ε带 ó���ϴ� �Լ�
bool File_Manager::HandleFileOperation(HWND hWnd, std::vector<Pen_Info>* penMemory, bool isSave) {
    DWORD flags = isSave ? (OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT) : (OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST);
    WCHAR* filePath = isSave ? fileName : fileOpenName;
    const wchar_t* operation = isSave ? L"����" : L"����";

    /// ���� ��ȭ���ڸ� �����ϰ� ��ΰ� ��ȿ�ϸ� ó��
    if (ConfigureDialog(hWnd, flags, filePath, sizeof(fileName))) {
        wsprintf(str, L"%s", OFN.lpstrFile);
        bool result = isSave ? save(str, penMemory) : load(str, penMemory, hWnd);

        if (result) {
            if (isSave) {  /// ����� ��� ǥ��
                WCHAR successMessage[512];
                wsprintf(successMessage, L"������ ���������� %s�Ǿ����ϴ�.\n���: %s", operation, str);
                MessageBox(hWnd, successMessage, L"���� ����", MB_OK); /// ���� �޽��� ǥ��
            }
        }
        else {
            MessageBox(hWnd, L"���� �۾� ����", L"����", MB_OK); /// ���� �޽��� ǥ��
        }
        return result;
    }
    return false; /// ��ȭ���� ����
}

/// ���� ��带 �����Ͽ� ���� �Ǵ� �ε� �۾��� �����ϴ� �Լ�
void File_Manager::selectFileMode(int wmId, HWND g_Hwnd, std::vector<Pen_Info>* penMemory) {
    switch (wmId) {
    case SAVE:
        HandleFileOperation(g_Hwnd, penMemory, true); /// ����
        break;
    case LOAD:
        HandleFileOperation(g_Hwnd, penMemory, false); /// �ε�
        break;
    }
}

/// ������ �����ϴ� �Լ�
bool File_Manager::save(const wchar_t* path, std::vector<Pen_Info>* penMemory) {
    if (penMemory->size() < 80 || !openForWrite(path)) {
        return false;
    }

    /// penMemory�� �����͸� ���Ͽ� ���
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

    this->fs.close(); /// ������ ����
    return true;
}

/// ������ �ε��ϴ� �Լ�
bool File_Manager::load(const wchar_t* path, std::vector<Pen_Info>* penMemory, HWND g_Hwnd) {
    if (!openForRead(path)) {
        return false;
    }

    penMemory->clear();
    PEN_INFO pen_info;

    /// ���Ͽ��� �����͸� �о�� penMemory�� �߰�
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

    this->fs.close(); /// ������ ����

    /// ȭ�� ������ ���� ��ȿȭ ���� ����
    RECT paintAreaLoad = { PAINT_R_LEFT, PAINT_R_TOP, PAINT_R_RIGHT, PAINT_R_BOTTOM };
    InvalidateRect(g_Hwnd, &paintAreaLoad, TRUE); /// ȭ�� ����
    return true;
}

/// ���� ��ȭ���ڸ� �����ϴ� �Լ�
bool File_Manager::ConfigureDialog(HWND hWnd, DWORD flags, WCHAR* fileBuffer, DWORD bufferSize) {
    OFN.lStructSize = sizeof(OPENFILENAME);
    OFN.hwndOwner = hWnd;
    OFN.lpstrFilter = L"��� ����(*.*)\0*.*\0";
    OFN.lpstrFile = fileBuffer;
    OFN.nMaxFile = bufferSize / sizeof(fileBuffer[0]);
    OFN.Flags = flags;

    /// ���� �Ǵ� ���� ��ȭ���ڸ� ����
    return (flags & OFN_OVERWRITEPROMPT ? GetSaveFileName(&OFN) : GetOpenFileName(&OFN)) != 0;
}

/// ������ ���� ���� ���� �Լ�
bool File_Manager::openForWrite(const wchar_t* path) {
    fs.open(path, std::ios::out | std::ios::trunc);
    return !fs.fail();
}

/// ������ �б� ���� ���� �Լ�
bool File_Manager::openForRead(const wchar_t* path) {
    fs.open(path, std::ios::in);
    return !fs.fail();
}
