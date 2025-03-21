//
// Created by coles on 3/11/2025.
//

#ifndef OVENCONFIG_H
#define OVENCONFIG_H

#ifndef PID_KP
#define PID_KP 500.0
#endif

#ifndef PID_KI
#define PID_KI 0.0
#endif

#ifndef PID_KD
#define PID_KD 0.0
#endif


#ifndef PID_DELTA
#define PID_DELTA 5.0
#endif


// 121 degrees c is 250 degrees f
#ifndef PREHEAT_TEMP
#define PREHEAT_TEMP 121
#endif

// time is in minutes
#ifndef PREHEAT_TIME
#define PREHEAT_TIME (10)
#endif


// 121 degrees c is 250 degrees f
#ifndef CURE_TEMP
#define CURE_TEMP 121
#endif

// time is in minutes
#ifndef CURE_TIME
#define CURE_TIME (40)
#endif


// 121 degrees c is 250 degrees f
#ifndef DWELL_TEMP
#define DWELL_TEMP 121
#endif

// time is in minutes
#ifndef DWELL_TIME
#define DWELL_TIME (20)
#endif


#endif //OVENCONFIG_H