//spencer jackson
// a cross platform sleep
// this file is public domain, use it wherever you want

#ifdef _WIN32
#include <windows.h>
#define csleep(x) Sleep(x)
#else
#include <stdlib.h>
#include <unistd.h>
#define csleep(x) usleep(x*1000.0)
#endif
