#include "MyGUI.h"

#include <QLabel>
#include <QRegularExpressionValidator>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMenuBar>

#include "BasketUI.h"
#include "CosCrudGui.h"
#include "CosReadOnlyGui.h"

void MyGUI::initGUIComp()
{
	QHBoxLayout* mainLy = new QHBoxLayout();
	setLayout(mainLy);


	QMenuBar* toolBar = new QMenuBar();

	QMenu* searchMenu = new QMenu();
	searchMenu->setTitle("Search");
	searchByTitle = searchMenu->addAction("By Title");
	searchByYear = searchMenu->addAction("By Year");
	searchByActor = searchMenu->addAction("By Actor");
	searchByGenre = searchMenu->addAction("By Genre");

	toolBar->addMenu(searchMenu);


	QMenu* findMenu = new QMenu();
	findMenu->setTitle("Filter");
	findByTitle = findMenu->addAction("By Title");
	findByYear = findMenu->addAction("By Year");
	findByActor = findMenu->addAction("By Actor");
	findByGenre = findMenu->addAction("By Genre");

	toolBar->addMenu(findMenu);

	mainLy->setMenuBar(toolBar);


	QWidget* widRight = new QWidget;
	QVBoxLayout* vl = new QVBoxLayout;
	widRight->setLayout(vl);

	vl->addWidget(listMovies);

	QWidget* widBtnRight = new QWidget;
	QHBoxLayout* lyBtnsRight = new QHBoxLayout;
	widBtnRight->setLayout(lyBtnsRight);
	sort1 = new QPushButton("Sort by Title");
	lyBtnsRight->addWidget(sort1);
	sort2 = new QPushButton("Sort by Year and Genre");
	lyBtnsRight->addWidget(sort2);
	sort3 = new QPushButton("Sort by Actor");
	lyBtnsRight->addWidget(sort3);

	vl->addWidget(widBtnRight);

	QWidget* utilsBtnRight = new QWidget;
	QHBoxLayout* lyUtilsRight = new QHBoxLayout;
	utilsBtnRight->setLayout(lyUtilsRight);
	btnUndo = new QPushButton("Undo last operation");
	lyUtilsRight->addWidget(btnUndo);
	btnClear = new QPushButton("Clear selection");
	btnClear->setDisabled(true);
	lyUtilsRight->addWidget(btnClear);

	vl->addWidget(utilsBtnRight);

	QWidget* basketBtnRight = new QWidget;
	QHBoxLayout* lyBasketRight = new QHBoxLayout;
	basketBtnRight->setLayout(lyBasketRight);
	btnAddToBasket = new QPushButton("Add to basket");
	lyBasketRight->addWidget(btnAddToBasket);
	btnClearBasket = new QPushButton("Clear basket");
	lyBasketRight->addWidget(btnClearBasket);
	btnViewBasket = new QPushButton("View basket");
	lyBasketRight->addWidget(btnViewBasket);

	btnViewMap = new QPushButton("View map[lab]");
	lyBasketRight->addWidget(btnViewMap);

	btnBasketCrud = new QPushButton("CRUD");
	lyBasketRight->addWidget(btnBasketCrud);

	btnBasketReadOnly = new QPushButton("READ Only");
	lyBasketRight->addWidget(btnBasketReadOnly);

	vl->addWidget(basketBtnRight);


	basketBtnDelete = new QWidget;
	lyBasketDelete = new QHBoxLayout;
	basketBtnDelete->setLayout(lyBasketDelete);


	vl->addWidget(basketBtnDelete);


	mainLy->addWidget(widRight);

	QWidget* widDetails = new QWidget;
	QFormLayout* formDetails = new QFormLayout;
	widDetails->setLayout(formDetails);

	textTitle = new QLineEdit;
	formDetails->addRow(new QLabel("Title: "), textTitle);
	txtYear = new QLineEdit;
	formDetails->addRow(new QLabel("Year: "), txtYear);
	textGenre = new QLineEdit;
	formDetails->addRow(new QLabel("Genre: "), textGenre);
	textActor = new QLineEdit;
	formDetails->addRow(new QLabel("Actor: "), textActor);

	QHBoxLayout* vlDetails = new QHBoxLayout;

	btnAdd = new QPushButton("Add movie");
	btnDelete = new QPushButton("Delete movie");

	btnDelete->setDisabled(true);

	vlDetails->addWidget(btnAdd);
	vlDetails->addWidget(btnDelete);

	formDetails->addRow(vlDetails);

	mainLy->addWidget(widDetails);
}

