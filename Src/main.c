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
#include "system_ini.h" 

unsigned char measure_Uart_Flag = 1; 				//��ѧ�������ڽ���ʱҪ�������ݲ�ѯ 
unsigned char control_Uart_Flag = 1; 				//�����������ڽ���ʱҪ�������ݲ�ѯ
unsigned char measureComPort;				//Serial Com Number
unsigned char controlComPort;
unsigned char measUartTxBuf1[32]={0};
unsigned char measUartRxBuf1[500]={0};
unsigned char measUartTxBuf2[32]={0};
unsigned char measUartRxBuf2[500]={0};
float X1 = 0;
float X2 = 0; 
int logFlag;
RxDataTypeDef RxData1,RxData2;
void CVICALLBACK ComCallback(int portNumber ,int eventMask, void * callbackData);
void CVICALLBACK ComCallbackCGS(int portNumber, int eventMask, void * callbackData); 																		 
int CVICALLBACK TimerCallback (int reserved, int timerId, int event, void *callbackData, int eventData1, int eventData2);
int CheckPortStatus(unsigned char portNumber, unsigned char uartRxLen, void (*pFunc)(int, int, void*));
void DeviceQuery();				//��ѯ�豸���ں�
int rowIndex=2;
int rowIndex2=2;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	DeviceQuery();											//��ѯ�豸���ں�
	
	LoadInitPanel(); 
	CheckPortStatus(measureComPort, 20, ComCallback);
	CheckPortStatus(controlComPort, 14, ComCallbackCGS);
	RunUserInterface();	
	int temp = DiscardPanel (mainPanel);
	SaveSystemClose(temp);
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
void Getxy(unsigned char *measUartRxBuf, RxDataTypeDef* RxData1, RxDataTypeDef* RxData2) //�жϽ���Դ��1 Դ��2������
{
		if((*measUartRxBuf  == 0x01) &&(Graph.pCurveArray->numofSmu1RxDots <= Graph.pCurveArray->numOfTotalDots-1)) //�ж��Ƿ��� 01 ��ַ���� ������
		{
			if(TestPara1.testMode == NO_SWEEP_IV ) //���ݲ�ͬģʽ ѡ��ͬ��X ������
			{
				if(logFlag)
				{
					*(Graph.pCurveArray->pDotY++) = log10((double)(RxData1->rx_current.num_float));				//get y, set pointer to the next data 
				}
				else
				{
					*(Graph.pCurveArray->pDotY++) = RxData1->rx_current.num_float;								//get y, set pointer to the next data 
				}
				*(Graph.pCurveArray->pDotX++) = RxData1->rx_Theory_voltaget;
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
				if(logFlag)
				{
					*(Graph.pCurveArray->pDotY++) = log10((double)(RxData1->rx_current.num_float));				//get y, set pointer to the next data 
				}
				else
				{
					*(Graph.pCurveArray->pDotY++) = RxData1->rx_current.num_float;				//get y, set pointer to the next data 
				}
				*(Graph.pCurveArray->pDotX++) = (X1++)*TestPara1.timeStep*0.001;
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
		else if((*measUartRxBuf  == 0x02) && ((Graph.pCurveArray + 1)->numofSmu2RxDots <= (Graph.pCurveArray + 1)->numOfTotalDots-1)) //�ж��Ƿ��� 02 ��ַ���� ������
		{
			if(TestPara2.testMode == NO_SWEEP_IV )
			{
				if(logFlag)
				{
					*((Graph.pCurveArray + 1)->pDotY++) = log10((double)(RxData2->rx_current.num_float));				//get y, set pointer to the next data 
				}
				else
				{
					*((Graph.pCurveArray + 1)->pDotY++) = RxData2->rx_current.num_float;  			//get y, set pointer to the next data 
				}
				*((Graph.pCurveArray + 1)->pDotX++) = RxData2->rx_Theory_voltaget;
				SetTableCellRangeAttribute (tablePanel, TABLE_TABLE1, MakeRect (rowIndex2, 3, 1, 2), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);
				SetTableCellVal (tablePanel, TABLE_TABLE1, MakePoint (3,rowIndex2), *((Graph.pCurveArray + 1)->pDotX-1));
				SetTableCellVal (tablePanel, TABLE_TABLE1, MakePoint (4,rowIndex2), *((Graph.pCurveArray + 1)->pDotY-1)); 
				rowIndex2++; 
			}
			
			if(TestPara2.testMode == NO_SWEEP_VI )
				*((Graph.pCurveArray + 1)->pDotX++) = RxData2->rx_Theory_current;
		
			if(TestPara2.testMode == NO_SWEEP_IT )
			{
				if(logFlag)
				{
					*((Graph.pCurveArray + 1)->pDotY++) = log10((double)(RxData2->rx_current.num_float));
				}
				else
				{
					*((Graph.pCurveArray + 1)->pDotY++) = RxData2->rx_current.num_float; 
				}
				*((Graph.pCurveArray + 1)->pDotX++) = (X2++)*TestPara2.timeStep*0.001;
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
				if((RxData1.rxStopSign == 0x01)&&(RxData2.rxStopSign == 0x01))	//�ж��Ƿ������߽�����־λ �룬
					{
						StopKeyAction();										//ֹͣ��ť���º������һϵ�ж���
					}
				break;
			case NO_SWEEP_VI:
				
				break;
			case NO_SWEEP_IT:
					if((Graph.pCurveArray->numofSmu1RxDots > Graph.pCurveArray->numOfTotalDots-1) && ((Graph.pCurveArray + 1)->numofSmu2RxDots > (Graph.pCurveArray + 1)->numOfTotalDots-1) == 1)
					{
						StopKeyAction();																		//ֹͣ��ť���º������һϵ�ж���
					}
					else if(Graph.pCurveArray->numOfPlotDots >= Graph.pCurveArray->numOfTotalDots)				//����1
					{
						ProtocolStop(measureComPort, select_Addr1, 0x00, measUartTxBuf1, measUartTxBuf2);  			//���͵�ַ1ָֹͣ��
					}
					else if((Graph.pCurveArray + 1)->numOfPlotDots >= (Graph.pCurveArray + 1)->numOfTotalDots)  //����2
					{
						ProtocolStop(measureComPort, 0x00, select_Addr2, measUartTxBuf1, measUartTxBuf2);  			//���͵�ַ2ָֹͣ�� 
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
	measure_Uart_Flag = 0;
	int status;
	int rxNum;																							  
	int i=0;																						//����ʱ���β�ѯ�����ڲ�ѯ����
	//RxDataTypeDef RxData1,RxData2;
	//RxData1.rxStopSign=0x00;
	//RxData2.rxStopSign=0x00;
	rxNum = GetInQLen(measureComPort);  															//��ȡ�����з���������������
	if(rxNum>500) rxNum=500;																		//��ֹ�����ڴ淶Χ
	while(rxNum>=UART_RX_LEN)
	{	 
	/*	 if((Graph.pCurveArray->numOfPlotDots >= Graph.pCurveArray->numOfTotalDots) && ((Graph.pCurveArray + 1)->numOfPlotDots >= (Graph.pCurveArray + 1)->numOfTotalDots))//if complete the test, stop the timer
		 {
		 	//DiscardAsyncTimer(TimerID);
			rxNum =0;
		 }
		 else
		 {*/
			status = ComRd(measureComPort, (char *)measUartRxBuf1, UART_RX_LEN); 				
			ProtocolGetData(measUartRxBuf1+i*UART_RX_LEN, &RxData1,&RxData2);						//get data from uart buffer ,�����ж��Ƿ���Դ��1��2 ���ݣ��ֱ������Ӧ�Ļ�����
			Getxy(&measUartRxBuf1[i*UART_RX_LEN], &RxData1, &RxData2);								//�Ӵ��ڴ�����������ȡ��  X��Y�� ������
			rxNum -=UART_RX_LEN;
		 //}
	}
							
	//PlotCurve1(&Graph, graphDispPanel, GRAPHDISP_GRAPH1, 0);	//  ���Ӳ���    ��������Ŀ   ��һ�����߱��												//��ͼ   ��ѧ��������ͼ
	
	PlotCurve(&Graph, graphDispPanel, GRAPHDISP_GRAPH1);											//  liangt  
	SetGraphX_Axis(GRAPHDISP_GRAPH1,&Graph);
	TestStop(TestPara1.testMode);
	measure_Uart_Flag = 1; 																			//������ѯ����
}
void CVICALLBACK ComCallbackCGS(int portNumber, int eventMask, void * callbackData)
{
	control_Uart_Flag = 0;																			//����ʱ���β�ѯ�����ڲ�ѯ����     
	int rxNum;
	int i,j;
	Rx_CGS_DataTypeDef Rx_CGS_Data;
	Rx_CGS_Data.environmental_temp = 0;
	Rx_CGS_Data.environmental_humidity = 0;
	Rx_CGS_Data.pressure = 0;
	rxNum = GetInQLen(controlComPort);  															//��ȡ�����з���������������
	if(rxNum>500) rxNum=500;																		//��ֹ�����ڴ淶Χ
 
	while(rxNum>=15)
	{
		//ComRd(controlComPort, (char *)meas_CGS_UartRxBuf, rxNum);									//Read UART Buffer to local buffer at one time
		//ProtocolGet_CGS_Data(meas_CGS_UartRxBuf, &Rx_CGS_Data);										// �� ������ȡ�� ������������
		//
		//j = Graph1.pCurveArray->numOfPlotDots - x2;
		//for(i = 0; i<j; i++)
		//{

		//*(Graph_Temp.pCurveArray->pDotX++) = X1-1;
		//*((Graph_Temp.pCurveArray + 1)->pDotX++) = X1-1; 
		//*((Graph_Temp.pCurveArray + 2)->pDotX++) = X1-1; 
		//
	    //*(Graph_Temp.pCurveArray->pDotY++) = Rx_CGS_Data.environmental_humidity; 					 //����ʪ��
		//*((Graph_Temp.pCurveArray + 1)->pDotY++) = Rx_CGS_Data.environmental_temp;		 			//�����¶�
		//*((Graph_Temp.pCurveArray + 2)->pDotY++) = Rx_CGS_Data.pressure * 0.001;		 			//����ѹǿ
		//
		//(Graph_Temp.pCurveArray +1)->numOfDotsToPlot++;										
		//(Graph_Temp.pCurveArray +2)->numOfDotsToPlot++; 
		//Graph_Temp.pCurveArray->numOfDotsToPlot++; 
		//rxNum -=15; 
	}
	SetCtrlVal (hEnvResultPanel, ENVIRPANEL_STR_TEMP, Rx_CGS_Data.environmental_temp);				//�����¶�
	SetCtrlVal (hEnvResultPanel, ENVIRPANEL_STR_HUM,  Rx_CGS_Data.environmental_humidity);			//����ʪ��
	SetCtrlVal (hEnvResultPanel, ENVIRPANEL_STR_PRES, Rx_CGS_Data.pressure);				 		//ѹǿ
	PlotCurve_Temp(&Graph_Temp, graphDispPanel, GRAPHDISP_GRAPH2);									//������ͼ
	control_Uart_Flag = 1;																			//����ʱ���β�ѯ�����ڲ�ѯ����
}
void DeviceQuery()																					//��ѯ�豸���ں�
{
	char IDquery[] = {0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF};
	char IDquery2[] = {0x11, 0x03, 0x00, 0x02, 0x00, 0x05, 0x26, 0x99}; 
	char USART_RX_Buffer1[40];   //����
	char USART_RX_Buffer2[40];   //����
	unsigned char i;
	int b, strLen;
		for(i = 1; i<=10; i++)
		{
			SetBreakOnLibraryErrors (0);
			b = OpenComConfig(i, "", 115200, 0, 8, 1, 30, 30);										//���úʹ򿪴��� 
		    if(b<0 )
			{
		
			}else
			{	
			    ComWrt(i, IDquery, 30);//���Ͳ�ѯָ��
				Delay(3);
				strLen = GetInQLen (i);
				ComRd (i,USART_RX_Buffer1,strLen);
				if((USART_RX_Buffer1[1]== '3') && (USART_RX_Buffer1[2] == '1') && (USART_RX_Buffer1[3] == '0') && (USART_RX_Buffer1[4]== '2'))
				{
					measureComPort = i;
					FlushInQ(measureComPort);	   														//Clear input and output buffer
					FlushOutQ(measureComPort);
					CloseCom (measureComPort);
					break;
				}
				else
				{
					CloseCom(i);
				}
				SetCTSMode (i, LWRS_HWHANDSHAKE_OFF);   //��Ӳ������
			}
		}
		for(i = 1; i<=10; i++)
		{
			SetBreakOnLibraryErrors (0);
			b = OpenComConfig(i, "", 115200, 0, 8, 1, 30, 30);  //���úʹ򿪴��� 
		    if(b<0 )
			{
		
			}else
			{	
			    ComWrt(i, IDquery2, 8);							//���Ͳ�ѯָ��
				Delay(3);
				strLen = GetInQLen (i);
				ComRd (i,USART_RX_Buffer2,strLen);
				if((USART_RX_Buffer2[0]== 0x11) && (USART_RX_Buffer2[1] == 0x03) && (USART_RX_Buffer2[2] == 0x0a))
				{
					controlComPort = i;							
					FlushInQ(controlComPort);	   				//Clear input and output buffer
					FlushOutQ(controlComPort);
					CloseCom (controlComPort);
					break;
				}
				else
				{
					CloseCom(i);
				}
				SetCTSMode (i, LWRS_HWHANDSHAKE_OFF);			//��Ӳ������
			}
		}
}


