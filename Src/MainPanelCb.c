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
#include <windows.h>
#include "AbnormalDataCache.h"
#include <cvintwrk.h>
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
#include "ResultMenuPanel.h"
#include "table.h"
#include "SetPanelCB.h"
#include "File.h"
#include <rs232.h>
#include "MainPanel.h"
#include "main.h"
#include "Tools.h"
#include "SetPanel.h"
#include "cvixml.h"

//==============================================================================
// Constants
#define TWO_TERMINAL 0
#define EXP_I_V 1
#define EXP_V_I 2
#define EXP_I_T 3
#define EXP_V_T 4
#define EXP_R_T 5
#define THREE_TERMINAL 12 
#define FOUR_TERMINAL 16
#define EXP_ID_VDS 17
#define EXP_ID_VGS 18
#define VAL_TEXTBG               0xF0F0F0L    //δ��ѡ�б���ɫ
#define VAL_TEXTBG_PRESSED       0x065279L    //��ѡ�б���
#define VAL_BG_ENABLE            0x065279L 
#define VAL_BG_DISABLE           0xB2C9D5L 
//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables

CmtThreadFunctionID  abnmDCthreadFunctionID; 

int TimerID;
char configSavePath[512]={0};
FileLableTypeDef *pFileLable[64];									//������FileLable��ָ�룬���ֻ�ܼ���һ���ļ����µ�64���ļ�
PrjHandleTypeDef SingleProject[64];									
Graph_TypeDef Graph;
Graph_TypeDef Graph_Temp;
char ABC1[11][20] ={"A","B","C","D","E","F","G","H","I","J","K"};
char Table_title_IV[11][20] ={"V1(mV)","I1(A)","V2(mV)","I2(A)"};
char Table_title_VI[11][20] ={"V1(mV)","I1(A)","V2(mV)","I2(A)"}; 
char Table_title_IT[11][20] ={"Time(s)","I1(A)","Time(s)","I2(A)"};
char Table_title_RT[11][20] ={"Time(s)","R1(��)","Time(s)","R2(��)"};

//==============================================================================
// Global functions
static void DispRuntime(int display)
{ 
	SetCtrlAttribute (hBasicSamplePanel, SAMPLE_CFG_TXT_RUNTIME, ATTR_VISIBLE, display);
	SetCtrlAttribute (hBasicSamplePanel, SAMPLE_CFG_RUNTIME, ATTR_VISIBLE, display); 
	SetCtrlAttribute (hBasicSamplePanel, SAMPLE_CFG_TXT_S, ATTR_VISIBLE, display);
}

