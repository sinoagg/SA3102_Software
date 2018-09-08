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
<<<<<<< HEAD
#include <rs232.h>
=======
>>>>>>> 60731950687cb7b8b744a8e5d654e7bb290c0afb
#include <userint.h>   
#include "Tools.h"
#include "LoadPanel.h"
#include "Protocol.h"
#include "main.h"

//==============================================================================
// Constants

//==============================================================================
// Types
#define VAL_TEXTBG       0xB2C9D5L  
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
			break;
	}
	return 0;
}


<<<<<<< HEAD

int CVICALLBACK TEXTMSG_7_Callback (int panel, int control, int event,
=======
int CVICALLBACK OutputVoltageCaliCallback (int panel, int control, int event,
>>>>>>> 60731950687cb7b8b744a8e5d654e7bb290c0afb
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
<<<<<<< HEAD
			SetCtrlAttribute (hCalibrationPanel, CALIPANEL_ZEROCURCALI, ATTR_DIMMED, 0);
			//SetCtrlAttribute (hCalibrationPanel, CALIPANEL_ZEROCURCALI, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);
			SetCtrlAttribute (hCalibrationPanel, CALIPANEL_OUTVOLCALI, ATTR_DIMMED, 0);
			//SetCtrlAttribute (hCalibrationPanel, CALIPANEL_OUTVOLCALI, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);
			break;
	}
	
=======
			SetCtrlAttribute (hCalibrationPanel, CALIPANEL_OUTVOLCALI, ATTR_DIMMED, 1);
			SetCtrlAttribute (hCalibrationPanel, CALIPANEL_OUTVOLCALI, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);

			break;

	}
	return 0;
}
								  

int CVICALLBACK ZeroCurrentCaliCallback (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			SetCtrlAttribute (hCalibrationPanel, CALIPANEL_ZEROCURCALI, ATTR_DIMMED, 1);
			SetCtrlAttribute (hCalibrationPanel, CALIPANEL_ZEROCURCALI, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);
			break;

	}
>>>>>>> 60731950687cb7b8b744a8e5d654e7bb290c0afb
	return 0;
}
