#pragma once

class MovieMapDTO
{
private:
	int year;
	int count;
public:
	MovieMapDTO() = default;

	MovieMapDTO(int year, int count)
		: year(year),
		  count(count)
	{
	}

	int get_year() const;
	void set_year(int input);
	int get_count() const;
	void set_count(int input);
};

void testMovieMapDTO();
