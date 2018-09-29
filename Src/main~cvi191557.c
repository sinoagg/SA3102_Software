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
	comSelect =3;
	CGS_comSelect = 1;
	LoadInitPanel(); 
	CheckPortStatus(comSelect, 20, ComCallback);
//	CheckPortStatus(CGS_comSelect, 14, ComCallbackCGS);
	RunUserInterface ();
	DiscardPanel (mainPanel);
	//return 0;
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
	//if(((Graph.pCurveArray->numOfPlotDots >= Graph.pCurveArray->numOfTotalDots-1) && ((Graph.pCurveArray + 1)->numOfPlotDots >= (Graph.pCurveArray + 1)->numOfTotalDots-1)) == 0)//if complete the test, stop the timer
	//{
		if((*measUartRxBuf  == 0x01) &&(Graph.pCurveArray->numOfPlotDots <= Graph.pCurveArray->numOfTotalDots-1)) //�ж��Ƿ��� 01 ��ַ���� ������
		{
			if(TestPara1.testMode == NO_SWEEP_IV ) //���ݲ�ͬģʽ ѡ��ͬ��X ������
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
			Graph.pCurveArray->numOfDotsToPlot++;				 						//number of dots to plot increase 
		}
		else if(*measUartRxBuf  == 0x02) &&) //�ж��Ƿ��� 02 ��ַ���� ������
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
		}

}
//void TestStop(float currentX_Val)
//{
//	if((RxData1.rxStopSign == 0x01) || (RxData2.rxStopSign == 0x01) || (currentX_Val >= Graph.pCurveArray->numOfTotalDots) || ((Graph.pCurveArray + 1)->numOfPlotDots >= (Graph.pCurveArray + 1)->numOfTotalDots))
//	{
//		switch(TestPara1.testMode)
//		{
//			case CALIBRATION:
//				
//				break;
//			case NO_SWEEP_IV:
//				if((RxData1.rxStopSign == 0x01)&&(RxData2.rxStopSign == 0x01))	//�ж��Ƿ������߽�����־λ �룬��ͼ�ܵ������ѻ������Ƿ����
//					{
//						StopKeyAction();										//ֹͣ��ť���º������һϵ�ж���      
//					}
//				break;
//			case NO_SWEEP_VI:
//				
//				break;
//			case NO_SWEEP_IT:
//				
//					if((Graph.pCurveArray->numOfPlotDots >= Graph.pCurveArray->numOfTotalDots) && ((Graph.pCurveArray + 1)->numOfPlotDots == (Graph.pCurveArray + 1)->numOfTotalDots) )
//					{
//						StopKeyAction();				//ֹͣ��ť���º������һϵ�ж���
//					}
//					else if(Graph.pCurveArray->numOfPlotDots >= Graph.pCurveArray->numOfTotalDots)	//����1
//					{
//						ProtocolStop(comSelect, select_Addr1, 0x00, measUartTxBuf1, measUartTxBuf2);  	//���͵�ַ1ָֹͣ��
//					}
//					else if((Graph.pCurveArray + 1)->numOfPlotDots >= (Graph.pCurveArray + 1)->numOfTotalDots)  //����2
//					{
//						ProtocolStop(comSelect, 0x00, select_Addr2, measUartTxBuf1, measUartTxBuf2);  	//���͵�ַ2ָֹͣ�� 
//					}
//				
//				
//				break;
//			case NO_SWEEP_RT:
//				
//				break;
//			case NO_SWEEP_VT:
//				
//				break;
//		}
//	}
//}
void CVICALLBACK ComCallback(int portNumber, int eventMask, void * callbackData)
{
	int status;
	int rxNum;																							  
	int i=0;
	queryFlag = 0;																//����ʱ���β�ѯ�����ڲ�ѯ����
	//RxDataTypeDef RxData1,RxData2;
	//RxData1.rxStopSign=0x00;
	//RxData2.rxStopSign=0x00;
	rxNum = GetInQLen(comSelect);  												//��ȡ�����з���������������
	if(rxNum>500) rxNum=500;													//��ֹ�����ڴ淶Χ
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
			ProtocolGetData(measUartRxBuf1+i*UART_RX_LEN, &RxData1,&RxData2);					//get data from uart buffer ,�����ж��Ƿ���Դ��1��2 ���ݣ��ֱ������Ӧ�Ļ�����
			Getxy(&measUartRxBuf1[i*UART_RX_LEN], &RxData1, &RxData2);							//�Ӵ��ڴ�����������ȡ��  X��Y�� ������
			rxNum -=UART_RX_LEN;
		 //}
	}
							
	//PlotCurve1(&Graph, graphDispPanel, GRAPHDISP_GRAPH1, 0);	//  ���Ӳ���    ��������Ŀ   ��һ�����߱��												//��ͼ   ��ѧ��������ͼ
	PlotCurve(&Graph, graphDispPanel, GRAPHDISP_GRAPH1);		//  liangt  
	
	//if(((RxData1.rxStopSign == 0x01)&&(RxData2.rxStopSign == 0x01)) || (Graph.pCurveArray->numOfPlotDots == Graph.pCurveArray->numOfTotalDots))	//�ж��Ƿ������߽�����־λ �룬��ͼ�ܵ������ѻ������Ƿ���� 
	
	if((RxData1.rxStopSign == 0x01) || (RxData2.rxStopSign == 0x01) || (Graph.pCurveArray->numOfPlotDots >= Graph.pCurveArray->numOfTotalDots-1) || ((Graph.pCurveArray + 1)->numOfPlotDots >= (Graph.pCurveArray + 1)->numOfTotalDots-1))
	{
		switch(TestPara1.testMode)
		{
			case CALIBRATION:
				
				break;
			case NO_SWEEP_IV:
				if((RxData1.rxStopSign == 0x01)&&(RxData2.rxStopSign == 0x01))	//�ж��Ƿ������߽�����־λ �룬��ͼ�ܵ������ѻ������Ƿ����
					{
						StopKeyAction();										//ֹͣ��ť���º������һϵ�ж���
						
					}
				break;
			case NO_SWEEP_VI:
				
				break;
			case NO_SWEEP_IT:
				
					if((Graph.pCurveArray->numOfPlotDots >= Graph.pCurveArray->numOfTotalDots-1) && ((Graph.pCurveArray + 1)->numOfPlotDots == (Graph.pCurveArray + 1)->numOfTotalDots-1))
					{
						StopKeyAction();				//ֹͣ��ť���º������һϵ�ж���
					}
					else if(Graph.pCurveArray->numOfPlotDots >= Graph.pCurveArray->numOfTotalDots)	//����1
					{
						ProtocolStop(comSelect, select_Addr1, 0x00, measUartTxBuf1, measUartTxBuf2);  	//���͵�ַ1ָֹͣ��
					}
					else if((Graph.pCurveArray + 1)->numOfPlotDots >= (Graph.pCurveArray + 1)->numOfTotalDots)  //����2
					{
						ProtocolStop(comSelect, 0x00, select_Addr2, measUartTxBuf1, measUartTxBuf2);  	//���͵�ַ2ָֹͣ�� 
					}
				
				
				break;
			case NO_SWEEP_RT:
				
				break;
			case NO_SWEEP_VT:
				
				break;
		}
	}
			//if((RxData1.rxStopSign == 0x01)&&(RxData2.rxStopSign == 0x01))	//�ж��Ƿ������߽�����־λ �룬��ͼ�ܵ������ѻ������Ƿ����
			//{
			//	StopKeyAction();				//ֹͣ��ť���º������һϵ�ж���      
			//}
			//if((Graph.pCurveArray->numOfPlotDots == Graph.pCurveArray->numOfTotalDots))
			//{
			//	StopKeyAction();				//ֹͣ��ť���º������һϵ�ж���
			//}
	queryFlag = 1; 																				//������ѯ����
}

