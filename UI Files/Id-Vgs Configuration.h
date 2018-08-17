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

#define  IDVGS_CFG                        1
#define  IDVGS_CFG_PIC_IDVD_DRAIN         2       /* control type: picture, callback function: (none) */
#define  IDVGS_CFG_PIC_IDVD_SOURCE        3       /* control type: picture, callback function: (none) */
#define  IDVGS_CFG_PIC_IDVD_BLUK          4       /* control type: picture, callback function: (none) */
#define  IDVGS_CFG_PIC_IDVD_GATE          5       /* control type: picture, callback function: (none) */
#define  IDVGS_CFG_PIC_FET                6       /* control type: picture, callback function: (none) */
#define  IDVGS_CFG_TEXTMSG                7       /* control type: textMsg, callback function: (none) */
#define  IDVGS_CFG_VG_STEP_2              8       /* control type: numeric, callback function: IdVgDRAINDecoCB */
#define  IDVGS_CFG_VG_STEP                9       /* control type: numeric, callback function: IdVgGATEDecoCB */
#define  IDVGS_CFG_VG_STOP_2              10      /* control type: numeric, callback function: IdVgDRAINDecoCB */
#define  IDVGS_CFG_VG_START_2             11      /* control type: numeric, callback function: IdVgDRAINDecoCB */
#define  IDVGS_CFG_RING_10                12      /* control type: ring, callback function: IdVgDRAINDecoCB */
#define  IDVGS_CFG_TEXTMSG_42             13      /* control type: textMsg, callback function: IdVgDRAINDecoCB */
#define  IDVGS_CFG_TEXTMSG_43             14      /* control type: textMsg, callback function: IdVgDRAINDecoCB */
#define  IDVGS_CFG_TEXTMSG_44             15      /* control type: textMsg, callback function: IdVgDRAINDecoCB */
#define  IDVGS_CFG_TEXTMSG_45             16      /* control type: textMsg, callback function: IdVgDRAINDecoCB */
#define  IDVGS_CFG_TEXTMSG_46             17      /* control type: textMsg, callback function: IdVgDRAINDecoCB */
#define  IDVGS_CFG_TEXTMSG_47             18      /* control type: textMsg, callback function: IdVgDRAINDecoCB */
#define  IDVGS_CFG_TEXTMSG_48             19      /* control type: textMsg, callback function: IdVgDRAINDecoCB */
#define  IDVGS_CFG_TXT_DRAIN              20      /* control type: textMsg, callback function: IdVgDRAINDecoCB */
#define  IDVGS_CFG_DECORATION_Drain       21      /* control type: deco, callback function: IdVgDRAINDecoCB */
#define  IDVGS_CFG_VG_STOP                22      /* control type: numeric, callback function: IdVgGATEDecoCB */
#define  IDVGS_CFG_BG_DRAIN               23      /* control type: canvas, callback function: IdVgDRAINDecoCB */
#define  IDVGS_CFG_VG_START               24      /* control type: numeric, callback function: IdVgGATEDecoCB */
#define  IDVGS_CFG_RING_3                 25      /* control type: ring, callback function: IdVgGATEDecoCB */
#define  IDVGS_CFG_TEXTMSG_18             26      /* control type: textMsg, callback function: IdVgGATEDecoCB */
#define  IDVGS_CFG_TEXTMSG_14             27      /* control type: textMsg, callback function: IdVgGATEDecoCB */
#define  IDVGS_CFG_TEXTMSG_19             28      /* control type: textMsg, callback function: IdVgGATEDecoCB */
#define  IDVGS_CFG_TEXTMSG_15             29      /* control type: textMsg, callback function: IdVgGATEDecoCB */
#define  IDVGS_CFG_TEXTMSG_20             30      /* control type: textMsg, callback function: IdVgGATEDecoCB */
#define  IDVGS_CFG_TEXTMSG_17             31      /* control type: textMsg, callback function: IdVgGATEDecoCB */
#define  IDVGS_CFG_TEXTMSG_22             32      /* control type: textMsg, callback function: IdVgGATEDecoCB */
#define  IDVGS_CFG_TXT_GATE               33      /* control type: textMsg, callback function: IdVgGATEDecoCB */
#define  IDVGS_CFG_DECORATION_Gate        34      /* control type: deco, callback function: IdVgGATEDecoCB */
#define  IDVGS_CFG_BG_GATE                35      /* control type: canvas, callback function: IdVgGATEDecoCB */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK IdVgDRAINDecoCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IdVgGATEDecoCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
