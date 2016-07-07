//Spencer Jackson
//envfollower.h
#ifndef ENVFOLLOWER_H
#define ENVFOLLOWER_H

#define ENVFOLLOWER_URI "http://ssj71.github.io/infamousPlugins/plugs.html#envfollower"
#define ENVFOLLOWERCV_URI "http://ssj71.github.io/infamousPlugins/plugs.html#envfollowerCV"

#ifndef CV_PORTS

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

#else

enum envCV_ports
{
    INPUT = 0,
    OUTPUT,
    CV_OUT,
    CTL_IN,
    CTL_OUT,
    PEAKRMS,//5
    THRESHOLD,
    SATURATION,
    ATIME,
    DTIME,
    CMINV,//10
    CMAXV,
    CREVERSE
};
#endif

#endif
