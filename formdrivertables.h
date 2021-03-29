#ifndef FORMDRIVERTABLES_H
#define FORMDRIVERTABLES_H

#include <QWidget>
#include <QSqlTableModel>
#include <QTableView>

namespace Ui {
class FormDriverTables;
}

enum typesParams    //Типы данных для контекстов
{
    dtString,
    dtInt,
    dtFloat
};

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

    /*Слоты добавления/удаления строк тэгов*/
    void addTag();
    void removeTag();
};

#endif // FORMDRIVERTABLES_H
