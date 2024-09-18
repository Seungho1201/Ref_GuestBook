#pragma once
#include <Windows.h>
#include <iostream>
#include "framework.h"
#include "Resource.h"

class PenColorManager {

public:
    // 펜 색상 변경 함수, COLORREF 포인터를 받아 처리
    void Change_Color(int color, COLORREF* penColor);
};

