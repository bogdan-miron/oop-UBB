#pragma once
#include "Service.h"
#include <QObject>

class TaskCentralizer : public QObject {
	Q_OBJECT
private:
	Service& service;

public:
	TaskCentralizer(Service& service) : service(service) {}
	
	void addTask(const std::string& description, const std::string& status, int assignedProgrammerId) {
		service.addTask(description, status, assignedProgrammerId);
		emit taskAdded(description, status, assignedProgrammerId);
	}

	void removeTask(const std::string& description) {
		service.removeTask(description);
		emit taskRemoved(description);
	}

	std::vector<Task> getTasks() {
		return service.getTasks();
	}

signals:
	void taskAdded(const std::string& description, const std::string& status, int assignedProgrammerId);
	void taskRemoved(const std::string& description);

};
