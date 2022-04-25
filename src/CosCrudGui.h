#pragma once
#include "MovieBasketRepo.h"
#include "Observer.h"
#include "QWidget"
#include <QListWidget.h>
#include <qpushbutton.h>
#include <QtWidgets/QHBoxLayout>

#include "MovieService.h"

class CosCrudGui: public QWidget, public Observer
{
private:
	MovieService& service;
	QListWidget* lst;
	QPushButton* btn;
	QPushButton* btnRandom;

	void loadList(const std::vector<Movie>& movie) {
		lst->clear();
		for (auto& p : movie) {
			lst->addItem(QString::fromStdString(p.get_title()));
		}
	}
	void initGUI() {		
		QHBoxLayout* ly = new QHBoxLayout;
		lst = new QListWidget;
		ly->addWidget(lst);
		btn = new QPushButton("Clear cos");
		ly->addWidget(btn);

		btnRandom = new QPushButton("Add random 3");
		ly->addWidget(btnRandom);
		setLayout(ly);
	}
	void connectSignals() {
		service.basketRepo.addObserver(this);
		QObject::connect(btn, &QPushButton::clicked, [&]() {
			service.emptyBasket();
			loadList(service.basketRepo.getAll());
		});
		QObject::connect(btnRandom, &QPushButton::clicked, [&]() {
			service.populateBasket(3);
			loadList(service.basketRepo.getAll());
		});				
	}

public:
	CosCrudGui(MovieService& service) :service{service} {
		initGUI();
		connectSignals();
		loadList(service.basketRepo.getAll());
	}
	
	void update() override {
		loadList(service.getAllBasket());		
	}

	~CosCrudGui() {
		service.basketRepo.removeObserver(this);
	}
};
