/**
@file ColorPalette.cpp
@brief 펜 색상 변경을 위한 팔레트 기능을 구현한 코드
*/

#include "ColorPalette.h"

/// 색상 선택 대화상자 열고 선택된 색상을 설정하는 함수
/**
@fn ColorPalette::colorSelect(HWND hWnd, int penNum)
@brief 팔레트 상자를 열고 사용자가 선택한 색상을 설정하는 함수
@param hWnd 색상 선택 대화상자를 소유하는 창의 핸들
@param penNum 선택된 색상을 저장할 펜 번호 (colorArr 배열에서의 인덱스)
*/
void ColorPalette::colorSelect(HWND hWnd, int penNum)
{
	
	ZeroMemory(&cc, sizeof(cc));					// ChooseColor 구조체(cc)를 초기화하여 모든 값을 0으로 설정
	cc.lStructSize = sizeof(cc);					// ChooseColor 구조체 크기 설정 (ChooseColor API에서 사용됨)
	cc.hwndOwner = hWnd;							// 대화 상자를 소유할 창의 핸들 설정
	cc.lpCustColors = (LPDWORD)acrCustClr;			// 사용자 정의 색상 배열의 주소를 설정
	cc.rgbResult = RGB(0, 0, 0);					// 초기 색상 설정 (검정색으로 설정)
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;			// 색상 대화 상자 설정 (전체 색상 팔레트를 표시하고, 초기 색상을 설정)

	// 사용자가 색상을 선택한 경우 (OK를 누르면 ChooseColor 함수가 true를 반환)
	if (ChooseColor(&cc)) {
		
		// 기존에 생성된 브러시가 있으면 삭제하여 메모리 누수를 방지
		if (hBrush) {
			DeleteObject(hBrush); // 기존 브러시 객체 삭제
		}

		hBrush = CreateSolidBrush(cc.rgbResult);	// 새로 선택된 색상으로 단색 브러시를 생성
		colorArr[penNum] = cc.rgbResult;			// 선택된 색상을 지정된 펜 번호(penNum)에 저장 (colorArr 배열에 저장)
		InvalidateRect(hWnd, NULL, TRUE);			// 화면을 다시 그리도록 요청하여 선택된 색상이 반영되도록 함
	}
}

/// 색상 팔레트 관련 리소스를 정리하는 함수
/**
@fn ColorPalette::destroy()
@brief 생성된 브러시 객체를 삭제하여 리소스를 정리하는 함수
*/
void ColorPalette::destroy()
{
	// 브러시가 생성된 경우, 메모리에서 제거하여 리소스 누수를 방지
	if (hBrush) {
		DeleteObject(hBrush); // 브러시 객체 삭제
	}
}

/// 지정된 펜 번호에 대한 색상을 반환하는 함수
/**
@fn ColorPalette::getColor(int penNum)
@brief 펜 번호에 해당하는 색상을 반환하는 함수
@param penNum 색상을 가져올 펜 번호 (colorArr 배열의 인덱스)
@return 선택된 펜의 색상 (COLORREF 형식)
*/
COLORREF ColorPalette::getColor(int penNum) {
	// 지정된 penNum에 해당하는 색상을 colorArr 배열에서 반환
	return colorArr[penNum];
}
