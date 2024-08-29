#pragma once

#include "Pen_Str.h"
#include <fstream>

#define FILE_PATH L"../Save"

using namespace std;

bool file_save(const SPINFO& info_vector,  const wchar_t* name);
bool file_load(SPINFO& info_vector, const wchar_t* name);