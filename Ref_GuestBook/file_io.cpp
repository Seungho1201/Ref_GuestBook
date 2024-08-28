#include "file_io.h"

extern vector<PEN_INFO> penMemory;

bool file_save(const SPINFO& info_vector, const wchar_t* path)
{
	fstream fs;

	if (penMemory.size() < 50) {
		return false;
	}

	fs.open(path, ios::out | ios::trunc);
	if (fs.fail())	// 파일 열기에 실패한 경우
		return false;

	for (const auto& i : penMemory)
	{
		fs << i.penCoordinate << " ";
		fs << i.penWidth << " ";
		fs << i.penColor << " ";
		fs << i.penTime << " ";
		fs << i.penState << endl;
	}
	fs.close();
	return true;
}

bool file_load(SPINFO& info_vector, const wchar_t* path)
{
	wchar_t dir[100];
	fstream fs;

	fs.open(path, ios::in);

	if (fs.fail()) 
	{
		return false;
	}

	penMemory.clear();
	
	while (fs.good())
	{
		PEN_INFO i;

		if (!(fs >> i.penCoordinate >> i.penWidth >> i.penColor >> i.penTime >> i.penState))
		{
			break; // 데이터 읽기에 실패하면 루프 종료
		}

		/*fs >> i.penCoordinate;
		fs >> i.penWidth;
		fs >> i.penColor;
		fs >> i.penTime;
		fs >> i.penState;*/

		penMemory.push_back(i);
	}

	return true;
}