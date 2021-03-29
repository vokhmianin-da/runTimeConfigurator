#include "mainwindow.h"

QJsonObject MainWindow::createJsonLoggerDriverContext(MainWindow* ptr, QString driverName)
{
    QJsonObject currentDriver;
    QSqlQuery query;
    QString strQuery;

    /*Имя драйвера*/
    currentDriver["name"] = driverName;

    /*Класс драйвера*/
    QString strF = "SELECT type FROM 'Драйверы' WHERE name='%1';";
    strQuery = strF.arg(driverName);
    if (!query.exec(strQuery)) {
            qDebug() << "Не удалось найти драйвер";
        }
    QSqlRecord rec = query.record();
    query.next();   //НЕ ЗАБЫВАТЬ!!!
    QString typeCurrentDriver = query.value(rec.indexOf("type")).toString();
    currentDriver["type"] = typeCurrentDriver;

    /*Параметры драйвера*/
    QSqlRecord currentItems = ptr->getDrivers()[driverName]->driverContext->record(0);    //делаем QSqlRecord для контекста текущего драйвера
    for (int i = 0; i < 3; i++)
    {
       currentDriver[currentItems.fieldName(i)] = currentItems.value(i).toInt(); //scanRate, queueDepth, stackDepth
    }

    /*Добавление параметров драйвера*/
    QJsonObject parameters;
    parameters[currentItems.fieldName(3)] = currentItems.value(3).toString();    //directory
    parameters[currentItems.fieldName(4)] = currentItems.value(4).toString();    //mode
    currentDriver["parameters"] = parameters;

    return currentDriver;
}
