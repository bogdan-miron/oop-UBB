#pragma once
#include "Domain.h"
#include <fstream>

class Service {
private:
	std::vector<Programmer> programmers;
	std::vector<Task> tasks;
	std::string filename1, filename2;

public:
	Service() {
		filename1 = "programmers.txt";
		filename2 = "tasks.txt";
		readProgrammers(filename1);
		readTasks(filename2);
	}
	Service(const std::string& filename1, const std::string& filename2) : filename1(filename1), filename2(filename2) {
		readProgrammers(filename1);
		readTasks(filename2);
	}

	~Service() {
		writeProgrammers(filename1);
		writeTasks(filename2);
	}
	void addProgrammer(const std::string& name, int id) {
		programmers.emplace_back(name, id);
	}
	void addTask(const std::string& description, const std::string& status, int assignedProgrammerId) {
		tasks.emplace_back(description, status, assignedProgrammerId);
	}
	void removeTask(const std::string& description) {
		for (auto it = tasks.begin(); it != tasks.end(); ++it) {
			if (it->getDescription() == description) {
				tasks.erase(it);
				return;
			}
		}
	}

	std::vector<Programmer> getProgrammers() const {
		return programmers;
	}
	std::vector<Task> getTasks() const {
		return tasks;
	}
	void updateTaskStatus(int taskIndex, const std::string& newStatus) {
		if (taskIndex >= 0 && taskIndex < tasks.size()) {
			tasks[taskIndex].setStatus(newStatus);
		}
	}

	void readProgrammers(const std::string& filename) {
		std::ifstream fin(filename);
		if (!fin.is_open()) {
			throw std::runtime_error("Could not open file: " + filename);
		}
		std::string name;
		int id;
		while (fin >> name >> id) {
			programmers.emplace_back(name, id);
		}
		fin.close();
	}

	void writeProgrammers(const std::string& filename) const {
		std::ofstream fout(filename);
		if (!fout.is_open()) {
			throw std::runtime_error("Could not open file: " + filename);
		}
		for (const auto& programmer : programmers) {
			fout << programmer.getName() << " " << programmer.getId() << "\n";
		}
		fout.close();
	}

	void readTasks(const std::string& filename) {
		std::ifstream fin(filename);
		if (!fin.is_open()) {
			throw std::runtime_error("Could not open file: " + filename);
		}
		std::string description, status;
		int assignedProgrammerId;
		while (fin >> description >> status >> assignedProgrammerId) {
			tasks.emplace_back(description, status, assignedProgrammerId);
		}
		fin.close();
	}

	void writeTasks(const std::string& filename) const {
		std::ofstream fout(filename);
		if (!fout.is_open()) {
			throw std::runtime_error("Could not open file: " + filename);
		}
		for (const auto& task : tasks) {
			fout << task.getDescription() << " " << task.getStatus() << " " << task.getAssignedProgrammerId() << "\n";
		}
		fout.close();
	}
};
