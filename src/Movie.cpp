#include "Movie.h"

#include <cassert>


std::string Movie::get_genre() const
{
	return genre;
}

void Movie::set_genre(const std::string& i_genre)
{
	this->genre = i_genre;
}

std::string Movie::get_title() const
{
	return title;
}

void Movie::set_title(const std::string& i_title)
{
	this->title = i_title;
}

int Movie::get_year() const
{
	return year;
}

void Movie::set_year(const int& i_year)
{
	this->year = i_year;
}

std::string Movie::get_actor() const
{
	return actor;
}

void Movie::set_actor(const std::string& i_actor)
{
	this->actor = i_actor;
}


bool Movie::operator==(const Movie& movie) const
{
	if (this->get_title() == movie.get_title() && this->get_year() == movie.get_year())
	{
		return true;
	}
	return false;
}

std::istream& operator>>(std::istream& is, Movie& en)
{
	std::string title, actor, genre;
	int year;
	is >> title;
	is >> year;
	is >> actor;
	is >> genre;

	en.set_title(title);
	en.set_year(year);
	en.set_actor(actor);
	en.set_genre(genre);

	return is;
}

std::ostream& operator<<(std::ostream& os, const Movie& en)
{
	os << en.get_title() << ' ' << en.get_year() << ' ' << en.get_actor() << ' ' << en.get_genre() << '\n';
	return os;
}

void testMovie()
{
	Movie a = {"a", 2, "b", "b"};
	a.set_actor("a");
	a.set_genre("a");
	a.set_year(3);
	a.set_title("a");
	assert(a.get_title() == "a");
	assert(a.get_genre() == "a");
	assert(a.get_actor() == "a");
	assert(a.get_year() == 3);
}
