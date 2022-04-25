#pragma once
#include "MovieService.h"
#include "ListTemplate.h"

typedef Movie ElementType;

class MovieUI
{
private:
	MovieService& service;

	/**
	 * @brief UI function for adding a movie
	 * In case of bad input throws Exception
	*/
	void addMovieUI();
	/**
	 * @brief UI function for editing a movie
	 * In case of bad input throws Exception
	*/
	void modifyMovieUI();
	/**
	 * @brief UI function for deleting a movie
	 * In case of bad input throws Exception
	*/
	void deleteMovieUI();
	/**
	 * @brief UI function for searching a movie
	 * In case of bad input throws Exception
	*/
	void searchMovieUI();

	/**
	 * @brief UI function for printing all movies
	*/
	void printMoviesUI(const std::vector<Movie>& movies);

	/**
	 * @brief UI function for filtering all movies
	*/
	void filterMovieUI();
	/**
	 * @brief UI function for sorting all movies
	*/
	void sortMovieUI();

	/**
	 * @brief UI function to empty the basket
	*/
	void emptyBasketUI();

	/**
	 * @brief UI function to add to basket
	*/
	void addToBasketUI();

	/**
	 * @brief UI function to generate the basket
	*/
	void generateBasketUI();

	/**
	 * @brief UI function to print the basket
	*/
	void printBasketUI();

	/**
	 * @brief UI function to print the year map
	*/
	void printMapUI();

	/**
	 * @brief UI function to undo last operation
	*/
	void undoUI();

	/**
	 * @brief UI function to save basket to disk
	*/
	void saveBasketToDiskUI();


public:
	MovieUI(MovieService& ctr) : service{ctr}
	{
	}

	//nu permitem copierea obiectelor
	MovieUI(const MovieUI& ot);

	~MovieUI() = default;


	void start();
};
