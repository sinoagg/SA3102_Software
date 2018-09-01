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

#define  SAMPLE_ADV                       1
#define  SAMPLE_ADV_MAXRANGE              2       /* control type: ring, callback function: (none) */
#define  SAMPLE_ADV_MINRANGE              3       /* control type: ring, callback function: (none) */
#define  SAMPLE_ADV_OutputRelay           4       /* control type: radioButton, callback function: (none) */
#define  SAMPLE_ADV_TEXTMSG               5       /* control type: textMsg, callback function: (none) */
#define  SAMPLE_ADV_TEXTMSG_2             6       /* control type: textMsg, callback function: (none) */
#define  SAMPLE_ADV_BSCSET                7       /* control type: textMsg, callback function: BasicSetCallback */
#define  SAMPLE_ADV_TEXTMSG_3             8       /* control type: textMsg, callback function: (none) */

#define  SAMPLE_CFG                       2
#define  SAMPLE_CFG_QUIETTIME             2       /* control type: numeric, callback function: (none) */
#define  SAMPLE_CFG_TIMESTEP              3       /* control type: numeric, callback function: (none) */
#define  SAMPLE_CFG_SAMPLERATE            4       /* control type: numeric, callback function: (none) */
#define  SAMPLE_CFG_SAMPLENUMBER          5       /* control type: numeric, callback function: (none) */
#define  SAMPLE_CFG_RANGESETTING          6       /* control type: ring, callback function: (none) */
#define  SAMPLE_CFG_RUNTIME               7       /* control type: numeric, callback function: (none) */
#define  SAMPLE_CFG_TEXTMSG_2             8       /* control type: textMsg, callback function: (none) */
#define  SAMPLE_CFG_TEXTMSG_4             9       /* control type: textMsg, callback function: (none) */
#define  SAMPLE_CFG_TEXTMSG_6             10      /* control type: textMsg, callback function: (none) */
#define  SAMPLE_CFG_TEXTMSG_5             11      /* control type: textMsg, callback function: (none) */
#define  SAMPLE_CFG_TEXTMSG               12      /* control type: textMsg, callback function: (none) */
#define  SAMPLE_CFG_ADVCSET               13      /* control type: textMsg, callback function: AdvancSetCallback */
#define  SAMPLE_CFG_TEXTMSG_7             14      /* control type: textMsg, callback function: (none) */
#define  SAMPLE_CFG_TEXTMSG_8             15      /* control type: textMsg, callback function: (none) */
#define  SAMPLE_CFG_TEXTMSG_10            16      /* control type: textMsg, callback function: (none) */
#define  SAMPLE_CFG_TXT_RUNTIME           17      /* control type: textMsg, callback function: (none) */
#define  SAMPLE_CFG_TXT_S                 18      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK AdvancSetCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK BasicSetCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
