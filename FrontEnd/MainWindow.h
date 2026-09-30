#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>

class QLineEdit;

class MainWindow : public QMainWindow
{
public:
    MainWindow();
private:
    QComboBox *nameInput;
    QComboBox *timeIn;
    QComboBox *timeOut;
};

#endif // MAINWINDOW_H
