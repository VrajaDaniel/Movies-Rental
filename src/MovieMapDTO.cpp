#include "MovieMapDTO.h"

#include <cassert>

int MovieMapDTO::get_year() const
{
	return year;
}

void MovieMapDTO::set_year(int input)
{
	this->year = input;
}

int MovieMapDTO::get_count() const
{
	return count;
}

void MovieMapDTO::set_count(int input)
{
	this->count = input;
}


void testMovieMapDTO()
{
	MovieMapDTO a;
	a.set_year(1);
	a.set_count(1);
	assert(a.get_count() == 1);
	assert(a.get_year() == 1);
}