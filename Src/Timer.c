//==============================================================================
//
// Title:		Timer.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/16 at 17:33:45 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include "Graph.h"
#include "GraphDisp.h"
#include "LoadPanel.h"
#include "Plot.h"
#include "protocol.h"
#include "Cgs_mt.h"
#include "main.h"
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

//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
int CVICALLBACK TimerCallback (int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2)
{
<<<<<<< HEAD
	if(queryFlag == 1)//串口接收时要屏蔽数据查询
	{
		ProtocolQuery( comSelect, select_Addr1, select_Addr2, measUartTxBuf1,  measUartTxBuf2);
=======
	//PlotCurve(&Graph, graphDispPanel, GRAPHDISP_GRAPH1);//画曲线图
	PlotCurve_Temp(&Graph_Temp, graphDispPanel, GRAPHDISP_GRAPH2);//画曲线图
>>>>>>> 60731950687cb7b8b744a8e5d654e7bb290c0afb

	}
	
	
	//Graph.pGraphAttr->xAxisHead = 
	//Read_CGS_Value(CGS_comSelect);
<<<<<<< HEAD
	
=======
	//
>>>>>>> 60731950687cb7b8b744a8e5d654e7bb290c0afb
	////判断显示的 X 轴范围， X 轴范围要大于 实时显示的数据点
	//if(Graph.X_Axis_Max < Graph.pCurveArray->numOfPlotDots)
	//{
	//	Graph.X_Axis_Max = Graph.X_Axis_Max + 100; 			//将图中的 X 轴坐标最大值范围扩大100
	//	SetAxisScalingMode (graphDispPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, 0, Graph.X_Axis_Max);//设置 X 轴的范围

	//	//SetAxisScalingMode (panelHandle, PANEL_GRAPH2, VAL_LEFT_YAXIS , VAL_MANUAL, 0, 20);   //设置 Y 轴的范围
	//}
	//
	////判断显示的 X 轴范围， X 轴范围要大于 实时显示的数据点
	//if(Graph_Temp.X_Axis_Max < Graph_Temp.pCurveArray->numOfPlotDots)
	//{
	//	Graph_Temp.X_Axis_Max = Graph_Temp.X_Axis_Max + 100; 			//将图中的 X 轴坐标最大值范围扩大100
	//	SetAxisScalingMode (graphDispPanel, GRAPHDISP_GRAPH2, VAL_BOTTOM_XAXIS, VAL_MANUAL, 0, Graph_Temp.X_Axis_Max);//设置 X 轴的范围

	//	//SetAxisScalingMode (panelHandle, PANEL_GRAPH2, VAL_LEFT_YAXIS , VAL_MANUAL, 0, 20);   //设置 Y 轴的范围
	//}
	
	
	return 0;
}
