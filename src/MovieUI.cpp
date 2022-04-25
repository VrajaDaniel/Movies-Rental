#include "MovieUI.h"

#include <iostream>


using std::cin;
using std::cout;

void MovieUI::addMovieUI()
{
	std::string title, actor, genre, yearInput;
	int year;
	cout << "Titlu: ";
	cin >> title;
	cout << "An apartie: ";
	cin >> yearInput;

	try
	{
		year = std::stoi(yearInput);
	}
	catch (...)
	{
		std::vector<std::string> tmp;
		tmp.push_back("Invalid input for year");
		throw ValidateException(tmp);
	}

	cout << "Actor principal: ";
	cin >> actor;
	cout << "Tipul filmului: ";
	cin >> genre;
	service.addMovie(title, year, actor, genre);
	cout << "Added with success!\n";
}

void MovieUI::modifyMovieUI()
{
	std::string title, actor, genre, yearInput;
	int year;
	cout << "Titlu: ";
	cin >> title;
	cout << "An apartie: ";
	cin >> yearInput;

	try
	{
		year = std::stoi(yearInput);
	}
	catch (...)
	{
		std::vector<std::string> tmp;
		tmp.push_back("Invalid input for year");
		throw ValidateException(tmp);
	}

	cout << "Actor principal: ";
	cin >> actor;
	cout << "Tipul filmului: ";
	cin >> genre;
	service.modifyMovie(title, year, actor, genre);
	cout << "Modify with success!\n";
}

void MovieUI::deleteMovieUI()
{
	std::string title;
	int year;
	cout << "Titlu: ";
	cin >> title;
	cout << "An apartie: ";
	cin >> year;

	service.deleteMovie(title, year);
	cout << "Deleted with success!\n";
}

void MovieUI::searchMovieUI()
{
	cout << "Search by:\n 1)Title\n2)Year\n3)Actor\n4)Genre\nInput:";
	int option;
	cin >> option;

	std::string value;

	if (option != 1 && option != 2 && option != 3 && option != 4)
	{
		std::vector<std::string> tmp;
		tmp.push_back("Bad filter input number");
		throw ValidateException(tmp);
	}
	cout << "Search value: ";
	cin >> value;
	printMoviesUI(service.searchMovie(option, value));
}

void MovieUI::printMoviesUI(const std::vector<Movie>& movies)
{
	cout << "Movies:\n";
	for (const Movie& movie : movies)
	{
		cout << ' ' << movie.get_title() << ' ' << movie.get_year() << ' ' << movie.get_actor() << ' ' << movie.
			get_genre() << '\n';
	}
	/*for (unsigned int i = 0; i < movies.size(); ++i)
	{
		const auto& movie = movies.at(i);

		cout << ' ' << movie.get_title() << ' ' << movie.get_year() << ' ' << movie.get_actor() << ' ' << movie.
			get_genre() << '\n';
	}*/
	cout << "=====================\n";
}

void MovieUI::filterMovieUI()
{
	cout << "Filter by:\n 1)Title\n2)Year\n3)Actor\n4)Genre\nInput:";
	int option;
	cin >> option;

	std::string value;

	if (option != 1 && option != 2 && option != 3 && option != 4)
	{
		std::vector<std::string> tmp;
		tmp.push_back("Bad filter input number");
		throw ValidateException(tmp);
	}
	cout << "Filter value: ";
	cin >> value;
	printMoviesUI(service.filterMovie(option, value));
}

void MovieUI::sortMovieUI()
{
	cout << "Sort by:\n 1)Title\n2)Year+Genre\n3)Actor\nInput:";
	int option;
	cin >> option;

	if (option != 1 && option != 2 && option != 3)
	{
		std::vector<std::string> tmp;
		tmp.push_back("Bad filter input number");
		throw ValidateException(tmp);
	}

	printMoviesUI(service.sortMovie(option));
}

void MovieUI::emptyBasketUI()
{
	this->service.emptyBasket();

	cout << "Basket size : ";
	cout << this->service.getAllBasket().size() << '\n';
}

