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

#define  CHPANEL                          1
#define  CHPANEL_CHECKBOX                 2       /* control type: radioButton, callback function: ChoseCallback */

#define  RESULTMENU                       2
#define  RESULTMENU_TABLE                 2       /* control type: picture, callback function: TableCallback */
#define  RESULTMENU_SAVE                  3       /* control type: picture, callback function: SaveDataCallback */
#define  RESULTMENU_GRAPH                 4       /* control type: picture, callback function: GraphCallback */

#define  SAVEDATA                         3       /* callback function: SaveDataPanelCallbck */
#define  SAVEDATA_SHEETPATH               2       /* control type: string, callback function: (none) */
#define  SAVEDATA_GRAPH1PATH              3       /* control type: string, callback function: (none) */
#define  SAVEDATA_GRAPH2PATH              4       /* control type: string, callback function: (none) */
#define  SAVEDATA_TEXTMSG                 5       /* control type: textMsg, callback function: (none) */
#define  SAVEDATA_TEXTMSG_3               6       /* control type: textMsg, callback function: (none) */
#define  SAVEDATA_TEXTMSG_2               7       /* control type: textMsg, callback function: (none) */
#define  SAVEDATA_TEXTMSG_4               8       /* control type: textMsg, callback function: SaveSheetCallback */
#define  SAVEDATA_PICTURE_2               9       /* control type: picture, callback function: SaveSheetCallback */
#define  SAVEDATA_TEXTMSG_6               10      /* control type: textMsg, callback function: SaveGraph1Callback */
#define  SAVEDATA_PICTURE_3               11      /* control type: picture, callback function: SaveGraph1Callback */
#define  SAVEDATA_TEXTMSG_7               12      /* control type: textMsg, callback function: SaveGraph2Callback */
#define  SAVEDATA_PICTURE_4               13      /* control type: picture, callback function: SaveGraph2Callback */
#define  SAVEDATA_TEXTMSG_5               14      /* control type: textMsg, callback function: SaveAllCallback */
#define  SAVEDATA_PICTURE                 15      /* control type: picture, callback function: SaveAllCallback */
#define  SAVEDATA_TEXTMSG_11              16      /* control type: textMsg, callback function: ExitCallback */
#define  SAVEDATA_PICTURE_8               17      /* control type: picture, callback function: ExitCallback */
#define  SAVEDATA_TEXTMSG_9               18      /* control type: textMsg, callback function: BrowseGraph2Callback */
#define  SAVEDATA_TEXTMSG_10              19      /* control type: textMsg, callback function: BrowseGraph1Callback */
#define  SAVEDATA_PICTURE_7               20      /* control type: picture, callback function: BrowseGraph1Callback */
#define  SAVEDATA_TEXTMSG_8               21      /* control type: textMsg, callback function: BrowseSheetCallback */
#define  SAVEDATA_PICTURE_6               22      /* control type: picture, callback function: BrowseGraph2Callback */
#define  SAVEDATA_PICTURE_5               23      /* control type: picture, callback function: BrowseSheetCallback */


     /* Control Arrays: */

#define  CTRLARRAY                        1

     /* Menu Bars, Menus, and Menu Items: */

#define  MENUBAR                          1
#define  MENUBAR_UNNAMEDM                 2


     /* Callback Prototypes: */

int  CVICALLBACK BrowseGraph1Callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK BrowseGraph2Callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK BrowseSheetCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ChoseCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ExitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK GraphCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SaveAllCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SaveDataCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SaveDataPanelCallbck(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SaveGraph1Callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SaveGraph2Callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SaveSheetCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK TableCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
