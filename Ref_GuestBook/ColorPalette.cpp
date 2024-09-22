/**
@file ColorPalette.cpp
@brief �� ���� ������ ���� �ȷ�Ʈ ����� ������ �ڵ�
*/

#include "ColorPalette.h"

/// ���� ���� ��ȭ���� ���� ���õ� ������ �����ϴ� �Լ�
/**
@fn ColorPalette::colorSelect(HWND hWnd, int penNum)
@brief �ȷ�Ʈ ���ڸ� ���� ����ڰ� ������ ������ �����ϴ� �Լ�
@param hWnd ���� ���� ��ȭ���ڸ� �����ϴ� â�� �ڵ�
@param penNum ���õ� ������ ������ �� ��ȣ (colorArr �迭������ �ε���)
*/
void ColorPalette::colorSelect(HWND hWnd, int penNum)
{
	
	ZeroMemory(&cc, sizeof(cc));					// ChooseColor ����ü(cc)�� �ʱ�ȭ�Ͽ� ��� ���� 0���� ����
	cc.lStructSize = sizeof(cc);					// ChooseColor ����ü ũ�� ���� (ChooseColor API���� ����)
	cc.hwndOwner = hWnd;							// ��ȭ ���ڸ� ������ â�� �ڵ� ����
	cc.lpCustColors = (LPDWORD)acrCustClr;			// ����� ���� ���� �迭�� �ּҸ� ����
	cc.rgbResult = RGB(0, 0, 0);					// �ʱ� ���� ���� (���������� ����)
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;			// ���� ��ȭ ���� ���� (��ü ���� �ȷ�Ʈ�� ǥ���ϰ�, �ʱ� ������ ����)

	// ����ڰ� ������ ������ ��� (OK�� ������ ChooseColor �Լ��� true�� ��ȯ)
	if (ChooseColor(&cc)) {
		
		// ������ ������ �귯�ð� ������ �����Ͽ� �޸� ������ ����
		if (hBrush) {
			DeleteObject(hBrush); // ���� �귯�� ��ü ����
		}

		hBrush = CreateSolidBrush(cc.rgbResult);	// ���� ���õ� �������� �ܻ� �귯�ø� ����
		colorArr[penNum] = cc.rgbResult;			// ���õ� ������ ������ �� ��ȣ(penNum)�� ���� (colorArr �迭�� ����)
		InvalidateRect(hWnd, NULL, TRUE);			// ȭ���� �ٽ� �׸����� ��û�Ͽ� ���õ� ������ �ݿ��ǵ��� ��
	}
}

/// ���� �ȷ�Ʈ ���� ���ҽ��� �����ϴ� �Լ�
/**
@fn ColorPalette::destroy()
@brief ������ �귯�� ��ü�� �����Ͽ� ���ҽ��� �����ϴ� �Լ�
*/
void ColorPalette::destroy()
{
	// �귯�ð� ������ ���, �޸𸮿��� �����Ͽ� ���ҽ� ������ ����
	if (hBrush) {
		DeleteObject(hBrush); // �귯�� ��ü ����
	}
}

/// ������ �� ��ȣ�� ���� ������ ��ȯ�ϴ� �Լ�
/**
@fn ColorPalette::getColor(int penNum)
@brief �� ��ȣ�� �ش��ϴ� ������ ��ȯ�ϴ� �Լ�
@param penNum ������ ������ �� ��ȣ (colorArr �迭�� �ε���)
@return ���õ� ���� ���� (COLORREF ����)
*/
COLORREF ColorPalette::getColor(int penNum) {
	// ������ penNum�� �ش��ϴ� ������ colorArr �迭���� ��ȯ
	return colorArr[penNum];
}
