////////////////////////////////////////////////////////////////////////////////
//               Copyright(c) 2013
// Filename        :    common.h
// Projectname     :    Small game
// Author          :    Jujj
// Email           :    
// Date            :    周日 十二月  8 16:11:08 2013 (+0800)
// Version         :    v 1.0
// Description     :    
////////////////////////////////////////////////////////////////////////////////
#ifndef __COMMON_H__
#define __COMMON_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifndef DEBUG
    #define DEBUG
#endif

#ifdef DEBUG
#define DEBUG_PRINT_HEADER ">>>>>> Game OutPut <<<<<< : "
#define DEBUG_PRINT(format, ...) printf(DEBUG_PRINT_HEADER format, ##__VA_ARGS__)
#else
#define DEBUG_PRINT(format, ...)
#endif

#define TEST_EQZ(x)	if((x)){DEBUG_PRINT("ERROR : " #x " failed (equal non-zero).\n"); exit(0);}
#define TEST_NEZ(x) if(!(x)){DEBUG_PRINT("ERROR : " #x "failed (equal zero).\n"); exit(0);}
#define TEST_EQ_NUM(x, num) if((x) != num){DEBUG_PRINT("ERROR : " #x " != " #num "\n"); exit(0);}

#endif
