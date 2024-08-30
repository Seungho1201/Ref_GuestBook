#pragma once

#include "resource.h"
#include "Pen_Str.h"
#include "drawline.h"
#include "replay.h"
#include "button.h"
#include "erase.h"
#include "w_control.h"
#include "file_io.h"

void mouse_paint(HDC hdc);

// COMMAND ��� ��� ����

#define REPLAY 100
#define ERASE 200			// �����

#define SAVE 300
#define LOAD 400

///
/// �� ���� ���� func
/// 
#define W_UP 500
#define W_DOWN 600

#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))