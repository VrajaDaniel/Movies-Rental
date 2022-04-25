#pragma once
#include <QListWidget>
#include <QPushButton>


#include "CosCrudGui.h"
#include "CosReadOnlyGui.h"
#include "Movie.h"
#include "MovieService.h"

class MyGUI : public QWidget
{
public:
	QListWidget* listMovies = new QListWidget();
	QLineEdit* txtYear;
	QLineEdit* textTitle;
	QLineEdit* textGenre;
	QLineEdit* textActor;
	QPushButton* btnAdd;
	QPushButton* btnModify;
	QPushButton* btnDelete;
	QPushButton* btnClear;
	QPushButton* btnUndo;
	QPushButton* btnAddToBasket;
	QPushButton* btnClearBasket;
	QPushButton* btnViewBasket;
	QPushButton* btnViewMap;
	QPushButton* sort1;
	QPushButton* sort2;
	QPushButton* sort3;

	MovieService& service;

	QAction* searchByTitle;
	QAction* searchByYear;
	QAction* searchByActor;
	QAction* searchByGenre;

	QAction* findByTitle;
	QAction* findByYear;
	QAction* findByActor;
	QAction* findByGenre;


	QWidget* searchWidget;
	QLineEdit* inputSearch;
	QPushButton* searchBtn;
	int option = 1;
	bool isSearch = false;
	bool colorFilter = false;
	QPushButton* btnBasketCrud;
	QPushButton* btnBasketReadOnly;

	CosCrudGui* cosGUI;
	CosReadOnlyGui* cosGUI2;
	QHBoxLayout* lyBasketDelete;
	QWidget* basketBtnDelete;
	std::vector<QPushButton*> categories;

	explicit MyGUI(MovieService& service): service{service}
	{
		initGUIComp();
		initGUISignals();
		initGUIState();
	}


	void initGUIComp();
	void removeAllByCategory(const QString& text);
	void reloadListMovies(const std::vector<Movie>& movies);
	void initGUIState();
	void launchSearchOrFindWindow();
	void initSearchSignals();
	void initFilterSignals();
	void initGUISignals();
	void switchToAddMovie();
	void switchToEditMovie();

	void showBasketUI();
	void reloadBasketList();
};
