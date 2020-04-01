#include "stdafx.hpp"

int amount = 0;
int found = 0;

namespace Memory
{
	void Close(FILE* console, HMODULE current_module)
	{
		fclose(console);
		FreeConsole();
		FreeLibraryAndExitThread(current_module, 0);
	}

	uintptr_t SignatureToOffset(const char* signature)
	{
		static uintptr_t moduleAdress;
		if (!moduleAdress)
		{
			moduleAdress = reinterpret_cast<uintptr_t>(GetModuleHandleA(NULL));
			std::cout << "[+] Module Address: " << std::hex << moduleAdress << "\n\n";
		}

		static auto converter = [](const char* pattern)
		{
			std::vector<int>bytes = {};
			char* start = const_cast<char*>(pattern);
			char* end = const_cast<char*>(pattern) + strlen(pattern);

			for (auto current = start; current < end; ++current)
			{
				if (*current == '?')
				{
					++current;
					if (*current == '?')
						++current;
					bytes.push_back(-1);
				}
				else { bytes.push_back(strtoul(current, &current, 16)); }
			}
			return bytes;
		};

		PIMAGE_DOS_HEADER dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(moduleAdress);
		PIMAGE_NT_HEADERS ntHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(((std::uint8_t*)moduleAdress + dosHeader->e_lfanew));

		uintptr_t sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
		std::vector<int>patternBytes = converter(signature);
		uint8_t* const scanBytes = reinterpret_cast<std::uint8_t*>(moduleAdress);

		const size_t size = patternBytes.size();
		const int * data = patternBytes.data();

		for (auto i = 0ul; i < sizeOfImage - size; ++i)
		{
			bool found = true;
			for (auto j = 0ul; j < size; ++j)
			{
				if (scanBytes[i + j] != data[j] && data[j] != -1)
				{
					found = false;
					break;
				}
			}
			if (found) 
			{
				return reinterpret_cast<uintptr_t>((&scanBytes[i] + *reinterpret_cast<std::int32_t*>(&scanBytes[i] + 3) + 7) - moduleAdress);
			}
		}
		return 0x6969;
	}

	void CreateOffset(const char* name, const char* signature)
	{
		uintptr_t offset = SignatureToOffset(signature);

		amount++;

		if (offset == 0x6969)
		{
			std::cout << "[-] Unable to find: " << name << std::endl;
		}
		else
		{
			found++;
			std::cout << "[+] " << name << " 0x" << std::hex << offset << std::endl;
		}
	}
}