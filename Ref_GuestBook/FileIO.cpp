#include "FileManager.h"

bool File_Manager::save(const wchar_t* path, vector<Pen_Info>* penMemory)
{
    /// penMemory에 있는 데이터가 80개 미만이면 저장하지 않음
    if (penMemory->size() < 80) {
        return false;
    }

    /// 파일을 쓰기 모드로 열 수 없으면 false 반환
    if (!openForWrite(path)) {
        return false;
    }

    /// penMemory의 데이터를 파일에 기록
    for (const auto& i : *penMemory) {
        this->fs << i.penCoordinate << ' '
            << i.penWidth << ' '
            << i.penColor << ' '
            << i.penTime << ' '
            << i.penState << ' '
            << i.stampOn << ' '
            << i.stampImg << ' '
            << i.stampSize << '\n';
    }
    
    this->fs.close();               /// 파일을 닫음
    return true;                    /// 저장 성공
}

bool File_Manager::load(const wchar_t* path, vector<Pen_Info>* penMemory, HWND g_Hwnd)
{
    /// 로드 시, 다시 그릴 영역을 설정
    RECT paintAreaLoad = { PAINT_R_LEFT, PAINT_R_TOP, PAINT_R_RIGHT, PAINT_R_BOTTOM };

    /// 파일을 읽기 모드로 열 수 없으면 false 반환
    if (!openForRead(path)) {
        return false;
    }

    /// penMemory를 비움
    penMemory->clear();

    PEN_INFO pen_info;

    /// 파일에서 데이터를 읽어와 pen_info에 저장한 후, penMemory에 추가
    while (this->fs >>
        pen_info.penCoordinate >>
        pen_info.penWidth >>
        pen_info.penColor >>
        pen_info.penTime >>
        pen_info.penState >>
        pen_info.stampOn >>
        pen_info.stampImg >>
        pen_info.stampSize) {

        penMemory->push_back(pen_info);
    }

    /// 파일을 닫음
    this->fs.close();

    /// 화면을 다시 그려주기 위해 영역을 무효화
    InvalidateRect(g_Hwnd, &paintAreaLoad, TRUE);
    return true; // 로드 성공
}

bool File_Manager::openForWrite(const wchar_t* path)
{
    /// 파일을 쓰기 모드로 열고, 실패 여부 반환
    this->fs.open(path, ios::out | ios::trunc);
    return !this->fs.fail();
}

bool File_Manager::openForRead(const wchar_t* path)
{
    /// 파일을 읽기 모드로 열고, 실패 여부 반환
    this->fs.open(path, ios::in);
    return !this->fs.fail();
}
