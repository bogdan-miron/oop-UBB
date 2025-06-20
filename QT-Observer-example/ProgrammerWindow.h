#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include "TaskCentralizer.h"

class ProgrammerWindow : public QWidget {
	Q_OBJECT
private:
	TaskCentralizer* taskCentralizer;
	QString windowName; // this will be set to programmer name

	// UI elements
	QVBoxLayout* layout;
	QLabel* nameLabel;
	QLineEdit* taskDescriptionInput;
	QLineEdit* taskStatusInput;
	QLineEdit* assignedProgrammerIdInput;
	QPushButton* addTaskButton;
	QPushButton* removeTaskButton;
	QListWidget* taskListWidget;
public:
	ProgrammerWindow(TaskCentralizer* taskCentralizer, const QString& windowName, QWidget* parent = nullptr) : taskCentralizer(taskCentralizer), windowName(windowName) {
		setupUI();
		connectSignalsAndSlots();
		updateDisplay();
	}

	void setupUI() {
		layout = new QVBoxLayout(this);
		nameLabel = new QLabel(windowName, this);
		taskDescriptionInput = new QLineEdit(this);
		taskDescriptionInput->setPlaceholderText("Task Description");
		taskStatusInput = new QLineEdit(this);
		taskStatusInput->setPlaceholderText("Task Status");
		assignedProgrammerIdInput = new QLineEdit(this);
		assignedProgrammerIdInput->setPlaceholderText("Assigned Programmer ID");
		addTaskButton = new QPushButton("Add Task", this);
		removeTaskButton = new QPushButton("Remove Task", this);
		taskListWidget = new QListWidget(this);
		layout->addWidget(nameLabel);
		layout->addWidget(taskDescriptionInput);
		layout->addWidget(taskStatusInput);
		layout->addWidget(assignedProgrammerIdInput);
		layout->addWidget(addTaskButton);
		layout->addWidget(removeTaskButton);
		layout->addWidget(taskListWidget);
		setLayout(layout);
	}

	void connectSignalsAndSlots() {
		connect(addTaskButton, &QPushButton::clicked, this, &ProgrammerWindow::addTask);
		connect(removeTaskButton, &QPushButton::clicked, this, &ProgrammerWindow::removeTask);
		connect(taskCentralizer, &TaskCentralizer::taskAdded, this, &ProgrammerWindow::updateDisplay);
		connect(taskCentralizer, &TaskCentralizer::taskRemoved, this, &ProgrammerWindow::updateDisplay);
	}
	void addTask() {
		QString description = taskDescriptionInput->text();
		QString status = taskStatusInput->text();
		int assignedProgrammerId = assignedProgrammerIdInput->text().toInt();
		taskCentralizer->addTask(description.toStdString(), status.toStdString(), assignedProgrammerId);
		taskDescriptionInput->clear();
		taskStatusInput->clear();
		assignedProgrammerIdInput->clear();
	}
	void removeTask() {
		QString description = taskDescriptionInput->text();
		taskCentralizer->removeTask(description.toStdString());
		taskDescriptionInput->clear();
	}
	void updateDisplay() {
		taskListWidget->clear();
		for (const auto& task : taskCentralizer->getTasks()) {
			taskListWidget->addItem(QString::fromStdString(task.getDescription()) + " " + QString::fromStdString(task.getStatus()) + " " + QString::number(task.getAssignedProgrammerId()));
			
		}
	}

};
