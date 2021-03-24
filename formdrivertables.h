#ifndef FORMDRIVERTABLES_H
#define FORMDRIVERTABLES_H

#include <QWidget>
#include <QSqlTableModel>
#include <QTableView>

namespace Ui {
class FormDriverTables;
}

class FormDriverTables : public QWidget
{
    Q_OBJECT

public:
    explicit FormDriverTables(QWidget *parent = nullptr);
    ~FormDriverTables();
    QSqlTableModel* driverContext;  //указатель на контекст драйвера
    QSqlTableModel* tagContext; //указатель на контекст тэга

    QTableView *getPtrDriverContext();
    QTableView *getPtrTagContext();
private:
    Ui::FormDriverTables *ui;

public slots:
    /*Слоты для записи и отмены изменений БД*/
    void DrContextSubmitAll();
    void DrContextRevertAll();
    void TagContextSubmitAll();
    void TagContextRevertAll();
};

#endif // FORMDRIVERTABLES_H
