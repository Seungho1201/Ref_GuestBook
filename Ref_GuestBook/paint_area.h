#pragma once
#include <windows.h>
#include "Ref_GuestBook.h"


class PaintAreaSquare {
private:
    HPEN MyPen;
    HPEN OldPen;

public:
    PaintAreaSquare();
    ~PaintAreaSquare();
    void makeSquare(HDC hdc);
};
