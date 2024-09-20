#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <Windows.h>
#include <commdlg.h>
#include <vector>
#include <fstream>
#include "Pen_Str.h"
#include "Resource.h"

/// File_Manager
/// 파일을 저장하고 로드하는 관리 클래스
class File_Manager {
public:
    File_Manager() = default;                                                               /// 기본 생성자  
    ~File_Manager() = default;                                                              /// 기본 소멸자

    File_Manager(const File_Manager&) = delete;                                             /// 복사 생성자 사용 금지
    File_Manager& operator=(const File_Manager&) = delete;                                  /// 복사 대입 연산자 사용 금지

    void selectFileMode(int wmId, HWND g_Hwnd, std::vector<Pen_Info>* penMemory);            /// 파일 모드를 선택하는 함수

private:
    bool HandleFileOperation(HWND hWnd, std::vector<Pen_Info>* penMemory, bool isSave);      /// 파일 작업(저장 또는 로드)을 처리하는 함수
    bool ConfigureDialog(HWND hWnd, DWORD flags, WCHAR* fileBuffer, DWORD bufferSize);       /// 파일 대화상자를 설정하는 함수

    bool save(const wchar_t* path, std::vector<Pen_Info>* penMemory);                        /// 파일을 저장하는 함수    
    bool load(const wchar_t* path, std::vector<Pen_Info>* penMemory, HWND g_Hwnd);           /// 파일을 로드하는 함수
    bool openForWrite(const wchar_t* path);                                                 /// 파일을 쓰기 모드로 여는 함수
    bool openForRead(const wchar_t* path);                                                  /// 파일을 읽기 모드로 여는 함수

    OPENFILENAME OFN = { 0 };           /// 파일 대화상자 정보 구조체
    WCHAR fileName[256] = { 0 };        /// 파일 저장 경로
    WCHAR fileOpenName[256] = { 0 };    /// 파일 열기 경로
    WCHAR str[256] = { 0 };             /// 파일 경로 임시 저장

    std::fstream fs;                    /// 파일 스트림
};

#endif
