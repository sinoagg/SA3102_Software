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

#define  CALIPANEL                        1       /* callback function: CaliPanelCallback */
#define  CALIPANEL_TEXTMSG                2       /* control type: textMsg, callback function: (none) */
#define  CALIPANEL_RING                   3       /* control type: ring, callback function: (none) */
#define  CALIPANEL_TEXTMSG_2              4       /* control type: textMsg, callback function: (none) */
#define  CALIPANEL_TEXTMSG_7              5       /* control type: textMsg, callback function: TEXTMSG_7_Callback */
#define  CALIPANEL_OK_PIC_2               6       /* control type: picture, callback function: TEXTMSG_7_Callback */
#define  CALIPANEL_TEXTMSG_3              7       /* control type: textMsg, callback function: Calibration_save */
#define  CALIPANEL_OK_PIC                 8       /* control type: picture, callback function: Calibration_save */
#define  CALIPANEL_OUTVOLCALI             9       /* control type: textMsg, callback function: OutputVoltageCaliCallback */
#define  CALIPANEL_TEXTMSG_6              10      /* control type: textMsg, callback function: Current_Calibration */
#define  CALIPANEL_ZEROCURCALI            11      /* control type: textMsg, callback function: ZeroCurrentCaliCallback */
#define  TOOLSPANEL                       2       /* callback function: ToolsPanelCallback */
#define  TOOLSPANEL_PICTURE               2       /* control type: picture, callback function: CalibrationCallback */
#define  TOOLSPANEL_CALIBRATION           3       /* control type: textMsg, callback function: CalibrationCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */
int  CVICALLBACK Calibration_save(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CalibrationCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CaliPanelCallback(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Current_Calibration(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OutputVoltageCaliCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK TEXTMSG_7_Callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ToolsPanelCallback(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ZeroCurrentCaliCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
