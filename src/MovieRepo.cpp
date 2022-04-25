#include "MovieRepo.h"

#include <algorithm>
#include <cassert>
#include <sstream>

using std::ostream;
using std::stringstream;

#define TEST_FILENAME "./test/testRepo.data"


void MovieRepo::store(const Movie& movie)
{
    if (exist(movie))
	{
		throw MovieRepoException(
			"Movie already present: " + movie.get_title() + " year: " + std::to_string(movie.get_year()));
	}
	all.push_back(movie);
}

void MovieRepo::remove(const Movie& movie)
{
   for (unsigned int i = 0; i < all.size(); ++i)
	{
		if (all.at(i) == movie)
		{
			all.erase(all.begin() + i, all.begin() + i + 1);
			return;
		}
	}
	throw MovieRepoException("Movie not found for deletion\n");
}

void MovieRepo::modify(const Movie& movie)
{
    for (unsigned int i = 0; i < all.size(); ++i)
	{
		if (all.at(i) == movie)
		{
			all.at(i) = movie;
			return;
		}
	}
	throw MovieRepoException("Movie not found for updating\n");
}

bool MovieRepo::exist(const Movie& p) const
{
    try
    {
        find(p.get_title(), p.get_year());
        return true;
    }
    catch (MovieRepoException&)
    {
        return false;
    }
}

std::vector<Movie> MovieRepo::getAll()
{
    //loadFromDisk(all);
    return all;
}

const Movie& MovieRepo::find(const std::string title, const int year) const
{
    auto it = std::find_if(all.begin(), all.end(), [title, year](Movie p)
	{
		return p.get_title() == title && p.get_year() == year;
	});

	if (it != all.end())
		return *it;
	/*for (unsigned int i = 0; i < all.size(); ++i)
	{
		if (all.at(i).get_title() == title && all.at(i).get_year() == year)
		{
			return all.at(i);
		}
	}*/

	throw MovieRepoException("Movie not found, title: " + title + " year: " + std::to_string(year));
}

ostream& operator<<(ostream& out, const MovieRepoException& ex)
{
    out << ex.msg;
    return out;
}

void testAdauga()
{
    MovieRepo rep;
    rep.store(Movie("b", 4, "b", "b"));
    assert(rep.getAll().size() == 1);
    assert(rep.find("b", 4).get_title() == "b");

    rep.store(Movie("a", 4, "b", "b"));
    assert(rep.getAll().size() == 2);

    //nu pot adauga 2 cu acelasi tip si specie
    try
    {
        rep.store(Movie("b", 4, "b", "b"));
        assert(false);
    }
    catch (const MovieRepoException&)
    {
        assert(true);
    }
    //cauta inexistent
    try
    {
        rep.find("c", 1);
        assert(false);
    }
    catch (const MovieRepoException& e)
    {
        stringstream os;
        os << e;
        assert(os.str().find("exista") >= 0);
    }
    remove(TEST_FILENAME);
}

void testCauta()
{
    MovieRepo rep;
    rep.store(Movie("b", 4, "b", "b"));
    rep.store(Movie("a", 4, "b", "b"));

    auto p = rep.find("a", 4);
    assert(p.get_title() == "a");
    assert(p.get_year() == 4);

    //arunca exceptie daca nu gaseste
    try
    {
        rep.find("a", 2);
        assert(false);
    }
    catch (MovieRepoException&)
    {
        assert(true);
    }

    rep.remove(p);
    assert(rep.getAll().size() == 1);


    try
    {
        rep.modify(p);
        assert(false);
    }
    catch (MovieRepoException&)
    {
        assert(true);
    }

    try
    {
        rep.remove(p);
        assert(false);
    }
    catch (MovieRepoException&)
    {
        assert(true);
    }
    remove(TEST_FILENAME);
}

void testeRepo()
{
    testAdauga();
    testCauta();
}
