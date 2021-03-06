//==============================================================================
//
// Title:		main.h
// Purpose:		A short description of the interface.
//
// Created on:	2018/8/11 at 10:57:42 by 斌 何.
// Copyright:	内蒙古民族大学. All Rights Reserved.
//
//==============================================================================

#ifndef __main_H__
#define __main_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"

//==============================================================================
// Constants
#define UART_RX_LEN 20   
//==============================================================================
// Types

//==============================================================================
// External variables
extern int TimerID; 
extern unsigned char queryFlag; 
extern int rowIndex; 
extern int rowIndex2; 
//==============================================================================
// Global functions



#ifdef __cplusplus
    }
#endif

#endif  /* ndef __main_H__ */