int CVICALLBACK AbnmDCThreadFunction (void *functionData);
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
			if(controlComPort>0)
			CloseCom(controlComPort);
			if(measureComPort>0)
			CloseCom(measureComPort);
			ShutDownExcelCB(); 
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
void Dispgraph()
{
	int index;
	GetCtrlIndex(expListPanel, EXP_LIST_EXPLIST, &index);
	if(index==EXP_I_V)
	{
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "V(mV)");		  //graph1������
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "I(A)");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1X, "V");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1XUNIT, "mV");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1Y, "I");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1YUNIT, "A");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2X, "V");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2XUNIT, "mV");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2Y, "I");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2YUNIT, "A");
	}
	else if(index==EXP_V_I)
	{
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "I(mA)");
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "V(V)");		//graph1������
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1X, "I");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1XUNIT, "A");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1Y, "V");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1YUNIT, "mV");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2X, "I");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2XUNIT, "A");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2Y, "V");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2YUNIT, "mV");
	}
	else if(index==EXP_I_T)
	{
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "t(s)");
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "I(A)");		   //graph1������
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1X, "t");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1XUNIT, "s");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1Y, "I");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1YUNIT, "A");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2X, "t");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2XUNIT, "s");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2Y, "I");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2YUNIT, "A");
	}
	else if(index==EXP_V_T)
	{
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "t(s)");
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "V(mV)");		  //graph1������
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1X, "t");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1XUNIT, "s");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1Y, "V");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1YUNIT, "mV");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2X, "t");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2XUNIT, "s");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2Y, "V");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2YUNIT, "mV");
	}
	else if(index==EXP_R_T)
	{
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_XNAME, "t(s)");
		SetCtrlAttribute (graphDispPanel, GRAPHDISP_GRAPH1, ATTR_YNAME, "R(��)");		   //graph1������
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1X, "t");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1XUNIT, "s");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1Y, "R");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU1YUNIT, "��");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2X, "t");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2XUNIT, "s");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2Y, "R");
		SetCtrlVal (hResultDispPanel, SAMPLE_SMU2YUNIT, "��");
	}
	else
	{
	}
}
void RunKeyAction()					//���а�ť���º������һϵ�ж���
{
	SetCtrlAttribute (mainPanel, MAIN_PANEL_RUN, ATTR_DIMMED,1);         //���� ��ʼ��ť      
    SetCtrlAttribute (mainPanel, MAIN_PANEL_STOP, ATTR_DIMMED, 0);       //�ָ� ֹͣ��ť
    SetCtrlAttribute (mainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED,1);        //���� ���水ť
	SetCtrlAttribute (mainPanel, MAIN_PANEL_SETTINGS, ATTR_DIMMED,1);        //���� ���水ť  
	
	SetPanelPos(resultPanel, 105, 305);  
	DisplayPanel(resultPanel);  

	SetPanelPos(graphDispPanel, 172, 305);
	DisplayPanel(graphDispPanel);
		
	SetPanelPos(hResultDispPanel, 105, 1600);
	DisplayPanel(hResultDispPanel);
		
	SetPanelPos(hEnvResultPanel, 556, 1600);
	DisplayPanel(hEnvResultPanel);
	
	DisplayImageFile (mainPanel, MAIN_PANEL_SELECT, "Resource\\Select.ico");
	DisplayImageFile (mainPanel, MAIN_PANEL_CONFIGURE, "Resource\\Configure.ico"); 
	DisplayImageFile (mainPanel, MAIN_PANEL_ANALYZE, "Resource\\Analyze_pressed.ico");
	DisplayImageFile (resultPanel, RESULTMENU_TABLE, "Resource\\Table.ico"); 
	DisplayImageFile (resultPanel, RESULTMENU_GRAPH, "Resource\\Graph_pressed.ico"); 
	DispSingleGraph();
	
	SetCtrlAttribute(graphDispPanel, GRAPHDISP_GRAPH1, ATTR_ENABLE_ZOOM_AND_PAN, 1 );			//��������ͼ����ͨ�������̷Ŵ�����С
	SetCtrlAttribute(graphDispPanel, GRAPHDISP_GRAPH2, ATTR_ENABLE_ZOOM_AND_PAN, 1 );			//��������ͼ����ͨ�������̷Ŵ�����С
	
	DeleteGraphPlot (graphDispPanel, GRAPHDISP_GRAPH1,-1 , VAL_IMMEDIATE_DRAW); 				//�������ͼ�ϵ���������
	DeleteGraphPlot (graphDispPanel, GRAPHDISP_GRAPH2,-1 , VAL_IMMEDIATE_DRAW); 				//�������ͼ�ϵ��������� 
	DeleteTableRows (tablePanel, TABLE_TABLE1, 1, -1);											//������ 
	DeleteTableColumns (tablePanel, TABLE_TABLE1, 1, -1);

}
void StopKeyAction()																			//ֹͣ��ť���º������һϵ�ж���
{
	DiscardAsyncTimer(TimerID);									 							 	//�ر��첽��ʱ��  ֹͣ������ʾ 
	Graph.pCurveArray->numOfPlotDots=0;
	SetCtrlAttribute (mainPanel, MAIN_PANEL_STOP, ATTR_DIMMED,1);      							//���� ֹͣ��ť      
	SetCtrlAttribute (mainPanel, MAIN_PANEL_RUN, ATTR_DIMMED, 0);      							//�ָ� ��ʼ��ť
	SetCtrlAttribute (mainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED, 0);     							//�ָ� ���水ť
	SetCtrlAttribute (mainPanel, MAIN_PANEL_SETTINGS, ATTR_DIMMED,0); 
	ProtocolStop(measureComPort, select_Addr1, select_Addr2, measUartTxBuf1, measUartTxBuf2);  		//����ָֹͣ��
	Delay(0.050);																				
	ProtocolStop(measureComPort, select_Addr1, select_Addr2, measUartTxBuf1, measUartTxBuf2);  		//����ָֹͣ��
	FlushInQ(measureComPort);	   																	//Clear input and output buffer
	FlushOutQ(measureComPort);
}
void ProtocolCfg(unsigned char measureComPort, unsigned char devAddr1, unsigned char devAddr2,unsigned char expType, unsigned char* pmeasUartTxBuf1,unsigned char* pmeasUartTxBuf2)
{
	int graphIndex=1;
	int numOfCurve=2;
	int numOfDots=100;
	int temp = 0;
	int numOfDots1,numOfDots2;
	Table_TypeDef Table_ATTR;
	switch((enum ExpType)expType)
	{
		case NO_SWEEP_IV:
			Table_ATTR.column = 4 ;   				//����
			Table_ATTR.column_width = 200;  		//�п�
			
			GetTestPara(&I_V_Panel1, &TestPara1);  //�õ�Դ�� 1 �û����ò���
			GetTestPara(&I_V_Panel2, &TestPara2);  //�õ�Դ�� 2 �û����ò���
			
			numOfDots1 = abs(TestPara1.Current_Start - TestPara1.Current_Stop)/TestPara1.Current_Step +1;
			numOfDots2 = abs(TestPara2.Current_Start - TestPara2.Current_Stop)/TestPara2.Current_Step +1;
			numOfDots = numOfDots1 >= numOfDots2 ? numOfDots1:numOfDots2;
			Table_ATTR.row=numOfDots; 
			Table_init(Table_title_IV, Table_ATTR.column, Table_ATTR.column_width,Table_ATTR.row);  
			
			graphInit(graphIndex, numOfCurve, numOfDots, &Graph);
			Graph.pCurveArray->numOfTotalDots = numOfDots; 
			Graph.pGraphAttr->xAxisHead = TestPara1.Current_Start;
			Graph.pGraphAttr->xAxisTail = TestPara1.Current_Stop;
			SetAxisScalingMode(graphDispPanel,GRAPHDISP_GRAPH1,VAL_BOTTOM_XAXIS,VAL_MANUAL,Graph.pGraphAttr->xAxisHead,Graph.pGraphAttr->xAxisTail);
			
			break;
		case NO_SWEEP_VI:
			Table_ATTR.column = 4 ;   				//����
			Table_ATTR.column_width = 200;  		//�п�
			
			
			GetTestPara(&V_I_Panel1, &TestPara1);  //�õ�Դ�� 1 �û����ò���
			GetTestPara(&V_I_Panel2, &TestPara2);  //�õ�Դ�� 2 �û����ò���
			
			GetCtrlVal(VIPanel,PANEL_V_I_START1UNIT,&(temp));
			TestPara1.rangeMode = (temp<<4)|TestPara1.rangeMode; 
			
			
			
			numOfDots1 = abs(TestPara1.Voltage_Start - TestPara1.Voltage_Stop)/TestPara1.Voltage_Step + 1;
			numOfDots2 = abs(TestPara2.Voltage_Start - TestPara2.Voltage_Stop)/TestPara2.Voltage_Step + 1; 
			numOfDots = numOfDots1 >= numOfDots2 ? numOfDots1:numOfDots2;
			Table_ATTR.row=numOfDots; 
			Table_init(Table_title_VI, Table_ATTR.column, Table_ATTR.column_width,Table_ATTR.row);
			
			graphInit(graphIndex, numOfCurve, numOfDots, &Graph);
			Graph.pGraphAttr->xAxisHead = TestPara1.Voltage_Start;   
			Graph.pGraphAttr->xAxisTail = TestPara1.Voltage_Stop;
			SetAxisScalingMode(graphDispPanel,GRAPHDISP_GRAPH1,VAL_BOTTOM_XAXIS,VAL_MANUAL,Graph.pGraphAttr->xAxisHead,Graph.pGraphAttr->xAxisTail);
			
			break;
		case NO_SWEEP_IT:
			Graph.X_Axis_Max = 100;
			Graph_Temp.X_Axis_Max=100;
			Table_ATTR.column = 4 ;   				//����
			Table_ATTR.column_width = 200;			//�п�
			
			GetTestPara(&I_T_Panel1, &TestPara1);  //�õ�Դ�� 1 �û����ò���
			GetTestPara(&I_T_Panel2, &TestPara2);  //�õ�Դ�� 2 �û����ò���
			
			numOfDots1 = (TestPara1.runTime*1000)/TestPara1.timeStep + 1;
			numOfDots2 = (TestPara2.runTime*1000)/TestPara2.timeStep + 1;
			numOfDots = numOfDots1 >= numOfDots2 ? numOfDots1:numOfDots2;
			Table_ATTR.row=numOfDots; 
			Table_init(Table_title_IT, Table_ATTR.column, Table_ATTR.column_width,Table_ATTR.row);  
			graphInit(graphIndex, numOfCurve, numOfDots, &Graph);
			Graph.pCurveArray->numOfTotalDots = numOfDots;
			
			Graph.pGraphAttr->xAxisTail=100;
			Graph.pGraphAttr->yAxisHead=1.008e-7;
	   		Graph.pGraphAttr->yAxisTail=1.0134e-7; 
			
			SetAxisScalingMode(graphDispPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, 0,Graph.pGraphAttr->xAxisTail); 
			//SetAxisScalingMode(graphDispPanel, GRAPHDISP_GRAPH1, VAL_LEFT_YAXIS, VAL_MANUAL, Graph.pGraphAttr->yAxisHead,Graph.pGraphAttr->yAxisTail);
			SetAxisScalingMode (graphDispPanel, GRAPHDISP_GRAPH2, VAL_BOTTOM_XAXIS, VAL_MANUAL, 0, Graph_Temp.X_Axis_Max);//���� X ��ķ�Χ
			
			break;
		case NO_SWEEP_RT:
			expType = 3;
			Graph.X_Axis_Max = 100;
			Graph_Temp.X_Axis_Max=100;
			Table_ATTR.column = 4 ;   				//����
			Table_ATTR.column_width = 200;  		//�п�
			GetTestPara(&R_T_Panel1, &TestPara1);   //�õ�Դ�� 1 �û����ò���
			GetTestPara(&R_T_Panel2, &TestPara2);   //�õ�Դ�� 2 �û����ò���
			
			numOfDots1 =(TestPara1.runTime*1000)/TestPara1.timeStep + 1;
			numOfDots2 =(TestPara2.runTime*1000)/TestPara2.timeStep + 1;
			numOfDots = numOfDots1 >= numOfDots2 ? numOfDots1:numOfDots2;
			Table_ATTR.row=numOfDots; 
			Table_init(Table_title_IV, Table_ATTR.column, Table_ATTR.column_width,Table_ATTR.row);  
			graphInit(graphIndex, numOfCurve, numOfDots, &Graph);
			Graph.pCurveArray->numOfTotalDots = numOfDots;
			
			Graph.pGraphAttr->xAxisTail=100;
			SetAxisScalingMode (graphDispPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, 0, Graph.pGraphAttr->xAxisTail);     //���� X ��ķ�Χ
			SetAxisScalingMode (graphDispPanel, GRAPHDISP_GRAPH2, VAL_BOTTOM_XAXIS, VAL_MANUAL, 0, Graph_Temp.X_Axis_Max);//���� X ��ķ�Χ
			break;
		case NO_SWEEP_VT:
			expType = 4;	//��������
			Graph.X_Axis_Max = 100;
			Graph_Temp.X_Axis_Max=100;
			Table_ATTR.column = 4 ;   				//����
			Table_ATTR.column_width = 200;  		//�п�
			
			GetTestPara(&V_T_Panel1, &TestPara1);  //�õ�Դ�� 1 �û����ò���
			GetTestPara(&V_T_Panel2, &TestPara2);  //�õ�Դ�� 2 �û����ò���
			
			GetCtrlVal(VTPanel,PANEL_V_T_VTSTART1UNIT,&(temp));
			TestPara1.rangeMode = (temp<<4)|TestPara1.rangeMode; 
			
			numOfDots1 =(TestPara1.runTime*1000)/TestPara1.timeStep + 1;
			numOfDots2 =(TestPara2.runTime*1000)/TestPara2.timeStep + 1;
			numOfDots = numOfDots1 >= numOfDots2 ? numOfDots1:numOfDots2;
			Table_ATTR.row=numOfDots; 
			Table_init(Table_title_IV, Table_ATTR.column, Table_ATTR.column_width,Table_ATTR.row);  
			graphInit(graphIndex, numOfCurve, numOfDots, &Graph);
			Graph.pCurveArray->numOfTotalDots = numOfDots;
			
			SetAxisScalingMode (graphDispPanel, GRAPHDISP_GRAPH1, VAL_BOTTOM_XAXIS, VAL_MANUAL, 0, Graph.X_Axis_Max);     //���� X ��ķ�Χ
			SetAxisScalingMode (graphDispPanel, GRAPHDISP_GRAPH2, VAL_BOTTOM_XAXIS, VAL_MANUAL, 0, Graph_Temp.X_Axis_Max);//���� X ��ķ�Χ
			break;
	}
	Graph.pCurveArray->numofSmu1RxDots = 0;
	Graph.pCurveArray->numofSmu2RxDots = 0;
	(Graph.pCurveArray+1)->numofSmu1RxDots = 0;
	(Graph.pCurveArray+1)->numofSmu2RxDots = 0;
	graphInit(graphIndex, 3, numOfDots + 5, &Graph_Temp);
	PrepareCfgTxData(&TestPara1, &TestPara2, devAddr1, devAddr2, expType, pmeasUartTxBuf1,pmeasUartTxBuf2); //�ֱ���  Դ��1  Դ��2 �洢���� �����û������ �������� 
	if(devAddr1 == 0x01)	//�ж��Ƿ�ΪԴ�� 1 ��ַ��Ϊ������ Դ�� 1 ��������
	ComWrt(measureComPort, (const char*)pmeasUartTxBuf1, SA31_UART_TX_LEN);
	Delay(0.05);
	if(devAddr2 == 0x02)	//�ж��Ƿ�ΪԴ�� 2 ��ַ��Ϊ������ Դ�� 2 ��������  
	ComWrt(measureComPort, (const char*)pmeasUartTxBuf2, SA31_UART_TX_LEN);
}


