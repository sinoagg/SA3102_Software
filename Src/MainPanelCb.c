#include <rs232.h>
#include "MainPanel.h"

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
#include <utility.h>
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
#include "table.h"
#include "I_T_Panel.h"
#include "SetPanelCB.h"
#include "File.h"
//==============================================================================
// Constants
#define TWO_TERMINAL 0
#define EXP_I_V 1
#define EXP_V_I 2
#define EXP_I_T 3
#define EXP_V_T 4
#define EXP_R_T 5
#define FOUR_TERMINAL 16
#define EXP_ID_VDS 17
#define EXP_ID_VGS 18
#define VAL_TEXTBG                        0xF0F0F0L    //δ��ѡ�б���ɫ
#define VAL_TEXTBG_PRESSED                0x065279L    //��ѡ�б���
//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables
int TimerID;
char configSavePath[512]={0};
FileLableTypeDef *pFileLable[64];									//������FileLable��ָ�룬���ֻ�ܼ���һ���ļ����µ�64���ļ�
PrjHandleTypeDef SingleProject[64];									
Graph_TypeDef Graph;
char ABC[11][20] ={"A","B","C","D","E","F","G","H","I","J","K"};
char Table_title_IV[11][20] ={"Current(A)","Voltage(mV)","Current(A)","Voltage(mV)"};
char Table_title_VI[11][20] ={"Voltage(mV)","Current(A)","Voltage(mV)","Current(A)"}; 
char Table_title_IT[11][20] ={"Current(A)","Time(S)","Current(A)","Time(S)"};
char Table_title_RT[11][20] ={"Resistance(��)","Time(S)","Resistance(��)","Time(S)"};

//==============================================================================
// Global functions
static void DispRuntime(int display)
{ 
	SetCtrlAttribute (hBasicSamplePanel, SAMPLE_CFG_TXT_RUNTIME, ATTR_VISIBLE, display);
	SetCtrlAttribute (hBasicSamplePanel, SAMPLE_CFG_RUNTIME, ATTR_VISIBLE, display); 
	SetCtrlAttribute (hBasicSamplePanel, SAMPLE_CFG_TXT_S, ATTR_VISIBLE, display);
}
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

		if(CGS_comSelect>0)
		CloseCom(CGS_comSelect);
		if(comSelect>0)
		CloseCom(comSelect);
		QuitUserInterface(0); 
			break;
	}
	return 0;
}
static void InitSingleProject(PrjHandleTypeDef *pSingleProject)
{
	int i;
	for(i=0;i<64;i++)
	{
		(pSingleProject+i)->index=-1;	
	}
}

void Explist()
{
	int index;
	GetCtrlIndex(expListPanel, EXP_LIST_EXPLIST, &index);
	if(index==EXP_I_V)
	{
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "V(mV)");		  //graph1������
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "I(mA)");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1X, "V1");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1XUNIT, "mV");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1Y, "I1");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1YUNIT, "mA");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2X, "V2");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2XUNIT, "mV");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2Y, "I2");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2YUNIT, "mA");
		}
	else if(index==EXP_V_I)
	{
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "I(mA)");
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "V(mV)");		//graph1������
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1X, "I1");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1XUNIT, "mA");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1Y, "V1");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1YUNIT, "mV");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2X, "I2");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2XUNIT, "mA");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2Y, "V2");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2YUNIT, "mV");
	}
	else if(index==EXP_I_T)
	{
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "T(ms)");
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "I(mA)");		   //graph1������
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1X, "T1");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1XUNIT, "ms");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1Y, "I1");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1YUNIT, "mA");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2X, "T2");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2XUNIT, "ms");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2Y, "I2");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2YUNIT, "mA");
	}
	else if(index==EXP_V_T)
	{
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "T(ms)");
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "V(mV)");		  //graph1������
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1X, "T1");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1XUNIT, "ms");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1Y, "V1");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1YUNIT, "mV");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2X, "T2");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2XUNIT, "ms");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2Y, "V2");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2YUNIT, "mV");
	}
	else if(index==EXP_R_T)
	{
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "T(ms)");
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "R(��)");		   //graph1������
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1X, "T1");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1XUNIT, "ms");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1Y, "R1");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1YUNIT, "��");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2X, "T2");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2XUNIT, "ms");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2Y, "R2");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2YUNIT, "��");
	}
	else
	{
	}
}

