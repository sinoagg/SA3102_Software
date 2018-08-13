//==============================================================================
//
// Title:		ProjectPanelCB.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/7/27 at 13:22:00 by 
// Copyright:    . All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include <userint.h>
#include "ProjectPanel.h"
#include "LoadPanel.h"
#include "Result Menu.h"
#include "MainPanelCb.h"
//==============================================================================
// Constants
#define CHANGECOLOR 	0x94CEFF //浅蓝
#define BGCOLOR 		0xFFFFFF
#define COLOR  			0x065279 //深蓝
#define SEARCHCOLOR 	0xb2c9d5 //不可用颜色
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

int selectedPrjIndex=0;			//当前选中的项目序号 

static void DiscardAllPrjPanel(PrjHandleTypeDef *pSingleProject)
{
	int i=0;
	while((pSingleProject+i)->index != -1)
	{
		DiscardPanel((pSingleProject+i)->hSinglePrjPanel);
		i++;
	}
}

static int RecallAllPanelState(char* pConfigSavePath)
{
	RecallPanelState(II_T_Panel.panelHandle, pConfigSavePath, 1); //IT面板的值					
	//RecallPanelState(IdVgPanel.panelHandle, pConfigSavePath, 2);						
	//RecallPanelState(hIT_Panel, pConfigSavePath, 3);
	//RecallPanelState(hRT_Panel, pConfigSavePath, 4);
	RecallPanelState(hBasicSamplePanel, pConfigSavePath, 10);	   //用户设置 配置值
	RecallPanelState(hAdvanceSamplePanel, pConfigSavePath, 11);  //高级设置面板值
	RecallPanelState(hEnvCfgPanel, pConfigSavePath, 14);
	RecallPanelState(ENVTPanel, pConfigSavePath, 15);
	RecallPanelState(hSettingsGraphPanel, pConfigSavePath, 16);
	
	return 0;
}
int CVICALLBACK TXT_OpenPrjCallback (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			RecallAllPanelState(pFileLable[selectedPrjIndex]->pFileName);//load all panel and other parameters
			
			DiscardAllPrjPanel(SingleProject);
			RemovePopup (proPanel);
			break;
	}
	return 0;

}
static void SelectProject(int panel, int select)
{
	if(select)
	{
		SetPanelAttribute (panel, ATTR_BACKCOLOR, CHANGECOLOR);
		SetCtrlAttribute (panel, DEFPANEL_NAME, ATTR_TEXT_BGCOLOR, CHANGECOLOR);
		SetCtrlAttribute (panel, DEFPANEL_DESC, ATTR_TEXT_BGCOLOR, CHANGECOLOR);
		SetCtrlAttribute (panel, DEFPANEL_DATE, ATTR_TEXT_BGCOLOR, CHANGECOLOR);
		SetCtrlAttribute (panel, DEFPANEL_TIME, ATTR_TEXT_BGCOLOR, CHANGECOLOR);
		SetCtrlAttribute (panel, DEFPANEL_CANVAS, ATTR_PICT_BGCOLOR, COLOR);	
	}
	else
	{
		SetPanelAttribute (panel, ATTR_BACKCOLOR, BGCOLOR);
		SetCtrlAttribute (panel, DEFPANEL_NAME, ATTR_TEXT_BGCOLOR, BGCOLOR);
		SetCtrlAttribute (panel, DEFPANEL_DESC, ATTR_TEXT_BGCOLOR, BGCOLOR);
		SetCtrlAttribute (panel, DEFPANEL_DATE, ATTR_TEXT_BGCOLOR, BGCOLOR);
		SetCtrlAttribute (panel, DEFPANEL_TIME, ATTR_TEXT_BGCOLOR, BGCOLOR);
		SetCtrlAttribute (panel, DEFPANEL_CANVAS, ATTR_PICT_BGCOLOR, BGCOLOR);
	}
}

static char GetPanelIndex(int panel)
{
	int top;
	GetPanelAttribute(panel, ATTR_TOP, &top);
	return (char)((top-90)/117);								//减去偏置，除以单个高度
}

 int CVICALLBACK PrjSelectCallback (int panel, int event, void *callbackData,
							 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			SetPanelAttribute (panel, ATTR_BACKCOLOR, CHANGECOLOR);
			SetCtrlAttribute (panel, DEFPANEL_NAME, ATTR_TEXT_BGCOLOR, CHANGECOLOR);
			SetCtrlAttribute (panel, DEFPANEL_DESC, ATTR_TEXT_BGCOLOR, CHANGECOLOR);
			SetCtrlAttribute (panel, DEFPANEL_DATE, ATTR_TEXT_BGCOLOR, CHANGECOLOR);
			SetCtrlAttribute (panel, DEFPANEL_TIME, ATTR_TEXT_BGCOLOR, CHANGECOLOR);

			SetCtrlAttribute (proPanel, PROPANEL_PIC_OPENPRJ, ATTR_DIMMED, 0);
			SetCtrlAttribute (proPanel, PROPANEL_TXT_OPENPRJ, ATTR_DIMMED, 0);
			SetCtrlAttribute (proPanel, PROPANEL_TXT_OPENPRJ , ATTR_TEXT_BGCOLOR,COLOR ); 
			
			SelectProject(panel, 1);
			selectedPrjIndex=GetPanelIndex(panel);
			int i=0;
			while(SingleProject[i].index!=-1)
			{
				if(i!=selectedPrjIndex)
					SelectProject(SingleProject[i].hSinglePrjPanel, 0);
				i++;
			}
			break;
	}
	return 0;
}
//int CVICALLBACK PIC_ExitPrjCallback (int panel, int control, int event,
//									 void *callbackData, int eventData1, int eventData2)
//{
//	if(event==EVENT_LEFT_CLICK)
//	{
//		DiscardAllPrjPanel(SingleProject);
//		RemovePopup (proPanel);  
//	}

//	return 0;
//}

int CVICALLBACK SearchCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			SetPanelAttribute(defPanel, ATTR_BACKCOLOR, BGCOLOR);
			SetCtrlAttribute (defPanel, DEFPANEL_CANVAS, ATTR_PICT_BGCOLOR, BGCOLOR);
			SetCtrlAttribute (defPanel, DEFPANEL_NAME, ATTR_TEXT_BGCOLOR, BGCOLOR);
			SetCtrlAttribute (defPanel, DEFPANEL_DESC, ATTR_TEXT_BGCOLOR, BGCOLOR);
			SetCtrlAttribute (proPanel,PROPANEL_PIC_OPENPRJ , ATTR_DIMMED, 1);
			SetCtrlAttribute (proPanel,PROPANEL_TXT_OPENPRJ , ATTR_TEXT_BGCOLOR,SEARCHCOLOR );
			SetCtrlAttribute (proPanel,PROPANEL_TXT_OPENPRJ , ATTR_DIMMED, 1); 
			break;
	}
	return 0;
}


int CVICALLBACK PIC_ExitPrjCallback2 (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	if(event==EVENT_LEFT_CLICK)
	{
		DiscardAllPrjPanel(SingleProject);
		RemovePopup (proPanel);  
	}
	return 0;
}

int CVICALLBACK PIC_ExitPrjCallback (int panel, int event, void *callbackData,
									 int eventData1, int eventData2)
{
	switch (event)
	{
			
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:

				DiscardAllPrjPanel(SingleProject);
				RemovePopup (proPanel);  
			
			break;
			
	}
	return 0;
}
