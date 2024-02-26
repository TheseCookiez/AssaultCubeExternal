#pragma once

namespace HackStructs {

	struct PlayerStruct {
		// Player health and armor
		int playerHealth = 100;			// Default health value
		int playerArmor = 100;
		// Padding for unknown values
		int padding1[4] = {};
		// Int for toggling akimbo pistols
		int playerAkimboEnable = 0;
		// Player weapon reserve ammo 
		int playerKnifeAmmo = 1;
		int playerPistolAmmo = 0;
		int playerTMPAmmo = 0;
		int playerShotgunAmmo = 0;
		int playerSMGAmmo = 0;
		int playerSniperAmmo = 0;
		int padding2 = 0;				// unknown value
		int playerAkimboAmmo = 0;
	};

	struct InfiniteAmmo {
		// Player weapon clips
		int playerKnifeClip = 20;
		int playerPisolClip = 20;
		int playerTMPClip = 20;
		int playerShotgunClip = 20;
		int playerSMGClip = 20;
		int playerSniperClip = 20;
		int playerRifleclip = 20;
		int playerGrenadesClip = 20; 	// Player grenades
		int playerAkimboClip = 20;
	};

	struct GodMode {
		// Player health and armor
		int playerHealth = 100;
		int playerArmor = 100;
	};
}