void Runkeyaction()//���а�ť���º������һϵ�ж���
{
	SetCtrlAttribute (mainPanel, MAIN_PANEL_RUN, ATTR_DIMMED,1);         //���� ��ʼ��ť      
    SetCtrlAttribute (mainPanel, MAIN_PANEL_STOP, ATTR_DIMMED, 0);       //�ָ� ֹͣ��ť
    SetCtrlAttribute (mainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED,1);        //���� ���水ť
	
	SetPanelPos(resultPanel, 105, 305);  
    SetPanelSize(resultPanel, 65, 1293);      
	DisplayPanel(resultPanel);  

	SetPanelPos(graphDispPanel, 172, 305);  
    SetPanelSize(graphDispPanel, 834, 1293);
	DisplayPanel(graphDispPanel);
		
	SetPanelPos(hResultDispPanel, 105, 1600);
	SetPanelSize(hResultDispPanel, 449, 300);
	DisplayPanel(hResultDispPanel);
		
	SetPanelPos(hEnvResultPanel, 556, 1600);
	SetPanelSize(hEnvResultPanel, 449, 300);
	DisplayPanel(hEnvResultPanel);
	
	DisplayImageFile (mainPanel, MAIN_PANEL_SELECT, "Resource\\Select.ico");
	DisplayImageFile (mainPanel, MAIN_PANEL_CONFIGURE, "Resource\\Configure.ico"); 
	DisplayImageFile (mainPanel, MAIN_PANEL_ANALYZE, "Resource\\Analyze_pressed.ico");
}

/*

	1���õ��û����õĲ���


*/
void ProtocolCfg(unsigned char comSelect, unsigned char devAddr1, unsigned char devAddr2,unsigned char expType, unsigned char* pmeasUartTxBuf1,unsigned char* pmeasUartTxBuf2)
{
	int graphIndex=1;
	int numOfCurve=2;
	int numOfDots=100;
	switch((enum ExpType)expType)
	{
		case NO_SWEEP_IV:
			Table_ATTR.column = 4 ;   		//����
			Table_ATTR.column_width = 300;  //�п�
			Table_init(Table_title_IV, Table_ATTR.column, Table_ATTR.column_width );
			
			GetTestPara(&II_T_Panel, &TestPara1);  //�õ�Դ�� 1 �û����ò���
			GetTestPara(&II_T_Panel2, &TestPara2); //�õ�Դ�� 2 �û����ò���
			
			numOfDots = abs(TestPara1.Current_Start - TestPara1.Current_Stop)/TestPara1.Current_Step;
			graphInit(graphIndex, numOfCurve, numOfDots, &Graph);
			Graph.pGraphAttr->xAxisHead = TestPara1.Current_Start;
			Graph.pGraphAttr->xAxisTail = TestPara1.Current_Stop;
			SetAxisScalingMode(graphDispPanel,GRAPHDISP_GRAPH1,VAL_BOTTOM_XAXIS,VAL_MANUAL,Graph.pGraphAttr->xAxisHead,Graph.pGraphAttr->xAxisTail);
			
			break;
		case NO_SWEEP_VI:
			
			Table_ATTR.column = 4 ;   		//����
			Table_ATTR.column_width = 300;  //�п�
			Table_init(Table_title_VI, Table_ATTR.column, Table_ATTR.column_width );
			
			GetTestPara(&II_T_Panel, &TestPara1);  //�õ�Դ�� 1 �û����ò���
			GetTestPara(&II_T_Panel2, &TestPara2); //�õ�Դ�� 2 �û����ò���
			
			
			numOfDots = abs(TestPara1.Voltage_Start - TestPara1.Voltage_Stop)/TestPara2.Voltage_Stop;
			graphInit(graphIndex, numOfCurve, numOfDots, &Graph);
			Graph.pGraphAttr->xAxisHead = TestPara1.Voltage_Start;   
			Graph.pGraphAttr->xAxisTail = TestPara1.Voltage_Stop;
			SetAxisScalingMode(graphDispPanel,GRAPHDISP_GRAPH1,VAL_BOTTOM_XAXIS,VAL_MANUAL,Graph.pGraphAttr->xAxisHead,Graph.pGraphAttr->xAxisTail);
			
			break;
		case NO_SWEEP_IT:
			Graph.X_Axis_Max = 100;
			Graph_Temp.X_Axis_Max=100;
			Table_ATTR.column = 4 ;   		//����
			Table_ATTR.column_width = 300;  //�п�
			Table_init(Table_title_IT, Table_ATTR.column, Table_ATTR.column_width );
			
			GetTestPara(&II_T_Panel, &TestPara1);  //�õ�Դ�� 1 �û����ò���
			GetTestPara(&II_T_Panel2, &TestPara2); //�õ�Դ�� 2 �û����ò���
			
			numOfDots =TestPara1.runTime/TestPara1.timeStep; 
			graphInit(graphIndex, numOfCurve, numOfDots, &Graph);
			
			//SetAxisScalingMode (graphDispPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, 0, Graph.X_Axis_Max);//���� X ��ķ�Χ
			SetAxisScalingMode (graphDispPanel, GRAPHDISP_GRAPH2, VAL_BOTTOM_XAXIS, VAL_MANUAL, 0, Graph_Temp.X_Axis_Max);//���� X ��ķ�Χ
			
			break;
		case NO_SWEEP_RT:
			Graph.X_Axis_Max = 100;
			Graph_Temp.X_Axis_Max=100;
			Table_ATTR.column = 4 ;   		//����
			Table_ATTR.column_width = 300;  //�п�
			Table_init(Table_title_RT, Table_ATTR.column, Table_ATTR.column_width );
			GetTestPara(&II_T_Panel, &TestPara1);  //�õ�Դ�� 1 �û����ò���
			GetTestPara(&II_T_Panel2, &TestPara2); //�õ�Դ�� 2 �û����ò���
			
			numOfDots =TestPara1.runTime/TestPara1.timeStep; 
			graphInit(graphIndex, numOfCurve, numOfDots, &Graph);
			
			SetAxisScalingMode (graphDispPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, 0, Graph.X_Axis_Max);//���� X ��ķ�Χ
			SetAxisScalingMode (graphDispPanel, GRAPHDISP_GRAPH2, VAL_BOTTOM_XAXIS, VAL_MANUAL, 0, Graph_Temp.X_Axis_Max);//���� X ��ķ�Χ
			break;
	}
	graphInit(graphIndex, 3, numOfDots, &Graph_Temp);
	PrepareCfgTxData(&TestPara1, &TestPara2, devAddr1, devAddr2, expType, pmeasUartTxBuf1,pmeasUartTxBuf2); //�ֱ���  Դ��1  Դ��2 �洢���� �����û������ �������� 
	if(devAddr1 == 0x01)	//�ж��Ƿ�ΪԴ�� 1 ��ַ��Ϊ������ Դ�� 1 ��������
	ComWrt(comSelect, (const char*)pmeasUartTxBuf1, SA31_UART_TX_LEN); 
	Delay(0.2);
	if(devAddr2 == 0x02)	//�ж��Ƿ�ΪԴ�� 2 ��ַ��Ϊ������ Դ�� 2 ��������  
	ComWrt(comSelect, (const char*)pmeasUartTxBuf2, SA31_UART_TX_LEN);
}

