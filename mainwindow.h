#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFileSystemModel>
#include <QDir>
#include <QList>
#include <QPair>
#include "linkedlist.h"
#include "logger.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
class LinkedList;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSelectFileClicked();
    void onScanFileClicked();

signals:
    void setPath(const QString& filePath);
    void sortWords();
    void showSortWords();

private:
    Ui::MainWindow *ui;
    QFileSystemModel *model;
    QString filePath_;
    LinkedList<QString> latinWords_;
    LinkedList<QPair<QString, int>> sortedWords_;
};
#endif // MAINWINDOW_H
