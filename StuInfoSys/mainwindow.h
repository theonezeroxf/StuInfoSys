#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>
#include <QDebug>
#include <QTableWidgetSelectionRange>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase db;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QList<QTableWidgetSelectionRange> selectedList;
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