void MyGUI::removeAllByCategory(const QString& text)
{
	for (const auto& it : service.getAll())
	{
		if (it.get_genre() == text.toStdString())
		{
			service.deleteMovie(it.get_title(), it.get_year());
		}
	}
	reloadListMovies(service.getAll());
}

void MyGUI::reloadListMovies(const std::vector<Movie>& movies)
{
	listMovies->clear();


	for (const auto& category : categories)
	{
		delete category;
	}

	categories.clear();
	
	for (const auto& it : movies)
	{
		auto text = it.get_title() + "(" + std::to_string(it.get_year()) + ")";
		QListWidgetItem* item = new QListWidgetItem{QString::fromStdString(text)};
		QPair<std::string, std::string> a = {it.get_title(), std::to_string(it.get_year())};
		item->setData(Qt::UserRole, QVariant::fromValue(a));

		listMovies->addItem(item);


		QPushButton* category = new QPushButton(QString::fromStdString(it.get_genre()));
		QObject::connect(category, &QPushButton::clicked, this, [category, this]()
		{
			removeAllByCategory(category->text());
		});
		
		lyBasketDelete->addWidget(category);
		categories.push_back(category);
	}
}

void MyGUI::initGUIState()
{
	reloadListMovies(service.getAll());
	switchToAddMovie();
}

void MyGUI::launchSearchOrFindWindow()
{
	searchWidget = new QWidget;
	QVBoxLayout* window = new QVBoxLayout();

	inputSearch = new QLineEdit();

	searchBtn = new QPushButton();
	if (isSearch)
		searchBtn->setText("Search");
	else
		searchBtn->setText("Filter");

	window->addWidget(inputSearch);
	window->addWidget(searchBtn);

	searchWidget->setLayout(window);

	QObject::connect(searchBtn, &QPushButton::clicked, this, [&]()
	{
		std::vector<Movie> movies;
		if (isSearch)
			movies = service.searchMovie(option, inputSearch->text().toStdString());
		else
			movies = service.filterMovie(option, inputSearch->text().toStdString());


		if (colorFilter)
		{
			listMovies->clear();
			for (const auto& it : service.getAll())
			{
				auto text = it.get_title() + "(" + std::to_string(it.get_year()) + ")";
				QListWidgetItem* item = new QListWidgetItem{QString::fromStdString(text)};
				if (std::find(movies.begin(), movies.end(), it) != movies.end())
				{
					item->setBackground(Qt::green);
				}
				QPair<std::string, std::string> a = {it.get_title(), std::to_string(it.get_year())};
				item->setData(Qt::UserRole, QVariant::fromValue(a));

				listMovies->addItem(item);
			}
		}
		else
			reloadListMovies(movies);

		searchWidget->hide();
	});

	searchWidget->show();
}

void MyGUI::initSearchSignals()
{
	QObject::connect(searchByActor, &QAction::triggered, this, [&]()
	{
		isSearch = true;
		option = 3;
		launchSearchOrFindWindow();
	});

	QObject::connect(searchByTitle, &QAction::triggered, this, [&]()
	{
		isSearch = true;
		option = 1;
		launchSearchOrFindWindow();
	});

	QObject::connect(searchByYear, &QAction::triggered, this, [&]()
	{
		isSearch = true;
		option = 2;
		launchSearchOrFindWindow();
	});

	QObject::connect(searchByGenre, &QAction::triggered, this, [&]()
	{
		isSearch = true;
		option = 4;
		launchSearchOrFindWindow();
	});
}

