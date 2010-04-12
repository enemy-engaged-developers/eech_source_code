#include <windows.h>

#include "lamp_structs.h"
#include "sharedmem.h"

static HANDLE gHandleSharedMemory;
shared_memory_t* gPtrSharedMemory = NULL;

int Initialise_Shared_Memory()
{
	gPtrSharedMemory = 0;

	gHandleSharedMemory = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(shared_memory_t), "EECHSharedMemory");

	if (!gHandleSharedMemory)
	{
		CloseHandle(gHandleSharedMemory);
		return 0;
	}

	gPtrSharedMemory = (shared_memory_t*)MapViewOfFile(gHandleSharedMemory, FILE_MAP_READ, 0, 0, 0);
	return 1;
}

void DeInitialise_Shared_Memory(void)
{
	if (gPtrSharedMemory)
	{
		UnmapViewOfFile(gPtrSharedMemory);
		gPtrSharedMemory = NULL;
	}
	CloseHandle(gHandleSharedMemory);
}

extern "C" int _compiled_under_generic;
int _compiled_under_generic;
