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
