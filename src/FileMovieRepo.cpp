#include "FileMovieRepo.h"

#include <fstream>

void FileMovieRepo::loadFromDisk()
{
	std::ifstream f(storage);

	MovieRepo::all.clear();

	Movie m;
	while (f >> m)
	{
		MovieRepo::all.emplace_back(m);
	}
	f.close();
}

void FileMovieRepo::saveToDisk()
{
	std::ofstream f(storage);

	for (const auto& it : MovieRepo::getAll())
	{
		f << it;
	}

	f.close();
}
