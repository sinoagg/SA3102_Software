#include "main.h"
#include "Table.h"
#include <utility.h>
#include "Environment.h"
#include "asynctmr.h"
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include <rs232.h>
#include "Protocol.h"   
#include "LoadPanel.h"
#include "MainPanelCb.h"
#include "Graph.h"
#include "Cgs_mt.h"
#include "Plot.h"
unsigned char comSelect;					//Serial Com Number
unsigned char CGS_comSelect;				//Serial Com Number
unsigned char measUartTxBuf1[32]={0};
unsigned char measUartRxBuf1[500]={0};
unsigned char measUartTxBuf2[32]={0};
unsigned char measUartRxBuf2[500]={0};
unsigned char queryFlag = 1;
float X1 = 0;
float X2 = 0; 
RxDataTypeDef RxData1,RxData2;
void CVICALLBACK ComCallback(int portNumber ,int eventMask, void * callbackData);
void CVICALLBACK ComCallbackCGS(int portNumber, int eventMask, void * callbackData); 																		 
int CVICALLBACK TimerCallback (int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2);
int CheckPortStatus(unsigned char portNumber, unsigned char uartRxLen, void (*pFunc)(int, int, void*));
int rowIndex=2;
int rowIndex2=2;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	comSelect =6;
	CGS_comSelect = 1;
	LoadInitPanel(); 
	CheckPortStatus(comSelect, 20, ComCallback);
