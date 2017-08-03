#pragma once

#include <wiiu/types.h>

/**
* RPL handle type
*/
typedef void * OSDynLoad_moduleHandle;

/**
* Heap handle type
*/
typedef void * MEM_heapHandle;

/**
* Type for Wii U time functions
*/
typedef u64 WIIUTime;

/**
* Buffer values for OSScreen functions
*/
typedef enum{
	OSScreen_buffer_TV = 0,
	OSScreen_buffer_DRC
} OSScreen_buffer;

/**
* Logical memory areas
*/
typedef enum{
    MEM_area_mem1,
    MEM_area_mem2,
    MEM_area_3,
    MEM_area_4,
    MEM_area_5,
    MEM_area_6,
    MEM_area_7,
    MEM_area_8,
    MEM_area_bucket,
    MEM_area_max,
    MEM_area_invalid
} MEM_area;

/**
* Attempts to load an RPL
* 
* moduleName: name of the module to load
* handle: handle of the module
*
* returns: TODO
*/
int OSDynLoad_Acquire(const char *moduleName, OSDynLoad_moduleHandle *handle);

/**
* Releases a loaded RPL
* 
* handle: handle of the module
*/
void OSDynLoad_Release(OSDynLoad_moduleHandle handle);

/**
* Finds an export of a loaded RPL
*
* handle: handle of the RPL
* isData: set to true if the export is data
* exportName: name of the export to find
* address: address of the export
*
* returns: TODO
*/
int OSDynLoad_FindExport(OSDynLoad_moduleHandle handle, boolean isData, const char *exportName, void **address);

/**
* Initalizes the screens
*/
void OSScreenInit(void);

/**
* Gets the size of a screen buffer
*
* buffer: OSScreen_buffer_TV or OSScreen_buffer_DRC
*
* returns: size of the buffer
*/
u32 OSScreenGetBufferSizeEx(OSScreen_buffer buffer);

/**
* Allocates aligned memory from the provided heap
*
* heap: heap to allocate from
* size: amount of memory to allocate
* alignment: alignment of the allocated memory
*
* returns: pointer to allocated memory
*/
void* MEMAllocFromExpHeapEx(MEM_heapHandle handle, u32 size, int alignment);

/**
* Prints a string to the specified buffer at the specified location
*
* buffer: Buffer to print to
* x: X position in the buffer
* y: Y position in the buffer
* message: string to print
*
* returns: TODO
*/
int OSScreenPutFontEx(OSScreen_buffer buffer, u32 x, u32 y, const char* message);

/**
* Flushes L1 data cache
*
* address: address of buffer to flush
* size: size of buffer to flush
*/
void DCFlushRange(const void* address, u32 size);

/**
* Flips the specified buffer
*
* buffer: buffer to flip
*
* returns: TODO
*/
int OSScreenFlipBuffersEx(OSScreen_buffer buffer);

/**
* Sets the location of the provided buffer
* 
* buffer: the buffer to set
* address: the new address of the buffer
* 
* returns: TODO
*/
int OSScreenSetBufferEx(OSScreen_buffer buffer, void* address);

/**
* Enables or disables a screen
* 
* buffer: the buffer of the screen to enable or disable
* enable: enable if true
* 
* returns: TODO
*/
int OSScreenEnableEx(OSScreen_buffer buffer, boolean enable);

/**
* Clears the memory for the screen
* 
* buffer: screen to clear
* unknown: TODO
* 
* returns: TODO
*/
int OSScreenClearBufferEx(OSScreen_buffer buffer, u32 unknown);

/**
* Frees a memory block to a heap
* 
* heap: the heap that owns the block of memory
* address: address of the memory block
*/
void MEMFreeToExpHeap(MEM_heapHandle heap, void* address);

/**
* Makes the current thread sleep
*
* ticks: the amount of system ticks to sleep
*/
void OSSleepTicks(WIIUTime ticks);

/**
* Frees a memory heap
* 
* heap: the heap to free
* mode: the mode used to free TODO what are the modes?
*/
void MEMFreeToFrmHeap(MEM_heapHandle heap, int mode);

/**
* Gets the base heap handle for a area
* 
* area: area to get base heap handle of
* 
* returns: the heap handle
*/
MEM_heapHandle MEMGetBaseHeapHandle(MEM_area area);

/**
* Gets the amount of space you can allocate from a heap
* 
* heap: the heap to check
* alignment: the alignment of the heap
*
* returns: allocatable size
*/
u32 MEMGetAllocatableSizeForFrmHeapEx(MEM_heapHandle heap, int alignment);

/**
* Allocates a memory heap
* 
* heap: heap to allocate
* size: size of the heap
* alignment: alignment of the heap
*
* returns: pointer to new heap
*/
void* MEMAllocFromFrmHeapEx(MEM_heapHandle heap, u32 size, int alignment);

/**
* Creates a memory heap
*
* address: address of the start of the heap
* size: size of the heap
* options: options TODO what are the options?
*
* returns: handle to the heap
*/
MEM_heapHandle MEMCreateExpHeapEx(void* address, u32 size, u16 options);

/**
* Destroys a memory heap
* 
* heap: heap to destroy
*
* returns: TODO
*/
void* MEMDestroyExpHeap(MEM_heapHandle heap);
