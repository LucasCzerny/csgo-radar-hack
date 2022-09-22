#include <iostream>

#include "ExternalProcess.h"

struct _offsets
{
	DWORD entList = 0x4DA3FA4;
	DWORD bSpotted = 0x93D;
} offsets;

int main()
{
	ExternalProcess csgo(L"csgo.exe");
	uintptr_t clientDll = csgo.GetModuleBaseAddress(L"client.dll");

	uintptr_t entList = clientDll + 0x4DA2F24;

	while (true)
	{
		for (int i = 0; i < 64; i++)
		{
			uintptr_t ent = csgo.ReadMemory<uintptr_t>(entList + i * 0x10);
			if (ent != NULL)
			{
				csgo.WriteMemory<bool>(ent + offsets.bSpotted, true);
			}
		}
	}
}