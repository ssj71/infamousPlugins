//Spencer Jackson
//envfollower.h
#ifndef ENVFOLLOWER_H
#define ENVFOLLOWER_H

#define ENVFOLLOWER_URI "http://infamousplugins.sourceforge.net/plugs.html#envfollower"

enum envfollower_ports
{
    INPUT = 0,
    OUTPUT,
    MIDI_OUT,
    CTL_IN,
    CTL_OUT,
    PEAKRMS,
    THRESHOLD,//6
    SATURATION,
    ATIME,
    DTIME,
    CHANNEL,
    CONTROL_NO,//11
    MINV,
    MAXV,
    REVERSE,
    CMINV,
    CMAXV,//16
    CREVERSE,
    CV_OUT
};
#endif
