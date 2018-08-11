//==============================================================================
//
// Title:		Graph.h
// Purpose:		A short description of the interface.
//
// Created on:	18/7/12 at 13:50:53 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

#ifndef __Graph_H__
#define __Graph_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"
#include "curve.h"

//==============================================================================
// Constants

//==============================================================================
// Types
typedef struct
{
	int xAxisHead;
	int xAxisTail;
	int yAxisHead;
	int yAxisTail;
}GraphAttrTypeDef;		
typedef struct
{
	int plotHandle;									//graph handle 
	int graphIndex;									//graph Index
	int numOfCurve;									//number of Curves
	int X_Axis_Max;
	int Y_Axis_Max; 
	int X_Axis_Name; 
	int Y_Axis_Name;
	
	GraphAttrTypeDef* pGraphAttr;
	Curve_TypeDef* pCurveArray;						//pointer to curve array
}Graph_TypeDef;
//==============================================================================
// External variables
extern Graph_TypeDef Graph;
extern Graph_TypeDef Graph_Temp;
//extern Graph_TypeDef* pGraph1;
//extern Graph_TypeDef* pGraph2;
//==============================================================================
// Global functions
int graphInit(int graphIndex, int numOfCurve, int numOfDots, Graph_TypeDef* pGraph);
int GraphDeinit(Graph_TypeDef* pGraph);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __Graph_H__ */
