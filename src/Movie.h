	#pragma once
#include <iostream>
#include <string>

class Movie
{
private:
	std::string title;
	int year = 0;
	std::string actor;
	std::string genre;

public:
	/**
	 * Copy constructor
	 */
	Movie(const Movie& other)
		: title(other.title),
		  year(other.year),
		  actor(other.actor),
		  genre(other.genre)
	{
		std::cout << "Copy constructor\n";
	}

	/**
	 * @brief Empty constructor
	*/
	Movie() = default;

	/**
	 * @brief Constructor for movie object
	 * @param title std::string
	 * @param year int
	 * @param actor std::string
	 * @param genre std::string
	*/
	Movie(const std::string& title, int year, const std::string& actor, const std::string& genre)
		: title(title),
		  year(year),
		  actor(actor),
		  genre(genre)
	{
	}

	~Movie()
	{
		year = 0;
	}

	/**
	 * @brief Getter for genre
	 * @return std::string genre
	*/
	std::string get_genre() const;
	/**
	 * @brief Setter for genre
	 * @param i_genre std::string genre
	*/
	void set_genre(const std::string& i_genre);
	/**
	 * @brief Getter for title
	 * @return std::string title
	*/
	std::string get_title() const;
	/**
	 * @brief Setter for title
	 * @param i_title std::string title
	*/
	void set_title(const std::string& i_title);
	/**
	 * @brief Getter for year
	 * @return int year
	*/
	int get_year() const;
	/**
	 * @brief Setter for year
	 * @param i_year int year
	*/
	void set_year(const int& i_year);
	/**
	 * @brief Getter for actor
	 * @return std::string
	*/
	std::string get_actor() const;
	/**
	 * @brief Setter for actor
	 * @param i_actor std::string actor
	*/
	void set_actor(const std::string& i_actor);

	/**
	 * @brief Equal operator for two movies
	 * @param movie Movie
	 * @return true if two movies have title and year
	*/
	bool operator==(const Movie& movie) const;

	friend std::istream& operator>>(std::istream& is, Movie& en);
	friend std::ostream& operator<<(std::ostream& os, const Movie& en);
};


void testMovie();
