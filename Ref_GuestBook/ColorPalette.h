/**
@file ColorPalette.h
@brief ���� ���� ��ȭ���� ���� Ŭ���� ��� �� �޼��� ���� ����
*/

#pragma once

#include <windows.h>
#include "framework.h"
#include "Resource.h"
#include <commdlg.h> /// ���� ������ ����ϱ����� API 

/// ���� ���õ� ������ �����ϴ� ���� ���� (static���� �����Ͽ� ���α׷� �������� ����)
static COLORREF currentColor; //���� ���õ� ����

class ColorPalette {

private:
	COLORREF acrCustClr[16];										/// ����� ���� ���� ���� ����
	CHOOSECOLOR cc;													/// ���� ���� â�� ����, ȣ���ϴ� ����ü
	HBRUSH hBrush = NULL;											/// ������ �����ϴ� �귯�� => �ʱⰪ NULL
	COLORREF colorArr[3] = { RGB(0,0,0),RGB(0,0,0), RGB(0,0,0) };	/// �濡 ���� ������ �����ϴ� �迭


public:
	void colorSelect(HWND, int);
	void Change_Color(int color, COLORREF* penColor);
	void destroy();

	COLORREF getColor(int);

};