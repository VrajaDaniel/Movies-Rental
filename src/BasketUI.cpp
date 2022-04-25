#include "BasketUI.h"


#include <QLabel>
#include <QMessageBox>


void BasketUI::initGUIComp()
{
    wdg = new QWidget;
    wdg->setWindowTitle(QString::fromStdString("Basket"));

    tableWidget = new QTableWidget(this);

    tableWidget->setColumnCount(2);

    header = new QTableWidgetItem();

    header->setText("Title");
    tableWidget->setHorizontalHeaderItem(0, header);

    header2 = new QTableWidgetItem();
    header2->setText("Year");
    tableWidget->setHorizontalHeaderItem(1, header2);

    hl = new QHBoxLayout;
    vl = new QVBoxLayout;

    formDetails = new QFormLayout;

    numberOfRandom = new QLineEdit();
    numberOfRandom->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*"), formDetails));
    formDetails->addRow(new QLabel("Nr. of random items: "), numberOfRandom);

    btnGenerate = new QPushButton("Generate");
    formDetails->addRow(btnGenerate);

    lineEditExportFileName = new QLineEdit();
    formDetails->addRow(new QLabel("Export file name: "), lineEditExportFileName);

    btnExportCSV = new QPushButton("CSV");
    btnExportHTML = new QPushButton("HTML");

    QHBoxLayout* exportLayout = new QHBoxLayout();
    exportLayout->addWidget(btnExportCSV);
    exportLayout->addWidget(btnExportHTML);

    formDetails->addRow(exportLayout);


    vl->addWidget(tableWidget);

    hl->addItem(vl);
    hl->addItem(formDetails);

    wdg->setLayout(hl);
    wdg->show();
}

void BasketUI::initGUISignals()
{
    QObject::connect(btnGenerate, &QPushButton::clicked, this, [&]()
    {
        try
        {
            service->populateBasket(numberOfRandom->text().toInt());
            reloadBasketList();
        }
        catch (MovieBasketRepoException& e)
        {
            QMessageBox::warning(this, "Warning", QString::fromStdString(e.getMsg()));
        }
    });


    QObject::connect(btnExportCSV, &QPushButton::clicked, this, [&]()
    {
        if (lineEditExportFileName->text().isEmpty())
        {
            QMessageBox::warning(this, "Warning", "Empty export file name");
        }
        else
        {
            service->saveBasketToCSV(lineEditExportFileName->text().toStdString());
            QMessageBox::information(this, "Success", "Saved with success");
        }
    });
    QObject::connect(btnExportHTML, &QPushButton::clicked, this, [&]()
    {
        if (lineEditExportFileName->text().isEmpty())
        {
            QMessageBox::warning(this, "Warning", "Empty export file name");
        }
        else
        {
            service->saveBasketToHTML(lineEditExportFileName->text().toStdString());
            QMessageBox::information(this, "Success", "Saved with success");
        }
    });
}

void BasketUI::reloadBasketList() const
{
    tableWidget->clearContents();

    tableWidget->setRowCount(static_cast<int>(service->getAllBasket().size()));

    for (auto r = 0; r < service->getAllBasket().size(); r++)
    {
        tableWidget->
            setItem(r, 0, new QTableWidgetItem(QString::fromStdString(service->getAllBasket().at(r).get_title())));
        tableWidget->
            setItem(r, 1, new QTableWidgetItem(
                        QString::fromStdString(std::to_string(service->getAllBasket().at(r).get_year()))));
    }
}

void BasketUI::initGUIState()
{
    reloadBasketList();
}
