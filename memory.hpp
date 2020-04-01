#pragma once

extern int amount, found;

namespace Memory
{
	void CreateOffset(const char* name, const char* signature);
	void Close(FILE* console, HMODULE current_module);
}