//===================================================
//   RunCallback

int CVICALLBACK RunCallback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	int expType;
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			SetCtrlAttribute(graphDispPanel, GRAPHDISP_GRAPH1, ATTR_ENABLE_ZOOM_AND_PAN, 1 );	//��������ͼ����ͨ�������̷Ŵ�����С
			SetCtrlAttribute(graphDispPanel, GRAPHDISP_GRAPH2, ATTR_ENABLE_ZOOM_AND_PAN, 1 );	//��������ͼ����ͨ�������̷Ŵ�����С
			
			GetCtrlVal (hSettingsGraphPanel, SETGRAPH_GRAPH2CLR1, &graph2tempclr);				//�õ��¶�ʪ��ѹ���������ߵ���ɫ
			GetCtrlVal (hSettingsGraphPanel, SETGRAPH_GRAPH2CLR2, &graph2humclr);
			GetCtrlVal (hSettingsGraphPanel, SETGRAPH_GRAPH2CLR3, &graph2preclr);
			
			Explist();
			Runkeyaction();																//���а�ť���º������һϵ�ж���
			DeleteGraphPlot (graphDispPanel, GRAPHDISP_GRAPH1,-1 , VAL_IMMEDIATE_DRAW); //�������ͼ�ϵ���������
			DeleteGraphPlot (graphDispPanel, GRAPHDISP_GRAPH2,-1 , VAL_IMMEDIATE_DRAW); //�������ͼ�ϵ��������� 
			DeleteTableRows (tablePanel, TABLE_TABLE1, 1, -1);							//������ 
			DeleteTableColumns (tablePanel, TABLE_TABLE1, 1, -1);		
		
			if(GetCtrlVal(expListPanel, EXP_LIST_EXPLIST, &expType)<0)  //ÿ�ο�ʼ֮ǰ�ж�һ���û�ѡ��� ����ģʽ
				return -1;
			TestPara1.testMode = expType; //Դ�� 1 ��������
			TestPara2.testMode = expType; //Դ�� 1 ��������
			ProtocolCfg(comSelect, select_Addr1, select_Addr2,(unsigned char)expType, measUartTxBuf1,measUartTxBuf2);//�õ��û������ò���  ������
			//SetCtrlAttribute (mainPanel, MAIN_PANEL_TIMER, ATTR_INTERVAL, TestPara1.timeStep * 0.001);  //����ͬ���ص�������ʱֵ ��ʱ���Ͳ�ѯ����
			Delay(1); //��ʱ
			TimerID = NewAsyncTimer(1,-1, 1, TimerCallback, 0);		//Create Asynchronous (Timer time interval 1s, continue generating evernt, enabled, callback function name, passing no pointer)  
			ProtocolRun(comSelect, select_Addr1, select_Addr2, measUartTxBuf1, measUartTxBuf2);		//send RUN command to instrument via UART
			//SetCtrlAttribute (mainPanel, MAIN_PANEL_TIMER, ATTR_ENABLED, 1);       //����ͬ����ʱ�� 
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
		case EVENT_LEFT_CLICK_UP:
		  	 SetCtrlAttribute (mainPanel, MAIN_PANEL_STOP, ATTR_DIMMED,1);      //���� ֹͣ��ť      
		     SetCtrlAttribute (mainPanel, MAIN_PANEL_RUN, ATTR_DIMMED, 0);      //�ָ� ��ʼ��ť
			 SetCtrlAttribute (mainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED, 0);     //�ָ� ���水ť
			 X1 = 0;  
			 X2 = 0;
			 //SetCtrlAttribute (mainPanel, MAIN_PANEL_TIMER, ATTR_ENABLED, 0);   //�ر�ͬ����ʱ�� ֹͣ���Ͳ�ѯ����
			 ProtocolStop(comSelect, select_Addr1, select_Addr2, measUartTxBuf1, measUartTxBuf2);  //����ָֹͣ��
			 DiscardAsyncTimer(TimerID);//�ر��첽��ʱ��  ֹͣ������ʾ
			break;
	}
	return 0;
}

