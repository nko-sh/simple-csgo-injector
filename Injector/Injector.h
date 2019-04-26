#pragma once
#include <string>
#include <windows.h>

class Injector {
public:
	Injector(std::string path);
	int inject();
private:
	std::string path;
	DWORD Process(const char* processName);
	inline bool fileExists(const std::string& name);
};
