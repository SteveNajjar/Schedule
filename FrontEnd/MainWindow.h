#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QStringList>

class QList;
class QLineEdit;

class MainWindow : public QMainWindow
{
public:
    MainWindow();
private:
    QComboBox *nameInput;
    QComboBox *timeIn;
    QComboBox *timeOut;
    QStringList *times;
    QStringList *names;
    QList *employees;
};

#endif // MAINWINDOW_H
