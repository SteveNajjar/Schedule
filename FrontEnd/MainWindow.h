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
    QLineEdit *nameInput;
    QComboBox *dropDown;
};

#endif // MAINWINDOW_H