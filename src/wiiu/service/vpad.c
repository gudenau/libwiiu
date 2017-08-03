#include <wiiu/types.h>
#include <wiiu/types2d.h>
#include <wiiu/service/coreinit.h>
#include <wiiu/service/vpad.h>

#define GET_CODE_POINTER(name) if( name ## _pointer ){ name ## _pointer = vpad_findCodeExport( #name );}

static OSDynLoad_moduleHandle vpad_handle;
static OSDynLoad_moduleHandle vpad_getModule(void){
	if(!vpad_handle){
		OSDynLoad_Acquire("vpad.rpl", &vpad_handle);
	}
	
	return vpad_handle;
}

static void* vpad_findCodeExport(const char* name){
	void* address = 0;
	OSDynLoad_FindExport(vpad_getModule(), false, name, &address);
	return address;
}

static void (*VPADInit_pointer)(void);
void VPADInit(void){
	GET_CODE_POINTER(VPADInit);
	
	VPADInit();
}

static s32 (*VPADRead_pointer)(s32, VPADData[], u32, s32*);
s32 VPADRead(s32 channel, VPADData buffers[], u32 length, s32* error){
	GET_CODE_POINTER(VPADRead);
	
	return VPADRead_pointer(channel, buffers, length, error);
}

#undef GET_CODE_POINTER