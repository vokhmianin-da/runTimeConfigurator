#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      driverParamsTemplates
          {
            {"LoggerDriver", "CREATE TABLE '%1' (id INTEGER PRIMARY KEY NOT NULL, directory TEXT, mode TEXT)"}
          },
      driverTagContextTemplates
          {
            {"LoggerDriver", "CREATE TABLE '%1' (id INTEGER PRIMARY KEY NOT NULL, accuracy TEXT, aperture TEXT, description TEXT, units TEXT)"}
          }
{
    ui->setupUi(this);

    if(!createConnection()) return; //создание БД
    QSqlQuery query;
    QString strQuery = "CREATE TABLE 'Драйверы' ("
                       "id INTEGER PRIMARY KEY NOT NULL,"
            "'Имя драйвера' TEXT,"
            "'Тип драйвера' TEXT);";
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

MainWindow::~MainWindow()
{
//    QFile dbFile("RunTime.db");
//    db.removeDatabase(db.connectionName());
//    dbFile.remove();    //удаление файла БД
    delete ui;
}


void MainWindow::on_pbAddDriver_clicked()   //создать драйвер
{
    ui->cbDrivers->addItem(ui->leDriverName->text());

    QSqlQuery query;
    QString strQuery;

    QString strF = "INSERT INTO 'Драйверы' (id, 'Имя драйвера', 'Тип драйвера')"
                   "VALUES('%1', '%2', '%3');";
    strQuery = strF.arg(ui->cbDrivers->count()).arg(ui->leDriverName->text()).arg(ui->cbDriverTypes->currentData().String);
    if (!query.exec(strQuery)){
            qDebug() << "Не удалось вставить запись";
        }
    modelDrivers->setQuery("SELECT * FROM 'Драйверы';");

    /*Создание контекста драйвера*/
    strQuery =  driverParamsTemplates["LoggerDriver"].arg(ui->leDriverName->text());
    if (!query.exec(strQuery)){
            qDebug() << "Не удалось вставить запись";
        }
    QSqlTableModel* ptrDriverContextModel = new QSqlTableModel;
    DriversContest[ui->leDriverName->text()] = ptrDriverContextModel;   //добавление указателя на контекст драйвера в общий map
    ptrDriverContextModel->setTable(ui->leDriverName->text());
    QTableView* ptrDriverContextView = new QTableView;
    ptrDriverContextView->setModel(ptrDriverContextModel);
    layBases->addWidget(ptrDriverContextView);
}
