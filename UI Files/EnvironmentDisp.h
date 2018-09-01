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

#define  ENVIRONMEN                       1
#define  ENVIRONMEN_MEASURE               2       /* control type: radioButton, callback function: MesaureCallback */
#define  ENVIRONMEN_TEMPTER               3       /* control type: radioButton, callback function: (none) */
#define  ENVIRONMEN_HUMIDITY              4       /* control type: radioButton, callback function: (none) */
#define  ENVIRONMEN_PRESSURE              5       /* control type: radioButton, callback function: (none) */
#define  ENVIRONMEN_TEX_MEAS              6       /* control type: textMsg, callback function: (none) */
#define  ENVIRONMEN_TXT_HUM               7       /* control type: textMsg, callback function: (none) */
#define  ENVIRONMEN_TXT_TEMP              8       /* control type: textMsg, callback function: (none) */
#define  ENVIRONMEN_TXT_PRESS             9       /* control type: textMsg, callback function: (none) */

#define  ENVIRPANEL                       2
#define  ENVIRPANEL_LEGENDCHECK           2       /* control type: radioButton, callback function: Legend_display_CB */
#define  ENVIRPANEL_CHECKBOX              3       /* control type: radioButton, callback function: Temp_displayCB */
#define  ENVIRPANEL_STR_TEMP              4       /* control type: numeric, callback function: (none) */
#define  ENVIRPANEL_CHECKBOX_2            5       /* control type: radioButton, callback function: Humidity_displayCB */
#define  ENVIRPANEL_STR_HUM               6       /* control type: numeric, callback function: (none) */
#define  ENVIRPANEL_CHECKBOX_3            7       /* control type: radioButton, callback function: Pressure_displayCB */
#define  ENVIRPANEL_STR_PRES              8       /* control type: numeric, callback function: (none) */
#define  ENVIRPANEL_TXT_HUM               9       /* control type: textMsg, callback function: (none) */
#define  ENVIRPANEL_TXT_PRESS             10      /* control type: textMsg, callback function: (none) */
#define  ENVIRPANEL_TEXTMSG_2             11      /* control type: textMsg, callback function: (none) */
#define  ENVIRPANEL_TEXTMSG               12      /* control type: textMsg, callback function: (none) */
#define  ENVIRPANEL_TEXTMSG_3             13      /* control type: textMsg, callback function: (none) */
#define  ENVIRPANEL_TXT_TEMP              14      /* control type: textMsg, callback function: (none) */
#define  ENVIRPANEL_TXT_LEGEND            15      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK Humidity_displayCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Legend_display_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MesaureCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Pressure_displayCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Temp_displayCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
