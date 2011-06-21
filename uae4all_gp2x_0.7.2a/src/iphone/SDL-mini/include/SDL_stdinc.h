/*
 *  SDL_stdinc.h
 *  iAmiga
 *
 *  Created by Stuart Carnie on 1/2/11.
 *  Copyright 2011 Manomio LLC. All rights reserved.
 *
 */

#ifndef _SDL_stdinc_h
#define _SDL_stdinc_h

#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include <stddef.h>

#include <stdint.h>

/**
 *  \name Basic data types
 */
/*@{*/

typedef enum
{
    SDL_FALSE = 0,
    SDL_TRUE = 1
} SDL_bool;

/**
 * \brief A signed 8-bit integer type.
 */
typedef int8_t Sint8;
/**
 * \brief An unsigned 8-bit integer type.
 */
typedef uint8_t Uint8;
/**
 * \brief A signed 16-bit integer type.
 */
typedef int16_t Sint16;
/**
 * \brief An unsigned 16-bit integer type.
 */
typedef uint16_t Uint16;
/**
 * \brief A signed 32-bit integer type.
 */
typedef int32_t Sint32;
/**
 * \brief An unsigned 32-bit integer type.
 */
typedef uint32_t Uint32;


#define SDL_malloc  malloc
#define SDL_realloc realloc
#define SDL_free    free
#define SDL_memset  memset
#define SDL_memmove memmove

#endif