//===================================================
//   SaveCallback

int CVICALLBACK SaveCallback (int panel, int control, int event,void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:			    //��Save�����������ʱ 
			DisplayImageFile (mainPanel, MAIN_PANEL_SAVE, "Resource\\Save_pressed.ico");
			break;
		case EVENT_LEFT_CLICK_UP:		    //������ͷ�ʱ  
			DisplayImageFile (mainPanel, MAIN_PANEL_SAVE, "Resource\\Save.ico");
			if(FileSelectPopupEx("C:\\SINOAGG\\SA3102\\", ".sac", "*.sac", "Select Path", VAL_OK_BUTTON, 0, 1,  configSavePath)>0)
			SaveConfigToFile(configSavePath);
			break;
	}
	return 0;
}
static int SaveAllPanelState(char* pConfigSavePath)
{
	SavePanelState(II_T_Panel.panelHandle, pConfigSavePath, 1); //IT����ֵ					
	SavePanelState(hBasicSamplePanel, pConfigSavePath, 10);	   //�û����� ����ֵ
	SavePanelState(hAdvanceSamplePanel, pConfigSavePath, 11);  //�߼��������ֵ
	SavePanelState(hEnvCfgPanel, pConfigSavePath, 14);
	SavePanelState(ENVTPanel, pConfigSavePath, 15);
	SavePanelState(hSettingsGraphPanel, pConfigSavePath, 16);
	return 0;
}
static int SaveConfigToFile(char* pConfigSavePath)
{
	FILE * fp = NULL;							//��ʾ�򿪵��ļ�
	fp = fopen(pConfigSavePath, "w");
	if(fp == NULL)
	{
		MessagePopup ("Error", "Invalid Path, please select path to save configurations.");
		if(FileSelectPopup ("C:\\SINOAGG\\SA3102\\", ".sac", "*.sac", "Select Path", VAL_OK_BUTTON, 0, 1, 1, 1, pConfigSavePath)<0)
			return -1;
	}
	else
	{
		int maxCommentSize=255;
		char description[maxCommentSize];
		PromptPopup("Message", "Please enter description for this configuration:", description, maxCommentSize-1);
		SaveAllPanelState(pConfigSavePath);		//����������������
		fp = fopen(pConfigSavePath, "a+");
		fprintf(fp, "\r\n%-61s\r\n", description);		//��������64�ַ�
		fclose(fp);//�ر��ļ�
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
		case EVENT_LEFT_CLICK_UP:			    //��Select�����������ʱ,Selectͼ��ı䣬������������״̬ 
			
			DisplayImageFile (mainPanel, MAIN_PANEL_SELECT, "Resource\\Select_pressed.ico");
			DisplayImageFile (mainPanel, MAIN_PANEL_CONFIGURE, "Resource\\Configure.ico"); 
			DisplayImageFile (mainPanel, MAIN_PANEL_ANALYZE, "Resource\\Analyze.ico");
			HidePanel( hBasicSamplePanel);		
			HidePanel( hResultDispPanel);
			HidePanel( hEnvCfgPanel);
			HidePanel(hEnvResultPanel);
			HidePanel(hAdvanceSamplePanel);
			break;
	}
	return 0;
}
//===================================================
//   Configure_Callback