int CVICALLBACK AbnmDCThreadFunction (void *functionData)
{
	int n = 1; 
	while (Graph.pCurveArray->numOfPlotDots < Graph.pCurveArray->numOfTotalDots) 
	{
		if(Graph.pCurveArray->numOfPlotDots > 0 && Graph.pCurveArray->numOfPlotDots >= (Graph.pCurveArray->numOfTotalDots * n) / 10)
		{
			LaunchExcelCB();
			SaveExcelCB(tablePanel, TABLE_TABLE1);
			n +=1;
		}
	}
	return 0;
}

//===================================================
//   RunCallback

int CVICALLBACK RunCallback (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	int expType;
	int index;
	GetCtrlIndex(expListPanel, EXP_LIST_EXPLIST, &index);
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			if(index==TWO_TERMINAL||index==FOUR_TERMINAL||index==THREE_TERMINAL)
			{
				MessagePopup ("", "Please select a experiment!");
			}
			else
			{
				
				rowIndex=2;
				rowIndex2=2;
				GetCtrlVal (hAdvanceSamplePanel, SAMPLE_ADV_CURRENTMODE, &logFlag);
				GetCtrlVal (hSettingsGraphPanel, SETGRAPH_SMU1CLR, &smu1Clr);
				GetCtrlVal (hSettingsGraphPanel, SETGRAPH_SMU2CLR, &smu2Clr);
				GetCtrlVal (hSettingsGraphPanel, SETGRAPH_GRAPH2CLR1, &graph2tempclr);				//�õ��¶�ʪ��ѹ���������ߵ���ɫ
				GetCtrlVal (hSettingsGraphPanel, SETGRAPH_GRAPH2CLR2, &graph2humclr);
				GetCtrlVal (hSettingsGraphPanel, SETGRAPH_GRAPH2CLR3, &graph2preclr);
				X1 = 0;  
				X2 = 0;
				FlushInQ(measureComPort);	   														//Clear input and output buffer
				FlushOutQ(measureComPort);
				GraphDeinit(&Graph);														//�ڴ��ͷ��ڻ�ͼ֮��
				GraphDeinit(&Graph_Temp);
				Dispgraph();																//��ͬģʽ��ʾ��ͬ�ĵ�λ
				RunKeyAction();																//���а�ť���º������һϵ�ж���
				
			GetCtrlVal(mainPanel, MAIN_PANEL_SMU1, &expType);							//�ж��Ƿ�ѡ��SMU1���Ӳ���
			if(expType>0)
				select_Addr1=0x01;
			else
				select_Addr1=0x00;
			GetCtrlVal(mainPanel, MAIN_PANEL_SMU2, &expType);							//�ж��Ƿ�ѡ��SMU2���Ӳ���
			if(expType>0)
				select_Addr2=0x02;
			else
				select_Addr2=0x00;
			
				
				
			if(GetCtrlVal(expListPanel, EXP_LIST_EXPLIST, &expType)<0)  					//ÿ�ο�ʼ֮ǰ�ж�һ���û�ѡ��� ����ģʽ 
				
			if(GetCtrlVal(expListPanel, EXP_LIST_EXPLIST, &expType)<0)  					//ÿ�ο�ʼ֮ǰ�ж�һ���û�ѡ��� ����ģʽ
				return -1;
			TestPara1.testMode = expType; //Դ�� 1 ��������
			TestPara2.testMode = expType; //Դ�� 1 ��������
			ProtocolCfg(measureComPort, select_Addr1, select_Addr2,(unsigned char)expType, measUartTxBuf1,measUartTxBuf2);//�õ��û������ò���  ������
			Delay(2);//��ʱ
			ProtocolRun(measureComPort, select_Addr1, select_Addr2, measUartTxBuf1, measUartTxBuf2);		//send RUN command to instrument via UART 
			double temp=(double)TestPara1.timeStep * 0.001;
			if(temp<0.03) temp=0.03;													//�����ѯʱ����죬��������ݻ��ң���λ����Ӧ�жϹ���
			TimerID = NewAsyncTimer(temp,-1, 1, TimerCallback, 0);
			
			}
			break;
			CmtScheduleThreadPoolFunction (DEFAULT_THREAD_POOL_HANDLE, AbnmDCThreadFunction,  NULL, &abnmDCthreadFunctionID); 
	}
	return 0;
}

