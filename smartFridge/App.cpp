#include <iostream>
#include <crtdbg.h>
#include "UI.h"

template<typename T>
void PrintVector(const Vector<T>& vector) {
	for (size_t i = 0; i < vector.Size(); ++i) {
		std::cout << vector[i] << ' ';
	}
	std::cout << '\n';
}

int main() {
	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	Repository repo;
	Services serv(repo);
	serv.mockData();
	UI ui(serv);
	ui.Run();
	
	return 0;
}