int CVICALLBACK ConfigureCallback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{   
	int index;
	switch (event)
	{
 		case EVENT_LEFT_CLICK_UP:			    //��Configure�����������ʱ,Configureͼ��ı䣬������������״̬ 
				DisplayImageFile (mainPanel, MAIN_PANEL_SELECT, "Resource\\Select.ico");
				DisplayImageFile (mainPanel, MAIN_PANEL_CONFIGURE, "Resource\\Configure_pressed.ico"); 
				DisplayImageFile (mainPanel, MAIN_PANEL_ANALYZE, "Resource\\Analyze.ico");
			break;
		case EVENT_LEFT_CLICK:
				GetCtrlIndex(expListPanel, EXP_LIST_EXPLIST, &index);
				if(index==EXP_I_T||index==EXP_V_T||index==EXP_R_T)
				{
					SetPanelPos(II_T_Panel.panelHandle, 105, 305);
					SetPanelSize(II_T_Panel.panelHandle, 900, 1293);
					DisplayPanel(II_T_Panel.panelHandle);
					DispRuntime(1);
				}
				else if(index==EXP_I_V||index==EXP_V_I)
				{
					SetPanelPos(II_T_Panel.panelHandle, 105, 305);
					SetPanelSize(II_T_Panel.panelHandle, 900, 1293);
					DisplayPanel(II_T_Panel.panelHandle);
					DispRuntime(0); 
				}
				else if(index==EXP_ID_VDS)
				{
					SetPanelPos(IdVdPanel, 105, 305);
					SetPanelSize(IdVdPanel, 900, 1293);
					DisplayPanel(IdVdPanel);
					DispRuntime(1);
				}
				else if(index==EXP_ID_VGS)
				{
				
					SetPanelPos(IdVgPanel, 105, 305);
					SetPanelSize(IdVgPanel, 900, 1293);
					DisplayPanel(IdVgPanel);
					DispRuntime(1);
				}
				else
				{
					DispRuntime(1);
					//TODO  
				}
				SetPanelPos(hBasicSamplePanel, 105, 1600);
				SetPanelSize(hBasicSamplePanel, 449, 300);
				DisplayPanel(hBasicSamplePanel);
				
				SetPanelPos(hEnvCfgPanel, 556, 1600);
				SetPanelSize(hEnvCfgPanel, 449, 300);
				DisplayPanel(hEnvCfgPanel);
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
			Explist();
			SetPanelPos(resultPanel, 105, 305);  
		    SetPanelSize(resultPanel, 65, 1293);      
	 		DisplayPanel(resultPanel);  

			SetPanelPos(graphDispPanel, 172, 305);  
		    SetPanelSize(graphDispPanel, 834, 1293); 
	 		DisplayPanel(graphDispPanel);
				
			SetPanelPos(hResultDispPanel, 105, 1600);
			SetPanelSize(hResultDispPanel, 449, 300);
			DisplayPanel(hResultDispPanel);
				
			SetPanelPos(hEnvResultPanel, 556, 1600);
			SetPanelSize(hEnvResultPanel, 449, 300);
			DisplayPanel(hEnvResultPanel);
			break;
 		case EVENT_LEFT_CLICK_UP:			    //��Analyze�����������ʱ,Analyzeͼ��ı䣬������������״̬�� 
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
			InstallPopup (setPanel);  //����settingsPanel
			HidePanel (hSettingsGraphPanel);
			HidePanel (aboutPanel);
			SetPanelPos(ENVTPanel, 5, 160);
			SetPanelSize(ENVTPanel, 380, 660);
			DisplayPanel(ENVTPanel);
			
			SetCtrlAttribute (setPanel, SETTINGS_PRJBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG_PRESSED);   //project����ɫ
	     	SetCtrlAttribute (setPanel, SETTINGS_PRJBTN, ATTR_TEXT_COLOR, VAL_WHITE);              //project�ı���ɫ
			
			SetCtrlAttribute (setPanel, SETTINGS_GRAPHBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);         //graph����ɫ
	     	SetCtrlAttribute (setPanel, SETTINGS_GRAPHBTN, ATTR_TEXT_COLOR, VAL_BLACK);            //graph�ı���ɫ
			
			SetCtrlAttribute (setPanel, SETTINGS_ABOUTBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);         //about����ɫ
	     	SetCtrlAttribute (setPanel, SETTINGS_ABOUTBTN, ATTR_TEXT_COLOR, VAL_BLACK);            //about�ı���ɫ
		break;
	}
	return 0;
}
static int LoadAndDispPrj(FileLableTypeDef *pFileLable, char index)						//indexΪprj����λ������
{
	int hSinglePrjPanel;
	if ((hSinglePrjPanel = LoadPanel (projectPanel, "ProjectPanel.uir", DEFPANEL)) < 0)		//load projects panel
		return -1;
	SetCtrlVal(hSinglePrjPanel, DEFPANEL_NAME, pFileLable->FileName);
	SetCtrlVal(hSinglePrjPanel, DEFPANEL_DATE, pFileLable->FileDate);
	SetCtrlVal(hSinglePrjPanel, DEFPANEL_TIME, pFileLable->FileTime);
	SetCtrlVal(hSinglePrjPanel, DEFPANEL_DESC, pFileLable->FileDesc);
	SetPanelPos(hSinglePrjPanel, index*117, -10);
	SetPanelSize(hSinglePrjPanel, 115, 1300);
	DisplayPanel(hSinglePrjPanel);
	return hSinglePrjPanel;
}

