//==============================================================================
//
// Title:		MainPanel.c
// Purpose:		A short description of the implementation.
//
// Created on:	18/7/16 at 15:58:31 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include "asynctmr.h"
#include "MainPanelCb.h"
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "LoadPanel.h"
#include "Protocol.h"
#include "Timer.h"
#include "I_T_Panel.h"
#include "SampleCfgPanel.h" 

//==============================================================================
// Constants
//==============================================================================
// Types

#define VAL_TEXTBG                        0xF0F0F0L    //未被选中背景色
#define VAL_TEXTBG_PRESSED                0x065279L    //被选中背景色




//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables
int TimerID;
Graph_TypeDef Graph;

//==============================================================================
// Global functions


//===================================================
//   MAIN_PANEL_Callback

int CVICALLBACK MAIN_PANEL_Callback (int panel, int event, void *callbackData,
									 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			   	QuitUserInterface(0); 
			break;
	}
	return 0;
}

//===================================================
//   RunCallback

int CVICALLBACK RunCallback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
		case EVENT_LEFT_CLICK_UP:		    //当鼠标释放时
			SetCtrlAttribute (mainPanel, MAIN_PANEL_RUN, ATTR_DIMMED,1);         //禁用 开始按钮      
		    SetCtrlAttribute (mainPanel, MAIN_PANEL_STOP, ATTR_DIMMED, 0);       //恢复 停止按钮
	        SetCtrlAttribute (mainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED,1);        //禁用 保存按钮
			
			
			SetCtrlAttribute (mainPanel, MAIN_PANEL_TIMER, ATTR_INTERVAL, 0.2);  //设置同步回调函数定时值 
			
			
			
			if(!comSelect)
			{
				MessagePopup ("Warning", "Instrument Unconnected");   //Lost serial Connection
			}
			else
			{
				int expType;
				int graphIndex=1;	//currently only deal with one graph circumstance
				int numOfCurve=2;
				int numOfDots=10000;
				if(GetCtrlVal(expListPanel, EXP_LIST_EXPLIST, &expType)<0)  //得到用户选择的 测试模式
					return -1;
				switch(expType)
				{
						
					//I_V 模式
					case 0:
						
						//Get_IT_Cfg (ITPanel);			//得到 I_T 模式下用户在面板的设置值
						//GetSampleCfg (samplePanel); 	//得到其他设置参数
						//
						
						////if((IdVgCfg.cfgVgstart==IdVdCfg.cfgVgstop)||IdVgCfg.cfgVgstep==0)	//如果起始电压和终止电压相同
						//numOfCurve=abs(IdVdCfg.cfgVgstart-IdVdCfg.cfgVgstop)/IdVdCfg.cfgVgstep;
						//numOfDots=abs(IdVdCfg.cfgVdstart-IdVdCfg.cfgVdstop)/IdVdCfg.cfgVdstep;
						break;
					//V_I 模式
					case 1:
						//GetIdVgCfg (IdVgPanel);
						//numOfCurve = abs(IdVgCfg.cfgVdstart-IdVgCfg.cfgVdstop)/IdVgCfg.cfgVdstep;
						//numOfDots = abs(IdVgCfg.cfgVgstart-IdVgCfg.cfgVgstop)/IdVgCfg.cfgVgstep;
						break;
					//I_T 模式
					case 2:

						break;
					//V_T 模式
					case 3:
						//TODO
						Get_IT_Cfg (ITPanel);			//得到 I_T 模式下用户在面板的设置值
						GetSampleCfg (samplePanel); 	//得到其他设置参数
						numOfDots = SampleCfg.cfgRunTime / SampleCfg.cfgTimeInterval; 
						
						break;
					//R_T 模式
					case 4:
						//TODO
						
						break;
						
					default:
						break;
				}
				
				SetCtrlAttribute (mainPanel, MAIN_PANEL_TIMER, ATTR_INTERVAL, SampleCfg.cfgTimeInterval * 0.001);  //设置同步回调函数定时值
				
				ProtocolCfg(comSelect, DEFAULT_ADDR1,0x00, (unsigned char)expType, UartTxBuf, UartTxBuf2);		//send config to instrument via UART
				
				graphInit(graphIndex, numOfCurve, numOfDots, &Graph); 	//graph set up 
				
				TimerID = NewAsyncTimer(1,-1, 1, TimerCallback, 0);		//Create Asynchronous (Timer time interval 1s, continue generating evernt, enabled, callback function name, passing no pointer)  
				
				ProtocolRun(comSelect, DEFAULT_ADDR1, 0x00, UartTxBuf, UartTxBuf2);		//send RUN command to instrument via UART
				
				SetCtrlAttribute (mainPanel, MAIN_PANEL_TIMER, ATTR_ENABLED, 1);       //开启同步定时器 
			
				
			}
			break;
	}
	return 0;
}