//void CVICALLBACK ComCallback(int portNumber, int eventMask, void * callbackData)
//{
//	int status;
//	int rxNum;																							  
//	int i=0;

//	queryFlag = 0;
//	RxDataTypeDef RxData1,RxData2;
//	RxData1.rxStopSign=0x00; 
//	rxNum = GetInQLen(comSelect);  												//��ȡ�����з���������������
//	if(rxNum>1024) rxNum=1024;													//��ֹ�����ڴ淶Χ

   // rxNum-=rxNum%UART_RX_LEN;

//	//status = ComRd(comSelect, (char *)measUartRxBuf1, rxNum); 	
//	          
//	while(rxNum>=UART_RX_LEN)
//	{	 
//		
//		 //if((RxData1.rxStopSign == 0x01) || (Graph.pCurveArray->numOfPlotDots == Graph.pCurveArray->numOfTotalDots))//if complete the test, stop the timer
//		 //{
//		 //	DiscardAsyncTimer(TimerID);
//		//	rxNum =0;
//		 //}
//>>>>>>> 60731950687cb7b8b744a8e5d654e7bb290c0afb
//		 //else
//		 //{
//			status = ComRd(comSelect, (char *)measUartRxBuf1, 20); 				
//			ProtocolGetData(measUartRxBuf1+i*UART_RX_LEN, &RxData1,&RxData2);					//get data from uart buffer ,�����ж��Ƿ���Դ��1��2 ���ݣ��ֱ������Ӧ�Ļ�����
//			Getxy(&measUartRxBuf1[i*UART_RX_LEN], &RxData1, &RxData2);							//�Ӵ��ڴ�����������ȡ��  X��Y�� ������
//			rxNum -=UART_RX_LEN;
//		 //}
//<<<<<<< HEAD
//		 if((RxData1.rxStopSign == 0x01) || (Graph.pCurveArray->numOfPlotDots == Graph.pCurveArray->numOfTotalDots))//if complete the test, stop the timer
//		 {
//		 	DiscardAsyncTimer(TimerID);
//			//rxNum =0;
//		 }
//	}
//	rxNum = GetInQLen(comSelect); 
//	//PlotCurve(&Graph, graphDispPanel, GRAPHDISP_GRAPH1);//������ͼ 
//	PlotCurve1(&Graph, graphDispPanel, GRAPHDISP_GRAPH1, 0); 
//=======
//		
//	     //status = ComRd(comSelect, (char *)measUartRxBuf1, 20); 				
//	     //ProtocolGetData(measUartRxBuf1+i*UART_RX_LEN, &RxData1,&RxData2);					//get data from uart buffer ,�����ж��Ƿ���Դ��1��2 ���ݣ��ֱ������Ӧ�Ļ�����
//		 //Getxy(&measUartRxBuf1[i*UART_RX_LEN], &RxData1, &RxData2);							//�Ӵ��ڴ�����������ȡ��  X��Y�� ������
//		 //rxNum -=UART_RX_LEN;
//		// i++; 
//	}
//	//rxNum = GetInQLen(comSelect); 
//	//PlotCurve(&Graph, graphDispPanel, GRAPHDISP_GRAPH1);//������ͼ 
//	
//	PlotCurve1(&Graph, graphDispPanel, GRAPHDISP_GRAPH1, 0); 
//	
//>>>>>>> 60731950687cb7b8b744a8e5d654e7bb290c0afb
//	if((RxData1.rxStopSign == 0x01) || (Graph.pCurveArray->numOfPlotDots == Graph.pCurveArray->numOfTotalDots))
//	{
//		DiscardAsyncTimer(TimerID);
//		ProtocolStop(comSelect, select_Addr1, select_Addr2, measUartTxBuf1, measUartTxBuf2);  //����ָֹͣ��  
//		//GraphDeinit(&Graph);												//�ڴ��ͷ��ڻ�ͼ֮��
//		//GraphDeinit(&Graph_Temp);
//		SetCtrlAttribute (mainPanel, MAIN_PANEL_STOP, ATTR_DIMMED,1);      //���� ֹͣ��ť      
//	    SetCtrlAttribute (mainPanel, MAIN_PANEL_RUN, ATTR_DIMMED, 0);      //�ָ� ��ʼ��ť
//		SetCtrlAttribute (mainPanel, MAIN_PANEL_SAVE, ATTR_DIMMED, 0);     //�ָ� ���水ť
//	}
//<<<<<<< HEAD
//	 queryFlag = 1; 
//}


