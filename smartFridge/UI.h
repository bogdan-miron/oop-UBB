#pragma once
#include "Services.h"

class UI {

private:
	Services& serv;

public:
	UI(Services& s) : serv(s) {};

	void printMenu();

	void Run();
};
