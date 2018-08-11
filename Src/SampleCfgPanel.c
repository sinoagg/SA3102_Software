#include <userint.h>
//==============================================================================
//
// Title:		SampleCfgPanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/10 at 20:38:31 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "SampleCfgPanel.h"
#include "Sample Configuration.h"
#include "LoadPanel.h" 

int hBasicSamplePanelHandle; 
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

//SampleCfg_TypeDef SampleCfg;
//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?
//int GetSampleCfg (int panelHandle)
//{
//	int temp;
//	if(GetCtrlVal(panelHandle, SAMPLE_CFG_SRT_QUIET, &temp)<0)
//		return -1;
//	SampleCfg.cfgQuiteTime=temp;
//	if(GetCtrlVal(panelHandle, SAMPLE_CFG_SRT_INTERVAL, &temp)<0)
//		return -1;
//	SampleCfg.cfgTimeInterval=temp;
//	if(GetCtrlVal(panelHandle, SAMPLE_CFG_STR_RUNTIME, &temp)<0)
//		return -1;
//	SampleCfg.cfgRunTime=temp;
//	if(GetCtrlVal(panelHandle, SAMPLE_CFG_STR_RATE, &temp)<0)
//		return -1;
//	SampleCfg.cfgSampleRate=temp;
//	if(GetCtrlVal(panelHandle, SAMPLE_CFG_STR_NUMBER, &temp)<0)
//		return -1;
//	SampleCfg.cfgSampleNum=temp;
//	if(GetCtrlVal(panelHandle, SAMPLE_CFG_STR_SETTING, &temp)<0)
//		return -1;
//	SampleCfg.cfgRangeSetting=temp;
//	
//	return 0;
//	
//}
int CVICALLBACK AdvancSetCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch(event){
	
		case EVENT_LEFT_CLICK_UP:
			SetPanelPos(hAdvanceSamplePanel, 105, 1600);
			SetPanelSize(hAdvanceSamplePanel, 449, 300);
			DisplayPanel(hAdvanceSamplePanel);
			break;
	}
	return 0;
}

int CVICALLBACK BasicSetCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch(event){
		case EVENT_LEFT_CLICK_UP:
			    SetPanelPos(hBasicSamplePanel, 105, 1600);
				SetPanelSize(hBasicSamplePanel, 449, 300);
				DisplayPanel(hBasicSamplePanel);
			break;
	}
	return 0;
}
