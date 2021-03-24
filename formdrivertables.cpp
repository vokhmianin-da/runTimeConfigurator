#include "formdrivertables.h"
#include "ui_formdrivertables.h"

FormDriverTables::FormDriverTables(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDriverTables)
{
    ui->setupUi(this);
    connect (ui->pbDrContextSubmitAll, SIGNAL(clicked()), this, SLOT(DrContextSubmitAll()));
    connect (ui->pbDrContextRevertAll, SIGNAL(clicked()), this, SLOT(DrContextRevertAll()));
    connect (ui->pbTagContextSubmitAll, SIGNAL(clicked()), this, SLOT(TagContextSubmitAll()));
    connect (ui->pbTagContextRevertAll, SIGNAL(clicked()), this, SLOT(TagContextRevertAll()));

    connect (ui->pbAddTag, SIGNAL(clicked()), this, SLOT(addTag()));
    connect (ui->pbRemoveTag, SIGNAL(clicked()), this, SLOT(removeTag()));
}

FormDriverTables::~FormDriverTables()
{
    delete ui;
}

QTableView *FormDriverTables::getPtrDriverContext()
{
    return ui->tvDriverContext;
}

QTableView *FormDriverTables::getPtrTagContext()
{
    return ui->tvTagContext;
}

void FormDriverTables::DrContextSubmitAll()
{
    driverContext->submitAll();
}

void FormDriverTables::DrContextRevertAll()
{
    driverContext->revertAll();
}

void FormDriverTables::TagContextSubmitAll()
{
    tagContext->submitAll();
}

void FormDriverTables::TagContextRevertAll()
{
    tagContext->revertAll();
}

void FormDriverTables::addTag()
{
    QItemSelectionModel *selectItem = ui->tvTagContext->selectionModel();
    int lastRow = selectItem->currentIndex().row() + 1;
    tagContext->insertRow(lastRow);
}

void FormDriverTables::removeTag()
{
    QItemSelectionModel *selectItem = ui->tvTagContext->selectionModel();
    int currentRow = selectItem->currentIndex().row();
    tagContext->removeRow(currentRow);
    ui->tvTagContext->setRowHidden(currentRow, true);
}
