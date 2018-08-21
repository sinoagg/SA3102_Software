#include "Id-Vds Configuration.h"
#include <userint.h>
//==============================================================================
//
// Title:		IdVgsPanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/11 at 13:36:34 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "IdVgsPanel.h"
#include "Id-Vgs Configuration.h"
//==============================================================================
// Constants
#define VAL_BG                        0xA9A9A9L    //δ��ѡ��ʱ�ı���ɫ
#define VAL_BG_Pressed                0xA5B8D2L    //��ѡ��ʱ�ı���ɫ
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
IdVgCfg_TypeDef IdVgCfg; 
//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
//int GetIdVgCfg (int panelHandle)
//{
//	/*int temp;
//	if(GetCtrlVal(panelHandle, IDVGS_CFG_VD_START, &temp)<0)
//		return -1;
//	IdVgCfg.cfgVdstart=temp;
//	if(GetCtrlVal(panelHandle, IDVGS_CFG_VD_STOP, &temp)<0)
//		return -1;
//	IdVgCfg.cfgVdstop=temp;
//	if(GetCtrlVal(panelHandle, IDVGS_CFG_VD_STEP, &temp)<0)
//		return -1;
//	IdVgCfg.cfgVdstep=temp;*/
//	
//	
//		int temp;
//	/*if(GetCtrlVal(panelHandle, IDVGS_CFG_VG_BIAS, &temp)<0)
//		return -1;
//	IdVgCfg.cfgVdstart=temp;
//	if(GetCtrlVal(panelHandle, IDVGS_CFG_VG_COMPL_2, &temp)<0)
//		return -1;
//	IdVgCfg.cfgVdstop=temp;
//	if(GetCtrlVal(panelHandle, IDVGS_CFG_VG_BIAS_2, &temp)<0)
//		return -1;*/
//	IdVgCfg.cfgVdstep=temp;
//	
//	if(GetCtrlVal(panelHandle, IDVGS_CFG_VG_START, &temp)<0)
//		return -1;
//	IdVgCfg.cfgVgstart=temp;
//	if(GetCtrlVal(panelHandle, IDVGS_CFG_VG_STOP, &temp)<0)
//		return -1;
//	IdVgCfg.cfgVgstop=temp;
//	if(GetCtrlVal(panelHandle, IDVGS_CFG_VG_STEP, &temp)<0)
//		return -1;
//	IdVgCfg.cfgVgstep=temp;
//	
//	return 0;
//}

static void IdVgSetGATEDisp(int panel, char focus)
{
	if(focus==FOCUS)
	{
		SetCtrlAttribute (panel, IDVGS_CFG_BG_GATE, ATTR_PICT_BGCOLOR, VAL_BG_Pressed);
		SetCtrlAttribute (panel, IDVGS_CFG_TXT_GATE, ATTR_TEXT_BGCOLOR, VAL_BG_Pressed); // change text bgcolor together with picture
	}
	else
	{
		SetCtrlAttribute (panel, IDVGS_CFG_BG_GATE, ATTR_PICT_BGCOLOR, VAL_BG); 
		SetCtrlAttribute (panel, IDVGS_CFG_TXT_GATE, ATTR_TEXT_BGCOLOR, VAL_BG); // change text bgcolor together with picture
	}
}
static void IdVgSetDRAINDisp(int panel, char focus)
{
	if(focus==FOCUS)
	{
		SetCtrlAttribute (panel, IDVGS_CFG_BG_DRAIN, ATTR_PICT_BGCOLOR, VAL_BG_Pressed);
		SetCtrlAttribute (panel, IDVGS_CFG_TXT_DRAIN, ATTR_TEXT_BGCOLOR, VAL_BG_Pressed); // change text bgcolor together with picture
	}
	else
	{
		SetCtrlAttribute (panel, IDVGS_CFG_BG_DRAIN, ATTR_PICT_BGCOLOR, VAL_BG); 
		SetCtrlAttribute (panel, IDVGS_CFG_TXT_DRAIN, ATTR_TEXT_BGCOLOR, VAL_BG); // change text bgcolor together with picture
	}
}

int CVICALLBACK IdVgGATEDecoCB (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			IdVgSetGATEDisp(panel,FOCUS);
			IdVgSetDRAINDisp(panel,UNFOCUS); 
			break;
	}
	return 0;
}

int CVICALLBACK IdVgDRAINDecoCB (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			IdVgSetGATEDisp(panel,UNFOCUS);
			IdVgSetDRAINDisp(panel,FOCUS); 

			break;

	}
	return 0;
}

