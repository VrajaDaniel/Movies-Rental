#pragma once
#include "MovieRepo.h"

class FileMovieRepo
{
private:
	std::string storage;
public:
	void loadFromDisk();
	void saveToDisk();

	FileMovieRepo(const std::string& storage)
	{
		this->storage = storage;
		loadFromDisk();
	}

};
