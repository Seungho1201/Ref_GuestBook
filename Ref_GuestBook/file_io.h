/// ��� ���� ���
/// #pramga once�� �۵� �� �Ѵ�.... ������ �� �� ����...
/// FILE_IO_H�� ���� �ȵǾ������� �����Ѵ� 
#ifndef FILE_IO_H
#define FILE_IO_H

#include <vector>
#include <fstream>
#include "Pen_Str.h"
#include "Resource.h"

class FileOperations {
public:
    bool save(const wchar_t* path, std::vector<Pen_Info>* penMemory);
    bool load(const wchar_t* path, std::vector<Pen_Info>* penMemory, HWND g_Hwnd);

private:
    LPARAM lParam;
    std::fstream fs;

    bool openForWrite(const wchar_t* path);
    bool openForRead(const wchar_t* path);
};

#endif 
