#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <QString>
#include <QFileDialog>
#include <QRegularExpression>
#include <QTextStream>
#include <QPair>
#include <algorithm>
#include <QStringList>
#include <QDir>
#include "linkedlist.h"
#include <QStandardPaths>
#include "logger.h"

#include <QList>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->selectFile, &QPushButton::clicked, this, onSelectFileClicked); // нажал кнопку чтобы выбрать файл
    connect(this, &MainWindow::setPath,[this](QString filePath){
        ui->showfile->setText(filePath);    // отобразил путь к файлу
        ui->startButton->setEnabled(true);  // активировал кнопку сканирования
    });
    connect(ui->startButton, &QPushButton::clicked, this, onScanFileClicked); // начал сканирование
    connect(this, &MainWindow::showSortWords, [this](){

        QString filePath = QDir::currentPath() + "/ResultPairs.txt"; // в папке build (чтобы в "докуметах" -> закоментить эту и раскоментить следующую)
        // QString filePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/ResultPairs.txt";

        try
        {
            QFile file(filePath);
            QString line = sortedWords_.listToStr();

            if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                logger.log(Logger::ERROR, "File was not opened");
            }

            logger.log(Logger::WARNING, "the programm is closed");
            logger.log(Logger::ERROR, "the programm is closed");
            logger.log(Logger::INFO, "the file is opened");
            QTextStream out(&file);
            out << line;
            file.close();
        }
        catch (const std::exception& e)
        {
            logger.log(Logger::ERROR, e.what());
        }

        ui->textEnglish->setText(sortedWords_.listToStr());
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSelectFileClicked()
{
    logger.log(Logger::INFO, "onSelectFileClicked");
    filePath_ = QFileDialog::getOpenFileName(nullptr, "Выберите файл", QString(), "Text Files (*.txt);;All Files (*)"); // выбрал файл
    logger.log(Logger::INFO, "filePath_: ", filePath_);
    emit setPath(filePath_); // кинул сигнал
}

void MainWindow::onScanFileClicked()
{
    logger.log(Logger::INFO, "onScanFileClicked");
    latinWords_ = LinkedList<QString>(); // для обнуления

    try
    {
        QFile file(filePath_);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            logger.log(Logger::ERROR, "File was not opened");
        }

        QTextStream in(&file);
        while (!in.atEnd()) // прогоняю весь файл до конца
        {
            QString line = in.readLine();
            QStringList words = line.split(QRegularExpression("\\s+"), QString::SkipEmptyParts);  // делю по пробелам и закидываем в массив

            for (const QString& word : words)
            {
                if (QRegularExpression("^[a-zA-Z]+$").match(word).hasMatch() && word.length() <= 50) // ищу латинские слова  с длиной <=50
                {
                    latinWords_.append(word); // добавляю в свой лист( поле в классе)
                }
            }
        }

        file.close();
        sortedWords_ = latinWords_.countWords(); // добавил в массив (поле класса )
        emit showSortWords();
    }
    catch (const std::exception& exception)
    {
        logger.log(Logger::ERROR, exception.what());
    }
}




