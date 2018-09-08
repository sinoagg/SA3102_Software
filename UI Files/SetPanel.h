/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  ABOUT                            1
#define  ABOUT_PICTURE                    2       /* control type: picture, callback function: (none) */

#define  ENVT                             2
#define  ENVT_PROPATH                     2       /* control type: string, callback function: (none) */
#define  ENVT_DIRECT                      3       /* control type: command, callback function: ProCallback */

#define  SETGRAPH                         3
#define  SETGRAPH_RING                    2       /* control type: ring, callback function: (none) */
#define  SETGRAPH_RING_2                  3       /* control type: ring, callback function: (none) */
#define  SETGRAPH_GRAPH2CLR3              4       /* control type: color, callback function: (none) */
#define  SETGRAPH_GRAPH2CLR2              5       /* control type: color, callback function: (none) */
#define  SETGRAPH_GRAPH2CLR1              6       /* control type: color, callback function: (none) */
#define  SETGRAPH_GRAPH1CLR3              7       /* control type: color, callback function: (none) */
#define  SETGRAPH_GRAPH1CLR2              8       /* control type: color, callback function: (none) */
#define  SETGRAPH_SMU1CLR                 9       /* control type: color, callback function: (none) */
#define  SETGRAPH_SMU2CLR                 10      /* control type: color, callback function: (none) */
#define  SETGRAPH_GRAPH1CLR1              11      /* control type: color, callback function: (none) */
#define  SETGRAPH_CHECKBOX                12      /* control type: radioButton, callback function: (none) */
#define  SETGRAPH_TEXTMSG                 13      /* control type: textMsg, callback function: (none) */
#define  SETGRAPH_TEXTMSG_10              14      /* control type: textMsg, callback function: (none) */
#define  SETGRAPH_TEXTMSG_9               15      /* control type: textMsg, callback function: (none) */
#define  SETGRAPH_TEXTMSG_3               16      /* control type: textMsg, callback function: (none) */
#define  SETGRAPH_TEXTMSG_4               17      /* control type: textMsg, callback function: (none) */
#define  SETGRAPH_TEXTMSG_5               18      /* control type: textMsg, callback function: (none) */
#define  SETGRAPH_TEXTMSG_2               19      /* control type: textMsg, callback function: (none) */
#define  SETGRAPH_RING_3                  20      /* control type: ring, callback function: (none) */
#define  SETGRAPH_TEXTMSG_7               21      /* control type: textMsg, callback function: (none) */
#define  SETGRAPH_TXT_PLOT_STYLE          22      /* control type: textMsg, callback function: (none) */
#define  SETGRAPH_TEXTMSG_8               23      /* control type: textMsg, callback function: (none) */
#define  SETGRAPH_TEXTMSG_6               24      /* control type: textMsg, callback function: (none) */
#define  SETGRAPH_TEXTMSG_11              25      /* control type: textMsg, callback function: (none) */

#define  SETTINGS                         4       /* callback function: SettingsCB */
#define  SETTINGS_CANVAS                  2       /* control type: canvas, callback function: (none) */
#define  SETTINGS_DECORATION              3       /* control type: deco, callback function: (none) */
#define  SETTINGS_ABOUTBTN                4       /* control type: textMsg, callback function: AboutBtnCallback */
#define  SETTINGS_GRAPHBTN                5       /* control type: textMsg, callback function: GraphBtnCallback */
#define  SETTINGS_PRJBTN                  6       /* control type: textMsg, callback function: PrjBtnCallback */
#define  SETTINGS_TEXTMSG                 7       /* control type: textMsg, callback function: OkCallback */
#define  SETTINGS_Cancel                  8       /* control type: textMsg, callback function: CancelCallback */
#define  SETTINGS_OK_PIC                  9       /* control type: picture, callback function: OkCallback */
#define  SETTINGS_CANCEL_PIC              10      /* control type: picture, callback function: CancelCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK AboutBtnCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CancelCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK GraphBtnCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OkCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PrjBtnCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ProCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SettingsCB(int panel, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
