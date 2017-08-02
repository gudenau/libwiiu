#include <wiiu/types.h>
#include <wiiu/service/hbl.h>

void* hbl_getMemBase(void){
	return (void*)0x00800000;
}

vvoid* hbl_getElfDataAddress(void){
	return *(vvoid **)(hbl_getMemBase() + 0x1300);
}

u32 hbl_getElfDataSize(void){
	return *(vu32 *)(hbl_getMemBase() + 0x1304);
}

vvoid* hbl_getMainEntryAddress(void){
	return *(vvoid **)(hbl_getMemBase() + 0x1400);
}

u32 hbl_getOSFirmware(void){
	return *(vu32 *)(hbl_getMemBase() + 0x1404);
}

OSSpecifics* hbl_getOSSpecifics(void){
	return (OSSpecifics *)(hbl_getMemBase() + 0x1500);
}
