// -----------------------------------------------------------------------
//
//  Copyright (C) 2014-2111 Spencer Jackson <ssjackson71@gmail.com>
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


//  This code is mostly written by Jeff Glatt based on original code from Fons Adriaensen

#ifndef __RETUNER_H
#define __RETUNER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void* TUNERHANDLE;

void RetunerSetPitch(TUNERHANDLE tune, float v);
void RetunerSetNoteBias(TUNERHANDLE tune, float v);
void RetunerSetFilter(TUNERHANDLE tune, float v);
void RetunerSetGain(TUNERHANDLE tune, float v);
void RetunerSetOffset(TUNERHANDLE tune, float v);
void RetunerSetNoteMask(TUNERHANDLE tune, unsigned int k);
void RetunerSetLatency(TUNERHANDLE tune, unsigned int samp);
unsigned int RetunerGetLatency(TUNERHANDLE tune);
unsigned int RetunerGetNoteset(TUNERHANDLE tune);
void RetunerSetDryGain(TUNERHANDLE tune, float g);
float RetunerGetError(TUNERHANDLE tune);
void RetunerFree(TUNERHANDLE handle);
TUNERHANDLE RetunerAlloc(int fsamp);
void RetunerProcess(TUNERHANDLE handle, float * inp, float * out, unsigned int nfram);
#ifdef __cplusplus
}
#endif

#endif
