#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QLayout>
#include <QSqlTableModel>

#include "formdrivertables.h"


#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pbAddDriver_clicked();

    void on_pbDeleteDriver_clicked();

    void on_pbCreateJson_clicked();

    void on_pbAddTag_clicked();

    void on_pbRemoveTag_clicked();

    void on_pbTagListSubmitAll_clicked();

    void on_pbTagListRevertAll_clicked();

private:
    Ui::MainWindow *ui;
    QMap <QString, QString> driverParamsTemplates;    //хранит пару "тип драйвера - параметры драйвера (sql - запрос создания таблицы)"
    QMap <QString, QString> driverTagContextTemplates;    //хранит пару "тип драйвера - контекст тэга драйвера (sql - запрос создания таблицы)"

    QSqlDatabase db;    //модель списка драйверов
    QSqlQueryModel* modelDrivers;
    QTableView* tableDrivers;   //представление списка драйверов
    QMap <QString, FormDriverTables*> drivers;   //содержит указатели на все драйверы с их контекстами
    QHBoxLayout *layBases;

    QSqlTableModel* tagsList;  //указатель на таблицу тэгов с основными параметрами

    bool createConnection();    //создание БД
    bool createDriver(QString driverName, QString driverType);  //создание драйвера и добавление его в таблицу
    bool removeDriver(QString driverName);  //удаление драйвера (из checkBox и из таблицы
    bool createDriverContext(QString driverName, QString driverTemplate, FormDriverTables *ptrNewDriver);   //создание вкладки и таблицы "Контекст драйвера"
    bool createTagContext(QString driverName, QString tagTemplate, FormDriverTables *ptrNewDriver);   //создание вкладки и таблицы "Контекст драйвера"
    bool removeDriverContext(QString driverName);   //удаление вкладки и таблицы "Контекст драйвера"
    bool removeTagContext(QString driverName);   //удаление вкладки и таблицы "Контекст драйвера"
    // Текущий json объект, с которым производится работа
        QJsonObject m_currentJsonObject;
};
#endif // MAINWINDOW_H
