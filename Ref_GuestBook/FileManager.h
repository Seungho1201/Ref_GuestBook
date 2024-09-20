#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <Windows.h>
#include <commdlg.h>
#include <vector>
#include <fstream>
#include "Pen_Str.h"
#include "Resource.h"

/// File_Manager
/// ������ �����ϰ� �ε��ϴ� ���� Ŭ����
class File_Manager {
public:
    File_Manager() = default;                                                               /// �⺻ ������  
    ~File_Manager() = default;                                                              /// �⺻ �Ҹ���

    File_Manager(const File_Manager&) = delete;                                             /// ���� ������ ��� ����
    File_Manager& operator=(const File_Manager&) = delete;                                  /// ���� ���� ������ ��� ����

    void selectFileMode(int wmId, HWND g_Hwnd, std::vector<Pen_Info>* penMemory);            /// ���� ��带 �����ϴ� �Լ�

private:
    bool HandleFileOperation(HWND hWnd, std::vector<Pen_Info>* penMemory, bool isSave);      /// ���� �۾�(���� �Ǵ� �ε�)�� ó���ϴ� �Լ�
    bool ConfigureDialog(HWND hWnd, DWORD flags, WCHAR* fileBuffer, DWORD bufferSize);       /// ���� ��ȭ���ڸ� �����ϴ� �Լ�

    bool save(const wchar_t* path, std::vector<Pen_Info>* penMemory);                        /// ������ �����ϴ� �Լ�    
    bool load(const wchar_t* path, std::vector<Pen_Info>* penMemory, HWND g_Hwnd);           /// ������ �ε��ϴ� �Լ�
    bool openForWrite(const wchar_t* path);                                                 /// ������ ���� ���� ���� �Լ�
    bool openForRead(const wchar_t* path);                                                  /// ������ �б� ���� ���� �Լ�

    OPENFILENAME OFN = { 0 };           /// ���� ��ȭ���� ���� ����ü
    WCHAR fileName[256] = { 0 };        /// ���� ���� ���
    WCHAR fileOpenName[256] = { 0 };    /// ���� ���� ���
    WCHAR str[256] = { 0 };             /// ���� ��� �ӽ� ����

    std::fstream fs;                    /// ���� ��Ʈ��
};

#endif
