#pragma once
#include <string>
#include <vector>

class Programmer {
private:
	std::string name;
	int id;

public:
	Programmer(const std::string& name, int id) : name(name), id(id) {}
	std::string getName() const { return name; }
	int getId() const { return id; }
};

class Task {
private:
	std::string description;
	std::string status; // can be open, in progress, or closed
	int assignedProgrammerId;

public:
	Task(const std::string& description, const std::string& status, int assignedProgrammerId)
		: description(description), status(status), assignedProgrammerId(assignedProgrammerId) {
	}
	std::string getDescription() const { return description; }
	std::string getStatus() const { return status; }
	int getAssignedProgrammerId() const { return assignedProgrammerId; }
	void setStatus(const std::string& newStatus) { status = newStatus; }
};