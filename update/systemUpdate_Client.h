//==============================================================================
//
// Title:		systemUpdate_Client.h
// Purpose:		A short description of the interface.
//
// Created on:	2018/9/6 at 11:01:20 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __systemUpdate_Client_H__
#define __systemUpdate_Client_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// External variables

//==============================================================================
// Global functions

int Declare_Your_Functions_Here (int x);
__declspec(dllexport) int _stdcall SystemUpdate_CompareVer();
__declspec(dllexport) int _stdcall SystemUpdate_Download();
#ifdef __cplusplus
    }
#endif

#endif  /* ndef __systemUpdate_Client_H__ */
