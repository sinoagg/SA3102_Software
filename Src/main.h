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
extern int rowIndex; 
extern int rowIndex2;
extern unsigned char measure_Uart_Flag; 					//电学测量串口接收时要屏蔽数据查询 
extern unsigned char control_Uart_Flag; 					//环境参数串口接收时要屏蔽数据查询
//==============================================================================
// Global functions



#ifdef __cplusplus
    }
#endif

#endif  /* ndef __main_H__ */