//===================================================
//   StopCallback

int CVICALLBACK StopCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			//TODO
		case EVENT_LEFT_CLICK_UP:		    //当鼠标释放时
		  	 SetCtrlAttribute (mainPanel, MAIN_PANEL_STOP, ATTR_DIMMED,1);      //禁用 停止按钮      
		     SetCtrlAttribute (mainPanel, MAIN_PANEL_RUN, ATTR_DIMMED, 0);      //恢复 开始按钮
			 SetCtrlAttribute (mainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED, 0);     //恢复 保存按钮
			 
			 SetCtrlAttribute (mainPanel, MAIN_PANEL_TIMER, ATTR_ENABLED, 0);   //关闭同步定时器
			 
			 
			 ProtocolStop(comSelect, DEFAULT_ADDR1, DEFAULT_ADDR2, UartTxBuf, UartTxBuf2);  //发送停止指令
			 
			 
			 
			break;
	}
	return 0;
}

//===================================================
//   SaveCallback

int CVICALLBACK SaveCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			//TODO
			break;
		case EVENT_LEFT_CLICK:			    //当Save被鼠标左键点击时 
			
			DisplayImageFile (mainPanel, MAIN_PANEL_SAVE, "Resource\\Save_pressed.ico");
			
			break;
			
		case EVENT_LEFT_CLICK_UP:		    //当鼠标释放时  
			
			DisplayImageFile (mainPanel, MAIN_PANEL_SAVE, "Resource\\Save.ico");

			break;
	}
	return 0;
}
//===================================================
//   SelectCallback

int CVICALLBACK SelectCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:			    //当Select被鼠标左键点击时,Select图标改变，其它两个正常状态 
			
			DisplayImageFile (mainPanel, MAIN_PANEL_SELECT, "Resource\\Select_pressed.ico");
			DisplayImageFile (mainPanel, MAIN_PANEL_CONFIGURE, "Resource\\Configure.ico"); 
			DisplayImageFile (mainPanel, MAIN_PANEL_ANALYZE, "Resource\\Analyze.ico");
			
			break;
	
	}
	return 0;
}

//===================================================
//   Configure_Callback

int CVICALLBACK ConfigureCallback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
 		case EVENT_LEFT_CLICK_UP:			    //当Configure被鼠标左键点击时,Configure图标改变，其它两个正常状态 
			
			DisplayImageFile (mainPanel, MAIN_PANEL_SELECT, "Resource\\Select.ico");
			DisplayImageFile (mainPanel, MAIN_PANEL_CONFIGURE, "Resource\\Configure_pressed.ico"); 
			DisplayImageFile (mainPanel, MAIN_PANEL_ANALYZE, "Resource\\Analyze.ico");
			
			break;
			
			
		case EVENT_LEFT_CLICK:
			//点击Configure图标回到Id_vds界面
				SetPanelPos(IdVdPanel, 105, 305);
				SetPanelSize(IdVdPanel, 900, 1293);
				DisplayPanel(IdVdPanel);
			break;
	}
	return 0;
}

//===================================================
//   Analyze_Callback

int CVICALLBACK AnalyzeCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:
		
				SetPanelPos(resultPanel, 125, 305);  
		     	SetPanelSize(resultPanel, 50, 1293);      
	 			DisplayPanel(resultPanel);  
				
				

				SetPanelPos(graphDispPanel, 176, 305);  
		     	SetPanelSize(graphDispPanel, 830, 1293);      
	 			DisplayPanel(graphDispPanel);
			


			break;
 		case EVENT_LEFT_CLICK_UP:			    //当Analyze被鼠标左键点击时,Analyze图标改变，其它两个正常状态， 
			
			DisplayImageFile (mainPanel, MAIN_PANEL_SELECT, "Resource\\Select.ico");
			DisplayImageFile (mainPanel, MAIN_PANEL_CONFIGURE, "Resource\\Configure.ico"); 
			DisplayImageFile (mainPanel, MAIN_PANEL_ANALYZE, "Resource\\Analyze_pressed.ico");
		
			break;
			
			
	}
	return 0;
}

