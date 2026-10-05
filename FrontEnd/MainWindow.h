#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QStringList>

class QLineEdit;

class MainWindow : public QMainWindow
{
public:
    MainWindow();

    QList<QString> getStartTimes(){
	    return startTimes;
    }

    QList<QString> getEndTimes(){
	    return endTimes;
    }

private:
    QComboBox *nameInput;
    QComboBox *timeIn;
    QComboBox *timeOut;
    QList<QString> startTimes = {"6:00am", "6:30am", "7:00am", "7:30am", "8:00am", "8:30am", "9:00am",
	    			 "9:30am", "10:00am", "10:30am", "11:00am", "11:30am", "12:00pm"};
    QList<QString> endTimes = {"2:00pm", "2:30pm", "3:00pm", "3:30pm", "4:00pm", "4:30pm", "5:00pm", 
	                       "5:30pm", "6:00pm", "6:30pm", "7:00pm", "7:30pm", "8:00pm"};
};

#endif // MAINWINDOW_H
