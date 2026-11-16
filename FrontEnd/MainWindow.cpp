#include "MainWindow.h"
#include <utility>
#include <QTime>
#include <QPushButton>
#include <QMessageBox>
#include <QComboBox>
#include <QString>
#include <QTableWidget>
#include <QHeaderView>
#include "source.h"

MainWindow::MainWindow()
{
    setWindowTitle("Stater Scheduler");
    resize(1000, 600);

    // Create a table with 12 rows and 3 columns
    tableWidget = new QTableWidget(14, 4, this);
    tableWidget->setGeometry(100, 100, 800, 450);

    // Set column headers
    tableWidget->setHorizontalHeaderLabels({
        "Employee Name",
	"Employee Type",
        "Time In",
        "Time Out"
    });

    // Make columns fill the table
    tableWidget->horizontalHeader()
        ->setSectionResizeMode(QHeaderView::Stretch);

    // Create dropdown menus for every row
    for (int row = 0; row < 14; row++)
    {
        // Employee dropdown
        QComboBox *nameInput = new QComboBox();
	nameInput->setEditable(true);
	nameInput->setFrame(false);
        nameInput->addItem("Select employee");
        nameInput->addItems(getEmployees());

	// Employee type dropdown
	QComboBox *typeInput = new QComboBox();
	typeInput->setFrame(false);
	typeInput->addItems({
    		"Select type",
  		    "Checker",
   		        "GMC",
    	     "Courtesy Clerk"
	});

        // Start time dropdown
        QComboBox *timeIn = new QComboBox();
	timeIn->setEditable(true);
	timeIn->setFrame(false);
        timeIn->addItem("Select start time");
        timeIn->addItems(getStartTimes());

        // End time dropdown
        QComboBox *timeOut = new QComboBox();
	timeOut->setEditable(true);
	timeOut->setFrame(false);
        timeOut->addItem("Select end time");
        timeOut->addItems(getEndTimes());

        // Insert dropdowns into the table
        tableWidget->setCellWidget(row, 0, nameInput);
	tableWidget->setCellWidget(row, 1, typeInput);
	tableWidget->setCellWidget(row, 2, timeIn);
	tableWidget->setCellWidget(row, 3, timeOut);    
    }

    QPushButton* submitButton =
    new QPushButton("Submit Employees", this);

    submitButton->setGeometry(400, 555, 200, 35);

    connect(submitButton, &QPushButton::clicked,
        this, [this]()
	{

		std::vector<Checker> newCheckers;
		std::vector<GMC> newGMCs;
		std::vector<CourtesyClerk> newCCs;
		std::vector<assignments> hold_assignments;

    		for (int row = 0; row < tableWidget->rowCount(); row++)
		{
        		QComboBox* nameInput =
      			qobject_cast<QComboBox*>(tableWidget->cellWidget(row, 0));

			QComboBox* typeInput =
   			qobject_cast<QComboBox*>(tableWidget->cellWidget(row, 1));

			QComboBox* timeIn =
    			qobject_cast<QComboBox*>(tableWidget->cellWidget(row, 2));

			QComboBox* timeOut =
    			qobject_cast<QComboBox*>(tableWidget->cellWidget(row, 3));

			if (!nameInput || !typeInput || !timeIn || !timeOut)
			{
				continue;
			}

			// Retrieve the selected values
			QString name = nameInput->currentText().trimmed();
			QString type = typeInput->currentText().trimmed();
			QString start = timeIn->currentText().trimmed();
			QString end = timeOut->currentText().trimmed();

			// Skip empty employee rows
			if (name.isEmpty() || name == "Select employee")
			{
    				continue;
			}

			// Make sure an employee type was selected
			if (type == "Select type")
			{
    				QMessageBox::warning(this,
        			     		     "Missing Information",
       	 			     		     "Please select an employee type for " + name);
    				return;
			}

			// Make sure both times were selected
			if (start.isEmpty() || start == "Select start time" ||
    	    		    end.isEmpty() || end == "Select end time")
			{
 			QMessageBox::warning(this,
        		     		     "Missing Information",
        		     		     "Please enter both times for " + name);
    				return;
			}

			QTime startTime = QTime::fromString(start, "h:map");
			QTime endTime = QTime::fromString(end, "h:map");

			if (!startTime.isValid() || !endTime.isValid())
			{
    				QMessageBox::warning(this,
        					     "Invalid Time",
        				             "Invalid time entered for " + name);
    				return;
			}

			QString formattedStart = startTime.toString("HH:mm");
			QString formattedEnd = endTime.toString("HH:mm");

			std::string employeeName = name.toStdString();
			std::string employeeStart = formattedStart.toStdString();
			std::string employeeEnd = formattedEnd.toStdString();


			if (type == "Checker")
			{
    				getChecker(newCheckers, employeeName, employeeStart, employeeEnd);
			}
			else if (type == "GMC")
			{
    				getGMC(newGMCs, employeeName, employeeStart, employeeEnd);
			}
			else if (type == "Courtesy Clerk")
			{
   				getCC(newCCs, employeeName, employeeStart, employeeEnd);
			}

		}

		hold_Checker = std::move(newCheckers);
		hold_GMC = std::move(newGMCs);
		hold_CC = std::move(newCCs);

		print(hold_Checker, hold_GMC, hold_CC);
		fillAssignments(hold_assignments, hold_GMC, hold_CC);

		QMessageBox::information(this,
    				         "Employees Submitted",
    				         QString("Checkers: %1\nGMCs: %2\nCourtesy Clerks: %3")
					 .arg(hold_Checker.size())
        				 .arg(hold_GMC.size())
        				 .arg(hold_CC.size()));
	});
}

