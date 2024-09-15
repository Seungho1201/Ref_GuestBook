#pragma once

#include "resource.h"
#include "Pen_Str.h"
#include "DrawFunc.h"
#include "replay.h"
#include "button.h"
#include "erase.h"
#include "w_control.h"
#include "file_io.h"
#include "file_operations.h"
#include "c_color.h"
#include "paint_area.h"
#include "Window_Size.h"
#include "stamp.h"

// 그리기 영역
#define PAINT_R_LEFT 10
#define PAINT_R_TOP 120
#define PAINT_R_RIGHT 1425
#define PAINT_R_BOTTOM 830


// 펜, 스탬프 굵기 영역
#define WIDTH_R_LEFT 410
#define WIDTH_R_TOP  15
#define WIDTH_R_RIGHT 440
#define WIDTH_R_BOTTOM 45


/// COMMAND 기능 (500번대)
#define REPLAY      500
#define ERASE       501			
#define SAVE        502
#define LOAD        503
#define W_UP        504
#define W_DOWN      505


/// 스탬프 func (700번대)
#define CHANGE_PEN      700
#define HEART_STAMP     701
#define UH_STAMP        702
#define YUHAN_STAMP     703
#define YONGBIN_STAMP   704


/// 펜 색상 변경 상수 정의 (800번대)
#define C_RED		 800
#define C_ORANGE	 801
#define C_YELLOW	 802
#define C_GREEN		 803
#define C_BLUE		 804
#define C_NAVY		 805
#define C_PURPLE	 806
#define C_BLACK		 807

/**
* @Window_Size_Width 윈도우 넓이
* @Window_Size_Height 윈도우 높이
*/
#define Window_Size_Width 1450  
#define Window_Size_Height 900  