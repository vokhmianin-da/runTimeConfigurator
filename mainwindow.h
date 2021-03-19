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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QMap <QString, QStringList> driverParamsTemplates;    //хранит пару "тип драйвера - параметры драйвера"
    QMap <QString, QStringList> driverTagContextTemplates;    //хранит пару "тип драйвера - контекст тэга драйвера"
};
#endif // MAINWINDOW_H
