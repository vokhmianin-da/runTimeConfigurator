#include "formdrivertables.h"
#include "ui_formdrivertables.h"

FormDriverTables::FormDriverTables(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDriverTables)
{
    ui->setupUi(this);
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
