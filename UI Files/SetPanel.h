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
#define  SETGRAPH_GRAPH2CLR3              4       /* control type: color, callback function: Graph2clr3CB */
#define  SETGRAPH_GRAPH2CLR2              5       /* control type: color, callback function: Graph2clr2CB */
#define  SETGRAPH_GRAPH2CLR1              6       /* control type: color, callback function: Graph2clr1CB */
#define  SETGRAPH_GRAPH1CLR3              7       /* control type: color, callback function: (none) */
#define  SETGRAPH_GRAPH1CLR2              8       /* control type: color, callback function: (none) */
#define  SETGRAPH_GRAPH1CLR1              9       /* control type: color, callback function: (none) */
#define  SETGRAPH_CHECKBOX                10      /* control type: radioButton, callback function: (none) */
#define  SETGRAPH_TEXTMSG                 11      /* control type: textMsg, callback function: (none) */
#define  SETGRAPH_TEXTMSG_3               12      /* control type: textMsg, callback function: (none) */
#define  SETGRAPH_TEXTMSG_4               13      /* control type: textMsg, callback function: (none) */
#define  SETGRAPH_TEXTMSG_5               14      /* control type: textMsg, callback function: (none) */
#define  SETGRAPH_TEXTMSG_2               15      /* control type: textMsg, callback function: (none) */
#define  SETGRAPH_RING_3                  16      /* control type: ring, callback function: (none) */
#define  SETGRAPH_TEXTMSG_7               17      /* control type: textMsg, callback function: (none) */
#define  SETGRAPH_TXT_PLOT_STYLE          18      /* control type: textMsg, callback function: (none) */
#define  SETGRAPH_TEXTMSG_8               19      /* control type: textMsg, callback function: (none) */
#define  SETGRAPH_TEXTMSG_6               20      /* control type: textMsg, callback function: (none) */

#define  SETTINGS                         4       /* callback function: SettingsCB */
#define  SETTINGS_CANVAS                  2       /* control type: canvas, callback function: (none) */
#define  SETTINGS_DECORATION              3       /* control type: deco, callback function: (none) */
#define  SETTINGS_ABOUTBTN                4       /* control type: textMsg, callback function: AboutBtnCallback */
#define  SETTINGS_GRAPHBTN                5       /* control type: textMsg, callback function: GraphBtnCallback */
#define  SETTINGS_PRJBTN                  6       /* control type: textMsg, callback function: PrjBtnCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK AboutBtnCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Graph2clr1CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Graph2clr2CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Graph2clr3CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK GraphBtnCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PrjBtnCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ProCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SettingsCB(int panel, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
