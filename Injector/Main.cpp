#include <iostream>

#include "Version.h"
#include "Injector.h"

int main(int argc, char **argv) {
	std::cout << "Starting Injector v" + Version::version << std::endl;

	if (argv[1] == NULL) {
		std::cout << "Error: No path specified" << std::endl;
		return -1;
	}

	Injector injector (argv[1]);
	
	int status = injector.inject();

	switch (status) {
		case 0:
			std::cout << "Injected successfully" << std::endl;
			break;
		case -1:
			std::cout << "Injection failed successfully" << std::endl;
			break;
		default:
			std::cout << "Unknown status" << std::endl;
			break;
	}

	return status;
}