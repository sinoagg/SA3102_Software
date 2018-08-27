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

#define  IDVDS_CFG                        1
#define  IDVDS_CFG_PIC_IDVD_DRAIN         2       /* control type: picture, callback function: (none) */
#define  IDVDS_CFG_PIC_GATE               3       /* control type: picture, callback function: (none) */
#define  IDVDS_CFG_PIC_IDVD_BLUK_2        4       /* control type: picture, callback function: (none) */
#define  IDVDS_CFG_PIC_IDVD_BLUK          5       /* control type: picture, callback function: (none) */
#define  IDVDS_CFG_PIC_FET                6       /* control type: picture, callback function: (none) */
#define  IDVDS_CFG_TEXTMSG                7       /* control type: textMsg, callback function: (none) */
#define  IDVDS_CFG_VG_STEP_2              8       /* control type: numeric, callback function: IdVdDRAINDecoCB */
#define  IDVDS_CFG_VG_STOP_2              9       /* control type: numeric, callback function: IdVdDRAINDecoCB */
#define  IDVDS_CFG_VG_START_2             10      /* control type: numeric, callback function: IdVdDRAINDecoCB */
#define  IDVDS_CFG_RING_6                 11      /* control type: ring, callback function: IdVdDRAINDecoCB */
#define  IDVDS_CFG_TEXTMSG_32             12      /* control type: textMsg, callback function: IdVdDRAINDecoCB */
#define  IDVDS_CFG_TEXTMSG_33             13      /* control type: textMsg, callback function: IdVdDRAINDecoCB */
#define  IDVDS_CFG_TEXTMSG_34             14      /* control type: textMsg, callback function: IdVdDRAINDecoCB */
#define  IDVDS_CFG_TEXTMSG_35             15      /* control type: textMsg, callback function: IdVdDRAINDecoCB */
#define  IDVDS_CFG_TEXTMSG_36             16      /* control type: textMsg, callback function: IdVdDRAINDecoCB */
#define  IDVDS_CFG_TEXTMSG_37             17      /* control type: textMsg, callback function: IdVdDRAINDecoCB */
#define  IDVDS_CFG_TEXTMSG_38             18      /* control type: textMsg, callback function: IdVdDRAINDecoCB */
#define  IDVDS_CFG_TXT_DRAIN              19      /* control type: textMsg, callback function: IdVdDRAINDecoCB */
#define  IDVDS_CFG_DECORATION_Drain       20      /* control type: deco, callback function: IdVdDRAINDecoCB */
#define  IDVDS_CFG_BG_DRAIN               21      /* control type: canvas, callback function: IdVdDRAINDecoCB */
#define  IDVDS_CFG_VG_STEP                22      /* control type: numeric, callback function: IdVdGATEDecoCB */
#define  IDVDS_CFG_VG_STOP                23      /* control type: numeric, callback function: IdVdGATEDecoCB */
#define  IDVDS_CFG_VG_START               24      /* control type: numeric, callback function: IdVdGATEDecoCB */
#define  IDVDS_CFG_GATEMODE               25      /* control type: ring, callback function: IdVdGateModeCB */
#define  IDVDS_CFG_TEXTMSG_24             26      /* control type: textMsg, callback function: IdVdGATEDecoCB */
#define  IDVDS_CFG_TEXTMSG_25             27      /* control type: textMsg, callback function: IdVdGATEDecoCB */
#define  IDVDS_CFG_TEXTMSG_26             28      /* control type: textMsg, callback function: IdVdGATEDecoCB */
#define  IDVDS_CFG_TXT_STOP               29      /* control type: textMsg, callback function: IdVdGATEDecoCB */
#define  IDVDS_CFG_TXT_MV                 30      /* control type: textMsg, callback function: IdVdGATEDecoCB */
#define  IDVDS_CFG_TXT_STEP               31      /* control type: textMsg, callback function: IdVdGATEDecoCB */
#define  IDVDS_CFG_TXT_MV2                32      /* control type: textMsg, callback function: IdVdGATEDecoCB */
#define  IDVDS_CFG_TXT_GATE               33      /* control type: textMsg, callback function: IdVdGATEDecoCB */
#define  IDVDS_CFG_BG_GATE                34      /* control type: canvas, callback function: IdVdGATEDecoCB */
#define  IDVDS_CFG_DECORATION_Gate        35      /* control type: deco, callback function: IdVdGATEDecoCB */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK IdVdDRAINDecoCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IdVdGATEDecoCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IdVdGateModeCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
