#include <wiiu/types.h>
#include <wiiu/service/coreinit.h>
#include <wiiu/service/hbl.h>

static OSDynLoad_moduleHandle coreinit_handle;
static OSDynLoad_moduleHandle coreinit_getModule(void){
	if(!coreinit_handle){
		OSDynLoad_Acquire("coreinit.rpl", &coreinit_handle);
	}
	
	return coreinit_handle;
}

static void* coreinit_findCodeExport(const char* name){
	void* address = 0;
	OSDynLoad_FindExport(coreinit_getModule(), false, name, &address);
	return address;
}

static void* coreinit_findDataExport(const char* name){
	void* address = 0;
	OSDynLoad_FindExport(coreinit_getModule(), true, name, &address);
	return address;
}

int OSDynLoad_Acquire(const char *moduleName, OSDynLoad_moduleHandle *handle){
	return hbl_getOSSpecifics()->OSDynLoad_Acquire(moduleName, handle);
}

static void (*OSDynLoad_Release_pointer)(OSDynLoad_moduleHandle) = 0;
void OSDynLoad_Release(OSDynLoad_moduleHandle handle){
	if(!OSDynLoad_Release_pointer){
		OSDynLoad_Release_pointer = coreinit_findCodeExport("OSDynLoad_Release");
	}
	
	OSDynLoad_Release_pointer(handle);
}

int OSDynLoad_FindExport(OSDynLoad_moduleHandle handle, boolean isData, const char *exportName, void **address){
	return hbl_getOSSpecifics()->OSDynLoad_FindExport(handle, isData, exportName, address);
}

// No need to cache, as this is a dead end
void OSFatal(const char* message){
	((void(*)(const char*))coreinit_findCodeExport("OSFatal"))(message);
}