int CVICALLBACK RunAgainCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			
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
			
			StopKeyAction();				//ֹͣ��ť���º������һϵ�ж���

			DiscardAsyncTimer(TimerID);//�ر��첽��ʱ��  ֹͣ������ʾ
			SetCtrlAttribute (mainPanel, MAIN_PANEL_STOP, ATTR_DIMMED,1);      //���� ֹͣ��ť      
			SetCtrlAttribute (mainPanel, MAIN_PANEL_RUN, ATTR_DIMMED, 0);      //�ָ� ��ʼ��ť
			SetCtrlAttribute (mainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED, 0);     //�ָ� ���水ť
			SetCtrlAttribute (mainPanel, MAIN_PANEL_SETTINGS, ATTR_DIMMED,0); 
			//SetCtrlAttribute (mainPanel, MAIN_PANEL_TIMER, ATTR_ENABLED, 0);   //�ر�ͬ����ʱ�� ֹͣ���Ͳ�ѯ����
			ProtocolStop(measureComPort, select_Addr1, select_Addr2, measUartTxBuf1, measUartTxBuf2);  //����ָֹͣ��
			FlushInQ(measureComPort);	   														//Clear input and output buffer
			FlushOutQ(measureComPort);
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
	SavePanelState(IVPanel, pConfigSavePath, 1);
	SavePanelState(VIPanel, pConfigSavePath, 2);
	SavePanelState(I_T_Panel1.panelHandle, pConfigSavePath, 3); //IT����ֵ  
	SavePanelState(VTPanel, pConfigSavePath, 4);
	SavePanelState(RTPanel, pConfigSavePath, 5);
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
			HidePanel(hBasicSamplePanel);		
			HidePanel(hResultDispPanel);
			HidePanel(hEnvCfgPanel);
			HidePanel(hEnvResultPanel);
			HidePanel(hAdvanceSamplePanel);
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
		case EVENT_LEFT_CLICK_UP:
		
			DispResultTableGraph();
			
			SetPanelPos(resultPanel, 105, 305);       
	 		DisplayPanel(resultPanel);  
			
			SetPanelPos(hResultDispPanel, 105, 1600);
			DisplayPanel(hResultDispPanel);
				
			SetPanelPos(hEnvResultPanel, 556, 1600);
			DisplayPanel(hEnvResultPanel);

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
			DisplayPanel(ENVTPanel);
			
			SetCtrlAttribute (setPanel, SETTINGS_PRJBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG_PRESSED);   //project����ɫ
	     	SetCtrlAttribute (setPanel, SETTINGS_PRJBTN, ATTR_TEXT_COLOR, VAL_WHITE);              //project�ı���ɫ
			
			SetCtrlAttribute (setPanel, SETTINGS_GRAPHBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);         //graph����ɫ
	     	SetCtrlAttribute (setPanel, SETTINGS_GRAPHBTN, ATTR_TEXT_COLOR, VAL_BLACK);            //graph�ı���ɫ
			
			SetCtrlAttribute (setPanel, SETTINGS_ABOUTBTN, ATTR_TEXT_BGCOLOR, VAL_TEXTBG);         //about����ɫ
	     	SetCtrlAttribute (setPanel, SETTINGS_ABOUTBTN, ATTR_TEXT_COLOR, VAL_BLACK);            //about�ı���ɫ
			
			GetCtrlVal (hSettingsGraphPanel, SETGRAPH_SMU1CLR, &smu1ClrOld);
			GetCtrlVal (hSettingsGraphPanel, SETGRAPH_SMU2CLR, &smu2ClrOld);
			GetCtrlVal (hSettingsGraphPanel, SETGRAPH_GRAPH2CLR1, &graph2Color1Old); 
			GetCtrlVal (hSettingsGraphPanel, SETGRAPH_GRAPH2CLR2, &graph2Color2Old); 
			GetCtrlVal (hSettingsGraphPanel, SETGRAPH_GRAPH2CLR3, &graph2Color3Old);
			
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
			SetCtrlAttribute (proPanel,PROPANEL_PIC_OPENPRJ , ATTR_DIMMED, 1);	  //����openproject
			SetCtrlAttribute (proPanel,PROPANEL_TXT_OPENPRJ , ATTR_DIMMED, 1); 
		break;
	}	 
	return 0;
}

