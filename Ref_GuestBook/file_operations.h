/// file_operations.h
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

    bool SaveFile(HWND hWnd);

    bool LoadFile(HWND hWnd);

private:
    bool ConfigureDialog(HWND hWnd, DWORD flags, WCHAR* fileBuffer, DWORD bufferSize);

    OPENFILENAME OFN = { 0 };           /// ���� ��ȭ���� ���� ����ü
    WCHAR fileName[256] = { 0 };        /// ���� ���� ��θ� ����
    WCHAR fileOpenName[256] = { 0 };    /// ���� ���� ��θ� ����
    WCHAR str[256] = { 0 };             /// ���� ��θ� ����

    FileOperations fileOps;             /// FileOperations ��ü
};