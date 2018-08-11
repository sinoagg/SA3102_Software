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

#define  DEFPANEL                         1       /* callback function: PrjSelectCallback */
#define  DEFPANEL_NAME                    2       /* control type: textMsg, callback function: (none) */
#define  DEFPANEL_CANVAS                  3       /* control type: canvas, callback function: (none) */
#define  DEFPANEL_DESC                    4       /* control type: textMsg, callback function: (none) */
#define  DEFPANEL_PICS                    5       /* control type: picture, callback function: (none) */
#define  DEFPANEL_DATE                    6       /* control type: textMsg, callback function: (none) */
#define  DEFPANEL_TIME                    7       /* control type: textMsg, callback function: (none) */

#define  PROPANEL                         2       /* callback function: PIC_ExitPrjCallback */
#define  PROPANEL_SPLITTER                2       /* control type: splitter, callback function: (none) */
#define  PROPANEL_STRING                  3       /* control type: string, callback function: (none) */
#define  PROPANEL_SEARCH                  4       /* control type: command, callback function: SearchCallback */
#define  PROPANEL_PIC_EXIT                5       /* control type: picture, callback function: PIC_ExitPrjCallback2 */
#define  PROPANEL_TXT_EXIT                6       /* control type: textMsg, callback function: PIC_ExitPrjCallback2 */
#define  PROPANEL_TXT_OPENPRJ             7       /* control type: textMsg, callback function: TXT_OpenPrjCallback */
#define  PROPANEL_PIC_OPENPRJ             8       /* control type: picture, callback function: TXT_OpenPrjCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK PIC_ExitPrjCallback(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PIC_ExitPrjCallback2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PrjSelectCallback(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SearchCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK TXT_OpenPrjCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
