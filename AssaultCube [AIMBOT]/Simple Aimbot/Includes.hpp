#include <iostream>
#include <cstdio>
#include "Vector.hpp"
#include "Math.hpp"
#include "Memory.hpp"

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


namespace Features {
	Vec2 CalcAimbot(Player& Local, Player& Enemy) {
		const Vec3 ToCalc = (Local.HeadPosition - Enemy.HeadPosition); // merci la cock i love da math
		Vec2 NewAngles{}; // merci la cock i love da Result

		auto distance = sqrt((ToCalc.x * ToCalc.x) + (ToCalc.y * ToCalc.y));

		const auto hyp_angle = -atan2f(ToCalc.x, ToCalc.y); // if its postive
		NewAngles.x = Math::RadToAng(hyp_angle);

		const auto hypP_angle = atan2f(-ToCalc.z, std::hypot(ToCalc.x, ToCalc.y));
		NewAngles.y = Math::RadToAng(hypP_angle);

		return NewAngles;
	}
	int ClosestPlayer(Player& Local, Player Enemy) {
		if(Local.ViewAngle.x > 90)

		return NULL;
	}
}