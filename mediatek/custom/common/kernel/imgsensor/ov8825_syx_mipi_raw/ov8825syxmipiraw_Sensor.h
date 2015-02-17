/*******************************************************************************************/


/*******************************************************************************************/

/* SENSOR FULL SIZE */
#ifndef __SENSOR_H
#define __SENSOR_H   

#define ZSD15FPS
#define VIDEO_PREVIEW_SYNC
typedef enum group_enum {
    PRE_GAIN=0,
    CMMCLK_CURRENT,
    FRAME_RATE_LIMITATION,
    REGISTER_EDITOR,
    GROUP_TOTAL_NUMS
} FACTORY_GROUP_ENUM;


#define ENGINEER_START_ADDR 10
#define FACTORY_START_ADDR 0

typedef enum engineer_index
{
    CMMCLK_CURRENT_INDEX=ENGINEER_START_ADDR,
    ENGINEER_END
} FACTORY_ENGINEER_INDEX;

typedef enum register_index
{
	SENSOR_BASEGAIN=FACTORY_START_ADDR,
	PRE_GAIN_R_INDEX,
	PRE_GAIN_Gr_INDEX,
	PRE_GAIN_Gb_INDEX,
	PRE_GAIN_B_INDEX,
	FACTORY_END_ADDR
} FACTORY_REGISTER_INDEX;

typedef struct
{
    SENSOR_REG_STRUCT	Reg[ENGINEER_END];
    SENSOR_REG_STRUCT	CCT[FACTORY_END_ADDR];
} SENSOR_DATA_STRUCT, *PSENSOR_DATA_STRUCT;

typedef enum {
    SENSOR_MODE_INIT = 0,
    SENSOR_MODE_PREVIEW,
    SENSOR_MODE_VIDEO,
    SENSOR_MODE_CAPTURE
} OV8825SYX_SENSOR_MODE;


typedef struct
{
	kal_uint32 DummyPixels;
	kal_uint32 DummyLines;
	
	kal_uint32 pvShutter;
	kal_uint32 pvGain;
	
	kal_uint32 pvPclk;  // x10 480 for 48MHZ
	kal_uint32 videoPclk;
	kal_uint32 capPclk; // x10
	
	kal_uint32 shutter;
	kal_uint32 maxExposureLines;

	kal_uint16 sensorGlobalGain;//sensor gain read from 0x350a 0x350b;
	kal_uint16 ispBaseGain;//64
	kal_uint16 realGain;//ispBaseGain as 1x

	kal_int16 imgMirror;

	OV8825SYX_SENSOR_MODE sensorMode;

	kal_bool OV8825SYXAutoFlickerMode;
	kal_bool OV8825SYXVideoMode;
	
}OV8825SYX_PARA_STRUCT,*POV8825SYX_PARA_STRUCT;


	#define OV8825SYX_IMAGE_SENSOR_FULL_WIDTH					(3264-64)	
	#define OV8825SYX_IMAGE_SENSOR_FULL_HEIGHT					(2448-48)

	/* SENSOR PV SIZE */
	#define OV8825SYX_IMAGE_SENSOR_PV_WIDTH					(1632-32)
	#define OV8825SYX_IMAGE_SENSOR_PV_HEIGHT					(1224-24)

#ifdef VIDEO_PREVIEW_SYNC	
	#define OV8825SYX_IMAGE_SENSOR_VIDEO_WIDTH					OV8825SYX_IMAGE_SENSOR_PV_WIDTH
	#define OV8825SYX_IMAGE_SENSOR_VIDEO_HEIGHT				OV8825SYX_IMAGE_SENSOR_PV_HEIGHT
#else
	#define OV8825SYX_IMAGE_SENSOR_VIDEO_WIDTH					(2160-40)
	#define OV8825SYX_IMAGE_SENSOR_VIDEO_HEIGHT				(1620-30)
