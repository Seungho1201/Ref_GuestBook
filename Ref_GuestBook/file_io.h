#pragma once

#include "Pen_Str.h"
#include <fstream>
#include <vector>

using namespace std;

class FileOperations {
public:

    bool save(const SPINFO& info_vector, const wchar_t* path);
    bool load(SPINFO& info_vector, const wchar_t* path);

private:

};

extern vector<PEN_INFO> penMemory;
extern LPARAM lParam;