int CVICALLBACK SettingsCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			
			InstallPopup (settingsPanel);  //弹出settingsPanel
			
	
			SetPanelPos(ENVPanel, 5, 170);
			SetPanelSize(ENVPanel, 350, 650);
			DisplayPanel(ENVPanel);
			
		
			
			break;

	}
	return 0;
}

int CVICALLBACK CancelCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{		
	      if (event == EVENT_COMMIT)
				{
	    		//移除、关闭settingsPanel
				RemovePopup (settingsPanel);
		        }
			return 0;
}

int CVICALLBACK PrjBtnCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			
			SetPanelPos(ENVPanel, 5, 170);
			SetPanelSize(ENVPanel, 350, 650);
			DisplayPanel(ENVPanel); 
			
			HidePanel (GRAPHPanel);
			HidePanel (ABOUTPanel); 
			
			SetCtrlAttribute (settingsPanel, SETTINGS_PRJBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG_PRESSED);   //environment背景色
	     	SetCtrlAttribute (settingsPanel, SETTINGS_PRJBTN, ATTR_TEXT_COLOR, VAL_WHITE);              //environment文本颜色
			
			SetCtrlAttribute (settingsPanel, SETTINGS_GRAPHBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);         //graph背景色
	     	SetCtrlAttribute (settingsPanel, SETTINGS_GRAPHBTN, ATTR_TEXT_COLOR, VAL_BLACK);            //graph文本颜色
			
			SetCtrlAttribute (settingsPanel, SETTINGS_ABOUTBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);         //about背景色
	     	SetCtrlAttribute (settingsPanel, SETTINGS_ABOUTBTN, ATTR_TEXT_COLOR, VAL_BLACK);            //about文本颜色
																								 
			break;

	}
	return 0;
}

int CVICALLBACK GraphBtnCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			
			SetPanelPos(GRAPHPanel, 5, 170);
			SetPanelSize(GRAPHPanel, 350, 650);
			DisplayPanel(GRAPHPanel);
			
			HidePanel (ENVPanel); 
			HidePanel (ABOUTPanel);
			
			SetCtrlAttribute (settingsPanel, SETTINGS_GRAPHBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG_PRESSED);   //graph背景色
	     	SetCtrlAttribute (settingsPanel, SETTINGS_GRAPHBTN, ATTR_TEXT_COLOR, VAL_WHITE);              //graph文本颜色
			
			SetCtrlAttribute (settingsPanel, SETTINGS_PRJBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);             //environment背景色
	     	SetCtrlAttribute (settingsPanel, SETTINGS_PRJBTN, ATTR_TEXT_COLOR, VAL_BLACK);                //environment文本颜色
			
			SetCtrlAttribute (settingsPanel, SETTINGS_ABOUTBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);           //about背景色
	     	SetCtrlAttribute (settingsPanel, SETTINGS_ABOUTBTN, ATTR_TEXT_COLOR, VAL_BLACK);              //about文本颜色

			break;

	}
	return 0;
}

int CVICALLBACK AboutBtnCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			 
			SetPanelPos(ABOUTPanel, 5, 170);
			SetPanelSize(ABOUTPanel, 350, 650);
			DisplayPanel(ABOUTPanel);
			
		    HidePanel (ENVPanel); 
			HidePanel (GRAPHPanel);
		
			
			SetCtrlAttribute (settingsPanel, SETTINGS_ABOUTBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG_PRESSED);   //about背景色
	     	SetCtrlAttribute (settingsPanel, SETTINGS_ABOUTBTN, ATTR_TEXT_COLOR, VAL_WHITE);              //about文本颜色
			
			SetCtrlAttribute (settingsPanel, SETTINGS_GRAPHBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);           //graph背景色
	     	SetCtrlAttribute (settingsPanel, SETTINGS_GRAPHBTN, ATTR_TEXT_COLOR, VAL_BLACK);              //graph文本颜色
			
			SetCtrlAttribute (settingsPanel, SETTINGS_PRJBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);             //environment背景色
	     	SetCtrlAttribute (settingsPanel, SETTINGS_PRJBTN, ATTR_TEXT_COLOR, VAL_BLACK);                //environment文本颜色
			break;

	}
	return 0;
}
