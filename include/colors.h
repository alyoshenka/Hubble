#include "config.h"

#if ON_RPI
#include "/home/jay/raylib/src/raylib.h"
#else
#include "raylib.h"
#endif

extern "C"
{
#define A_BLUE \
    CLITERAL(Color) { 17, 24, 36, 255 }
#define A_BLUE_1 \
    CLITERAL(Color) { 73, 147, 255, 255 }
#define A_BLUE_2 \
    CLITERAL(Color) { 0, 64, 159, 255 }
#define A_BLUE_3 \
    CLITERAL(Color) { 0, 13, 32, 255 }
#define A_BLUE_4 \
    CLITERAL(Color) { 0, 42, 103, 255 }

#define A_GREEN \
    CLITERAL(Color) { 16, 38, 27, 255 }
#define A_GREEN_1 \
    CLITERAL(Color) { 56, 255, 154, 255 }
#define A_GREEN_2 \
    CLITERAL(Color) { 0, 169, 8, 255 }
#define A_GREEN_3 \
    CLITERAL(Color) { 0, 34, 17, 255 }
#define A_GREEN_4 \
    CLITERAL(Color) { 0, 110, 54, 255 }
}