int CVICALLBACK ToolsCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			InstallPopup (hToolsPanel); 
			break;
	}
	return 0;
}
//////////////////////////////////У׼//////////////////////////////////
int CVICALLBACK OutputVoltageCaliCallback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)	//��ѹУ׼
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			SetCtrlAttribute (hCalibrationPanel, CALIPANEL_OUTVOLCALI, ATTR_DIMMED, 1);
			SetCtrlAttribute (hCalibrationPanel, CALIPANEL_OUTVOLCALI, ATTR_TEXT_BGCOLOR, VAL_BG_DISABLE);
			
			
			measUartTxBuf1[0] = select_Addr1;
			measUartTxBuf1[1] = 0x15;
			measUartTxBuf1[2] = 0x00;
			measUartTxBuf1[29] = GetXorCheckVal(measUartTxBuf1, SA31_UART_TX_LEN-1);
			ComWrt(measureComPort, (const char*)measUartTxBuf1, 30);
			
			

			break;

	}
	return 0;
}
								  

int CVICALLBACK ZeroCurrentCaliCallback (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)//���У׼
{
	int expType;
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			SetCtrlAttribute (hCalibrationPanel, CALIPANEL_ZEROCURCALI, ATTR_DIMMED, 1);   //����
			SetCtrlAttribute (hCalibrationPanel, CALIPANEL_ZEROCURCALI, ATTR_TEXT_BGCOLOR, VAL_BG_DISABLE);
			
			//measUartTxBuf1[0] = select_Addr1;
			//measUartTxBuf1[1] = 0x15;
			//measUartTxBuf1[2] = 0x01;
			//measUartTxBuf1[29] = GetXorCheckVal(measUartTxBuf1, SA31_UART_TX_LEN-1);
			//ComWrt(measureComPort, (const char*)measUartTxBuf1, 30);
			
			GetCtrlVal(mainPanel, MAIN_PANEL_SMU1, &expType);							//�ж��Ƿ�ѡ��SMU1���Ӳ���
			if(expType>0)
				select_Addr1=0x01;
			else
				select_Addr1=0x00;
			GetCtrlVal(mainPanel, MAIN_PANEL_SMU2, &expType);							//�ж��Ƿ�ѡ��SMU2���Ӳ���
			if(expType>0)
				select_Addr2=0x02;
			else
				select_Addr2=0x00;
			
			if(select_Addr1 == 0x01)
			{
				measUartTxBuf1[0] = select_Addr1;
				measUartTxBuf1[1] = 0x15;
				measUartTxBuf1[2] = 0x01;
				measUartTxBuf1[29] = GetXorCheckVal(measUartTxBuf1, SA31_UART_TX_LEN-1);
				ComWrt(measureComPort, (const char*)measUartTxBuf1, 30);
			}
			if(select_Addr2 == 0x02)
			{
				measUartTxBuf2[0] = select_Addr2;
				measUartTxBuf2[1] = 0x15;
				measUartTxBuf2[2] = 0x01;
				measUartTxBuf2[29] = GetXorCheckVal(measUartTxBuf2, SA31_UART_TX_LEN-1);
				ComWrt(measureComPort, (const char*)measUartTxBuf2, 30);
			}
			break;
	}
	return 0;
}

