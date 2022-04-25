#pragma once
#include <string>
#include <vector>


#include "FileMovieRepo.h"
#include "Movie.h"

class FileRepo : public MovieRepo
{
private:
    std::string storage;
public:

    explicit FileRepo(const std::string& storage) : MovieRepo(), storage(storage)
    {
        loadFromDisk(all);
    }

    /**
	 * @brief Store a Movie
	 * @param movie Movie
	*/
    void store(const Movie& movie) override
    {
        MovieRepo::store(movie);
        saveToDisk(all);
    }

    /**
     * @brief Delete a Movie
     * @param movie Movie to be deleted
    */
    void remove(const Movie& movie) override
    {
        MovieRepo::remove(movie);
        saveToDisk(all);
    }

    /**
     * @brief Modify a movie based with given title and year
     * @param movie Movie
    */
    void modify(const Movie& movie) override
    {
        MovieRepo::modify(movie);
        saveToDisk(all);
    }

    /**
     * @brief Get all stored Movies
     * @return vector<MovieDomain>
    */
    std::vector<Movie> getAll() override
    {
        //loadFromDisk(data);
        return MovieRepo::getAll();
    }

    void loadFromDisk(std::vector<Movie>& list);
    void saveToDisk(const std::vector<Movie>& list);
};
