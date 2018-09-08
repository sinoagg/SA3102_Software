//==============================================================================
//
// Title:		ToolsPanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/8/18 at 15:06:35 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include <rs232.h>
#include <userint.h>   
#include "Tools.h"
#include "LoadPanel.h"
#include "Protocol.h"
#include "main.h"

//==============================================================================
// Constants

//==============================================================================
// Types
#define VAL_BG_ENABLE            0x065279L 
#define VAL_BG_DISABLE           0xB2C9D5L  
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

int CVICALLBACK ToolsPanelCallback (int panel, int event, void *callbackData,			
									int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			RemovePopup(hToolsPanel);
			break;
	}
	return 0;
}

int CVICALLBACK CalibrationCallback (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			InstallPopup (hCalibrationPanel); 
			break;
	}
	return 0;
}
int CVICALLBACK CaliPanelCallback (int panel, int event, void *callbackData,
									int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			HidePanel(hCalibrationPanel);
			SetCtrlAttribute (hCalibrationPanel, CALIPANEL_ZEROCURCALI, ATTR_DIMMED, 0);
			SetCtrlAttribute (hCalibrationPanel, CALIPANEL_ZEROCURCALI, ATTR_TEXT_BGCOLOR, VAL_BG_ENABLE);
			SetCtrlAttribute (hCalibrationPanel, CALIPANEL_OUTVOLCALI, ATTR_DIMMED, 0);
			SetCtrlAttribute (hCalibrationPanel, CALIPANEL_OUTVOLCALI, ATTR_TEXT_BGCOLOR, VAL_BG_ENABLE);
			SetCtrlAttribute (hCalibrationPanel, CALIPANEL_CURRENTCALI, ATTR_DIMMED, 0);
			SetCtrlAttribute (hCalibrationPanel, CALIPANEL_CURRENTCALI, ATTR_TEXT_BGCOLOR, VAL_BG_ENABLE);  
			break;
	}
	return 0;
}

int CVICALLBACK RangeSelectCallback (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_VAL_CHANGED:
			SetCtrlAttribute (hCalibrationPanel, CALIPANEL_CURRENTCALI, ATTR_DIMMED, 0);
			SetCtrlAttribute (hCalibrationPanel, CALIPANEL_CURRENTCALI, ATTR_TEXT_BGCOLOR, VAL_BG_ENABLE);  
			break;
	}
	return 0;
}

int CVICALLBACK ExitCaliCallback (int panel, int control, int event,void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			
			HidePanel(hCalibrationPanel);
			SetCtrlAttribute (hCalibrationPanel, CALIPANEL_ZEROCURCALI, ATTR_DIMMED, 0);
			SetCtrlAttribute (hCalibrationPanel, CALIPANEL_ZEROCURCALI, ATTR_TEXT_BGCOLOR, VAL_BG_ENABLE);
			SetCtrlAttribute (hCalibrationPanel, CALIPANEL_OUTVOLCALI, ATTR_DIMMED, 0);
			SetCtrlAttribute (hCalibrationPanel, CALIPANEL_OUTVOLCALI, ATTR_TEXT_BGCOLOR, VAL_BG_ENABLE);
			SetCtrlAttribute (hCalibrationPanel, CALIPANEL_CURRENTCALI, ATTR_DIMMED, 0);
			SetCtrlAttribute (hCalibrationPanel, CALIPANEL_CURRENTCALI, ATTR_TEXT_BGCOLOR, VAL_BG_ENABLE);  
			break;
	}
	return 0;
}
