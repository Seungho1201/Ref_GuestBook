#pragma once
#include <Windows.h>
#include <iostream>
#include "framework.h"
#include "Resource.h"

class PenColorManager {

public:
    // �� ���� ���� �Լ�, COLORREF �����͸� �޾� ó��
    void Change_Color(int color, COLORREF* penColor);
};
