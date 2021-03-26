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
    int countTags = ui->spBcountTags->value();

    if(selectItem->currentIndex().isValid())    //вставка после выделенной строки
    {
        int lastRow = selectItem->currentIndex().row() + 1;
        tagContext->insertRows(lastRow, countTags);
        //tagContext->setData(this->tagContext->index(lastRow,0), tagContext->data(this->tagContext->index(lastRow - 1,0)).toInt() + 1);
    }
    else    //вставка по умолчанию
    {
        tagContext->insertRows(tagContext->rowCount(), countTags);
    }
}

void FormDriverTables::removeTag()
{
    QItemSelectionModel *selectItem = ui->tvTagContext->selectionModel();
    //int currentRow = selectItem->currentIndex().row();

    QModelIndexList currentItems = selectItem->selectedIndexes();   //все выделенные строки
    for (auto it: currentItems)
    {
         tagContext->removeRow(it.row());   //удаление каждой из выделенных строк
    }
    //tagContext->removeRow(currentRow);
    //ui->tvTagContext->setRowHidden(currentRow, true);
}