int CVICALLBACK CurrentCaliCallback (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)//����У׼
{ 	int temp;
int expType; 
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			
			SetCtrlAttribute (hCalibrationPanel, CALIPANEL_CURRENTCALI, ATTR_DIMMED, 1);   //����
			SetCtrlAttribute (hCalibrationPanel, CALIPANEL_CURRENTCALI, ATTR_TEXT_BGCOLOR, VAL_BG_DISABLE);
			
			GetCtrlVal (hCalibrationPanel,CALIPANEL_RANGESELECT,&temp);  
			
			//measUartTxBuf1[0] = select_Addr1;
			//measUartTxBuf1[1] = 0x15;
			//measUartTxBuf1[2] = 0x02;
			//measUartTxBuf1[3] = (unsigned char)temp;
			//measUartTxBuf1[29] = GetXorCheckVal(measUartTxBuf1, SA31_UART_TX_LEN-1);
			//ComWrt(measureComPort, (const char*)measUartTxBuf1, 30);
			
			GetCtrlVal(mainPanel, MAIN_PANEL_SMU1, &expType);							//�ж��Ƿ�ѡ��SMU1���Ӳ���
			if(expType>0)
				select_Addr1=0x01;
			else
				select_Addr1=0x00;
			GetCtrlVal(mainPanel, MAIN_PANEL_SMU2, &expType);							//�ж��Ƿ�ѡ��SMU2���Ӳ���
			if(expType>0)
				select_Addr2=0x02;
			else
				select_Addr2=0x00;
			
			if(select_Addr1 == 0x01)
			{
				measUartTxBuf1[0] = select_Addr1;
				measUartTxBuf1[1] = 0x15;
				measUartTxBuf1[2] = 0x02;
				measUartTxBuf1[3] = (unsigned char)temp; 
				measUartTxBuf1[29] = GetXorCheckVal(measUartTxBuf1, SA31_UART_TX_LEN-1);
				ComWrt(measureComPort, (const char*)measUartTxBuf1, 30);
			}
			if(select_Addr2 == 0x02)
			{
				measUartTxBuf2[0] = select_Addr2;
				measUartTxBuf2[1] = 0x15;
				measUartTxBuf2[2] = 0x02;
				measUartTxBuf2[3] = (unsigned char)temp; 
				measUartTxBuf2[29] = GetXorCheckVal(measUartTxBuf2, SA31_UART_TX_LEN-1);
				ComWrt(measureComPort, (const char*)measUartTxBuf2, 30);
			}
			break;
	}
	return 0;
}

