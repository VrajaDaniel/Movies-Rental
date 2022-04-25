#pragma once
#include <map>
#include <random>

#include "FileMovieBasketRepo.h"
#include "FileMovieRepo.h"
#include "FileRepo.h"
#include "MovieBasketRepo.h"
#include "MovieMapDTO.h"
#include "MovieRepo.h"
#include "MovieValidator.h"
#include "UndoAction.h"
#include "RepoLab.h"

class MovieService
{
private:
	Repo* repo;
	MovieValidator& validator;
	std::mt19937 mt{std::random_device{}()};

	std::vector<std::unique_ptr<UndoAction>> undoActions;


public:
	FileMovieBasketRepo& basketRepo;

	//nu permitem copierea de obiecte MovieService
	MovieService(const MovieService& ot) = delete;

	MovieService(Repo* rep, FileMovieBasketRepo& basket_repo, MovieValidator& validator) : repo{rep},
		basketRepo{basket_repo}, validator{validator}
	{
	}

	~MovieService() = default;

	/**
	 * @brief Get all movies
	 * @return vector<Movie> in which order they have been added
	*/
	std::vector<Movie> getAll() noexcept
	{
		return repo->getAll();
	}

	/**
	 * @brief Adds a new movie
	 * @param title string
	 * @param year int
	 * @param actor string
	 * @param genre string
	 * @throw ValidateException in case the inputs are not valid
	*/
	void addMovie(const std::string& title, const int& year, const std::string& actor, const std::string& genre);

	/**
	 * @brief Deletes a movies
	 * @param title string
	 * @param year int
	*/
	void deleteMovie(const std::string& title, const int& year);

	/**
	 * @brief Updates a movie based on title and year
	 * @param title string
	 * @param year int
	 * @param actor string
	 * @param genre string
	*/
	void modifyMovie(const std::string& title, const int& year, const std::string& actor, const std::string& genre);
	/**
	 * @brief Returns a list of movies according with search options
	 * @param option filter option
	 * @param value value for filter
	 * @return List of movies
	*/
	std::vector<Movie> searchMovie(int option, const std::string& value);
	/**
	 * @brief Returns a list of movies according with filters
	 * @param option filter option
	 * @param value value for filter
	 * @return List of movies
	*/
	std::vector<Movie> filterMovie(int option, const std::string& value);
	/**
	 * @brief Returns a list of movies sorted by given input
	 * @param option sort option
	 * @return List of movies
	*/
	std::vector<Movie> sortMovie(int option);

	/**
	 * @brief Deletes all movies from basket
	*/
	void emptyBasket();

	/**
	 * @brief Adds a movie by title in basket
	 * @param title string
	 * @param year int
	*/
	void addMovieToBasket(const std::string& title, const int& year);


	/**
	 * @brief Get all movies
	 * @return vector<Movie> in which order they have been added
	*/
	const std::vector<Movie>& getAllBasket() const noexcept
	{
		return basketRepo.getAll();
	}

	/**
	 * @brief Populates the basket with random items
	 * @param howMany int
	*/
	void populateBasket(const unsigned int& howMany);

	/**
	 * @brief Function to return the year based map 
	*/
	std::map<int, MovieMapDTO> getMap();

	/**
	 * @brief Undo last add/remove/modify action
	*/
	void undo();
	/**
	 * @brief Function to save basket to persistance memory
	 * @param output string file name to save the content
	*/
	void saveBasketToCSV(const std::string& output);

	/**
	 * @brief Function to save basket to persistance memory as html
	 * @param output file name to save the content
	*/
	void saveBasketToHTML(const std::string& output);
	const Movie& findMovie(const std::string& title, const std::string& year);
};


void testCtr();
