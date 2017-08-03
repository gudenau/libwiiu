#pragma once

#include <wiiu/types.h>
#include <wiiu/types2d.h>

#define VPAD_BUTTON_SYNC	(1 <<  0)
#define VPAD_BUTTON_POWER	(1 <<  1)
#define VPAD_BUTTON_HOME	(1 <<  1)
#define VPAD_BUTTON_MINUS	(1 <<  2)
#define VPAD_BUTTON_PLUS	(1 <<  3)
#define VPAD_BUTTON_R		(1 <<  4)
#define VPAD_BUTTON_L		(1 <<  5)
#define VPAD_BUTTON_ZR		(1 <<  6)
#define VPAD_BUTTON_ZL		(1 <<  7)
#define VPAD_BUTTON_DOWN	(1 <<  8)
#define VPAD_BUTTON_UP		(1 <<  9)
#define VPAD_BUTTON_RIGHT	(1 << 10)
#define VPAD_BUTTON_LEFT	(1 << 11)
#define VPAD_BUTTON_Y		(1 << 12)
#define VPAD_BUTTON_X		(1 << 13)
#define VPAD_BUTTON_B		(1 << 14)
#define VPAD_BUTTON_A		(1 << 15)
#define VPAD_BUTTON_TV		(1 << 16)
#define VPAD_BUTTON_STICK_R	(1 << 17)
#define VPAD_BUTTON_STICK_L	(1 << 18)

typedef struct{
	u16 x;
	u16 y;
	u16 touch;
	u16 valid;
} VPADTouch;

typedef struct{
	Vec3f x;
	Vec3f y;
	Vec3f z;
} VPADPosition;

typedef struct{
	u32 buttonsHeld;
	u32 buttonsPressed;
	u32 buttonsRelease;
	Vec2f leftStick;
	Vec2f rightStick;
	Vec3f accelerometer;
	float accelerometerM;
	float accelerometerV;
	Vec2f accelerometerVert;
	Vec3f gyro;
	Vec3f rotation;
	s8 errorCode;
	VPADTouch touch;
	VPADTouch touch2;
	VPADTouch touch3;
	VPADPosition position;
	boolean headphones;
	Vec3f magnetometer;
	u8 volumeRaw;
	u8 battery;
	u8 microphone;
	u8 volume;
	u8 padding[7];
} VPADData;

/**
* Initilizes the VPAD library
*/
void VPADInit(void);

/**
* Reads a set of values from a DRC
* 
* channel: which DRC to read from
* buffers: an array of VPADData structures to read
* length: the length of buffers
* error: an error code if something goes wrong
*/
s32 VPADRead(s32 channel, VPADData buffers[], u32 length, s32* error);
