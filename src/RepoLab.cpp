#include "RepoLab.h"

#include <cassert>
#include <sstream>

void RepoLab::store(const Movie& movie)
{
    if (get_random_bool())
        throw RepoLabException("Probability");
    if (data.find({movie.get_title(), movie.get_year()}) != data.end())
        throw RepoLabException("Movie not found " + movie.get_title() + " year: " + std::to_string(movie.get_year()));
    //data[{movie.get_title(), movie.get_year()}] = movie;
    data.insert({{movie.get_title(), movie.get_year()}, movie});
    //data.insert_or_assign({movie.get_title(), movie.get_year()}, movie);
}

void RepoLab::remove(const Movie& movie)
{
    if (get_random_bool())
        throw RepoLabException("Probability");
    if (data.find({movie.get_title(), movie.get_year()}) == data.end())
    {
        throw RepoLabException("Movie not found " + movie.get_title() + " year: " + std::to_string(movie.get_year()));
    }
    data.erase({movie.get_title(), movie.get_year()});
}

void RepoLab::modify(const Movie& movie)
{
    if (get_random_bool())
        throw RepoLabException("Probability");

    const auto& pair = data.find({movie.get_title(), movie.get_year()});
    if (pair != data.end())
        data.insert_or_assign({movie.get_title(), movie.get_year()}, movie);
    else
        throw RepoLabException(
            "Movie not found, title: " + movie.get_title() + " year: " + std::to_string(movie.get_year()));
}

std::vector<Movie> RepoLab::getAll()
{
    if (get_random_bool())
        throw RepoLabException("Probability");

    std::vector<Movie> tmp;

    for (auto pair : data)
    {
        tmp.push_back(pair.second);
    }

    return tmp;
}

const Movie& RepoLab::find(const std::string title, const int year) const
{
    const auto& pair = data.find({title, year});
    if (pair != data.end())
    {
        return pair->second;
    }

    throw RepoLabException("Movie not found, title: " + title + " year: " + std::to_string(year));
}


std::ostream& operator<<(std::ostream& out, const RepoLabException& ex)
{
    out << ex.msg;
    return out;
}

void testAdaugaRepoLab()
{
    RepoLab rep(1.0);
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
    catch (const RepoLabException&)
    {
        assert(true);
    }
    //cauta inexistent
    try
    {
        rep.find("c", 1);
        assert(false);
    }
    catch (const RepoLabException& e)
    {
        std::stringstream os;
        os << e;
        assert(os.str().find("exista") >= 0);
    }
}

void testCautaRepoLab()
{
    RepoLab rep(1.0);
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
    catch (RepoLabException&)
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
    catch (RepoLabException&)
    {
        assert(true);
    }

    try
    {
        rep.remove(p);
        assert(false);
    }
    catch (RepoLabException&)
    {
        assert(true);
    }
}

void testeRepoLab()
{
    testAdaugaRepoLab();
    testCautaRepoLab();
}
