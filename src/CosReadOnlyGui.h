#pragma once
#include "MovieBasketRepo.h"
#include "Observer.h"
#include "QWidget"
#include <QListWidget.h>
#include <qpushbutton.h>
#include <QPainter.h>
#include <QImage.h>
#include <QtWidgets/QHBoxLayout>

#include "MovieService.h"

class CosReadOnlyGui : public QWidget, public Observer
{
private:
	MovieService& service;
	QListWidget* lst;
	QPushButton* btn;
	QPushButton* btnRandom;


	void initGUI()
	{
		QHBoxLayout* ly = new QHBoxLayout;

		setLayout(ly);
	}

	void paintEvent(QPaintEvent*) override
	{
		QPainter p{this};
		for (int i = 0; i < service.basketRepo.getAll().size(); ++i)
		{
			QPainter painter(this);
			QPen pen;
			pen.setWidth(4);
			pen.setColor(Qt::red);
			painter.setBrush(Qt::blue);
			painter.setPen(pen);
			QPointF* points = new QPointF[3];
			points[0] = QPointF(100*(i+1), 50*(i+1));
			points[1] = QPointF(50*(i+1), 150*(i+1));
			points[2] = QPointF(150*(i+1), 150*(i+1));
			painter.drawPolygon(points, 3);		}
	}

public:
	CosReadOnlyGui(MovieService& service) : service{service}
	{
		initGUI();
		service.basketRepo.addObserver(this);
		update();
	}

	void update() override
	{
		repaint();
	}

	~CosReadOnlyGui()
	{
		service.basketRepo.removeObserver(this);
	}
};
