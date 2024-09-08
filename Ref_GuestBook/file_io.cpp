#include "file_io.h"
#include "replay.h"

LPARAM lParam;

bool FileOperations::save(const wchar_t* path)
{
    if (penMemory.size() < 80) {
        return false;
    }

    if (!openForWrite(path)) {
        return false;
    }

    for (const auto& i : penMemory) {
        this->fs << i.penCoordinate << ' '
            << i.penWidth << ' '
            << i.penColor << ' '
            << i.penTime << ' '
            << i.penState << '\n';
    }

    this->fs.close();
    return true;
}

bool FileOperations::load(const wchar_t* path)
{
    if (!openForRead(path)) {
        return false;
    }

    penMemory.clear();

    PEN_INFO pen_info;
    while (this->fs >> pen_info.penCoordinate >> pen_info.penWidth >> pen_info.penColor >> pen_info.penTime >> pen_info.penState) {
        penMemory.push_back(pen_info);
    }

    this->fs.close();
    CreateThread(NULL, 0, replay, (LPVOID)lParam, 0, NULL);

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
