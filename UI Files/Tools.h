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

#define  CALPANEL                         1       /* callback function: CalPanelCallback */
#define  CALPANEL_TEXTMSG                 2       /* control type: textMsg, callback function: (none) */
#define  CALPANEL_RING                    3       /* control type: ring, callback function: (none) */
#define  CALPANEL_TEXTMSG_2               4       /* control type: textMsg, callback function: (none) */
#define  CALPANEL_TEXTMSG_3               5       /* control type: textMsg, callback function: CalOkCallback */
#define  CALPANEL_OK_PIC                  6       /* control type: picture, callback function: CalOkCallback */
#define  CALPANEL_OUTVOLCAL               7       /* control type: textMsg, callback function: OutVoltageCallback */
#define  CALPANEL_TEXTMSG_6               8       /* control type: textMsg, callback function: (none) */
#define  CALPANEL_ZEROCURCAL              9       /* control type: textMsg, callback function: ZeroCurrentCallback */

#define  TOOLSPANEL                       2       /* callback function: ToolsPanelCallback */
#define  TOOLSPANEL_PICTURE               2       /* control type: picture, callback function: CalibrationCallback */
#define  TOOLSPANEL_CALIBRATION           3       /* control type: textMsg, callback function: CalibrationCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK CalibrationCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CalOkCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CalPanelCallback(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OutVoltageCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ToolsPanelCallback(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ZeroCurrentCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
