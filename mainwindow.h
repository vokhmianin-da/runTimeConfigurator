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

private:
    Ui::MainWindow *ui;
    QMap <QString, QString> driverParamsTemplates;    //хранит пару "тип драйвера - параметры драйвера (sql - запрос создания таблицы)"
    QMap <QString, QString> driverTagContextTemplates;    //хранит пару "тип драйвера - контекст тэга драйвера (sql - запрос создания таблицы)"
    QSqlDatabase db;    //модель списка драйверов
    QSqlQueryModel* modelDrivers;
    QTableView* tableDrivers;   //представление списка драйверов
    QMap <QString, QSqlTableModel*> DriversContest; //хранит указатели на контекст драйвера для каждого созданного драйвера
    QMap <QString, QSqlTableModel*> TagsDriverContest;  //хранит указатели на контекст тэга для каждого созданного драйвера
    QHBoxLayout *layBases;

    bool createConnection();    //создание БД
    // Текущий json объект, с которым производится работа
        QJsonObject m_currentJsonObject;
};
#endif // MAINWINDOW_H
