#pragma once
#include <vector>

#include "Movie.h"
#include "Observer.h"

class MovieBasketRepo: public Observable
{
private:
    std::vector<Movie> all;
    /**
     * @brief Check to see if we already have this movie in repository
     * @param p Movie
     * @return true if we already have it, false if we don't have it
    */
    bool exist(const Movie& p) const;
public:
    /**
     * @brief Default constructor
    */
    MovieBasketRepo() = default;

    /**
     * @brief Store a Movie
     * @param movie Movie
    */
    void store(const Movie& movie);
    const Movie& find(std::string title, int year) const;

    /**
     * @brief Deletes all movies
    */
    void clear();


    /**
     * @brief Get all stored Movies
     * @return vector<MovieDomain>
    */
    const std::vector<Movie>& getAll() const noexcept;
};


/**
 * @brief Used for exception encountered in Repository
*/
class MovieBasketRepoException
{
    std::string msg;
public:
    MovieBasketRepoException(std::string m) : msg{m}
    {
    }

    std::string getMsg()
    {
        return msg;
    }

    //functie friend (vreau sa folosesc membru privat msg)
    friend std::ostream& operator<<(std::ostream& out, const MovieBasketRepoException& ex);
};

std::ostream& operator<<(std::ostream& out, const MovieBasketRepoException& ex);
