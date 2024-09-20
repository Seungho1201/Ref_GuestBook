#include "FileManager.h"

bool File_Manager::save(const wchar_t* path, vector<Pen_Info>* penMemory)
{
    /// penMemory�� �ִ� �����Ͱ� 80�� �̸��̸� �������� ����
    if (penMemory->size() < 80) {
        return false;
    }

    /// ������ ���� ���� �� �� ������ false ��ȯ
    if (!openForWrite(path)) {
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
    
    this->fs.close();               /// ������ ����
    return true;                    /// ���� ����
}

bool File_Manager::load(const wchar_t* path, vector<Pen_Info>* penMemory, HWND g_Hwnd)
{
    /// �ε� ��, �ٽ� �׸� ������ ����
    RECT paintAreaLoad = { PAINT_R_LEFT, PAINT_R_TOP, PAINT_R_RIGHT, PAINT_R_BOTTOM };

    /// ������ �б� ���� �� �� ������ false ��ȯ
    if (!openForRead(path)) {
        return false;
    }

    /// penMemory�� ���
    penMemory->clear();

    PEN_INFO pen_info;

    /// ���Ͽ��� �����͸� �о�� pen_info�� ������ ��, penMemory�� �߰�
    while (this->fs >>
        pen_info.penCoordinate >>
        pen_info.penWidth >>
        pen_info.penColor >>
        pen_info.penTime >>
        pen_info.penState >>
        pen_info.stampOn >>
        pen_info.stampImg >>
        pen_info.stampSize) {

        penMemory->push_back(pen_info);
    }

    /// ������ ����
    this->fs.close();

    /// ȭ���� �ٽ� �׷��ֱ� ���� ������ ��ȿȭ
    InvalidateRect(g_Hwnd, &paintAreaLoad, TRUE);
    return true; // �ε� ����
}

bool File_Manager::openForWrite(const wchar_t* path)
{
    /// ������ ���� ���� ����, ���� ���� ��ȯ
    this->fs.open(path, ios::out | ios::trunc);
    return !this->fs.fail();
}

bool File_Manager::openForRead(const wchar_t* path)
{
    /// ������ �б� ���� ����, ���� ���� ��ȯ
    this->fs.open(path, ios::in);
    return !this->fs.fail();
}
