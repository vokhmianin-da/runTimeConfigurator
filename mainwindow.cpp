#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      driverParamsTemplates
          {
            {"LoggerDriver", "CREATE TABLE '%1' (directory TEXT, mode TEXT)"}
          },
      driverTagContextTemplates
          {
            {"LoggerDriver", "CREATE TABLE '%1' (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, accuracy TEXT, aperture TEXT, description TEXT, units TEXT)"}
          }
{
    ui->setupUi(this);

    if(!createConnection()) return; //создание БД
    QSqlQuery query;
    QString strQuery = "CREATE TABLE 'Драйверы' ("
                       "id INTEGER PRIMARY KEY NOT NULL,"
            "name TEXT UNIQUE,"
            "type TEXT);";
    query.exec(strQuery);
    tableDrivers = new QTableView;
    modelDrivers = new QSqlQueryModel;
    layBases = new QHBoxLayout;
    layBases->addWidget(tableDrivers);
    tableDrivers->setModel(modelDrivers);
    modelDrivers->setQuery("SELECT * FROM 'Драйверы';");

    ui->tab_2->setLayout(layBases);


    /*Тест создания json-файла*/
//    //ССылочка на работу с QJson - https://evileg.com/ru/post/419/
//    // Создаём объект текста
//    QJsonObject textObject;
//    textObject["scanrate"] = 200;                // Устанавливаем заголовок текста
//    textObject["type"] = "LogicDriver";     // Устанавливаем содержание текста

//    QJsonArray mapArr;
//    mapArr.append(textObject);
//    textObject["mappings"] = mapArr;


//    QJsonArray textsArray = m_currentJsonObject["drivers"].toArray(); // Забираем текущий массив текстов, даже если он не существует, он будет создан автоматически

//    QJsonArray arr1;
//    arr1.append(textObject);
//    arr1.append(textObject);
//    m_currentJsonObject["devices"] = arr1;

//    textsArray.append(textObject);                                  // Добавляем объект текста в массив
//    m_currentJsonObject["drivers"] = textsArray;                      // Сохраняем массив обратно в текущий объект


//    QString saveFileName = QFileDialog::getSaveFileName(this,
//                                                        tr("Save Json File"),
//                                                        QString(),
//                                                        tr("JSON (*.json)"));
//    QFileInfo fileInfo(saveFileName);   // С помощью QFileInfo
//    QDir::setCurrent(fileInfo.path());  // установим текущую рабочую директорию, где будет файл, иначе может не заработать
//    // Создаём объект файла и открываем его на запись
//    QFile jsonFile(saveFileName);
//    if (!jsonFile.open(QIODevice::WriteOnly))
//    {
//        return;
//    }

//    // Записываем текущий объект Json в файл
//    jsonFile.write(QJsonDocument(m_currentJsonObject).toJson(QJsonDocument::Indented));
//    jsonFile.close();   // Закрываем файл
}

bool MainWindow::createConnection()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("RunTime.db");
    if(!db.open())
    {
        qDebug() << "НЕ удалось открыть БД";
        return false;
    }
    return true;
}

bool MainWindow::createDriver(QString driverName, QString driverType)
{
    QSqlQuery query;
    QString strQuery;

    QString strF = "INSERT INTO 'Драйверы' (id, name, type)"
                   "VALUES('%1', '%2', '%3');";
    strQuery = strF.arg(ui->cbDrivers->count()).arg(driverName).arg(driverType);
    if (!query.exec(strQuery)){
            qDebug() << "Такой драйвер уже есть";
            return false;
        }
    ui->cbDrivers->addItem(driverName); //добавление нового драйвера в checkBox
    modelDrivers->setQuery("SELECT * FROM 'Драйверы';");
    return true;
}

bool MainWindow::removeDriver(QString driverName)
{
    if (driverName.isEmpty())
    {
        qDebug() << "Такого драйвера нет";
        return false;
    }

    QSqlQuery query;
    QString strQuery;

    QString strF = "DELETE FROM 'Драйверы' WHERE "
                   "name = '%1';";
    strQuery = strF.arg(driverName);
    if (!query.exec(strQuery)){
            qDebug() << "Такого драйвера нет";
            return false;
        }
    ui->cbDrivers->removeItem(ui->cbDrivers->currentIndex()); //удаление драйвера из checkBox
    modelDrivers->setQuery("SELECT * FROM 'Драйверы';");
    return true;
}

