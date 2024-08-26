#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include<vector>
#include<Windows.h>

using namespace std;

/**
 * @brief       펜 정보 관련한 구조체
 * (좌표, 펜 굵기, 색깔, 시간, 상태(LBUTTON))
*/
typedef struct Pen_Info
{
    LPARAM      penCoordinate;     // 좌표
    int         penWidth;          // 펜 굵기
    COLORREF    penColor;          // 펜 색깔
    DWORD       penTime;           // 시간
    UINT        penState;          // 상태 (LBUTTON)

} PEN_INFO;

typedef struct Scale_Point_Info
{
    std::vector<PEN_INFO> pinfo;
    int x;
    int y;
    int width;
    int height;
}SPINFO;


/**
 * @brief       Pen_Info 구조체를 벡터 자료구조로 저장하기 위한 벡터 구조체
 * 리플레이 스레드시 사용
*/
extern vector<PEN_INFO> penMemory;

extern PEN_INFO g_Pen_Info;     // 펜 구조체 전역변수 선언 (extern)
extern COLORREF pen_Color;      // 펜 색상 전역변수 선언 (extern)
extern int pen_Width;           // 펜 굵기 전역변수 선언 (ectern)