int CVICALLBACK SaveCaliCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)	//����У׼����
{
	int expType; 
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			//measUartTxBuf1[0] = select_Addr1;
			//measUartTxBuf1[1] = 0x15;
			//measUartTxBuf1[2] = 0xff;
			//measUartTxBuf1[29] = GetXorCheckVal(measUartTxBuf1, SA31_UART_TX_LEN-1);
			//ComWrt(measureComPort, (const char*)measUartTxBuf1, 30);
			
			GetCtrlVal(mainPanel, MAIN_PANEL_SMU1, &expType);							//�ж��Ƿ�ѡ��SMU1���Ӳ���
			if(expType>0)
				select_Addr1=0x01;
			else
				select_Addr1=0x00;
			GetCtrlVal(mainPanel, MAIN_PANEL_SMU2, &expType);							//�ж��Ƿ�ѡ��SMU2���Ӳ���
			if(expType>0)
				select_Addr2=0x02;
			else
				select_Addr2=0x00;
			
			if(select_Addr1 == 0x01)
			{
				measUartTxBuf1[0] = select_Addr1;
				measUartTxBuf1[1] = 0x15;
				measUartTxBuf1[2] = 0xff;
				measUartTxBuf1[29] = GetXorCheckVal(measUartTxBuf1, SA31_UART_TX_LEN-1);
				ComWrt(measureComPort, (const char*)measUartTxBuf1, 30);
			}
			if(select_Addr2 == 0x02)
			{
				measUartTxBuf2[0] = select_Addr2;
				measUartTxBuf2[1] = 0x15;
				measUartTxBuf2[2] = 0xff;
				measUartTxBuf2[29] = GetXorCheckVal(measUartTxBuf2, SA31_UART_TX_LEN-1);
				ComWrt(measureComPort, (const char*)measUartTxBuf2, 30);
			}

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
//�����´��룬�ӷ����������ش���
int CVICALLBACK COMMANDBUTTON_Callback (int panel, int control, int event,
										void *callbackData, int eventData1, int eventData2)
{
switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
		int len;
		char getProjectDir[MAX_PATHNAME_LEN];
		char updateInfoPath[MAX_PATHNAME_LEN];
		CVIXMLDocument    hUpDocument = 0;
		CVIXMLElement	 hCurrElem = 0;
		CVIXMLElement    hChildElem = 0;
		CVIXMLAttribute  hCurrAttr = 0;
		char *serversSoftVersion = NULL;
		char attrName[5];
		int handle;
		
		CheckUpdate();//����������Ƿ�Ϊ����
		
		LaunchExecutableEx ("..\\..\\updates\\SystemUpdate.exe", LE_SHOWNA, &handle);
		while((ExecutableHasTerminated (handle)) == 0)
		{
		}
		GetProjectDir (getProjectDir);
		MakePathname(getProjectDir, "..\\..\\updates\\updateInfo.xml", updateInfoPath);
		CVIXMLLoadDocument (updateInfoPath, &hUpDocument);
		CVIXMLGetRootElement (hUpDocument, &hCurrElem);
		CVIXMLGetChildElementByTag(hCurrElem, "SoftwareVersion", &hChildElem); //��ñ�ǩSoftwareVersion ��Ԫ��
		CVIXMLGetAttributeByIndex(hChildElem, 0, &hCurrAttr);
		CVIXMLGetAttributeNameLength(hCurrAttr, &len);
		CVIXMLGetAttributeName(hCurrAttr, attrName);
		CVIXMLGetAttributeValueLength (hCurrAttr, &len);
		serversSoftVersion = malloc (len + 1); 
		CVIXMLGetAttributeValue(hCurrAttr,serversSoftVersion);   //�ӷ���������.xml�ļ�������Ŀ¼�£��ٴӸ�XML�ļ��л�ȡ������Ӳ���汾��
		if(serversSoftVersion[0] != '0')
		{
			QuitUserInterface (0);
			LaunchExecutable ("..\\..\\updates\\replace.exe");
		}
			break;
	}
	return 0;
}

