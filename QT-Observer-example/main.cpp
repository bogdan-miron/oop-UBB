#include <QtWidgets/QApplication>
#include "Service.h"
#include <iostream>
#include "ProgrammerWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	Service service("programmers.txt", "tasks.txt");

	TaskCentralizer* taskCentralizer = new TaskCentralizer(service);

	for (const auto& programmer : service.getProgrammers()) {
		QString windowName = QString::fromStdString(programmer.getName());
		ProgrammerWindow* programmerWindow = new ProgrammerWindow(taskCentralizer, windowName);
		programmerWindow->setWindowTitle(windowName);
		programmerWindow->show();
	}
    
    return app.exec();
}


