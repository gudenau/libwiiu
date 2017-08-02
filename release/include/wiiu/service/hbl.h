#pragma once

#include <wiiu/types.h>
#include <wiiu/service/coreinit.h>

#define HBL_EXIT_SUCCESS  0x00000000
#define HBL_EXIT_HBL      0xFFFFFFFE
#define HBL_EXIT_RELAUNCH 0xFFFFFFFD

typedef struct{
    int (*OSDynLoad_Acquire)(const char*, OSDynLoad_moduleHandle*);
    int (*OSDynLoad_FindExport)(OSDynLoad_moduleHandle, boolean, const char*, void** address);
    void* OSTitle_main_entry;
    
    void* KernSyscallTbl1;
    void* KernSyscallTbl2;
    void* KernSyscallTbl3;
    void* KernSyscallTbl4;
    void* KernSyscallTbl5;
} OSSpecifics;

/**
* Gets the pointer of MemBase that HBL uses
*
* returns: MemBase pointer
*/
void* hbl_getMemBase(void);

/**
* Gets the data address of the loaded ELF file
*
* returns: ELF data address
*/
vvoid* hbl_getElfDataAddress(void);

/**
* Gets the data size of the loaded ELF file
* 
* returns: ELF data size
*/
u32 hbl_getElfDataSize(void);

/**
* Gets the main entry address
* 
* returns: Main entry address
*/
vvoid* hbl_getMainEntryAddress(void);

/**
* Gets the OS Firmware
*
* returns: OS Firmware
*/
u32 hbl_getOSFirmware(void);

/**
* Gets OSSpecifics struct
* 
* returns: Pointer to OSSpecifics
*/
OSSpecifics* hbl_getOSSpecifics(void);