void MovieUI::addToBasketUI()
{
	std::string title, yearInput;
	int year;
	cout << "Titlu: ";
	cin >> title;
	cout << "An apartie: ";
	cin >> yearInput;

	try
	{
		year = std::stoi(yearInput);
	}
	catch (...)
	{
		std::vector<std::string> tmp;
		tmp.push_back("Invalid input for year");
		throw ValidateException(tmp);
	}
	this->service.addMovieToBasket(title, year);


	cout << "Basket size : ";
	cout << this->service.getAllBasket().size() << '\n';
}

void MovieUI::generateBasketUI()
{
	unsigned int number;
	cout << "Number of itmes: ";
	cin >> number;
	this->service.populateBasket(number);

	cout << "Basket size : ";
	cout << this->service.getAllBasket().size() << '\n';
}

void MovieUI::printBasketUI()
{
	printMoviesUI(service.getAllBasket());
}

void MovieUI::printMapUI()
{
	for (const auto& it : service.getMap())
	{
		cout << it.first << ": " << it.second.get_year() << ' ' << it.second.get_count() << '\n';
	}
}

void MovieUI::undoUI()
{
	this->service.undo();
	cout << "Undo with success !\n";
	cout << "=====================\n";
}

void MovieUI::saveBasketToDiskUI()
{
	int option = 0;
	cout << "Output format, CSV = 0, HTML = 1 : ";
	cin >> option;

	if (option > 1 || option < 0)
	{
		std::vector<std::string> tmp;
		tmp.push_back("Bad output option");
		throw ValidateException(tmp);
	}

	std::string fileNameForOutput;

	cout<<"Output filename: ";
	cin>>fileNameForOutput;

	if(option == 0)
	{
		this->service.saveBasketToCSV(fileNameForOutput);
	} else
	{
		this->service.saveBasketToHTML(fileNameForOutput);
	}
}

void MovieUI::start()
{
	while (true)
	{
		cout << "=====================\n";
		cout << "Menu:\n";
		cout << "1. Add movie\n";
		cout << "2. Delete movie\n";
		cout << "3. Modify movie\n";
		cout << "4. Print all movies\n";
		cout << "5. Search movies\n";
		cout << "6. Filter movies\n";
		cout << "7. Sort movies\n";
		cout << "81. Empty basket\n";
		cout << "82. Add to basket\n";
		cout << "83. Generate basket\n";
		cout << "84. Print basket\n";
		cout << "85. Save basket to disk\n";
		cout << "9. Print map\n";
		cout << "99. Undo last operation(add/delete/modify)\n";
		cout << "0. Exit\n";
		cout << "=====================\n";
		int cmd;
		cin >> cmd;
		try
		{
			switch (cmd)
			{
			case 1:
				addMovieUI();
				break;
			case 2:
				deleteMovieUI();
				break;
			case 3:
				modifyMovieUI();
				break;
			case 4:
				printMoviesUI(service.getAll());
				break;
			case 5:
				searchMovieUI();
				break;
			case 6:
				filterMovieUI();
				break;
			case 7:
				sortMovieUI();
				break;
			case 81:
				emptyBasketUI();
				break;
			case 82:
				addToBasketUI();
				break;
			case 83:
				generateBasketUI();
				break;
			case 84:
				printBasketUI();
				break;
			case 85:
				saveBasketToDiskUI();
				break;
			case 9:
				printMapUI();
				break;
			case 99:
				undoUI();
				break;
			case 0:
				return;
			default:
				cout << "Invalid command \n";
			}
		}
		catch (const MovieRepoException& ex)
		{
			cout << ex << '\n';
		}
		catch (const ValidateException& ex)
		{
			cout << ex << '\n';
		} catch (const MovieBasketRepoException& ex)
		{
			cout << ex << '\n';
		}catch (const RepoLabException& ex)
		{
			cout << ex << '\n';
		}
	}
}