bool MainWindow::createDriverContext(QString driverName, QString driverType, FormDriverTables *ptrNewDriver) //Создание контекста драйвера
{
    QString temp;
    QSqlQuery query;
    QString strQuery;

    temp = driverName + "ContextDriver";
    strQuery =  driverParamsTemplates[driverType].arg(temp);
    if (!query.exec(strQuery)){
            qDebug() << "Не удалось создать таблицу " + temp;
            return false;
        }

    ptrNewDriver->driverContext = new QSqlTableModel(ptrNewDriver);
    ptrNewDriver->driverContext->setTable(temp);
    ptrNewDriver->getPtrDriverContext()->setModel(ptrNewDriver->driverContext);
    ptrNewDriver->driverContext->setEditStrategy(QSqlTableModel::OnManualSubmit);   //запись изменений по вызову submitAll(), отмена - revertAll()

    /*Добавление новой (и единственной для драйвера) строки*/
    int lastRow = ptrNewDriver->driverContext->rowCount();
    ptrNewDriver->driverContext->insertRow(lastRow);
    //ptrNewDriver->driverContext->setData(ptrNewDriver->driverContext->index(lastRow,0),2);
    return true;
}

bool MainWindow::createTagContext(QString driverName, QString driverType, FormDriverTables *ptrNewDriver)  //Создание контекста тэгов для драйвера
{
    QString temp;
    QSqlQuery query;
    QString strQuery;

    temp = driverName + "ContextTag";
    strQuery =  driverTagContextTemplates[driverType].arg(temp);
    if (!query.exec(strQuery)){
            qDebug() << "Не удалось создать таблицу " + temp;
            return false;
        }
    ptrNewDriver->tagContext = new QSqlTableModel(ptrNewDriver);
    ptrNewDriver->tagContext->setTable(temp);
    ptrNewDriver->tagContext->setEditStrategy(QSqlTableModel::OnFieldChange);   //запись изменений по нажатию ENTER в поле ввода ячейки или при смене строки
    ptrNewDriver->getPtrTagContext()->setModel(ptrNewDriver->tagContext);
    return true;
}

bool MainWindow::removeDriverContext(QString driverName)
{
    QSqlQuery query;
    QString strQuery;
    QString temp;

    /*Удаление контекста драйвера*/
    temp = driverName + "ContextDriver";
    strQuery =  "DROP TABLE '" + temp + "';";
    if (!query.exec(strQuery)){
            qDebug() << "Не удалось удалить таблицу " + temp;
            return false;
        }
    return true;
}

bool MainWindow::removeTagContext(QString driverName)
{
    QSqlQuery query;
    QString strQuery;
    QString temp;

    temp = driverName + "ContextTag";
    strQuery =  "DROP TABLE '" + temp + "';";
    if (!query.exec(strQuery)){
            qDebug() << "Не удалось удалить таблицу " + temp;
            return false;
        }
    return true;
}

MainWindow::~MainWindow()
{
    /*Удаление файла БД*/
    QFile dbFile("RunTime.db");
    db.removeDatabase(db.connectionName());
    dbFile.remove();
    /////////////////////
    delete ui;
}


void MainWindow::on_pbAddDriver_clicked()   //создать драйвер
{
    QString driverName = ui->leDriverName->text();
    QString driverType = ui->cbDriverTypes->currentText();

    /*Добавление нового драйвера в таблицу драйверов*/
    if (!createDriver(driverName, driverType)) return;

    /*Создание таблиц с контекстом драйверов*/
    FormDriverTables *ptrNewDriver = new FormDriverTables(this);
    drivers[driverName] = ptrNewDriver; //сохраняем указатель в общем списке
    ui->tabWidget->addTab(ptrNewDriver, driverName);    //добавляем новую вкладку

    /*Создание контекста драйвера*/
    if(!createDriverContext(driverName, driverType, ptrNewDriver)) return;

    /*Создание контекста тэгов*/
    if (!createTagContext(driverName, driverType, ptrNewDriver)) return;
}

void MainWindow::on_pbDeleteDriver_clicked()    //удалить драйвер
{
    QString driverName = ui->cbDrivers->currentText();

    /*Удаление драйвера из таблицы драйверов*/
    if(!removeDriver(driverName)) return;

    /*Удаление контекста драйвера*/
    if(!removeDriverContext(driverName)) return;

    /*Удаление контекста тэгов*/
    if (!removeTagContext(driverName)) return;

    /*Удаление таблиц с контекстом драйверов*/
    ui->tabWidget->removeTab(ui->tabWidget->indexOf(drivers[driverName]));    //удаляем вкладку

    /*Очистка памяти*/
    delete drivers[driverName]->driverContext;
    delete drivers[driverName]->tagContext;
    delete drivers[driverName];
    ////////////////////////////////////////////

    drivers.remove(driverName); //удаляем указатель из общего списка
}
