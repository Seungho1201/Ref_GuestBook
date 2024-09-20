/// 헤더 가드 사용
/// #pragma once가 작동하지 않는 이유를 알 수 없다...
/// FILE_IO_H가 정의되지 않았을 경우 정의한다
#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <Windows.h>
#include <commdlg.h>
#include <vector>
#include <fstream>
#include "Pen_Str.h"
#include "Resource.h"

/// 네임스페이스 사용
using std::vector;
using std::fstream;
using std::ios;

/// File_Manager
/// 파일을 저장하고 로드하는 관리 클래스
class File_Manager {
public:
    File_Manager() = default;                                                               /// 기본 생성자  
    ~File_Manager() = default;                                                              /// 기본 소멸자

    File_Manager(const File_Manager&) = delete;                                             /// 복사 생성자 사용 금지
    File_Manager& operator=(const File_Manager&) = delete;                                  /// 복사 대입 연산자 사용 금지

    bool SaveFile(HWND hWnd, vector<Pen_Info>* penMemory);                                  /// 파일을 저장하는 함수
    bool LoadFile(HWND hWnd, vector<Pen_Info>* penMemory);                                  /// 파일을 로드하는 함수
    void selectFileMode(int wmId, HWND g_Hwnd, vector<Pen_Info>* penMemory);                /// 파일 모드를 선택하는 함수
    bool save(const wchar_t* path, vector<Pen_Info>* penMemory);                            /// 파일을 저장하는 함수    
    bool load(const wchar_t* path, vector<Pen_Info>* penMemory, HWND g_Hwnd);               /// 파일을 로드하는 함수

private:
    bool ConfigureDialog(HWND hWnd, DWORD flags, WCHAR* fileBuffer, DWORD bufferSize);      ///파일 대화상자를 설정하는 함수

    OPENFILENAME OFN = { 0 };           /// 파일 대화상자 정보 구조체
    WCHAR fileName[256] = { 0 };        /// 파일 저장 경로
    WCHAR fileOpenName[256] = { 0 };    /// 파일 열기 경로
    WCHAR str[256] = { 0 };             /// 파일 경로 임시 저장

    LPARAM lParam;   /// 파일 작업을 위한 lParam
    fstream fs;      /// 파일 스트림

    bool openForWrite(const wchar_t* path);                                                 /// 파일을 쓰기 모드로 여는 함수
    bool openForRead(const wchar_t* path);                                                  /// 파일을 읽기 모드로 여는 함수
};

#endif