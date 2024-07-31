//
//
//namespace Aimbot {
//	Vec2 CalcAimbot(Player& Local, Player& Enemy) {
//		const Vec3 ToCalc = (Local.HeadPosition - Enemy.HeadPosition); // merci la cock i love da math
//		Vec2 NewAngles{}; // merci la cock i love da Result
//
//		const auto hyp_angle = -atan2f(ToCalc.x, ToCalc.y); // if its postive
//		NewAngles.x = Math::RadToAng(hyp_angle);
//
//		const auto hypP_angle = atan2f(ToCalc.z, ToCalc.y);
//		std::cout << hypP_angle;
//		if (hypP_angle > 3) {
//			//NewAngles.y = Math::RadToAng(hypP_angle) - 180;
//		}
//		else {
//			//NewAngles.y = Math::RadToAng(hypP_angle);
//		}
//
//
//		return NewAngles;
//	}
//}