void CheckUpdate()
{
	int len;
	static int ftp_handle = -1;
	static int error; 
	static char getProjectDir[MAX_PATHNAME_LEN];
	static char getProjectDirs[MAX_PATHNAME_LEN];
	static char updateInfoPath[MAX_PATHNAME_LEN];
	static char localInfoPath[MAX_PATHNAME_LEN];
	static char updateUpdateFilePath[MAX_PATHNAME_LEN]; 
	static char *serversUpdateVersion = NULL;
	static char *currentUpdateVersion = NULL;
	static CVIXMLDocument	 hLoDocument = 0;
	static CVIXMLDocument    hUpDocument = 0;
	static CVIXMLElement	 hRootElem = 0;
	static CVIXMLElement    hChildElem = 0;
	static CVIXMLAttribute  hUpdateCurrAttr = 0;

	    GetProjectDir (getProjectDir);
		MakePathname(getProjectDir, "..\\..\\updates\\", getProjectDirs);
		MakePathname(getProjectDirs, "updateInfo.xml", updateInfoPath);
		MakePathname(getProjectDirs, "localInfo.xml", localInfoPath);
	    if ((ftp_handle = InetFTPLogin ("106.15.183.58", "anonymous", "")) < 0)           //�û�������½������
		{
			MessagePopup ("An Error Occurred", "Can't Connect To Server");
		}
		if ((InetFTPSetPassiveMode (ftp_handle, 0)) <0)                                   //ftpͨ�ŷ�ʽΪ����ģʽ
			MessagePopup ("An Error Occurred", "Current communication mode is active mode");
		 if ((InetFTPChangeDir (ftp_handle, "SA3102//")) < 0)							
			MessagePopup ("An Error Occurred", "Server current directory error");
		if((error = InetFTPRetrieveFile (ftp_handle, updateInfoPath, "updateInfo.xml", INET_FTP_FILE_TYPE_BINARY)))  //���ط�������ǰ�б��еĸ�����Ϣ�ļ�
			MessagePopup ("An Error Occurred", "The server version number could not be found");
		InetFTPClose(ftp_handle);
	
		CVIXMLLoadDocument (updateInfoPath, &hUpDocument);
		CVIXMLGetRootElement (hUpDocument, &hRootElem);
		CVIXMLGetChildElementByTag(hRootElem, "UpdateVersion", &hChildElem); //��ñ�ǩUpdateVersion ��Ԫ��
		CVIXMLGetAttributeByIndex(hChildElem, 0, &hUpdateCurrAttr);
		CVIXMLGetAttributeNameLength(hUpdateCurrAttr, &len);
		CVIXMLGetAttributeValueLength (hUpdateCurrAttr, &len);
		serversUpdateVersion = malloc (len + 1); 
		CVIXMLGetAttributeValue(hUpdateCurrAttr,serversUpdateVersion);   //�ӷ���������.xml�ļ�������Ŀ¼�£��ٴӸ�XML�ļ��л�ȡ���¸��°汾��
         
	    CVIXMLLoadDocument (localInfoPath, &hLoDocument);
		CVIXMLGetRootElement (hLoDocument, &hRootElem);
		CVIXMLGetChildElementByTag(hRootElem, "UpdateVersion", &hChildElem); //��ñ�ǩversion ��Ԫ��
		CVIXMLGetAttributeByIndex(hChildElem, 0, &hUpdateCurrAttr);
		CVIXMLGetAttributeNameLength(hUpdateCurrAttr, &len);
		CVIXMLGetAttributeValueLength (hUpdateCurrAttr, &len);
		currentUpdateVersion = malloc (len + 1); 
		CVIXMLGetAttributeValue(hUpdateCurrAttr,currentUpdateVersion);   //�ӱ���Ŀ¼��XML�ļ��л�ȡ�����ǰ�汾��
	    int i;
		for(i=0;i<=len;i++)
		{
			 if(serversUpdateVersion[i] != currentUpdateVersion[i])
			 {
					int	num, i;
					char **files = NULL;
					if ((ftp_handle = InetFTPLogin ("106.15.183.58", "anonymous", "")) < 0)           //�û�������½������
					MessagePopup ("An Error Occurred", "Can't Connect To Server");
					if ((InetFTPSetPassiveMode (ftp_handle, 0)) <0)                                   //ftpͨ�ŷ�ʽΪ����ģʽ
					MessagePopup ("An Error Occurred", "Current communication mode is active mode");
					if ((InetFTPChangeDir (ftp_handle, ".//SA3102//updates//")) < 0)							
					MessagePopup ("An Error Occurred", "Server current directory error");
					if ((error = InetFTPGetDirList (ftp_handle, &files, &num)) < 0) 
					MessagePopup ("An Error Occurred", "Failed to get directory list");    
					for(i = 2;i<num;i++)
					{    
						MakePathname(getProjectDir, "..\\..\\updates\\", getProjectDirs);
						MakePathname(getProjectDirs, files[i], updateUpdateFilePath);
						InetFTPRetrieveFile (ftp_handle, updateUpdateFilePath, files[i], INET_FTP_FILE_TYPE_BINARY);  //���ط�������ǰ�б��еĸ����ļ�
					}
					InetFTPClose(ftp_handle);
					CVIXMLSetAttributeValue (hUpdateCurrAttr, serversUpdateVersion);  //���޸ı���xml�ļ��еĸ��°汾��  
					CVIXMLSaveDocument (hLoDocument, 0, NULL);
			  	
			 }

	     }
}

int ReadFromConfigFile(char* temp,char* temp1)
{
	
	FILE* fp;
	char buf[40*1024]={0};
	int size;
	//temp1[0]=0X35;
	ComWrt(measureComPort,temp1, 30);
    Delay(1);
    temp1[0]='Y';
	ComWrt(measureComPort,temp1, 1);
	Delay(0.1);
	fp=fopen(temp,"rb");
	size=fread(buf, 1,40*1024,fp);
	ComWrt(measureComPort,buf,size);
	Delay(4);
	*temp1 = 0;
	*(temp1+1) = 0; 
	*(temp1+29) = 0;
	ComWrt(measureComPort,temp1, 30);
	Delay(0.3); 
	ComWrt(measureComPort,temp1, 30);
	Delay(0.3); 
	fclose(fp);
	return 0;
}


int CVICALLBACK UpdateSMU1Callback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{   
	char temp[MAX_PATHNAME_LEN]=".//hardFileBackups//SMU2.0_Code1.bin";
	char temp1[MAX_PATHNAME_LEN]={0x01,0x16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								  0,0,0,0,0,0,0,0,0,0,0x17};
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			ReadFromConfigFile(temp,temp1);
			//ReadFromConfigFile(); 
			break;

	}
	return 0;
}


int CVICALLBACK UpdateSMU2Callback (int panel, int control, int event,
									void *callbackData, int eventData1, int eventData2)
{
	char temp[MAX_PATHNAME_LEN]=".//hardFileBackups//SMU2.0_Code2.bin";
	char temp1[MAX_PATHNAME_LEN]={0x02,0x16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								  0,0,0,0,0,0,0,0,0,0,0x14};
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			
			ReadFromConfigFile(temp,temp1);

			break;
	}
	return 0;
}
