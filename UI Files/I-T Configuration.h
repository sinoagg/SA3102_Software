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
#define  PANEL_I_T_START2                 2       /* control type: numeric, callback function: SMU2DecoCallback */
#define  PANEL_I_T_SMU2MODE               3       /* control type: ring, callback function: SMU2DecoCallback */
#define  PANEL_I_T_START1                 4       /* control type: numeric, callback function: SMU1DecoCallback */
#define  PANEL_I_T_SMU1MODE               5       /* control type: ring, callback function: SMU1DecoCallback */
#define  PANEL_I_T_START_1                6       /* control type: textMsg, callback function: (none) */
#define  PANEL_I_T_PICTURE_4              7       /* control type: picture, callback function: (none) */
#define  PANEL_I_T_PICTURE_2              8       /* control type: picture, callback function: (none) */
#define  PANEL_I_T_ST_TEXT_3              9       /* control type: textMsg, callback function: (none) */
#define  PANEL_I_T_PICTURE_5              10      /* control type: picture, callback function: (none) */
#define  PANEL_I_T_PICTURE                11      /* control type: picture, callback function: (none) */
#define  PANEL_I_T_ST_TEXT_1              12      /* control type: textMsg, callback function: (none) */
#define  PANEL_I_T_START_2                13      /* control type: textMsg, callback function: (none) */
#define  PANEL_I_T_DECORATION_SMU1        14      /* control type: deco, callback function: SMU1DecoCallback */
#define  PANEL_I_T_DECORATION_SMU2        15      /* control type: deco, callback function: SMU2DecoCallback */
#define  PANEL_I_T_TXT_SMU2               16      /* control type: textMsg, callback function: (none) */
#define  PANEL_I_T_TXT_SMU1               17      /* control type: textMsg, callback function: (none) */
#define  PANEL_I_T_BG_SMU2                18      /* control type: canvas, callback function: (none) */
#define  PANEL_I_T_TEXTMSG                19      /* control type: textMsg, callback function: (none) */
#define  PANEL_I_T_BG_SMU1                20      /* control type: canvas, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK SMU1DecoCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SMU2DecoCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
