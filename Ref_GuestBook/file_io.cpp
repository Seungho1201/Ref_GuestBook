#include "file_io.h"
#include "replay.h"

LPARAM lParam;

bool FileOperations::save(const SPINFO& info_vector, const wchar_t* path)
{
    fstream fs;

    if (penMemory.size() < 80) {
        return false;
    }

    fs.open(path, ios::out | ios::trunc);
    if (fs.fail()) {
        return false;
    }

    for (const auto& i : penMemory) {
        fs << i.penCoordinate << " ";
        fs << i.penWidth << " ";
        fs << i.penColor << " ";
        fs << i.penTime << " ";
        fs << i.penState << endl;
    }

    fs.close();
    return true;
}

bool FileOperations::load(SPINFO& info_vector, const wchar_t* path)
{
    fstream fs;

    fs.open(path, ios::in);
    if (fs.fail()) {
        return false;
    }

    penMemory.clear();

    while (fs.good()) {
        PEN_INFO pen_info;
        if (!(fs >> pen_info.penCoordinate >> pen_info.penWidth >> pen_info.penColor >> pen_info.penTime >> pen_info.penState)) {
            break;
        }
        penMemory.push_back(pen_info);
    }

    CreateThread(NULL, 0, replay, (LPVOID)lParam, 0, NULL);

    return true;
}
