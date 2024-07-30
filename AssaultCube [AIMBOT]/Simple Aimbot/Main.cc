#include "Includes.hpp"

HANDLE GetProcessHandle(const TCHAR *name) {

    PROCESSENTRY32 entry { };
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (Process32First(snapshot, &entry)) {
        do {
            if (_tcscmp(entry.szExeFile, name) == 0) {
                return OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
            }
        } while (Process32Next(snapshot, &entry));
    }

    return nullptr;
}

struct Player {
	char pad_0000[4]; //0x0000
	Vec3 HeadPosition; //0x0004
	Vec3 InputVelocity; //0x0010
	char pad_001C[12]; //0x001C
	Vec3 RealVelocity; //0x0028
	Vec3 FootPosition; //0x0034
	Vec3 ViewAngle; //0x0040
	char pad_004C[28]; //0x004C
	int32_t Jumping; //0x0068
	char pad_006C[4]; //0x006C
	int32_t bIsJumping; //0x0070
	char pad_0074[160]; //0x0074
	int32_t PistolChamberAmmo; //0x0114
	int32_t CarbineChamberAmmo; //0x0118
	int32_t ShotgunChamberAmmo; //0x011C
	int32_t SubmaChamberAmmo; //0x0120
	int32_t SniperChamberAmmo; //0x0124
	int32_t ArChambeAmmo; //0x0128
	char pad_012C[8]; //0x012C
	int32_t SpecialChamberAmmo; //0x0134
	char pad_0138[4]; //0x0138
	int32_t PistolAmmo; //0x013C
	int32_t CarabinAmmo; //0x0140
	int32_t ShootgunAmmo; //0x0144
	int32_t submaAmmo; //0x0148
	int32_t SniperAmmo; //0x014C
	int32_t ArAmmo; //0x0150
	char pad_0154[4]; //0x0154
	int32_t GranadeAmmo; //0x0158
	int32_t SpecialAmmo; //0x015C
	int32_t KnifeDelay; //0x0160
	int32_t PistolDelay; //0x0164
	int32_t CarabinDelay; //0x0168
	int32_t ShotgunDelay; //0x016C
	int32_t SubmaDelay; //0x0170
	int32_t SniperDelay; //0x0174
	int32_t ArDelay; //0x0178
	char pad_017C[4]; //0x017C
	int32_t GranadeDelay; //0x0180
	int32_t SpecialDelay; //0x0184
	int32_t TimesKnifeUsed; //0x0188
	int32_t TimesPistolShoot; //0x018C
	int32_t TimesCarabinShoot; //0x0190
	int32_t TimesSchotgunShoot; //0x0194
	int32_t TimesSubmaShoot; //0x0198
	int32_t TimesSniperShoot; //0x019C
	int32_t TimesArShoot; //0x01A0
	char pad_01A4[4]; //0x01A4
	int32_t TimesGranadeShoot; //0x01A8
	int32_t TimesSpecialShoot; //0x01AC
	char pad_01B0[456]; //0x01B0
	class CurrentWeapon* CurrentWeaponptr; //0x0378
};

inline float RadToAng(float Rad) {
    return (Rad * (180.0 / M_PI)); // merci la cock i love da math
}

inline float AngToRad(float Rad) {
    return (Rad / (180.0 * M_PI)); // merci la cock i love da math
}

Vec2 CalcAimbot(Player& Local, Player& Enemy) {
    Vec3 ToCalc = (Local.HeadPosition - Enemy.HeadPosition); // merci la cock i love da math
    Vec2 NewAngles{}; // merci la cock i love da Result

    auto hyp_angle = -atan2f(ToCalc.x, ToCalc.y); // if its postive
    NewAngles.x = RadToAng(hyp_angle);

	auto hypP_angle = atan2f(ToCalc.y, ToCalc.z);
	NewAngles.y = RadToAng(hypP_angle);
    return NewAngles;
}

int main() {
    HANDLE handle = GetProcessHandle("ac_client.exe");

	if (handle == nullptr || handle == INVALID_HANDLE_VALUE) {
		return 0;
	}

    while (true) {
		Player Local;
		uintptr_t DynamicPlayerAddy;
		uintptr_t DynamicEntityList;

		ReadProcessMemory(handle, reinterpret_cast<void*>(0x50F4F4), &DynamicPlayerAddy, sizeof(DynamicPlayerAddy), 0); // Read Dynamic Address

	    ReadProcessMemory(handle, reinterpret_cast<void*>(0x50F4F8), &DynamicEntityList, sizeof(DynamicEntityList), 0); // Read Dynamic Address

		ReadProcessMemory(handle, reinterpret_cast<Player*>(DynamicPlayerAddy), &Local, sizeof(Local), 0); // Read It As A Struct!

		for (int PlayerIndex = 0; PlayerIndex <= 1; PlayerIndex++) {
			Player Enemy;

			uintptr_t DynamicPlayer2Addy;

			ReadProcessMemory(handle, reinterpret_cast<void*>(DynamicEntityList + (PlayerIndex * 0x4)), &DynamicPlayer2Addy, sizeof(DynamicPlayer2Addy), 0); // Read Dynamic Address

			ReadProcessMemory(handle, reinterpret_cast<Player*>(DynamicPlayer2Addy), &Enemy, sizeof(Enemy), 0); // Read It As A Struct!

			Vec2 Positions = CalcAimbot(Local, Enemy);
			Vec3 ToCalc = (Local.HeadPosition - Enemy.HeadPosition);
			float distance = sqrt(ToCalc.x*ToCalc.x + ToCalc.y*ToCalc.y);
			if (distance <= 10) {
				WriteProcessMemory(handle, reinterpret_cast<void*>(DynamicPlayerAddy + 0x0040), &Positions.x, sizeof(Positions.x), 0); // Closest Cheat
				WriteProcessMemory(handle, reinterpret_cast<void*>(DynamicPlayerAddy + 0x0044), &Positions.y, sizeof(Positions.y), 0); // Closest Cheat
			}
		}
    }
    return 0;
}
