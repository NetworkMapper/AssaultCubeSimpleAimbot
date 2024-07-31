#include "Includes.hpp"
#include "Aimbot.hpp"

int main() {
	auto handle = Mem::GetProcessHandle("ac_client.exe");

	if (handle == nullptr || handle == INVALID_HANDLE_VALUE) {
		MessageBoxA(nullptr, "Error Getting Handle", "Generic Error", 0);
		return 0;
	}

	while (true) {
		Player Local;
		uintptr_t DynamicPlayerAddy;
		uintptr_t DynamicEntityList;

		ReadProcessMemory(handle, reinterpret_cast<void*>(0x50F4F4), &DynamicPlayerAddy, sizeof(DynamicPlayerAddy), 0); // Read Dynamic Address

		ReadProcessMemory(handle, reinterpret_cast<void*>(0x50F4F8), &DynamicEntityList, sizeof(DynamicEntityList), 0); // Read Dynamic Address

		ReadProcessMemory(handle, reinterpret_cast<Player*>(DynamicPlayerAddy), &Local, sizeof(Local), 0); // Read It As A Struct!

		if (GetAsyncKeyState(VK_INSERT)) {
			for (int PlayerIndex = 0; PlayerIndex <= 1; PlayerIndex++) {
				Player Enemy;

				uintptr_t DynamicPlayer2Addy;

				ReadProcessMemory(handle, reinterpret_cast<void*>(DynamicEntityList + (0x4 * PlayerIndex)), &DynamicPlayer2Addy, sizeof(DynamicPlayer2Addy), 0); // Read Dynamic Address

				ReadProcessMemory(handle, reinterpret_cast<Player*>(DynamicPlayer2Addy), &Enemy, sizeof(Enemy), 0); // Read It As A Struct!

				Vec2 Positions = Features::CalcAimbot(Local, Enemy);
				Vec3 ToCalc = (Local.HeadPosition - Enemy.HeadPosition);
				auto distance = sqrt(ToCalc.x * ToCalc.x + ToCalc.y * ToCalc.y);
				if (distance <= 50) {
					WriteProcessMemory(handle, reinterpret_cast<void*>(DynamicPlayerAddy + 0x0040), &Positions.x, sizeof(Positions.x), 0); // Closest Cheat
					WriteProcessMemory(handle, reinterpret_cast<void*>(DynamicPlayerAddy + 0x0044), &Positions.y, sizeof(Positions.y), 0); // Closest Cheat
				}
			}
		}
	}

	if (CloseHandle(handle))
		MessageBeep(2);

	return 0;
}