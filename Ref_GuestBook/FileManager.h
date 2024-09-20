/// ��� ���� ���
/// #pragma once�� �۵����� �ʴ� ������ �� �� ����...
/// FILE_IO_H�� ���ǵ��� �ʾ��� ��� �����Ѵ�
#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <Windows.h>
#include <commdlg.h>
#include <vector>
#include <fstream>
#include "Pen_Str.h"
#include "Resource.h"

/// ���ӽ����̽� ���
using std::vector;
using std::fstream;
using std::ios;

/// File_Manager
/// ������ �����ϰ� �ε��ϴ� ���� Ŭ����
class File_Manager {
public:
    File_Manager() = default;                                                               /// �⺻ ������  
    ~File_Manager() = default;                                                              /// �⺻ �Ҹ���

    File_Manager(const File_Manager&) = delete;                                             /// ���� ������ ��� ����
    File_Manager& operator=(const File_Manager&) = delete;                                  /// ���� ���� ������ ��� ����

    bool SaveFile(HWND hWnd, vector<Pen_Info>* penMemory);                                  /// ������ �����ϴ� �Լ�
    bool LoadFile(HWND hWnd, vector<Pen_Info>* penMemory);                                  /// ������ �ε��ϴ� �Լ�
    void selectFileMode(int wmId, HWND g_Hwnd, vector<Pen_Info>* penMemory);                /// ���� ��带 �����ϴ� �Լ�
    bool save(const wchar_t* path, vector<Pen_Info>* penMemory);                            /// ������ �����ϴ� �Լ�    
    bool load(const wchar_t* path, vector<Pen_Info>* penMemory, HWND g_Hwnd);               /// ������ �ε��ϴ� �Լ�

private:
    bool ConfigureDialog(HWND hWnd, DWORD flags, WCHAR* fileBuffer, DWORD bufferSize);      ///���� ��ȭ���ڸ� �����ϴ� �Լ�

    OPENFILENAME OFN = { 0 };           /// ���� ��ȭ���� ���� ����ü
    WCHAR fileName[256] = { 0 };        /// ���� ���� ���
    WCHAR fileOpenName[256] = { 0 };    /// ���� ���� ���
    WCHAR str[256] = { 0 };             /// ���� ��� �ӽ� ����

    LPARAM lParam;   /// ���� �۾��� ���� lParam
    fstream fs;      /// ���� ��Ʈ��

    bool openForWrite(const wchar_t* path);                                                 /// ������ ���� ���� ���� �Լ�
    bool openForRead(const wchar_t* path);                                                  /// ������ �б� ���� ���� �Լ�
};

#endif