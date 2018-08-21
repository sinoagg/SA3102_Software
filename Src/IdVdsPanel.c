#include <userint.h>
//==============================================================================
//
// Title:		IdVdsPanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/10 at 18:10:32 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "IdVdsPanel.h"
#include "Id-Vds Configuration.h"
//==============================================================================
// Constants
#define VAL_BG                        0xA9A9A9L    //未被选中时的背景色
#define VAL_BG_Pressed                0xA5B8D2L    //被选中时的背景色
#define FOCUS	0
#define UNFOCUS 1
//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables
//IdVdCfg_TypeDef IdVdCfg;
//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
//int GetIdVdCfg (int panelHandle)
//{
//	int temp;
//	
//	
//	if(GetCtrlVal(panelHandle, IDVDS_CFG_VD_START, &temp)<0)
//		return -1;
//	IdVdCfg.cfgVdstart=temp;
//	if(GetCtrlVal(panelHandle, IDVDS_CFG_VD_STOP, &temp)<0)
//		return -1;
//	IdVdCfg.cfgVdstop=temp;
//	if(GetCtrlVal(panelHandle, IDVDS_CFG_VD_STEP, &temp)<0)
//		return -1;
//	IdVdCfg.cfgVdstep=temp;
//	
//	
//	
//	//
//	//if(GetCtrlVal(panelHandle, IDVDS_CFG_VG_START, &temp)<0)
//	//	return -1;
//	//IdVdCfg.cfgVgstart=temp;
//	//if(GetCtrlVal(panelHandle, IDVDS_CFG_VG_STOP, &temp)<0)
//	//	return -1;
//	//IdVdCfg.cfgVgstop=temp;
//	//if(GetCtrlVal(panelHandle, IDVDS_CFG_VG_STEP, &temp)<0)
//	//	return -1;
//	//IdVdCfg.cfgVgstep=temp;
//	
//		
//	if(GetCtrlVal(panelHandle, IDVDS_CFG_VD_START_2, &temp)<0)
//		return -1;
//	IdVdCfg.cfgVgstart=temp;
//	if(GetCtrlVal(panelHandle, IDVDS_CFG_VD_STOP_2, &temp)<0)
//		return -1;
//	IdVdCfg.cfgVgstop=temp;
//	if(GetCtrlVal(panelHandle, IDVDS_CFG_VD_STEP_2, &temp)<0)
//		return -1;
//	IdVdCfg.cfgVgstep=temp;
//	
//	
//	
//	return 0;
//}
static void IdVdSetGATEDisp(int panel, char focus)
{
	if(focus==FOCUS)
	{
		SetCtrlAttribute (panel, IDVDS_CFG_BG_GATE, ATTR_PICT_BGCOLOR, VAL_BG_Pressed);
		SetCtrlAttribute (panel, IDVDS_CFG_TXT_GATE, ATTR_TEXT_BGCOLOR, VAL_BG_Pressed); // change text bgcolor together with picture
	}
	else
	{
		SetCtrlAttribute (panel, IDVDS_CFG_BG_GATE, ATTR_PICT_BGCOLOR, VAL_BG); 
		SetCtrlAttribute (panel, IDVDS_CFG_TXT_GATE, ATTR_TEXT_BGCOLOR, VAL_BG); // change text bgcolor together with picture
	}
}
static void IdVdSetDRAINDisp(int panel, char focus)
{
	if(focus==FOCUS)
	{
		SetCtrlAttribute (panel, IDVDS_CFG_BG_DRAIN, ATTR_PICT_BGCOLOR, VAL_BG_Pressed);
		SetCtrlAttribute (panel, IDVDS_CFG_TXT_DRAIN, ATTR_TEXT_BGCOLOR, VAL_BG_Pressed); // change text bgcolor together with picture
	}
	else
	{
		SetCtrlAttribute (panel, IDVDS_CFG_BG_DRAIN, ATTR_PICT_BGCOLOR, VAL_BG); 
		SetCtrlAttribute (panel, IDVDS_CFG_TXT_DRAIN, ATTR_TEXT_BGCOLOR, VAL_BG); // change text bgcolor together with picture
	}
}
int CVICALLBACK IdVdGATEDecoCB (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			
			IdVdSetGATEDisp(panel,FOCUS);
			IdVdSetDRAINDisp(panel,UNFOCUS); 

			break;

	}
	return 0;
}
int CVICALLBACK IdVdDRAINDecoCB (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			
			IdVdSetGATEDisp(panel,UNFOCUS);
			IdVdSetDRAINDisp(panel,FOCUS); 

			break;

	}
	return 0;
}


















