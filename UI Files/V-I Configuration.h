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

#define  PANEL_V_I                        1
#define  PANEL_V_I_GAP2                   2       /* control type: numeric, callback function: VISMU2DecoCallback */
#define  PANEL_V_I_START2                 3       /* control type: numeric, callback function: VISMU2DecoCallback */
#define  PANEL_V_I_STOP2                  4       /* control type: numeric, callback function: VISMU2DecoCallback */
#define  PANEL_V_I_SMU2MODE               5       /* control type: ring, callback function: VISMU2DecoCallback */
#define  PANEL_V_I_GAP1                   6       /* control type: numeric, callback function: VISMU1DecoCallback */
#define  PANEL_V_I_START1                 7       /* control type: numeric, callback function: VISMU1DecoCallback */
#define  PANEL_V_I_STOP1                  8       /* control type: numeric, callback function: VISMU1DecoCallback */
#define  PANEL_V_I_SMU1MODE               9       /* control type: ring, callback function: VISMU1DecoCallback */
#define  PANEL_V_I_STOP_1                 10      /* control type: textMsg, callback function: (none) */
#define  PANEL_V_I_STEP_1                 11      /* control type: textMsg, callback function: (none) */
#define  PANEL_V_I_START_1                12      /* control type: textMsg, callback function: (none) */
#define  PANEL_V_I_PICTURE_4              13      /* control type: picture, callback function: (none) */
#define  PANEL_V_I_PICTURE_2              14      /* control type: picture, callback function: (none) */
#define  PANEL_V_I_ST_TEXT_2              15      /* control type: textMsg, callback function: (none) */
#define  PANEL_V_I_ST_TEXT_1              16      /* control type: textMsg, callback function: (none) */
#define  PANEL_V_I_START_2                17      /* control type: textMsg, callback function: (none) */
#define  PANEL_V_I_STOP_2                 18      /* control type: textMsg, callback function: (none) */
#define  PANEL_V_I_DECORATION_SMU2        19      /* control type: deco, callback function: VISMU2DecoCallback */
#define  PANEL_V_I_TXT_SMU2               20      /* control type: textMsg, callback function: (none) */
#define  PANEL_V_I_TXT_SMU1               21      /* control type: textMsg, callback function: (none) */
#define  PANEL_V_I_BG_SMU1                22      /* control type: canvas, callback function: (none) */
#define  PANEL_V_I_DECORATION_SMU1        23      /* control type: deco, callback function: VISMU1DecoCallback */
#define  PANEL_V_I_BG_SMU2                24      /* control type: canvas, callback function: (none) */
#define  PANEL_V_I_TEXTMSG                25      /* control type: textMsg, callback function: (none) */
#define  PANEL_V_I_PICTURE_7              26      /* control type: picture, callback function: (none) */
#define  PANEL_V_I_PICTURE_6              27      /* control type: picture, callback function: (none) */
#define  PANEL_V_I_STEP_2                 28      /* control type: textMsg, callback function: (none) */
#define  PANEL_V_I_START2UNIT             29      /* control type: ring, callback function: Start2UnitCB */
#define  PANEL_V_I_START1UNIT             30      /* control type: ring, callback function: Start1UnitCB */
#define  PANEL_V_I_GAP1UNIT               31      /* control type: textMsg, callback function: VISMU1DecoCallback */
#define  PANEL_V_I_STOP2UNIT              32      /* control type: textMsg, callback function: VISMU2DecoCallback */
#define  PANEL_V_I_STOP1UNIT              33      /* control type: textMsg, callback function: VISMU1DecoCallback */
#define  PANEL_V_I_GAP2UNIT               34      /* control type: textMsg, callback function: VISMU2DecoCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK Start1UnitCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Start2UnitCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK VISMU1DecoCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK VISMU2DecoCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
