#include "MovieBasketRepo.h"

void MovieBasketRepo::store(const Movie& movie)
{
	if (exist(movie))
	{
		throw MovieBasketRepoException(
			"Movie already present in basket: " + movie.get_title() + " year: " + std::to_string(movie.get_year()));
	}
	all.push_back(movie);
	notify();
}

const Movie& MovieBasketRepo::find(const std::string title, const int year) const
{
	auto it = std::find_if(all.begin(), all.end(), [title, year](Movie p)
	{
		return p.get_title() == title && p.get_year() == year;
	});

	if (it != all.end())
		return *it;
	throw MovieBasketRepoException("Movie not found in basket, title: " + title + " year: " + std::to_string(year));
}

void MovieBasketRepo::clear()
{
	all.clear();
	notify();
}

bool MovieBasketRepo::exist(const Movie& p) const
{
	try
	{
		find(p.get_title(), p.get_year());
		return true;
	}
	catch (MovieBasketRepoException&)
	{
		return false;
	}
}

const std::vector<Movie>& MovieBasketRepo::getAll() const noexcept
{
	return all;
}

std::ostream& operator<<(std::ostream& out, const MovieBasketRepoException& ex)
{
	out << ex.msg;
	return out;
}
