#pragma once

#include "Pen_Str.h"
#include <fstream>
#include <vector>

using namespace std;

class FileOperations {
public:
    bool save(const wchar_t* path, vector<Pen_Info>* penMemory);
    bool load(const wchar_t* path, vector<Pen_Info>* penMemory, HWND g_Hwnd);

private:
    LPARAM lParam;
    std::fstream fs; 

    bool openForWrite(const wchar_t* path);
    bool openForRead(const wchar_t* path);
};