//	CheckPortStatus(CGS_comSelect, 14, ComCallbackCGS);
	RunUserInterface ();
	DiscardPanel (mainPanel);
	return 0;
}
static int CheckPortStatus(unsigned char portNumber, unsigned char uartRxLen, void (*pFunc)(int, int, void*))
{
	int status;
	status = OpenComConfig(portNumber, "", 115200, 0, 8, 1, 512, 512);	   //Config and Connect serial port
	if(status != 0) 
	{
		MessagePopup("Error","Device unconnected.");
		return -1;
	}
	else
	{
		InstallComCallback (portNumber, LWRS_RECEIVE, uartRxLen, 0, pFunc, 0);   //binding Callback function to serial input data		18 bytes received will calling for an interrupt
		SetCTSMode(portNumber, LWRS_HWHANDSHAKE_OFF);
		FlushInQ(portNumber);	   														//Clear input and output buffer
		FlushOutQ(portNumber);
		return 0;
	}
}
void Getxy(unsigned char *measUartRxBuf, RxDataTypeDef* RxData1, RxDataTypeDef* RxData2) //判断接收源表1 源表2的数据
{
		if((*measUartRxBuf  == 0x01) &&(Graph.pCurveArray->numofSmu1RxDots <= Graph.pCurveArray->numOfTotalDots-1)) //判断是否是 01 地址传来 的数据
		{
			if(TestPara1.testMode == NO_SWEEP_IV ) //根据不同模式 选择不同的X 轴数据
			{
				*(Graph.pCurveArray->pDotX++) = RxData1->rx_Theory_voltaget;
				*(Graph.pCurveArray->pDotY++) = RxData1->rx_current.num_float;				//get y, set pointer to the next data 
				SetTableCellRangeAttribute (tablePanel, TABLE_TABLE1, MakeRect (rowIndex, 1, 1, 2), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
				SetTableCellVal (tablePanel, TABLE_TABLE1, MakePoint (1,rowIndex), *(Graph.pCurveArray->pDotX-1));
				SetTableCellVal (tablePanel, TABLE_TABLE1, MakePoint (2,rowIndex),*(Graph.pCurveArray->pDotY-1)); 
				rowIndex++; 
			}
			else if(TestPara1.testMode == NO_SWEEP_VI )
			{
				*(Graph.pCurveArray->pDotX++) = RxData1->rx_Theory_current;
				*(Graph.pCurveArray->pDotY++) = RxData1->rx_voltage.num_float;				//get y, set pointer to the next data
		
			}
			else if(TestPara1.testMode == NO_SWEEP_IT )
			{
				*(Graph.pCurveArray->pDotX++) = X1++;
				*(Graph.pCurveArray->pDotY++) = RxData1->rx_current.num_float;				//get y, set pointer to the next data 
				SetTableCellRangeAttribute (tablePanel, TABLE_TABLE1, MakeRect (rowIndex, 1, 1, 2), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
				SetTableCellVal (tablePanel, TABLE_TABLE1, MakePoint (1,rowIndex), *(Graph.pCurveArray->pDotX-1));
				SetTableCellVal (tablePanel, TABLE_TABLE1, MakePoint (2,rowIndex),*(Graph.pCurveArray->pDotY-1)); 
				rowIndex++;
			}
			if(TestPara1.testMode == NO_SWEEP_VT )
			{
				*(Graph.pCurveArray->pDotX++) = X1++;
				*(Graph.pCurveArray->pDotY++) = RxData1->rx_voltage.num_float;				//get y, set pointer to the next data 

			}
			if(TestPara1.testMode == NO_SWEEP_RT )
			{
				*(Graph.pCurveArray->pDotX++) = X1++;		
				*(Graph.pCurveArray->pDotY++) = (TestPara1.Voltage_Start*0.001)/RxData1->rx_current.num_float;				//get y, set pointer to the next data
				SetTableCellRangeAttribute (tablePanel, TABLE_TABLE1, MakeRect (rowIndex, 1, 1, 2), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
				SetTableCellVal (tablePanel, TABLE_TABLE1, MakePoint (1,rowIndex), *(Graph.pCurveArray->pDotX-1));
				SetTableCellVal (tablePanel, TABLE_TABLE1, MakePoint (2,rowIndex),*(Graph.pCurveArray->pDotY-1)); 
				rowIndex++; 
			}
			Graph.pCurveArray->numOfDotsToPlot++;				//number of dots to plot increase 
			Graph.pCurveArray->numofSmu1RxDots++;
		}
		else if((*measUartRxBuf  == 0x02) && ((Graph.pCurveArray + 1)->numofSmu2RxDots <= (Graph.pCurveArray + 1)->numOfTotalDots-1)) //判断是否是 02 地址传来 的数据
		{
			if(TestPara2.testMode == NO_SWEEP_IV )
			{
				*((Graph.pCurveArray + 1)->pDotX++) = RxData2->rx_Theory_voltaget;
				*((Graph.pCurveArray + 1)->pDotY++) = RxData2->rx_current.num_float;
				SetTableCellRangeAttribute (tablePanel, TABLE_TABLE1, MakeRect (rowIndex2, 3, 1, 2), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
				SetTableCellVal (tablePanel, TABLE_TABLE1, MakePoint (3,rowIndex2), *((Graph.pCurveArray + 1)->pDotX-1));
				SetTableCellVal (tablePanel, TABLE_TABLE1, MakePoint (4,rowIndex2), *((Graph.pCurveArray + 1)->pDotY-1)); 
				rowIndex2++; 
			}
			
			if(TestPara2.testMode == NO_SWEEP_VI )
				*((Graph.pCurveArray + 1)->pDotX++) = RxData2->rx_Theory_current;
		
			if(TestPara2.testMode == NO_SWEEP_IT )
			{
				*((Graph.pCurveArray + 1)->pDotX++) = X2++;
				*((Graph.pCurveArray + 1)->pDotY++) = RxData2->rx_current.num_float;
				SetTableCellRangeAttribute (tablePanel, TABLE_TABLE1, MakeRect (rowIndex2, 3, 1, 2), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);    
				SetTableCellVal (tablePanel, TABLE_TABLE1, MakePoint (3,rowIndex2), *((Graph.pCurveArray + 1)->pDotX-1));
				SetTableCellVal (tablePanel, TABLE_TABLE1, MakePoint (4,rowIndex2), *((Graph.pCurveArray + 1)->pDotY-1)); 
				rowIndex2++; 
			}
			//if(TestPara2.testMode == NO_SWEEP_VT )
			//*(Graph.pCurveArray->pDotX++) = RxData2.rx_Theory_voltaget;
		
			if(TestPara2.testMode == NO_SWEEP_RT )
			{
				*((Graph.pCurveArray + 1)->pDotX++) = X2++;
				*((Graph.pCurveArray + 1)->pDotY++) = (TestPara2.Voltage_Start*0.001)/RxData2->rx_current.num_float;
				SetTableCellRangeAttribute (tablePanel, TABLE_TABLE1, MakeRect (rowIndex2, 3, 1, 2), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);    
				SetTableCellVal (tablePanel, TABLE_TABLE1, MakePoint (3,rowIndex2), *((Graph.pCurveArray + 1)->pDotX-1));
				SetTableCellVal (tablePanel, TABLE_TABLE1, MakePoint (4,rowIndex2), *((Graph.pCurveArray + 1)->pDotY-1)); 
				rowIndex2++; 
			}
			(Graph.pCurveArray+1)->numOfDotsToPlot++;				 					//number of dots to plot increase
			(Graph.pCurveArray+1)->numofSmu2RxDots++;
		}

}
void TestStop(enum TestMode testMode)
{
	if((RxData1.rxStopSign == 0x01) || (RxData2.rxStopSign == 0x01) || (Graph.pCurveArray->numofSmu1RxDots > Graph.pCurveArray->numOfTotalDots-1) || ((Graph.pCurveArray + 1)->numofSmu2RxDots > (Graph.pCurveArray + 1)->numOfTotalDots-1))
	{
		switch(TestPara1.testMode)
		{
			case CALIBRATION:
				
				break;
			case NO_SWEEP_IV:
				if((RxData1.rxStopSign == 0x01)&&(RxData2.rxStopSign == 0x01))	//判断是否有曲线结束标志位 与，
					{
						StopKeyAction();										//停止按钮按下后产生的一系列动作
					}
				break;
			case NO_SWEEP_VI:
				
				break;
			case NO_SWEEP_IT:
					if((Graph.pCurveArray->numofSmu1RxDots > Graph.pCurveArray->numOfTotalDots-1) && ((Graph.pCurveArray + 1)->numofSmu2RxDots > (Graph.pCurveArray + 1)->numOfTotalDots-1) == 1)
					{
						StopKeyAction();																		//停止按钮按下后产生的一系列动作
					}
					else if(Graph.pCurveArray->numOfPlotDots >= Graph.pCurveArray->numOfTotalDots)				//板子1
					{
						ProtocolStop(comSelect, select_Addr1, 0x00, measUartTxBuf1, measUartTxBuf2);  			//发送地址1停止指令
					}
					else if((Graph.pCurveArray + 1)->numOfPlotDots >= (Graph.pCurveArray + 1)->numOfTotalDots)  //板子2
					{
						ProtocolStop(comSelect, 0x00, select_Addr2, measUartTxBuf1, measUartTxBuf2);  			//发送地址2停止指令 
					}
				break;
			case NO_SWEEP_RT:
				
				break;
			case NO_SWEEP_VT:
				
				break;
		}
	}
}
void CVICALLBACK ComCallback(int portNumber, int eventMask, void * callbackData)
{
	int status;
	int rxNum;																							  
	int i=0;
	queryFlag = 0;																//接收时屏蔽查询，不在查询数据
	//RxDataTypeDef RxData1,RxData2;
	//RxData1.rxStopSign=0x00;
	//RxData2.rxStopSign=0x00;
	rxNum = GetInQLen(comSelect);  												//读取串口中发送来的数据数量
	if(rxNum>500) rxNum=500;													//防止超过内存范围
	while(rxNum>=UART_RX_LEN)
	{	 
	/*	 if((Graph.pCurveArray->numOfPlotDots >= Graph.pCurveArray->numOfTotalDots) && ((Graph.pCurveArray + 1)->numOfPlotDots >= (Graph.pCurveArray + 1)->numOfTotalDots))//if complete the test, stop the timer
		 {
		 	//DiscardAsyncTimer(TimerID);
			rxNum =0;
		 }
		 else
		 {*/
			status = ComRd(comSelect, (char *)measUartRxBuf1, UART_RX_LEN); 				
			ProtocolGetData(measUartRxBuf1+i*UART_RX_LEN, &RxData1,&RxData2);					//get data from uart buffer ,并且判断是否是源表1或2 数据，分别放入相应的缓存里
			Getxy(&measUartRxBuf1[i*UART_RX_LEN], &RxData1, &RxData2);							//从串口传来的数据中取出  X与Y轴 的数据
			rxNum -=UART_RX_LEN;
		 //}
	}
							
	//PlotCurve1(&Graph, graphDispPanel, GRAPHDISP_GRAPH1, 0);	//  增加参数    曲线总数目   第一条曲线标号												//画图   电学测量曲线图
	PlotCurve(&Graph, graphDispPanel, GRAPHDISP_GRAPH1);		//  liangt  
	TestStop(TestPara1.testMode);
	queryFlag = 1; 																				//开启查询数据
}void CVICALLBACK ComCallbackCGS(int portNumber, int eventMask, void * callbackData)
{
	int status;
	int rxNum;																							  
	int i=0;
	//static a = 0;
	Rx_CGS_DataTypeDef Rx_CGS_Data;
	rxNum = GetInQLen(CGS_comSelect);  													//读取串口中发送来的数据数量
	if(rxNum>500) rxNum=500;															//防止超过内存范围
	status = ComRd(CGS_comSelect, (char *)meas_CGS_UartRxBuf, rxNum);					//Read UART Buffer to local buffer at one time 
	while(rxNum>=14)
	{
		ProtocolGet_CGS_Data(meas_CGS_UartRxBuf, &Rx_CGS_Data);							// 从 串口中取出 环境测量参数
		*(Graph_Temp.pCurveArray->pDotX++) = X1-1;
		*((Graph_Temp.pCurveArray + 1)->pDotX++) = X1-1; 
		*((Graph_Temp.pCurveArray + 2)->pDotX++) = X1-1; 
	    *(Graph_Temp.pCurveArray->pDotY++) = Rx_CGS_Data.environmental_humidity; 		 //环境湿度
		*((Graph_Temp.pCurveArray + 1)->pDotY++) = Rx_CGS_Data.environmental_temp;		 //环境温度
		*((Graph_Temp.pCurveArray + 2)->pDotY++) = Rx_CGS_Data.pressure * 0.001;		 //环境压强
		(Graph_Temp.pCurveArray +1)->numOfDotsToPlot++;
		(Graph_Temp.pCurveArray +2)->numOfDotsToPlot++; 
		Graph_Temp.pCurveArray->numOfDotsToPlot++; 
		SetCtrlVal (hEnvResultPanel, ENVIRPANEL_STR_TEMP, Rx_CGS_Data.environmental_temp);			//环境温度
		SetCtrlVal (hEnvResultPanel, ENVIRPANEL_STR_HUM,  Rx_CGS_Data.environmental_humidity);		//环境湿度
		SetCtrlVal (hEnvResultPanel, ENVIRPANEL_STR_PRES, Rx_CGS_Data.pressure);				 	//压强
		rxNum -=14; 
		i++; 
	}
	PlotCurve_Temp(&Graph_Temp, graphDispPanel, GRAPHDISP_GRAPH2);	//画曲线图
}


