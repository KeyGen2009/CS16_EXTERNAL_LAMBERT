#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>


using namespace std;

//Variables del proceso
DWORD pid;
HANDLE hp;


//Header de busqueda de modulos
#include "KGModulos.h"	

//Modulos del juego
ModuloInfo hw;

//Parches en memoria
uintptr_t LAMBERT = 0x1F1F0B;
unsigned char lambert_on[] = { 0x0F, 0x85, 0x88, 0x00 ,0x00 ,0x00 };
unsigned char lambert_off[] = { 0x0F, 0x84, 0x88, 0x00 ,0x00 ,0x00 };

int main()
{
	//Abrir proceso
	hp = kg_abrir_proceso("hl.exe", PROCESS_ALL_ACCESS);

	//Cargar modulos
	hw = kg_obtener_modulo_info(pid, L"hw.dll");

	while (1)
	{
		if (GetKeyState(VK_F1))
		{
			WriteProcessMemory(hp, (LPBYTE)(hw.base + LAMBERT), &lambert_on, sizeof(lambert_on), 0);
		}
		else {
			WriteProcessMemory(hp, (LPBYTE)(hw.base + LAMBERT), &lambert_off, sizeof(lambert_off), 0);

		}
		Sleep(50);
	}

}
