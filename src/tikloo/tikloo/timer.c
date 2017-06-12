/* timer.h  -  Cross-platform timer library  -  Public Domain  -  2011 Mattias Jansson / Rampant Pixels
 * 
 * This library provides a cross-platform interface to measure
 * elapsed time with (at least) millisecond accuracy.
 *
 * This library is put in the public domain; you can redistribute
 * it and/or modify it without any restrictions.
 *
 */

#include "timer.h"
#include "stdlib.h"

#define TIMER_PLATFORM_WINDOWS 0
#define TIMER_PLATFORM_APPLE   0
#define TIMER_PLATFORM_POSIX   0

#if defined( _WIN32 ) || defined( _WIN64 )
#  undef  TIMER_PLATFORM_WINDOWS
#  define TIMER_PLATFORM_WINDOWS 1
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#elif defined( __APPLE__ )
#  undef  TIMER_PLATFORM_APPLE
#  define TIMER_PLATFORM_APPLE 1
#  include <mach/mach_time.h>
#  include <string.h>
   void absolutetime_to_nanoseconds ( mach_timebase_info_data_t _timerlib_info,uint64_t mach_time, uint64_t* clock ) { *clock = mach_time * _timerlib_info.numer / _timerlib_info.denom; }
#else
#  undef  TIMER_PLATFORM_POSIX
#  define TIMER_PLATFORM_POSIX 1
#  include <unistd.h>
#  include <time.h>
#  include <string.h>
#endif

typedef struct __timer_lib_handle_t
{
    tick_t _timerlib_freq;
    double _timerlib_oofreq;
#if TIMER_PLATFORM_APPLE
    mach_timebase_info_data_t _timerlib_info;
#endif
}_timer_lib_handle_t;


int timer_lib_initialize( timer_lib_handle_t* handle )
{
    *handle = (timer_lib_handle_t)malloc( sizeof( _timer_lib_handle_t ) );
    _timer_lib_handle_t* h = (_timer_lib_handle_t*)*handle;
#if TIMER_PLATFORM_WINDOWS
	tick_t unused;
	if( !QueryPerformanceFrequency( (LARGE_INTEGER*)&(h->_timerlib_freq) ) ||
	    !QueryPerformanceCounter( (LARGE_INTEGER*)&unused ) )
		return -1;
#elif TIMER_PLATFORM_APPLE
	if( mach_timebase_info( &(h->_timerlib_info) ) )
		return -1;
	h->_timerlib_freq = 1000000000ULL;
#elif TIMER_PLATFORM_POSIX
	struct timespec ts = { .tv_sec = 0, .tv_nsec = 0 };
	if( clock_gettime( CLOCK_MONOTONIC, &ts ) )
		return -1;
	h->_timerlib_freq = 1000000000ULL;
#endif

	h->_timerlib_oofreq = 1.0 / (double)h->_timerlib_freq;

	return 0;
}


void timer_lib_shutdown( timer_lib_handle_t handle )
{
    _timer_lib_handle_t* h = (_timer_lib_handle_t*)handle;
    free(h);
}


tick_t timer_current( timer_lib_handle_t handle )
{
#if TIMER_PLATFORM_WINDOWS

    (void)handle;
	tick_t curclock;
	QueryPerformanceCounter( (LARGE_INTEGER*)&curclock );
	return curclock;

#elif TIMER_PLATFORM_APPLE

    _timer_lib_handle_t* h = (_timer_lib_handle_t*)handle;
	tick_t curclock = 0;
	absolutetime_to_nanoseconds( h->_timer_lib_info, mach_absolute_time(), &curclock );
	return curclock;

#elif TIMER_PLATFORM_POSIX

    (void)handle;
	struct timespec ts = { .tv_sec = 0, .tv_nsec = 0 };
	clock_gettime( CLOCK_MONOTONIC, &ts );
	return ( (uint64_t)ts.tv_sec * 1000000000ULL ) + ts.tv_nsec;

#endif
}

deltatime_t timer_current_seconds( timer_lib_handle_t handle )
{
    return timer_ticks_to_seconds( handle, timer_current( handle ) );
}

tick_t timer_ticks_per_second( timer_lib_handle_t handle )
{
    _timer_lib_handle_t* h = (_timer_lib_handle_t*)handle;
	return h->_timerlib_freq;
}


deltatime_t timer_elapsed( timer_lib_handle_t handle, const tick_t t )
{
    _timer_lib_handle_t* h = (_timer_lib_handle_t*)handle;
	return (deltatime_t)( (double)timer_elapsed_ticks( handle, t ) * h->_timerlib_oofreq );
}


tick_t timer_elapsed_ticks( timer_lib_handle_t handle, const tick_t t )
{
	tick_t dt = 0;

#if TIMER_PLATFORM_WINDOWS

    (void)handle;
	tick_t curclock = t;
	QueryPerformanceCounter( (LARGE_INTEGER*)&curclock );
	dt = curclock - t;

#elif TIMER_PLATFORM_APPLE

    _timer_lib_handle_t* h = (_timer_lib_handle_t*)handle;
	tick_t curclock = t;
	absolutetime_to_nanoseconds( h->_timer_lib_info, mach_absolute_time(), &curclock );
	dt = curclock - t;

#elif TIMER_PLATFORM_POSIX

    (void)handle;
	tick_t curclock;
	struct timespec ts = { .tv_sec = 0, .tv_nsec = 0 };
	clock_gettime( CLOCK_MONOTONIC, &ts );

	curclock = ( (tick_t)ts.tv_sec * 1000000000ULL ) + ts.tv_nsec;
	dt = curclock - t;

#endif

	return dt;
}


deltatime_t timer_ticks_to_seconds( timer_lib_handle_t handle, const tick_t dt )
{
    _timer_lib_handle_t* h = (_timer_lib_handle_t*)handle;
	return (deltatime_t)( (double)dt * h->_timerlib_oofreq );
}


#if TIMER_PLATFORM_WINDOWS
struct __timeb64 {
	__time64_t time;
	unsigned short millitm;
	short timezone;
	short dstflag;
	};
_CRTIMP errno_t __cdecl _ftime64_s(_Out_ struct __timeb64 * _Time);
#endif

tick_t timer_system( timer_lib_handle_t handle )
{
#if TIMER_PLATFORM_WINDOWS

    (void)handle;
	struct __timeb64 tb;
	_ftime64_s( &tb );
	return ( (tick_t)tb.time * 1000ULL ) + (tick_t)tb.millitm;

#elif TIMER_PLATFORM_APPLE

    _timer_lib_handle_t* h = (_timer_lib_handle_t*)handle;
	tick_t curclock = 0;
	absolutetime_to_nanoseconds( h->timer_lib_info, mach_absolute_time(), &curclock );
	return ( curclock / 1000000ULL );

#elif TIMER_PLATFORM_POSIX

    (void)handle;
	struct timespec ts = { .tv_sec = 0, .tv_nsec = 0 };
	clock_gettime( CLOCK_REALTIME, &ts );
	return ( (uint64_t)ts.tv_sec * 1000ULL ) + ( ts.tv_nsec / 1000000ULL );

#endif
}
