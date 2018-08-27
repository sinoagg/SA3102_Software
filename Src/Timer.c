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

//#include "Timer.h"
#include "Graph.h"
#include "GraphDisp.h"
#include "LoadPanel.h"
#include "Plot.h"
#include "protocol.h"
#include "Cgs_mt.h"
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
	//PlotCurve(&Graph, graphDispPanel, GRAPHDISP_GRAPH1);//画曲线图
	PlotCurve_Temp(&Graph_Temp, graphDispPanel, GRAPHDISP_GRAPH2);//画曲线图

	ProtocolQuery( comSelect, select_Addr1, select_Addr2, measUartTxBuf1,  measUartTxBuf2);
	//Read_CGS_Value(CGS_comSelect);
	
	//判断显示的 X 轴范围， X 轴范围要大于 实时显示的数据点
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
