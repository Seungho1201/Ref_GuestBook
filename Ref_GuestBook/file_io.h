#pragma once

#include "Pen_Str.h"
#include <fstream>
#include <vector>

using namespace std;

class FileOperations {
public:
    bool save(const wchar_t* path);
    bool load(const wchar_t* path);

private:
    bool openForWrite(const wchar_t* path);
    bool openForRead(const wchar_t* path);
    std::fstream fs; 
};

extern vector<PEN_INFO> penMemory;
extern LPARAM lParam;
