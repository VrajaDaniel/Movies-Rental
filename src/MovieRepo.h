#pragma once
#include <vector>

#include "Movie.h"
#include "Repo.h"

class MovieRepo : public Repo
{
protected:
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
    MovieRepo() = default;

    /**
     * @brief Not allowing object coping 
     * @param ot MovieRepo
    */
    MovieRepo(const MovieRepo& ot) = delete;

    /**
     * @brief Store a Movie
     * @param movie Movie
    */
    void store(const Movie& movie) override;

    /**
     * @brief Delete a Movie
     * @param movie Movie to be deleted
    */
    void remove(const Movie& movie) override;
    /**
     * @brief Modify a movie based with given title and year
     * @param movie Movie
    */
    void modify(const Movie& movie) override;

    /**
     * @brief Get all stored Movies
     * @return vector<MovieDomain>
    */
    std::vector<Movie> getAll() override;

    /**
     * @brief Search a movie by title and year
     * @param title string
     * @param year int
     * @return Movie in case we find it
     * @throws MovieRepoException if we can't find it
    */
    const Movie& find(const std::string title, const int year) const override;
};

/**
 * @brief Used for exception encountered in Repository
*/
class MovieRepoException
{
    std::string msg;
public:
    MovieRepoException(std::string m) : msg{m}
    {
    }

    std::string getMsg()
    {
        return msg;
    }

    //functie friend (vreau sa folosesc membru privat msg)
    friend std::ostream& operator<<(std::ostream& out, const MovieRepoException& ex);
};

std::ostream& operator<<(std::ostream& out, const MovieRepoException& ex);

void testeRepo();
