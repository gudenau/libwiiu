#include <wiiu/types.h>
#include <wiiu/service/coreinit.h>
#include <wiiu/service/hbl.h>

#define GET_CODE_POINTER(name) if( name ## _pointer ){ name ## _pointer = coreinit_findCodeExport( #name );}

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

/*
Currently not needed
static void* coreinit_findDataExport(const char* name){
	void* address = 0;
	OSDynLoad_FindExport(coreinit_getModule(), true, name, &address);
	return address;
}
*/

int OSDynLoad_Acquire(const char *moduleName, OSDynLoad_moduleHandle *handle){
	return hbl_getOSSpecifics()->OSDynLoad_Acquire(moduleName, handle);
}

static void (*OSDynLoad_Release_pointer)(OSDynLoad_moduleHandle) = 0;
void OSDynLoad_Release(OSDynLoad_moduleHandle handle){
	GET_CODE_POINTER(OSDynLoad_Release);
	
	OSDynLoad_Release_pointer(handle);
}

int OSDynLoad_FindExport(OSDynLoad_moduleHandle handle, boolean isData, const char *exportName, void **address){
	return hbl_getOSSpecifics()->OSDynLoad_FindExport(handle, isData, exportName, address);
}

// No need to cache, as this is a dead end
void OSFatal(const char* message){
	((void(*)(const char*))coreinit_findCodeExport("OSFatal"))(message);
}

static void (*OSScreenInit_pointer)(void) = 0;
void OSScreenInit(void){
	GET_CODE_POINTER(OSScreenInit);
	
	OSScreenInit_pointer();
}

static u32 (*OSScreenGetBufferSizeEx_pointer)(OSScreen_buffer) = 0;
u32 OSScreenGetBufferSizeEx(OSScreen_buffer buffer){
	GET_CODE_POINTER(OSScreenGetBufferSizeEx);
	
	return OSScreenGetBufferSizeEx_pointer(buffer);
}

static u32 (*MEMAllocFromExpHeapEx_pointer)(MEM_heapHandle, u32, int);
void* MEMAllocFromExpHeapEx(MEM_heapHandle handle, u32 size, int alignment){
	GET_CODE_POINTER(MEMAllocFromExpHeapEx);
	
	// Make sure it is at least word aligned
	return MEMAllocFromExpHeapEx(handle, size, alignment < 4 ? 4 : alignment);
}

static int (*OSScreenPutFontEx_pointer)(OSScreen_buffer, u32, u32, const char*);
int OSScreenPutFontEx(OSScreen_buffer buffer, u32 x, u32 y, const char* message){
	GET_CODE_POINTER(OSScreenPutFontEx);
	
	return OSScreenPutFontEx_pointer(buffer, x, y, message);
}

static void (*DCFlushRange_pointer)(const void*, u32);
void DCFlushRange(const void* address, u32 size){
	GET_CODE_POINTER(DCFlushRange);
	
	return DCFlushRange_pointer(address, size);
}

static int (*OSScreenFlipBuffersEx_pointer)(OSScreen_buffer);
int OSScreenFlipBuffersEx(OSScreen_buffer buffer){
	GET_CODE_POINTER(OSScreenFlipBuffersEx);
	
	return OSScreenFlipBuffersEx_pointer(buffer);
}

static int (*OSScreenSetBufferEx_pointer)(OSScreen_buffer, void*);
int OSScreenSetBufferEx(OSScreen_buffer buffer, void* address){
	GET_CODE_POINTER(OSScreenSetBufferEx);
	
	return OSScreenSetBufferEx_pointer(buffer, address);
}

static int (*OSScreenEnableEx_pointer)(OSScreen_buffer, boolean);
int OSScreenEnableEx(OSScreen_buffer buffer, boolean enable){
	GET_CODE_POINTER(OSScreenEnableEx);
	
	return OSScreenEnableEx_pointer(buffer, enable);
}

static int (*OSScreenClearBufferEx_pointer)(OSScreen_buffer, u32);
int OSScreenClearBufferEx(OSScreen_buffer buffer, u32 unknown){
	GET_CODE_POINTER(OSScreenClearBufferEx);
	
	return OSScreenClearBufferEx_pointer(buffer, unknown);
}

static void (*MEMFreeToExpHeap_pointer)(MEM_heapHandle, void*);
void MEMFreeToExpHeap(MEM_heapHandle heap, void* address){
	GET_CODE_POINTER(MEMFreeToExpHeap);
	
	MEMFreeToExpHeap_pointer(heap, address);
}

static void (*OSSleepTicks_pointer)(WIIUTime);
void OSSleepTicks(WIIUTime ticks){
	GET_CODE_POINTER(OSSleepTicks);
	
	OSSleepTicks_pointer(ticks);
}

static void (*MEMFreeToFrmHeap_pointer)(MEM_heapHandle, int);
void MEMFreeToFrmHeap(MEM_heapHandle heap, int mode){
	GET_CODE_POINTER(MEMFreeToFrmHeap);
	
	MEMFreeToFrmHeap_pointer(heap, mode);
}

static MEM_heapHandle (*MEMGetBaseHeapHandle_pointer)(MEM_area);
MEM_heapHandle MEMGetBaseHeapHandle(MEM_area area){
	GET_CODE_POINTER(MEMGetBaseHeapHandle);
	
	return MEMGetBaseHeapHandle_pointer(area);
}

static u32 (*MEMGetAllocatableSizeForFrmHeapEx_pointer)(MEM_heapHandle, int);
u32 MEMGetAllocatableSizeForFrmHeapEx(MEM_heapHandle heap, int alignment){
	GET_CODE_POINTER(MEMGetAllocatableSizeForFrmHeapEx);
	
	return MEMGetAllocatableSizeForFrmHeapEx_pointer(heap, alignment < 4 ? 4 : alignment);
}

static void* (*MEMAllocFromFrmHeapEx_pointer)(MEM_heapHandle, u32, int);
void* MEMAllocFromFrmHeapEx(MEM_heapHandle heap, u32 size, int alignment){
	GET_CODE_POINTER(MEMAllocFromFrmHeapEx);
	
	return MEMAllocFromFrmHeapEx_pointer(heap, size, alignment < 4 ? 4 : alignment);
}

static MEM_heapHandle (*MEMCreateExpHeapEx_pointer)(void*, u32, u16);
MEM_heapHandle MEMCreateExpHeapEx(void* address, u32 size, u16 options){
	GET_CODE_POINTER(MEMCreateExpHeapEx);
	
	return MEMCreateExpHeapEx_pointer(address, size, options);
}

static void* (*MEMDestroyExpHeap_pointer)(MEM_heapHandle);
void* MEMDestroyExpHeap(MEM_heapHandle heap){
	GET_CODE_POINTER(MEMDestroyExpHeap);
	
	return MEMDestroyExpHeap_pointer(heap);
}

#undef GET_CODE_POINTER