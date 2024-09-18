/// 헤더 가드 사용
/// #pramga once가 작동 안 한다.... 이유를 알 수 없다...
/// FILE_IO_H가 정의 안되어있을시 정의한다 
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
