// file_operations.h
#pragma once

#include <Windows.h>
#include <commdlg.h>
#include "file_io.h"
#include "Pen_Str.h"

class File_Manager {

public:
    File_Manager() = default;
    ~File_Manager() = default;

    File_Manager(const File_Manager&) = delete;
    File_Manager& operator=(const File_Manager&) = delete;

    bool SaveFile(HWND hWnd, SPINFO penInfo);
    bool LoadFile(HWND hWnd, SPINFO penInfo);

private:

    //unique_ptr<file_io> fileIO;

    OPENFILENAME OFN = { 0 };
    WCHAR fileName[256] = { 0 };
    WCHAR str[256] = { 0 };
    WCHAR fileOpenName[256] = { 0 };

    FileOperations fileOps;  /// FileOperations °´Ã¼
};
