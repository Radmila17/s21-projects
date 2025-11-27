#ifndef TYPES_H
#define TYPES_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    unsigned int bits[4];
} s21_decimal;

typedef struct
{
    unsigned int bits[8];
} s21_big_decimal;

#define MAX_LIMIT 1000

#define OK 0

#define FALSE 0

#define TRUE 1

#define CONVERTATION_ERROR 1

#define VALIDATION_ERROR 4

#define TOO_LARGE_POSITIVE_NUM 1

#define TOO_SMALL_NUM 2

#define MAX_INT 2147483648

#define MAX_DEC {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}}

#endif