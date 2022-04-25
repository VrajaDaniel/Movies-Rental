#pragma once
#include <qformlayout.h>
#include <QLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QWidget>

#include "MovieService.h"

class BasketUI : public QWidget
{
private:
    MovieService* service;

    QWidget* wdg;
    QTableWidget* tableWidget;
    QTableWidgetItem* header;
    QTableWidgetItem* header2;

    QHBoxLayout* hl;
    QVBoxLayout* vl;

    QFormLayout* formDetails;

    QLineEdit* numberOfRandom;
    QPushButton* btnGenerate;

    QLineEdit* lineEditExportFileName;
    QPushButton* btnExportCSV;
    QPushButton* btnExportHTML;

    void initGUIComp();

    void initGUISignals();

    void reloadBasketList() const;
    void initGUIState();
public:


    explicit BasketUI(MovieService* service): service(service)
    {
        initGUIComp();
        initGUISignals();
        initGUIState();
    }
};
