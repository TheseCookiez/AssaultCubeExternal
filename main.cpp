#include "memory.h"
#include <thread>
#include <conio.h>
#include "localplayer.h"


namespace offsets {
	// ptr to local player struct
	constexpr auto localPlayer = 0x17E0A8;
	// ptrs to values in localplayer structs
	constexpr auto playerHealth = 0xEC;
	constexpr auto playerArmor = 0xF0;
	constexpr auto playerPistolAmmo = 0x12C;
	constexpr auto playerTMPCarbineAmmo = 0x130;
	constexpr auto playerSMGAmmo = 0x138;
	constexpr auto playerSniperAmmo = 0x13C;
	constexpr auto playerRifleAmmo = 0x140;
	constexpr auto playerGrenades = 0x144;
	constexpr auto playerClipSection = 0x128;
	constexpr auto playerAkimboToggle = 0x100;

}

bool toggleCheat = false;

void getKeyStates() {
	if (GetAsyncKeyState(VK_HOME)) {
		std::cout << "Toggle: ON\n";
		toggleCheat = true;
	}

	if (GetAsyncKeyState(VK_END)) {
		std::cout << "Toggle: OFF\n";
		toggleCheat = false;
	}
}

int main() {
	
	int infinitAmmo[9] = { 20 };

	// Init class with the name of the target process
	auto mem = Memory("ac_client.exe");
	// Get a handle to the process
	std::cout << "Process id: " << mem.GetProcessId() << "\n";
	// Get the module address (base address of the module) (exe or dll)
	const auto client = mem.GetModuleAddress("ac_client.exe");
	std::cout << "Module id: " << "0x" << std::hex << client << std::dec << "\n";

	const auto localPlayer = mem.Read<uintptr_t>(client + offsets::localPlayer);
	std::cout << "Local player offset: " << std::hex << localPlayer << std::dec << "\n";

	const auto playerHealth = mem.Read<uintptr_t>(localPlayer + offsets::playerHealth);
	std::cout << "Player health value: " << playerHealth << "\n";

	const auto playerRifleAmmo = mem.Read<uintptr_t>(localPlayer + offsets::playerRifleAmmo);
	std::cout << "Player Rifle ammo value: " << playerRifleAmmo << "\n";

	const auto playerstruct = mem.ReadWithSize<HackStructs::PlayerStruct>(localPlayer + offsets::playerHealth, sizeof(HackStructs::PlayerStruct));
	std::cout << "Player struct: " << playerstruct.playerArmor << "\n";
	std::cout << "Player struct: " << playerstruct.playerHealth << "\n";


	const auto godMode = HackStructs::GodMode();
	const auto infiniteAmmo = HackStructs::InfiniteAmmo();


	while (true) {

		getKeyStates();

		if (toggleCheat) {
			mem.Write<HackStructs::GodMode>(localPlayer + offsets::playerHealth, godMode);
			mem.Write<HackStructs::InfiniteAmmo>(localPlayer + offsets::playerClipSection, infiniteAmmo);

		if (GetAsyncKeyState(VK_SPACE)) 
			keybd_event(VK_SPACE, 0, 0, 0); // Press Spacebar

		}

		std::this_thread::sleep_for(std::chrono::milliseconds(10));

	}

	return 0;
}