static int LoadAllProject(char* pProjectSavePath)
{
	char tempFileName[512];
	char tempFilePath[512];
	char index=0;
	char tempPathToSearch[512];
	InitSingleProject(SingleProject);
	sprintf(tempPathToSearch, "%s%s", pProjectSavePath, "\\*.sac");
	if(0==GetFirstFile(tempPathToSearch, 1, 1, 1, 1, 1, 0, tempFileName))		//�����һ���ļ���ȡ�ɹ�
	{
		sprintf(tempFilePath, "%s%s%s", pProjectSavePath, "\\", tempFileName);
		pFileLable[index] = (FileLableTypeDef *)malloc(sizeof(FileLableTypeDef));
		InitFileLable(pFileLable[index], tempFilePath); 				//���ļ�ʱ����ļ����Ƽ�description����չʾ
		SingleProject[index].hSinglePrjPanel = LoadAndDispPrj(pFileLable[index], index);
		SingleProject[index].index=index;
		index++;
		while(GetNextFile(tempFileName)==0)								//�����ȡ��ȷ��������ȡ
		{
			sprintf(tempFilePath, "%s%s%s", pProjectSavePath, "\\", tempFileName);
			pFileLable[index] = (FileLableTypeDef *)malloc(sizeof(FileLableTypeDef));
			InitFileLable(pFileLable[index], tempFilePath); //���ļ�ʱ����ļ����Ƽ�description
			SingleProject[index].hSinglePrjPanel = LoadAndDispPrj(pFileLable[index], index);
			SingleProject[index].index=index; 
			index++;
		}
	}
	return 0;
}

int CVICALLBACK ProjectCallback (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch(event)
	{
		case EVENT_LEFT_CLICK_UP:
			InstallPopup (proPanel);
			SetPanelPos(projectPanel, 85, 0);
			SetPanelSize(projectPanel, 380, 1250);
			DisplayPanel(projectPanel);
			LoadAllProject(ProjectSavePath);
		break;
	}	 
	return 0;
}
