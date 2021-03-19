#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*Тест создания json-файла*/
    //ССылочка на работу с QJson - https://evileg.com/ru/post/419/
    // Создаём объект текста
    QJsonObject textObject;
    textObject["scanrate"] = 200;                // Устанавливаем заголовок текста
    textObject["type"] = "LogicDriver";     // Устанавливаем содержание текста

    QJsonArray mapArr;
    mapArr.append(textObject);
    textObject["mappings"] = mapArr;


    QJsonArray textsArray = m_currentJsonObject["drivers"].toArray(); // Забираем текущий массив текстов, даже если он не существует, он будет создан автоматически

    QJsonArray arr1;
    arr1.append(textObject);
    arr1.append(textObject);
    m_currentJsonObject["devices"] = arr1;

    textsArray.append(textObject);                                  // Добавляем объект текста в массив
    m_currentJsonObject["drivers"] = textsArray;                      // Сохраняем массив обратно в текущий объект


    QString saveFileName = QFileDialog::getSaveFileName(this,
                                                        tr("Save Json File"),
                                                        QString(),
                                                        tr("JSON (*.json)"));
    QFileInfo fileInfo(saveFileName);   // С помощью QFileInfo
    QDir::setCurrent(fileInfo.path());  // установим текущую рабочую директорию, где будет файл, иначе может не заработать
    // Создаём объект файла и открываем его на запись
    QFile jsonFile(saveFileName);
    if (!jsonFile.open(QIODevice::WriteOnly))
    {
        return;
    }

    // Записываем текущий объект Json в файл
    jsonFile.write(QJsonDocument(m_currentJsonObject).toJson(QJsonDocument::Indented));
    jsonFile.close();   // Закрываем файл
}

MainWindow::~MainWindow()
{
    delete ui;
}

