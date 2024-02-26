#pragma once
#include <Windows.h>
#include <iostream>

//Thx cazz

class Memory {
	DWORD id = 0; // Id of process
	HANDLE process = NULL; // Handle to the process

public:
	Memory(const char* processName);
	~Memory();

	DWORD GetProcessId();
	HANDLE GetProcessHandle();

	uintptr_t GetModuleAddress(const char* moduleName);

	template <typename T>
	T ReadWithSize(uintptr_t address, int size) {
		T value;
		ReadProcessMemory(this->process, (LPVOID)address, &value, size , NULL);

		return value;
	}


	template <typename T>
	T Read(uintptr_t address) {
		T value;
		ReadProcessMemory(this->process, (LPVOID)address, &value, sizeof(T), NULL);

		return value;
	}

	template <typename T>
	bool Write(uintptr_t address, T value) {

		return WriteProcessMemory(this->process, (LPVOID)address, &value, sizeof(T), NULL);
	}

};