#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "common.h"
#include "RGBColor.h"

#define RT_ZERO ((RTdouble)0.)
#define RT_ONE ((RTdouble)1.)

#define RT_EPSILON ((RTdouble)1e-6)
#define RT_INFINITY ((RTdouble)1e20)

#define RT_PI ((RTdouble)3.1415926535)
#define RT_INVPI (RT_ONE / RT_PI)

#define COLOR_BLACK RGBColor(RT_ZERO)
#define COLOR_WHITE RGBColor(RT_ONE)
#define COLOR_RED RGBColor(RT_ONE, RT_ZERO, RT_ZERO)
#define COLOR_GREEN RGBColor(RT_ZERO, RT_ONE, RT_ZERO)
#define COLOR_YELLOW RGBColor(RT_ONE, RT_ONE, RT_ZERO)
#define COLOR_BLUE RGBColor(RT_ZERO, RT_ZERO, RT_ONE)

#endif 