//=======
//}
void CVICALLBACK ComCallbackCGS(int portNumber, int eventMask, void * callbackData)
{
	int status;
	int rxNum;																							  
	int i=0;
	//static a = 0;
	Rx_CGS_DataTypeDef Rx_CGS_Data;
	rxNum = GetInQLen(CGS_comSelect);  													//��ȡ�����з���������������
	if(rxNum>500) rxNum=500;															//��ֹ�����ڴ淶Χ
	status = ComRd(CGS_comSelect, (char *)meas_CGS_UartRxBuf, rxNum);					//Read UART Buffer to local buffer at one time 
	while(rxNum>=14)
	{
		ProtocolGet_CGS_Data(meas_CGS_UartRxBuf, &Rx_CGS_Data);							// �� ������ȡ�� ������������
		*(Graph_Temp.pCurveArray->pDotX++) = X1-1;
		*((Graph_Temp.pCurveArray + 1)->pDotX++) = X1-1; 
		*((Graph_Temp.pCurveArray + 2)->pDotX++) = X1-1; 
	    *(Graph_Temp.pCurveArray->pDotY++) = Rx_CGS_Data.environmental_humidity; 		 //����ʪ��
		*((Graph_Temp.pCurveArray + 1)->pDotY++) = Rx_CGS_Data.environmental_temp;		 //�����¶�
		*((Graph_Temp.pCurveArray + 2)->pDotY++) = Rx_CGS_Data.pressure * 0.001;		 //����ѹǿ
		(Graph_Temp.pCurveArray +1)->numOfDotsToPlot++;
		(Graph_Temp.pCurveArray +2)->numOfDotsToPlot++; 
		Graph_Temp.pCurveArray->numOfDotsToPlot++; 
		SetCtrlVal (hEnvResultPanel, ENVIRPANEL_STR_TEMP, Rx_CGS_Data.environmental_temp);			//�����¶�
		SetCtrlVal (hEnvResultPanel, ENVIRPANEL_STR_HUM,  Rx_CGS_Data.environmental_humidity);		//����ʪ��
		SetCtrlVal (hEnvResultPanel, ENVIRPANEL_STR_PRES, Rx_CGS_Data.pressure);				 	//ѹǿ
		rxNum -=14; 
		i++; 
	}
	PlotCurve_Temp(&Graph_Temp, graphDispPanel, GRAPHDISP_GRAPH2);	//������ͼ
}

