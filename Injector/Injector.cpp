#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <chrono>
#include <thread>
#include <string>
#include <cstdlib>

#include "Injector.h"

#define JUNKS \
__asm _emit 0xd5 \
__asm _emit 0x5c \
__asm _emit 0x3e \
__asm _emit 0xb4 \
__asm _emit 0xa6 \
__asm _emit 0x35 \
__asm _emit 0x19 \
__asm _emit 0x4b \
__asm _emit 0x2a \
__asm _emit 0xf2 \

#define _JUNK_BLOCK(s) __asm jmp s JUNKS __asm s:

using namespace std;

Injector::Injector(string _path) {
	path = _path;
}

int Injector::inject() {
	_JUNK_BLOCK(jmp_label11)

	if (!fileExists((path + ".dll"))) {
		cout << "Error: DLL not found" << endl;
		return -1;
	}

	_JUNK_BLOCK(jmp_label12)
	char myDLL[MAX_PATH];

	_JUNK_BLOCK(jmp_label13)
	GetFullPathName(path.c_str(), MAX_PATH, myDLL, 0);

	_JUNK_BLOCK(jmp_label4)

	DWORD dwProcess = Process("csgo.exe");
	if (dwProcess == 0) {
		cout << "Error: CSGO not found." << endl;
		return -1;
	}

	_JUNK_BLOCK(jmp_label15)
	HANDLE hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, dwProcess);

	_JUNK_BLOCK(jmp_label16)
	LPVOID allocatedMem = VirtualAllocEx(hProcess, NULL, sizeof(myDLL), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	_JUNK_BLOCK(jmp_label17)
	WriteProcessMemory(hProcess, allocatedMem, myDLL, sizeof(myDLL), NULL);

	_JUNK_BLOCK(jmp_label18)
	CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibrary, allocatedMem, 0, 0);

	_JUNK_BLOCK(jmp_label19)
	CloseHandle(hProcess);

	_JUNK_BLOCK(jmp_label20)
	cout << "Injected \"" << path << "\" (pid: " << dwProcess << ")" << endl;
	_JUNK_BLOCK(jmp_label21)
	return 0;
}

inline bool Injector::fileExists(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

DWORD Injector::Process(const char* processName) {
	_JUNK_BLOCK(jmp_label1)
	HANDLE hPID = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	_JUNK_BLOCK(jmp_label2)
	PROCESSENTRY32 ProcEntry;

	_JUNK_BLOCK(jmp_label3)
	ProcEntry.dwSize = sizeof(ProcEntry);

	_JUNK_BLOCK(jmp_label4)
	do
	{
		_JUNK_BLOCK(jmp_label5)
		if (!strcmp(ProcEntry.szExeFile, processName))
		{
			_JUNK_BLOCK(jmp_label6)
			DWORD dwPID = ProcEntry.th32ProcessID;

			_JUNK_BLOCK(jmp_label7)
			CloseHandle(hPID);

			_JUNK_BLOCK(jmp_label8)
			return dwPID;
		}
		_JUNK_BLOCK(jmp_label9)
	} while (Process32Next(hPID, &ProcEntry));
	_JUNK_BLOCK(jmp_label10)
}
