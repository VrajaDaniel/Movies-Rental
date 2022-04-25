#pragma once
#include <map>
#include <string>
#include <vector>


#include "Movie.h"

class Repo
{
public:
    virtual ~Repo() = default;

    virtual void store(const Movie& movie) =0;

    /**
     * @brief Delete a Movie
     * @param movie Movie to be deleted
    */
    virtual void remove(const Movie& movie) =0;
    /**
     * @brief Modify a movie based with given title and year
     * @param movie Movie
    */
    virtual void modify(const Movie& movie) =0;

    /**
     * @brief Get all stored Movies
     * @return vector<MovieDomain>
    */
    virtual std::vector<Movie> getAll() =0;

    /**
     * @brief Search a movie by title and year
     * @param title string
     * @param year int
     * @return Movie in case we find it
     * @throws MovieRepoException if we can't find it
    */
    virtual const Movie& find(const std::string title, const int year) const =0;
};
