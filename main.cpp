#include "stdafx.hpp"

const char * result;

/*
Round Manager Backup: 48 8b 05 ? ? ? ? 8b 90 e8 02 
*/

void __fastcall MainThread(HMODULE current_module)
{
	AllocConsole();
	FILE* console;
	freopen_s(&console, "CONOUT$", "w", stdout);

	SetConsoleTitleA("Lion Dumper R6 | F1 To Close");

	Memory::CreateOffset("GameManager", "48 8B 05 ? ? ? ? 8B 8E");
	Memory::CreateOffset("FovManager", "48 8b 05 ? ? ? ? f3 44 0f 10 91");
	Memory::CreateOffset("RoundManager", "48 8b 05 ? ? ? ? 8b 90 ? ? ? ? 83 3d");
	Memory::CreateOffset("GlowManager", "48 8b 0d ? ? ? ? 48 8b d7 e8 ? ? ? ? 48 85 c0");
	Memory::CreateOffset("ProfileManager", "48 8B 05 ? ? ? ? 33 D2 4C 8B 40 78");
	Memory::CreateOffset("VTMarker", "4c 8d 0d ? ? ? ? 48 ? ? ? 48 8d 8b ? ? ? ? 4c ? ? 48 8d ? ? ? ? ? e8");
	Memory::CreateOffset("NetworkManager", "48 8b 05 ? ? ? ? 48 85 c0 0f 84 ? ? ? ? 48 8b 88 ? ? ? ? 48 85 c9 0f 84 ? ? ? ? 4c 8b 8d");

	std::cout << std::endl;

	Memory::CreateOffset("InstantAnimationManager", "48 8B 05 ? ? ? ? 41 0F B6 F8 8B DA");
	Memory::CreateOffset("InputManager", "4c 8b 05 ? ? ? ? 41 80 78");
	Memory::CreateOffset("FreezeManager", "48 8B 05 ? ? ? ? 0F B6 48 61");

	if (amount == found)
		result = "All Found";
	else
		result = "Not All Found";

	std::cout << "\nSucessfully Dumped Offsets! [" << result << "]\n";

	while (!GetAsyncKeyState(VK_F1))
		Sleep(5);

	Memory::Close(console, current_module);
}

bool __stdcall DllMain(HMODULE module_entry, std::uint32_t call_reason) {
	if (call_reason == DLL_PROCESS_ATTACH)
	{
		CloseHandle(CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(MainThread), module_entry, 0, 0));
	}

	return TRUE;
}
