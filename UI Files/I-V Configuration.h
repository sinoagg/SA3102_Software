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

#define  PANEL_I_V                        1
#define  PANEL_I_V_SMU1MODE               2       /* control type: ring, callback function: IVSMU1DecoCallback */
#define  PANEL_I_V_START1                 3       /* control type: numeric, callback function: IVSMU1DecoCallback */
#define  PANEL_I_V_STOP1                  4       /* control type: numeric, callback function: IVSMU1DecoCallback */
#define  PANEL_I_V_GAP1                   5       /* control type: numeric, callback function: IVSMU1DecoCallback */
#define  PANEL_I_V_SMU2MODE               6       /* control type: ring, callback function: IVSMU2DecoCallback */
#define  PANEL_I_V_START2                 7       /* control type: numeric, callback function: IVSMU2DecoCallback */
#define  PANEL_I_V_STOP2                  8       /* control type: numeric, callback function: IVSMU2DecoCallback */
#define  PANEL_I_V_GAP2                   9       /* control type: numeric, callback function: IVSMU2DecoCallback */
#define  PANEL_I_V_DECORATION_SMU1        10      /* control type: deco, callback function: IVSMU1DecoCallback */
#define  PANEL_I_V_TEXTMSG_7              11      /* control type: textMsg, callback function: IVSMU1DecoCallback */
#define  PANEL_I_V_PICTURE                12      /* control type: picture, callback function: (none) */
#define  PANEL_I_V_PICTURE_2              13      /* control type: picture, callback function: (none) */
#define  PANEL_I_V_START_1                14      /* control type: textMsg, callback function: IVSMU1DecoCallback */
#define  PANEL_I_V_PICTURE_4              15      /* control type: picture, callback function: (none) */
#define  PANEL_I_V_STOP_1                 16      /* control type: textMsg, callback function: IVSMU1DecoCallback */
#define  PANEL_I_V_ST_TEXT_3              17      /* control type: textMsg, callback function: IVSMU2DecoCallback */
#define  PANEL_I_V_BG_SMU1                18      /* control type: canvas, callback function: IVSMU1DecoCallback */
#define  PANEL_I_V_ST_TEXT_1              19      /* control type: textMsg, callback function: IVSMU1DecoCallback */
#define  PANEL_I_V_START_2                20      /* control type: textMsg, callback function: IVSMU2DecoCallback */
#define  PANEL_I_V_STOP_2                 21      /* control type: textMsg, callback function: IVSMU2DecoCallback */
#define  PANEL_I_V_TXT_SMU2               22      /* control type: textMsg, callback function: IVSMU2DecoCallback */
#define  PANEL_I_V_TXT_SMU1               23      /* control type: textMsg, callback function: IVSMU1DecoCallback */
#define  PANEL_I_V_TEXTMSG_6              24      /* control type: textMsg, callback function: IVSMU2DecoCallback */
#define  PANEL_I_V_TEXTMSG_5              25      /* control type: textMsg, callback function: IVSMU2DecoCallback */
#define  PANEL_I_V_TEXTMSG_4              26      /* control type: textMsg, callback function: IVSMU1DecoCallback */
#define  PANEL_I_V_TEXTMSG_3              27      /* control type: textMsg, callback function: IVSMU2DecoCallback */
#define  PANEL_I_V_TEXTMSG_2              28      /* control type: textMsg, callback function: IVSMU1DecoCallback */
#define  PANEL_I_V_TEXTMSG                29      /* control type: textMsg, callback function: (none) */
#define  PANEL_I_V_BG_SMU2                30      /* control type: canvas, callback function: IVSMU2DecoCallback */
#define  PANEL_I_V_STEP_3                 31      /* control type: textMsg, callback function: IVSMU2DecoCallback */
#define  PANEL_I_V_DECORATION_SMU2        32      /* control type: deco, callback function: IVSMU2DecoCallback */
#define  PANEL_I_V_STEP_1                 33      /* control type: textMsg, callback function: IVSMU1DecoCallback */
#define  PANEL_I_V_PICTURE_6              34      /* control type: picture, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK IVSMU1DecoCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IVSMU2DecoCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
