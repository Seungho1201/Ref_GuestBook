/**
@file erase.cpp
@brief 지우기 기능 클래스 외부 정의 파일
*/
#include "erase.h"

/**
@fn  Eraser::Eraser()
@brief 지우는 영역 초기화를 위한 생성자
*/
Eraser::Eraser() {
    this->paintArea = { PAINT_R_LEFT, 
                        PAINT_R_TOP, 
                        PAINT_R_RIGHT, 
                        PAINT_R_BOTTOM };
}

/**
@fn   Eraser::erase(HWND hWnd, vector<Pen_Info>* penMemory)
@brief 지우기 기능 메서드
@param hWnd 윈도우 핸들
@param penMemory 지우기 기능과 동시에 벡터변수 초기화를 위한 포인터 인자
*/
void Eraser::erase(HWND hWnd, vector<Pen_Info>* penMemory)
{
    /// 벡터 변수 초기화
    penMemory->clear();

    /// 윈도우의 클라이언트 영역을 무효화하여 다시 그리기 요청
    InvalidateRect(hWnd, &this->paintArea, TRUE);
}