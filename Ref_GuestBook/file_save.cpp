#include "GB_File_io.h"

bool file_save(const SPINFO& info_vector, const wchar_t* path)
{
	//wchar_t path[256];
	fstream fs;


	//MessageBox(0, path, L"저장 경로", MB_OK);

	if (info_vector.pinfo.size() < 100)
		return false;

	fs.open(path, ios::out | ios::trunc);
	if (fs.fail())	// 파일 열기에 실패한 경우
		return false;
	fs << info_vector.x << " ";
	fs << info_vector.y << " ";
	fs << info_vector.width << " ";
	fs << info_vector.height << endl;
	for (const auto& i : info_vector.pinfo)
	{
		fs << i.lparm << " ";
		fs << i.cWidth << " ";
		fs << i.color << " ";
		fs << i.ctime << " ";
		fs << i.state << endl;
	}
	fs.close();
	return true;
}