#endif

	/* SENSOR SCALER FACTOR */
	#define OV8825SYX_PV_SCALER_FACTOR					    	3
	#define OV8825SYX_FULL_SCALER_FACTOR					    1
	                                        	
	/* SENSOR START/EDE POSITION */         	
	#define OV8825SYX_FULL_X_START						    		(2)
	#define OV8825SYX_FULL_Y_START						    		(2)
	#define OV8825SYX_PV_X_START						    		(2)
	#define OV8825SYX_PV_Y_START						    		(2)
	
	#define OV8825SYX_VIDEO_X_START								(2)
	#define OV8825SYX_VIDEO_Y_START								(2)


	#define OV8825SYX_MAX_ANALOG_GAIN					(16)
	#define OV8825SYX_MIN_ANALOG_GAIN					(1)
	#define OV8825SYX_ANALOG_GAIN_1X						(0x0020)

	//#define OV8825SYX_MAX_DIGITAL_GAIN					(8)
	//#define OV8825SYX_MIN_DIGITAL_GAIN					(1)
	//#define OV8825SYX_DIGITAL_GAIN_1X					(0x0100)

	/* SENSOR PIXEL/LINE NUMBERS IN ONE PERIOD */
	#define OV8825SYX_FULL_PERIOD_PIXEL_NUMS					(0x16C0+200) //5824+200 //mt6589 add dummy pixel 200 for line_start/end 
	#if defined(ZSD15FPS)
	#define OV8825SYX_FULL_PERIOD_LINE_NUMS					0x9B0	//2480
	#else
	#define OV8825SYX_FULL_PERIOD_LINE_NUMS					0xB78	//2936
	#endif
	
	#define OV8825SYX_PV_PERIOD_PIXEL_NUMS					0x0DBC  //3516
	#define OV8825SYX_PV_PERIOD_LINE_NUMS					0x51E	//1310

#ifdef VIDEO_PREVIEW_SYNC	
	#define OV8825SYX_VIDEO_PERIOD_PIXEL_NUMS				OV8825SYX_PV_PERIOD_PIXEL_NUMS
	#define OV8825SYX_VIDEO_PERIOD_LINE_NUMS				OV8825SYX_PV_PERIOD_LINE_NUMS
#else
    #define OV8825SYX_VIDEO_PERIOD_PIXEL_NUMS				0x0F30	//3888
    #define OV8825SYX_VIDEO_PERIOD_LINE_NUMS 			0x0740	//1856
#endif

	#define OV8825SYX_MIN_LINE_LENGTH						0x0AA4  //2724
	#define OV8825SYX_MIN_FRAME_LENGTH						0x0214  //532
	
	#define OV8825SYX_MAX_LINE_LENGTH						0xCCCC
	#define OV8825SYX_MAX_FRAME_LENGTH						0xFFFF

	/* DUMMY NEEDS TO BE INSERTED */
	/* SETUP TIME NEED TO BE INSERTED */
	#define OV8825SYX_IMAGE_SENSOR_PV_INSERTED_PIXELS			2
	#define OV8825SYX_IMAGE_SENSOR_PV_INSERTED_LINES			2

	#define OV8825SYX_IMAGE_SENSOR_FULL_INSERTED_PIXELS		4
	#define OV8825SYX_IMAGE_SENSOR_FULL_INSERTED_LINES		4

#define OV8825SYXMIPI_WRITE_ID 	(0x6C)
#define OV8825SYXMIPI_READ_ID	(0x6D)

// SENSOR CHIP VERSION

#define OV8825SYXMIPI_SENSOR_ID            OV8825SYX_SENSOR_ID

#define OV8825SYXMIPI_PAGE_SETTING_REG    (0xFF)

//s_add for porting
//s_add for porting
//s_add for porting

//export functions
UINT32 OV8825SYXMIPIOpen(void);
UINT32 OV8825SYXMIPIGetResolution(MSDK_SENSOR_RESOLUTION_INFO_STRUCT *pSensorResolution);
UINT32 OV8825SYXMIPIGetInfo(MSDK_SCENARIO_ID_ENUM ScenarioId, MSDK_SENSOR_INFO_STRUCT *pSensorInfo, MSDK_SENSOR_CONFIG_STRUCT *pSensorConfigData);
UINT32 OV8825SYXMIPIControl(MSDK_SCENARIO_ID_ENUM ScenarioId, MSDK_SENSOR_EXPOSURE_WINDOW_STRUCT *pImageWindow, MSDK_SENSOR_CONFIG_STRUCT *pSensorConfigData);
UINT32 OV8825SYXMIPIFeatureControl(MSDK_SENSOR_FEATURE_ENUM FeatureId, UINT8 *pFeaturePara,UINT32 *pFeatureParaLen);
UINT32 OV8825SYXMIPIClose(void);

//#define Sleep(ms) mdelay(ms)
//#define RETAILMSG(x,...)
//#define TEXT

//e_add for porting
//e_add for porting
//e_add for porting

#endif /* __SENSOR_H */

