#pragma once
#include "MovieBasketRepo.h"
#include "MovieRepo.h"

class FileMovieBasketRepo : public MovieBasketRepo
{
public:
	void saveToCSV(const std::string& fileName) const;
	void saveToHTML(const std::string& fileName);
};
