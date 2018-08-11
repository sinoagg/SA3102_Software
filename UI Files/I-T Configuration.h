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

#define  PANEL_I_T                        1
#define  PANEL_I_T_GAP2                   2       /* control type: numeric, callback function: Gap2Callback */
#define  PANEL_I_T_START2                 3       /* control type: numeric, callback function: Start2Callback */
#define  PANEL_I_T_STOP2                  4       /* control type: numeric, callback function: Stop2Callback */
#define  PANEL_I_T_SMU2MODE               5       /* control type: ring, callback function: SMU2ModeCallback */
#define  PANEL_I_T_GAP1                   6       /* control type: numeric, callback function: Gap1Callback */
#define  PANEL_I_T_START1                 7       /* control type: numeric, callback function: Start1Callback */
#define  PANEL_I_T_STOP1                  8       /* control type: numeric, callback function: Stop1Callback */
#define  PANEL_I_T_SMU1MODE               9       /* control type: ring, callback function: SMU1ModeCallback */
#define  PANEL_I_T_STOP_1                 10      /* control type: textMsg, callback function: (none) */
#define  PANEL_I_T_STEP_1                 11      /* control type: textMsg, callback function: (none) */
#define  PANEL_I_T_START_1                12      /* control type: textMsg, callback function: (none) */
#define  PANEL_I_T_PICTURE_4              13      /* control type: picture, callback function: (none) */
#define  PANEL_I_T_PICTURE_2              14      /* control type: picture, callback function: (none) */
#define  PANEL_I_T_ST_TEXT_3              15      /* control type: textMsg, callback function: (none) */
#define  PANEL_I_T_PICTURE_5              16      /* control type: picture, callback function: (none) */
#define  PANEL_I_T_PIC_SMU1               17      /* control type: picture, callback function: (none) */
#define  PANEL_I_T_PICTURE                18      /* control type: picture, callback function: (none) */
#define  PANEL_I_T_ST_TEXT_1              19      /* control type: textMsg, callback function: (none) */
#define  PANEL_I_T_START_2                20      /* control type: textMsg, callback function: (none) */
#define  PANEL_I_T_STOP_2                 21      /* control type: textMsg, callback function: (none) */
#define  PANEL_I_T_STEP_2                 22      /* control type: textMsg, callback function: (none) */
#define  PANEL_I_T_DECORATION_SMU1        23      /* control type: deco, callback function: SMU1DecoCallback */
#define  PANEL_I_T_DECORATION_SMU2        24      /* control type: deco, callback function: SMU2DecoCallback */
#define  PANEL_I_T_TXT_SMU2               25      /* control type: textMsg, callback function: (none) */
#define  PANEL_I_T_TXT_SMU1               26      /* control type: textMsg, callback function: (none) */
#define  PANEL_I_T_PIC_SMU2               27      /* control type: picture, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK Gap1Callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Gap2Callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SMU1DecoCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SMU1ModeCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SMU2DecoCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SMU2ModeCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Start1Callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Start2Callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Stop1Callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Stop2Callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
