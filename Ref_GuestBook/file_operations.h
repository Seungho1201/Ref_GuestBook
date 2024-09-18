#pragma once

#include <Windows.h>
#include <commdlg.h>
#include <vector>
#include "Pen_Str.h"
#include "Resource.h"
#include "file_io.h"

class File_Manager {
public:
    File_Manager() = default;
    ~File_Manager() = default;

    File_Manager(const File_Manager&) = delete;
    File_Manager& operator=(const File_Manager&) = delete;

    bool SaveFile(HWND hWnd, std::vector<Pen_Info>* penMemory);

    bool LoadFile(HWND hWnd, std::vector<Pen_Info>* penMemory);

    void selectFileMode(int wmId, HWND g_Hwnd, std::vector<Pen_Info>* penMemory);

private:
    bool ConfigureDialog(HWND hWnd, DWORD flags, WCHAR* fileBuffer, DWORD bufferSize);

    OPENFILENAME OFN = { 0 };           /// 파일 대화상자 정보 구조체
    WCHAR fileName[256] = { 0 };        /// 파일 저장 경로를 저장
    WCHAR fileOpenName[256] = { 0 };    /// 파일 열기 경로를 저장
    WCHAR str[256] = { 0 };             /// 파일 경로를 저장

    FileOperations fileOps;             /// FileOperations 객체

};
