/**
@file ColorPalette.h
@brief 색상 선택 대화상자 관련 클래스 멤버 및 메서드 정의 파일
*/

#pragma once

#include <windows.h>
#include <commdlg.h> /// 색상 선택을 사용하기위한 API 

/// 현재 선택된 색상을 저장하는 전역 변수 (static으로 선언하여 프로그램 전역에서 공유)
static COLORREF currentColor; //현재 선택된 색상

class ColorPalette {

private:
	COLORREF acrCustClr[16];										/// 사용자 정의 색상 저장 공간
	CHOOSECOLOR cc;													/// 색상 선택 창을 설정, 호출하는 구조체
	HBRUSH hBrush = NULL;											/// 색상을 저장하는 브러쉬 => 초기값 NULL
	COLORREF colorArr[3] = { RGB(0,0,0),RGB(0,0,0), RGB(0,0,0) };	/// 펜에 대한 색상을 저장하는 배열


public:
	void colorSelect(HWND, int);
	void destroy();

	COLORREF getColor(int);

};