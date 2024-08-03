#include <Windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <optional>

namespace Mem {
	HANDLE GetProcessHandle(const CHAR* name) {

		PROCESSENTRY32 entry{ entry.dwSize = sizeof(PROCESSENTRY32) };
		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		if (Process32First(snapshot, &entry)) {
			do {
				if (strcmp(entry.szExeFile, name) == 0) {
					return OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
				}
			} while (Process32Next(snapshot, &entry));
		}

		return nullptr;
	}
	std::optional<uint32_t> GetProcessId(const CHAR* name) {
		PROCESSENTRY32 entry{ entry.dwSize = sizeof(PROCESSENTRY32) };

		auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		if (Process32First(snapshot, &entry)) {
			do {
				if (strcmp(entry.szExeFile, name) == 0) {
					return entry.th32ProcessID;
				}
			} while (Process32Next(snapshot, &entry));
		}

		return 0;
	}
	std::optional<uintptr_t> GetModuleBase(uint32_t pid, const CHAR* name) {
		MODULEENTRY32 entry{ entry.dwSize = sizeof(MODULEENTRY32) };

		auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE32, pid);

		if (Module32First(snapshot, &entry)) {
			do {
				if (strcmp(entry.szModule, name) == 0) {
					return reinterpret_cast<uintptr_t>(entry.modBaseAddr);
				}
			} while (Module32Next(snapshot, &entry));
		}

		return NULL;
	}
}
