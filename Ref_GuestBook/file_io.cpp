#include "file_io.h"


bool FileOperations::save(const wchar_t* path, vector<Pen_Info>* penMemory)
{
    if (penMemory->size() < 80) {
        return false;
    }
    if (!openForWrite(path)) {
        return false;
    }
    for (const auto& i : *penMemory) {
        this->fs << i.penCoordinate << ' '
            << i.penWidth << ' '
            << i.penColor << ' '
            << i.penTime  << ' '
            << i.penState << ' '
            << i.stampOn  << ' '
            << i.stampImg << ' '
            << i.stampSize << '\n';
    }
    this->fs.close();
    return true;
}


bool FileOperations::load(const wchar_t* path, vector<Pen_Info>* penMemory, HWND g_Hwnd)
{
    RECT paintAreaLoad = { 10, 120, 1425, 830 };
   
    if (!openForRead(path)) {
        return false;
    }
    penMemory->clear();

    PEN_INFO pen_info;

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
    this->fs.close();

    InvalidateRect(g_Hwnd, &paintAreaLoad, TRUE);
    return true;
}

bool FileOperations::openForWrite(const wchar_t* path)
{
    this->fs.open(path, std::ios::out | std::ios::trunc);
    return !this->fs.fail();
}

bool FileOperations::openForRead(const wchar_t* path)
{
    this->fs.open(path, std::ios::in);
    return !this->fs.fail();
}
