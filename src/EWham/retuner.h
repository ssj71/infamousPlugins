// -----------------------------------------------------------------------
//
//  Copyright (C) 2014-2111 Spencer Jackson <ssjackson71@gmail.com>>
//    
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
// -----------------------------------------------------------------------

//this code is mostly written by Jeff Glatt based on code from Fons Adriaensen.

#ifndef __RETUNER_H
#define __RETUNER_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32
#include <windows.h>
#ifndef int32_t
#define int32_t long 
typedef DWORD REV_ERROR;
#endif
#else
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
typedef int REV_ERROR;
#endif

#define TUNERTYPE_8BIT			0
#define TUNERTYPE_16BIT			1
#define TUNERTYPE_32BIT			2
#define TUNERTYPE_FLOAT			3
#define TUNERTYPE_DOUBLE			4
#define TUNERTYPE_BITSMASK		0x07
#define TUNERTYPE_MONOOUTPUT		0x20
#define TUNERTYPE_MONOINPUT		0x40
//#define TUNERTYPE_NONINTERLEAVED	0x80

typedef void * TUNERHANDLE;

TUNERHANDLE RetunerAlloc(int);
void RetunerFree(TUNERHANDLE);
void RetunerProcess(TUNERHANDLE, float *, float *, unsigned int);
void RetunerSetPitch(TUNERHANDLE, float);
void RetunerSetNoteBias(TUNERHANDLE, float);
void RetunerSetFilter(TUNERHANDLE, float);
void RetunerSetGain(TUNERHANDLE, float);
void RetunerSetOffset(TUNERHANDLE, float);
void RetunerSetNoteMask(TUNERHANDLE, unsigned int);
unsigned int RetunerGetNoteset(TUNERHANDLE);
float RetunerGetError(TUNERHANDLE);
void RetunerSetLatency(TUNERHANDLE, unsigned int);//don't set below 256
unsigned int RetunerGetLatency(TUNERHANDLE);

#ifdef __cplusplus
}
#endif

#endif
