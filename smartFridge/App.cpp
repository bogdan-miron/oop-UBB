#include <iostream>
#include <crtdbg.h>
#include "UI.h"

int main() {
	
	
	Repository repo;
	Services serv(repo);
	serv.mockData();
	UI ui(serv);
	ui.Run();

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	return 0;
}