void MyGUI::initFilterSignals()
{
	QObject::connect(findByActor, &QAction::triggered, this, [&]()
	{
		isSearch = false;
		option = 3;
		colorFilter = true;
		launchSearchOrFindWindow();
	});

	QObject::connect(findByTitle, &QAction::triggered, this, [&]()
	{
		isSearch = false;
		option = 1;
		colorFilter = false;
		launchSearchOrFindWindow();
	});

	QObject::connect(findByYear, &QAction::triggered, this, [&]()
	{
		isSearch = false;
		option = 2;
		colorFilter = false;
		launchSearchOrFindWindow();
	});

	QObject::connect(findByGenre, &QAction::triggered, this, [&]()
	{
		isSearch = false;
		option = 4;
		colorFilter = false;
		launchSearchOrFindWindow();
	});
}

void MyGUI::initGUISignals()
{
	initSearchSignals();
	initFilterSignals();

	QObject::connect(btnBasketCrud, &QPushButton::clicked, this, [&]()
	{
		cosGUI = new CosCrudGui(service);
		cosGUI->move(10, 10);
		cosGUI->show();
	});

	QObject::connect(btnBasketReadOnly, &QPushButton::clicked, this, [&]()
	{
		cosGUI2 = new CosReadOnlyGui(service);
		cosGUI2->move(20, 20);
		cosGUI2->resize(500, 500);
		cosGUI2->show();
	});


	QObject::connect(btnClear, &QPushButton::clicked, this, [&]()
	{
		listMovies->clearSelection();
		this->switchToAddMovie();
	});
	QObject::connect(btnAdd, &QPushButton::clicked, this, [&]()
	{
		try
		{
			if (listMovies->selectedItems().isEmpty())
			{
				service.addMovie(textTitle->text().toStdString(), txtYear->text().toInt(),
				                 textActor->text().toStdString(),
				                 textGenre->text().toStdString());
			}
			else
			{
				service.modifyMovie(textTitle->text().toStdString(), txtYear->text().toInt(),
				                    textActor->text().toStdString(),
				                    textGenre->text().toStdString());
			}
			reloadListMovies(service.getAll());
		}
		catch (ValidateException& e)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(e.getMsg()));
		} catch (MovieRepoException& e)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(e.getMsg()));
		}
	});

	QObject::connect(listMovies, &QListWidget::itemSelectionChanged, this, [&]()
	{
		auto sel = listMovies->selectedItems();
		if (sel.isEmpty())
		{
			txtYear->setText("");
			textTitle->setText("");
			textGenre->setText("");
			textActor->setText("");
			this->switchToAddMovie();
		}
		else
		{
			auto selItem = sel.at(0);
			const auto& metadata = selItem->data(Qt::UserRole).value<QPair<std::string, std::string>>();

			const auto& movie = service.findMovie(metadata.first, metadata.second);

			txtYear->setText(QString::fromStdString(std::to_string(movie.get_year())));
			textTitle->setText(QString::fromStdString(movie.get_title()));
			textGenre->setText(QString::fromStdString(movie.get_genre()));
			textActor->setText(QString::fromStdString(movie.get_actor()));

			this->switchToEditMovie();
		}
	});

	QObject::connect(btnDelete, &QPushButton::clicked, this, [&]()
	{
		auto selItem = listMovies->selectedItems().at(0);
		const auto& metadata = selItem->data(Qt::UserRole).value<QPair<std::string, std::string>>();

		try
		{
			service.deleteMovie(metadata.first, stoi(metadata.second));
			reloadListMovies(service.getAll());
		}
		catch (MovieRepoException& e)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(e.getMsg()));
		}
	});

	QObject::connect(sort1, &QPushButton::clicked, this, [&]()
	{
		reloadListMovies(service.sortMovie(1));
		QWidget* wdg = new QWidget;

		std::vector<Movie> all = service.sortMovie(1);
		QTableWidget* tableWidget = new QTableWidget(this);
		tableWidget->setRowCount(static_cast<int>(all.size()));
		tableWidget->setColumnCount(2);
		QTableWidgetItem* header = new QTableWidgetItem();
		header->setText("Title");
		tableWidget->setHorizontalHeaderItem(0, header);

		QTableWidgetItem* header2 = new QTableWidgetItem();
		header2->setText("Year");
		tableWidget->setHorizontalHeaderItem(1, header2);

		for (auto r = 0; r < all.size(); r++)
		{
			tableWidget->
				setItem(r, 0, new QTableWidgetItem(QString::fromStdString(all.at(r).get_title())));
			tableWidget->
				setItem(r, 1, new QTableWidgetItem(QString::fromStdString(std::to_string(all.at(r).get_year()))));
		}

		QVBoxLayout* vl = new QVBoxLayout;
		vl->addWidget(tableWidget);
		wdg->setLayout(vl);
		wdg->show();
	});
	QObject::connect(sort2, &QPushButton::clicked, this, [&]()
	{
		reloadListMovies(service.sortMovie(2));
	});
	QObject::connect(sort3, &QPushButton::clicked, this, [&]()
	{
		reloadListMovies(service.sortMovie(3));
	});

	QObject::connect(btnUndo, &QPushButton::clicked, this, [&]()
	{
		try
		{
			service.undo();
			reloadListMovies(service.getAll());
		}
		catch (MovieRepoException& e)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(e.getMsg()));
		}
	});

	QObject::connect(btnAddToBasket, &QPushButton::clicked, this, [&]()
	{
		auto selItem = listMovies->selectedItems().at(0);
		const auto& metadata = selItem->data(Qt::UserRole).value<QPair<std::string, std::string>>();
		try
		{
			service.addMovieToBasket(metadata.first, stoi(metadata.second));
			QMessageBox::information(this, "Success", "Added with success to basket!");
		}
		catch (MovieBasketRepoException& e)
		{
			QMessageBox::warning(this, "Warning", QString::fromStdString(e.getMsg()));
		}
	});

	QObject::connect(btnClearBasket, &QPushButton::clicked, this, [&]()
	{
		service.emptyBasket();
		QMessageBox::information(this, "Success", "Basket cleared!");
	});

	QObject::connect(btnViewBasket, &QPushButton::clicked, this, [&]()
	{
		showBasketUI();
	});

	QObject::connect(btnViewMap, &QPushButton::clicked, this, [&]()
	{
		QWidget* wdg = new QWidget;

		std::map<int, MovieMapDTO> map = service.getMap();
		QTableWidget* tableWidget = new QTableWidget(this);
		tableWidget->setRowCount(static_cast<int>(map.size()));
		tableWidget->setColumnCount(2);
		QTableWidgetItem* header = new QTableWidgetItem();
		header->setText("Count");
		tableWidget->setHorizontalHeaderItem(0, header);

		QTableWidgetItem* header2 = new QTableWidgetItem();
		header2->setText("Year");
		tableWidget->setHorizontalHeaderItem(1, header2);

		int rows = 0;
		for (const auto& it : map)
		{
			tableWidget->
				setItem(rows, 0, new QTableWidgetItem(QString::fromStdString(std::to_string(it.second.get_count()))));
			tableWidget->
				setItem(rows, 1, new QTableWidgetItem(QString::fromStdString(std::to_string(it.second.get_year()))));

			rows++;
		}

		QVBoxLayout* vl = new QVBoxLayout;
		vl->addWidget(tableWidget);
		wdg->setLayout(vl);
		wdg->show();
	});
}

void MyGUI::switchToAddMovie()
{
	listMovies->clearSelection();
	txtYear->setText("");
	textTitle->setText("");
	textGenre->setText("");
	textActor->setText("");
	btnAdd->setText("Add movie");
	btnDelete->setDisabled(true);
	btnClear->setDisabled(true);

	btnAddToBasket->setDisabled(true);
}

void MyGUI::switchToEditMovie()
{
	btnAdd->setText("Modify movie");
	btnDelete->setEnabled(true);
	btnClear->setEnabled(true);

	btnAddToBasket->setEnabled(true);
}

void MyGUI::showBasketUI()
{
	new BasketUI(&service);
}
