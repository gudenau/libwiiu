#pragma once

#include <wiiu/types.h>

typedef void * OSDynLoad_moduleHandle;

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
