
/*

Copyright (C) 2011 JJS

http://gitorious.org/~jjs/ags/ags-for-psp

*/

#include "stdafx.h"

#include "Utility/ModulePSP.h"

#include <pspkernel.h>
#include <psppower.h>
#include <pspsuspend.h>

#include <malloc.h>

bool bVolatileMem = false; 
//*************************************************************************************
//
//*************************************************************************************
void VolatileMemInit()
{
	// Unlock memory partition 5
	void* pointer = NULL;
	int size = 0;
	int result = sceKernelVolatileMemLock(0, &pointer, &size);

	if (result == 0)
	{
		scePowerLock(0);
		printf("Successfully Unlocked Volatile Mem: %d KB\n",size / 1024);
		bVolatileMem = true;
	}
	else
	{
		printf( "Failed to unlock volatile mem: %08x\n", result );
		bVolatileMem = false;
	}

}
//u32 malloc_p5_memory_used = 0;
//*************************************************************************************
//
//*************************************************************************************
void* malloc_volatile(size_t size)
{
	//If volatile mem couldn't be unlocked, use normal memory
	//
	if (!bVolatileMem)	 return malloc(size);

	//void* result = (void*)malloc(size);

//	struct mallinfo info = _mallinfo_r(NULL);
//	printf("used memory %d of %d - %d\n", info.usmblks + info.uordblks, info.arena, malloc_p5_memory_used);

	// Only try to allocate to volatile mem if we run out of mem.
	//
	/*if (result)
		return result;*/

	SceUID uid = sceKernelAllocPartitionMemory(5, "", PSP_SMEM_Low, size + 8, NULL);
	if (uid >= 0)
	{

//		printf("getting memory from p5 %d KBS\n", size / 1024);  
//		malloc_p5_memory_used += size;

		u32* pointer = (u32*)sceKernelGetBlockHeadAddr(uid);
		*pointer = uid;
		*(pointer + 4) = size;
		return (void*)(pointer + 8);
	}
	else
	{

//		printf("*****failed to allocate %d byte from p5\n", size / 1024);
		return NULL;
	}
}

//*************************************************************************************
//
//*************************************************************************************
void free_volatile(void* ptr)
{
	if (!bVolatileMem)
	{
		_free_r(NULL, ptr);
		return;
	}

	if (!ptr)
		return;  

	if (ptr >= (void*)0x08800000)
	{
		_free_r(NULL, ptr);
	}
	else
	{
//		printf("freeing p5 memory %d\n", (u32)*((SceUID*)ptr - 8));
//		malloc_p5_memory_used -= *((SceUID*)ptr - 4);

		sceKernelFreePartitionMemory(*((SceUID*)ptr - 8));
	}
}