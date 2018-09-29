//==============================================================================
//
// Title:		Graph.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/12 at 13:50:53 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include <userint.h>
#include <ansi_c.h>
#include "Curve.h"
#include "Graph.h"
#include "protocol.h" 
#include "LoadPanel.h"
//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables
Graph_TypeDef pGraph;
Graph_TypeDef* pGraph1;
Graph_TypeDef* pGraph2;
//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect
/// HIRET What does your function return?
int graphInit(int graphIndex, int numOfCurve, int numOfDots, Graph_TypeDef* pGraph)
{
	int i;
	pGraph->graphIndex=graphIndex;		//画几个图
	pGraph->numOfCurve=numOfCurve;		//画几条曲线
	Curve_TypeDef* pCurveArray = (Curve_TypeDef *)malloc(numOfCurve * sizeof(Curve_TypeDef)); 	//Curve Array Saving pointers to curve structure  曲线阵列保存指针到曲线结构。
	if(pCurveArray==NULL) return -1;
	pGraph->pCurveArray=pCurveArray;
	for(i=0;i<numOfCurve;i++)		//init curve
	{
		if(curveInit(i, numOfDots, pCurveArray+i)==-1) return -1;
	}
	GraphAttrTypeDef* pGraphAttr = (GraphAttrTypeDef *)malloc(sizeof(Curve_TypeDef));
	if(pGraphAttr==NULL) return -1;
	pGraph->pGraphAttr=pGraphAttr;
	return 0;
}
int GraphDeinit(Graph_TypeDef* pGraph)
{
	int i=0;
	for(i=0;i<(pGraph->numOfCurve);i++)
	{
		curveDeinit(pGraph->pCurveArray++); 	
	}
	return 0;
}
void SetGraphX_Axis(int control,Graph_TypeDef* pGraph)		   
{					 
	switch(TestPara1.testMode)
	{
		case NO_SWEEP_IT:
		case NO_SWEEP_RT:
			if(pGraph->pGraphAttr->xAxisTail <= pGraph->pCurveArray->numOfPlotDots * TestPara1.timeStep * 0.001) //已画点数*Step ===》实际x轴长度
			{  	
				Graph.pGraphAttr->xAxisTail = Graph.pGraphAttr->xAxisTail*1.2;
				SetAxisScalingMode(graphDispPanel, control, VAL_BOTTOM_XAXIS, VAL_MANUAL, 
								   0, Graph.pGraphAttr->xAxisTail);//设置 X  轴的范围
			}
	   break;
	}

}
