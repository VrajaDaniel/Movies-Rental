#include "FileRepo.h"

#include <fstream>

void FileRepo::loadFromDisk(std::vector<Movie>& list)
{
    std::ifstream f(storage);

    list.clear();

    Movie m;
    while (f >> m)
    {
        list.push_back(m);
    }
    f.close();
}

void FileRepo::saveToDisk(const std::vector<Movie>& list)
{
    std::ofstream f(storage);

    for (const auto& it : list)
    {
        f << it;
    }

    f.close();
}
