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

#define  PANEL_V_T                        1
#define  PANEL_V_T_START2                 2       /* control type: numeric, callback function: VTSMU2DecoCallback */
#define  PANEL_V_T_SMU2MODE               3       /* control type: ring, callback function: VTSMU2DecoCallback */
#define  PANEL_V_T_START1                 4       /* control type: numeric, callback function: VTSMU1DecoCallback */
#define  PANEL_V_T_SMU1MODE               5       /* control type: ring, callback function: VTSMU1DecoCallback */
#define  PANEL_V_T_START_1                6       /* control type: textMsg, callback function: VTSMU1DecoCallback */
#define  PANEL_V_T_PICTURE_4              7       /* control type: picture, callback function: (none) */
#define  PANEL_V_T_PICTURE_2              8       /* control type: picture, callback function: (none) */
#define  PANEL_V_T_ST_TEXT_3              9       /* control type: textMsg, callback function: VTSMU2DecoCallback */
#define  PANEL_V_T_ST_TEXT_1              10      /* control type: textMsg, callback function: VTSMU1DecoCallback */
#define  PANEL_V_T_START_2                11      /* control type: textMsg, callback function: VTSMU2DecoCallback */
#define  PANEL_V_T_DECORATION_SMU1        12      /* control type: deco, callback function: VTSMU1DecoCallback */
#define  PANEL_V_T_DECORATION_SMU2        13      /* control type: deco, callback function: VTSMU2DecoCallback */
#define  PANEL_V_T_TXT_SMU2               14      /* control type: textMsg, callback function: VTSMU2DecoCallback */
#define  PANEL_V_T_TXT_SMU1               15      /* control type: textMsg, callback function: VTSMU1DecoCallback */
#define  PANEL_V_T_BG_SMU2                16      /* control type: canvas, callback function: VTSMU2DecoCallback */
#define  PANEL_V_T_TEXTMSG                17      /* control type: textMsg, callback function: (none) */
#define  PANEL_V_T_BG_SMU1                18      /* control type: canvas, callback function: VTSMU1DecoCallback */
#define  PANEL_V_T_PICTURE_6              19      /* control type: picture, callback function: (none) */
#define  PANEL_V_T_PICTURE_7              20      /* control type: picture, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK VTSMU1DecoCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK VTSMU2DecoCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
