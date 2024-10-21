#pragma once
#include <windows.h>
#include "Resource.h"


class PaintAreaSquare {
private:
    HPEN MyPen;
    HPEN OldPen;

public:
    PaintAreaSquare();
    ~PaintAreaSquare();
    void makeSquare(HDC hdc);
};
