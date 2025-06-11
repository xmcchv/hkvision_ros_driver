#ifndef __LINUX_PLAYM4_H__
#define __LINUX_PLAYM4_H__

#ifdef __cplusplus
	extern "C" 
	{
#endif

typedef unsigned int PLAYM4_HWND;
typedef void * PLAYM4_HWNDEX;
typedef void * PLAYM4_HDC;

#define PLAYM4_API 

#define __stdcall

#ifndef CALLBACK
#define CALLBACK
#endif

//Max channel numbers
#define PLAYM4_MAX_SUPPORTS 500

//Wave coef range;
#define MIN_WAVE_COEF -100
#define MAX_WAVE_COEF 100

//Timer type
#define TIMER_1 1 //Only 16 timers for every process.Default TIMER;
#define TIMER_2 2 //Not limit;But the precision less than TIMER_1; 

//BUFFER AND DATA TYPE
#define BUF_VIDEO_SRC               (1) //mixed input,total src buffer size;splited input,video src buffer size 
#define BUF_AUDIO_SRC               (2) //mixed input,not defined;splited input,audio src buffer size
#define BUF_VIDEO_RENDER            (3) //video render node count or node cout for decoded data
#define BUF_AUDIO_RENDER            (4) //audio render node count 
#define BUF_VIDEO_DECODED           (5) //video decoded node count to render
#define BUF_AUDIO_DECODED           (6) //audio decoded node count to render

//Error code
#define  PLAYM4_NOERROR					0	//no error
#define	 PLAYM4_PARA_OVER				1	//input parameter is invalid;
#define  PLAYM4_ORDER_ERROR				2	//The order of the function to be called is error.
#define	 PLAYM4_TIMER_ERROR				3	//Create multimedia clock failed;
#define  PLAYM4_DEC_VIDEO_ERROR			4	//Decode video data failed.
#define  PLAYM4_DEC_AUDIO_ERROR			5	//Decode audio data failed.
#define	 PLAYM4_ALLOC_MEMORY_ERROR		6	//Allocate memory failed.
#define  PLAYM4_OPEN_FILE_ERROR			7	//Open the file failed.
#define  PLAYM4_CREATE_OBJ_ERROR		8	//Create thread or event failed
//#define  PLAYM4_CREATE_DDRAW_ERROR		9	//Create DirectDraw object failed.
//#define  PLAYM4_CREATE_OFFSCREEN_ERROR 10	//failed when creating off-screen surface.
#define  PLAYM4_BUF_OVER			   11	//buffer is overflow
#define  PLAYM4_CREATE_SOUND_ERROR	   12	//failed when creating audio device.	
#define	 PLAYM4_SET_VOLUME_ERROR	   13	//Set volume failed
#define  PLAYM4_SUPPORT_FILE_ONLY	   14	//The function only support play file.
#define  PLAYM4_SUPPORT_STREAM_ONLY	   15	//The function only support play stream.
#define  PLAYM4_SYS_NOT_SUPPORT		   16	//System not support.
#define  PLAYM4_FILEHEADER_UNKNOWN     17	//No file header.
#define  PLAYM4_VERSION_INCORRECT	   18	//The version of decoder and encoder is not adapted.  
#define  PLAYM4_INIT_DECODER_ERROR     19	//Initialize decoder failed.
#define  PLAYM4_CHECK_FILE_ERROR	   20	//The file data is unknown.
#define  PLAYM4_INIT_TIMER_ERROR	   21	//Initialize multimedia clock failed.
#define	 PLAYM4_BLT_ERROR		       22	//Display failed.
//#define  PLAYM4_UPDATE_ERROR		   23	//Update failed.
#define  PLAYM4_OPEN_FILE_ERROR_MULTI  24   //openfile error, streamtype is multi
#define  PLAYM4_OPEN_FILE_ERROR_VIDEO  25   //openfile error, streamtype is video
#define  PLAYM4_JPEG_COMPRESS_ERROR    26   //JPEG compress error
#define  PLAYM4_EXTRACT_NOT_SUPPORT    27	//Don't support the version of this file.
#define  PLAYM4_EXTRACT_DATA_ERROR     28	//extract video data failed.
#define  PLAYM4_SECRET_KEY_ERROR       29	//Secret key is error //add 20071218
#define  PLAYM4_DECODE_KEYFRAME_ERROR  30   //add by hy 20090318
#define  PLAYM4_NEED_MORE_DATA         31   //add by hy 20100617
#define  PLAYM4_INVALID_PORT		   32	//add by cj 20100913
#define  PLAYM4_NOT_FIND               33	//add by cj 20110428
#define  PLAYM4_NEED_LARGER_BUFFER     34  //add by pzj 20130528
#define  PLAYM4_FAIL_UNKNOWN		   99   //Fail, but the reason is unknown;	

//锟斤拷锟桔癸拷锟杰达拷锟斤拷锟斤拷
#define PLAYM4_FEC_ERR_ENABLEFAIL				100 // 锟斤拷锟斤拷模锟斤拷锟斤拷锟绞э拷锟�
#define PLAYM4_FEC_ERR_NOTENABLE				101 // 锟斤拷锟斤拷模锟斤拷没锟叫硷拷锟斤拷
#define PLAYM4_FEC_ERR_NOSUBPORT				102 // 锟接端匡拷没锟叫凤拷锟斤拷
#define PLAYM4_FEC_ERR_PARAMNOTINIT				103 // 没锟叫筹拷始锟斤拷锟斤拷应锟剿口的诧拷锟斤拷
#define PLAYM4_FEC_ERR_SUBPORTOVER				104 // 锟接端匡拷锟窖撅拷锟斤拷锟斤拷
#define PLAYM4_FEC_ERR_EFFECTNOTSUPPORT			105 // 锟矫帮拷装锟斤拷式锟斤拷锟斤拷锟斤拷效锟斤拷锟斤拷支锟斤拷
#define PLAYM4_FEC_ERR_INVALIDWND				106 // 锟角凤拷锟侥达拷锟斤拷
#define PLAYM4_FEC_ERR_PTZOVERFLOW				107 // PTZ位锟斤拷越锟斤拷
#define PLAYM4_FEC_ERR_RADIUSINVALID			108 // 圆锟侥诧拷锟斤拷锟角凤拷
#define PLAYM4_FEC_ERR_UPDATENOTSUPPORT			109 // 指锟斤拷锟侥帮拷装锟斤拷式锟酵斤拷锟斤拷效锟斤拷锟斤拷锟矫诧拷锟斤拷锟斤拷锟铰诧拷支锟斤拷
#define PLAYM4_FEC_ERR_NOPLAYPORT				110 // 锟斤拷锟脚匡拷丝锟矫伙拷锟斤拷锟斤拷锟�
#define PLAYM4_FEC_ERR_PARAMVALID				111 // 锟斤拷锟斤拷为锟斤拷
#define PLAYM4_FEC_ERR_INVALIDPORT				112 // 锟角凤拷锟接端匡拷
#define PLAYM4_FEC_ERR_PTZZOOMOVER				113 // PTZ锟斤拷锟斤拷锟斤拷围越锟斤拷
#define PLAYM4_FEC_ERR_OVERMAXPORT				114  // 锟斤拷锟斤拷通锟斤拷锟斤拷锟酵ｏ拷锟斤拷锟街э拷值慕锟斤拷锟酵拷锟轿拷母锟�
#define PLAYM4_FEC_ERR_ENABLED                  115  //锟矫端匡拷锟窖撅拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷模锟斤拷
#define PLAYM4_FEC_ERR_D3DACCENOTENABLE			116 // D3D锟斤拷锟斤拷没锟叫匡拷锟斤拷
#define PLAYM4_FEC_ERR_PLACETYPE                117 // 锟斤拷装锟斤拷式锟斤拷锟斤拷.一锟斤拷锟斤拷锟脚匡拷port锟斤拷锟斤拷应一锟街帮拷装锟斤拷式
#define PLAYM4_FEC_ERR_CorrectType              118 // 锟斤拷锟斤拷锟斤拷式锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟绞斤拷锟斤拷锟�,锟斤拷锟杰匡拷锟斤拷锟斤拷锟斤拷锟斤拷锟揭伙拷锟斤拷锟斤拷趴锟絧ort,锟借定锟斤拷锟斤拷PTZ锟斤拷锟斤拷锟桔帮拷锟斤拷锟斤拷锟斤拷锟绞斤拷锟�,锟斤拷锟斤拷锟侥斤拷锟斤拷锟斤拷式锟斤拷只锟杰匡拷一路;锟斤拷锟斤拷180锟饺斤拷锟斤拷锟斤拷锟杰猴拷ptz锟斤拷锟斤拷一锟金开ｏ拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷薰锟斤拷锟斤拷浴锟�
#define PLAYM4_FEC_ERR_NULLWND                  119 // 锟斤拷锟桔达拷锟斤拷为锟斤拷
#define PLAYM4_FEC_ERR_PARA                     120 // 锟斤拷锟桔诧拷锟斤拷锟斤拷锟斤拷

//Max display regions.
#define MAX_DISPLAY_WND 4

//Display type
#define DISPLAY_NORMAL            0x00000001
#define DISPLAY_QUARTER           0x00000002
#define DISPLAY_YC_SCALE          0x00000004	//add by gb 20091116
#define DISPLAY_NOTEARING         0x00000008
//Display buffers
#define MAX_DIS_FRAMES 50
#define MIN_DIS_FRAMES 1

//Locate by
#define BY_FRAMENUM  1
#define BY_FRAMETIME 2

//Source buffer
#define SOURCE_BUF_MAX	1024*100000
#define SOURCE_BUF_MIN	1024*50

//Stream type
#define STREAME_REALTIME 0
#define STREAME_FILE	 1

//frame type
#define T_AUDIO16	101
#define T_AUDIO8	100
#define T_UYVY		1
#define T_YV12		3
#define T_RGB32		7

//capability
#define SUPPORT_DDRAW		1 
#define SUPPORT_BLT         2 
#define SUPPORT_BLTFOURCC   4 
#define SUPPORT_BLTSHRINKX  8 
#define SUPPORT_BLTSHRINKY  16
#define SUPPORT_BLTSTRETCHX 32
#define SUPPORT_BLTSTRETCHY 64
#define SUPPORT_SSE         128
#define SUPPORT_MMX			256 

// 锟斤拷锟铰宏定锟斤拷锟斤拷锟斤拷HIK_MEDIAINFO锟结构
#define FOURCC_HKMI			0x484B4D49	// "HKMI" HIK_MEDIAINFO锟结构锟斤拷锟�
// 系统锟斤拷装锟斤拷式	
#define SYSTEM_NULL			0x0				// 没锟斤拷系统锟姐，锟斤拷锟斤拷频锟斤拷锟斤拷锟斤拷频锟斤拷	
#define SYSTEM_HIK          0x1				// 锟斤拷锟斤拷锟侥硷拷锟斤拷
#define SYSTEM_MPEG2_PS     0x2				// PS锟斤拷装
#define SYSTEM_MPEG2_TS     0x3				// TS锟斤拷装
#define SYSTEM_RTP          0x4				// rtp锟斤拷装
#define SYSTEM_RTPHIK       0x401				// rtp锟斤拷装

// 锟斤拷频锟斤拷锟斤拷锟斤拷锟斤拷
#define VIDEO_NULL          0x0 // 没锟斤拷锟斤拷频
#define VIDEO_H264          0x1 // 锟斤拷准H.264锟酵猴拷锟斤拷H.264锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟�
#define VIDEO_MPEG2			0x2	// 锟斤拷准MPEG2
#define VIDEO_MPEG4         0x3 // 锟斤拷准MPEG4
#define VIDEO_MJPEG			0x4
#define VIDEO_AVC264        0x0100

// 锟斤拷频锟斤拷锟斤拷锟斤拷锟斤拷
#define AUDIO_NULL          0x0000 // 没锟斤拷锟斤拷频
#define AUDIO_ADPCM         0x1000 // ADPCM 
#define AUDIO_MPEG          0x2000 // MPEG 系锟斤拷锟斤拷频锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷应锟斤拷锟斤拷MPEG锟斤拷频
#define AUDIO_AAC           0x2001
// G系锟斤拷锟斤拷频
#define AUDIO_RAW_DATA8		0x7000      //锟斤拷锟斤拷锟斤拷为8k锟斤拷原始锟斤拷锟斤拷
#define AUDIO_RAW_UDATA16	0x7001      //锟斤拷锟斤拷锟斤拷为16k锟斤拷原始锟斤拷锟捷ｏ拷锟斤拷L16
#define AUDIO_G711_U		0x7110
#define AUDIO_G711_A		0x7111
#define AUDIO_G722_1		0x7221
#define AUDIO_G723_1        0x7231
#define AUDIO_G726_U        0x7260
#define AUDIO_G726_A        0x7261
#define AUDIO_G726_16       0x7262
#define AUDIO_G729          0x7290
#define AUDIO_AMR_NB		0x3000

#define SYNCDATA_VEH	    1 //同锟斤拷锟斤拷锟斤拷:锟斤拷锟斤拷锟斤拷息	
#define SYNCDATA_IVS	    2 //同锟斤拷锟斤拷锟斤拷:锟斤拷锟斤拷锟斤拷息

//motion flow type
#define	MOTION_FLOW_NONE			0
#define MOTION_FLOW_CPU				1
#define MOTION_FLOW_GPU				2

//锟斤拷锟斤拷频锟斤拷锟斤拷锟斤拷锟斤拷
#define ENCRYPT_AES_3R_VIDEO     1
#define ENCRYPT_AES_10R_VIDEO    2
#define ENCRYPT_AES_3R_AUDIO     1
#define ENCRYPT_AES_10R_AUDIO    2

typedef struct tagSystemTime
{
    short wYear;
    short wMonth;
    short wDayOfWeek;
    short wDay;
    short wHour;
    short wMinute;
    short wSecond;
    short wMilliseconds;
}SYSTEMTIME;

typedef struct tagHKRect
{
    unsigned long left;
    unsigned long top;
    unsigned long right;
    unsigned long bottom;
}HKRECT;

//Frame position
typedef struct
{
	long long nFilePos;
    int nFrameNum;
    int nFrameTime;
    int nErrorFrameNum;
    SYSTEMTIME *pErrorTime;
    int nErrorLostFrameNum;
    int nErrorFrameSize;
}FRAME_POS,*PFRAME_POS;

//Frame Info
typedef struct
{
    int nWidth;
    int nHeight;
    int nStamp;
    int nType;
    int nFrameRate;
    unsigned int dwFrameNum;
}FRAME_INFO;

//Frame 
typedef struct
{
    char *pDataBuf;
    int  nSize;
    int  nFrameNum;
    int  bIsAudio;
    int  nReserved;
}FRAME_TYPE;

//Watermark Info	//add by gb 080119
typedef struct
{
    char *pDataBuf;
    int  nSize;
    int  nFrameNum;
    int  bRsaRight;
    int  nReserved;
}WATERMARK_INFO;

typedef struct SYNCDATA_INFO 
{
    unsigned int dwDataType;        //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷同锟斤拷锟侥革拷锟斤拷锟斤拷息锟斤拷锟酵ｏ拷目前锟叫ｏ拷锟斤拷锟斤拷锟斤拷息锟斤拷锟斤拷锟斤拷锟斤拷息
    unsigned int dwDataLen;         //锟斤拷锟斤拷锟斤拷息锟斤拷锟捷筹拷锟斤拷
    unsigned char* pData;           //指锟斤拷锟斤拷锟斤拷息锟斤拷锟捷结构锟斤拷指锟斤拷,锟斤拷锟斤拷IVS_INFO锟结构
} SYNCDATA_INFO;

#ifndef _HIK_MEDIAINFO_FLAG_
#define _HIK_MEDIAINFO_FLAG_
typedef struct _HIK_MEDIAINFO_				// modified by gb 080425
{
    unsigned int    media_fourcc;			// "HKMI": 0x484B4D49 Hikvision Media Information
    unsigned short  media_version;			// 锟芥本锟脚ｏ拷指锟斤拷锟斤拷息锟结构锟芥本锟脚ｏ拷目前为0x0101,锟斤拷1.01锟芥本锟斤拷01锟斤拷锟斤拷锟芥本锟脚ｏ拷01锟斤拷锟接版本锟脚★拷
    unsigned short  device_id;				// 锟借备ID锟斤拷锟斤拷锟节革拷锟斤拷/锟斤拷锟斤拷			

    unsigned short  system_format;          // 系统锟斤拷装锟斤拷
    unsigned short  video_format;           // 锟斤拷频锟斤拷锟斤拷锟斤拷锟斤拷

    unsigned short  audio_format;           // 锟斤拷频锟斤拷锟斤拷锟斤拷锟斤拷
    unsigned char   audio_channels;         // 通锟斤拷锟斤拷  
    unsigned char   audio_bits_per_sample;  // 锟斤拷位锟斤拷
    unsigned int    audio_samplesrate;      // 锟斤拷锟斤拷锟斤拷 
    unsigned int    audio_bitrate;          // 压锟斤拷锟斤拷频锟斤拷锟斤拷,锟斤拷位锟斤拷bit
    unsigned char   flag; //8bit,0x81锟斤拷示锟斤拷 smart锟斤拷牵锟斤拷锟斤拷锟轿拷锟絪mart,锟斤拷锟斤拷识锟斤拷intra锟侥凤拷式锟斤拷 media_version >= 0x0103&& video_fortmat = (H.264 or H.265) && ((flag & 0x02) ==0x2) 
    unsigned char   stream_tag; //8bit,0x81锟斤拷示锟斤拷锟斤拷锟叫猴拷锟斤拷SDP锟斤拷息 
    unsigned char   reserved[14]; // 锟斤拷锟斤拷 
}HIK_MEDIAINFO;
#endif

typedef struct  
{
    int nPort;
    char* pBuf;
    int nBufLen;
    int nWidth;
    int nHeight;
    int nStamp;
    int nType;
    void* nUser;
}DISPLAY_INFO;

typedef struct
{
    int nPort;
    char *pVideoBuf;
    int nVideoBufLen;
    char *pPriBuf;
    int nPriBufLen;
    int nWidth;
    int nHeight;
    int nStamp;
    int nType;
    void* nUser;
}DISPLAY_INFOEX;

typedef struct PLAYM4_SYSTEM_TIME //锟斤拷锟斤拷时锟斤拷 
{
    unsigned int dwYear; //锟斤拷
    unsigned int dwMon;  //锟斤拷
    unsigned int dwDay;  //锟斤拷
    unsigned int dwHour; //时
    unsigned int dwMin;  //锟斤拷
    unsigned int dwSec;  //锟斤拷
    unsigned int dwMs;   //锟斤拷锟斤拷
} PLAYM4_SYSTEM_TIME;

#ifndef CROP_PIC_INFO_TAG
#define CROP_PIC_INFO_TAG
typedef struct
{
    unsigned char* pDataBuf;      //抓图锟斤拷锟斤拷buffer
    unsigned int   dwPicSize;	  //实锟斤拷图片锟斤拷小
    unsigned int   dwBufSize;      //锟斤拷锟斤拷buffer锟斤拷小
    unsigned int   dwPicWidth;	  //锟斤拷图锟斤拷
    unsigned int   dwPicHeight;    //锟斤拷图锟斤拷
    unsigned int   dwReserve;      //锟斤拷锟揭伙拷锟絩eserve锟街讹拷
    HKRECT*        pCropRect;     //选锟斤拷锟斤拷锟斤拷NULL, 同锟较碉拷抓图锟接匡拷
}CROP_PIC_INFO;
#endif

//////////////////////////////////////////////////////////////////////////////
//API
//////////////////////////////////////////////////////////////////////////////
int  PlayM4_GetPort(int* nPort);
int  PlayM4_FreePort(int nPort);

int  PlayM4_OpenFile(int nPort,char * sFileName);
int  PlayM4_CloseFile(int nPort);
int  PlayM4_SetStreamOpenMode(int nPort,unsigned int nMode);
int  PlayM4_GetStreamOpenMode(int nPort);
int  PlayM4_OpenStream(int nPort,unsigned char * pFileHeadBuf,unsigned int nSize,unsigned int nBufPoolSize);
int  PlayM4_CloseStream(int nPort);

int  PlayM4_Play(int nPort, PLAYM4_HWND hWnd);
int  PlayM4_PlayEx(int nPort, PLAYM4_HWNDEX hWnd);
int  PlayM4_Stop(int nPort);
int  PlayM4_Pause(int nPort,unsigned int nPause);
int  PlayM4_Fast(int nPort);
int  PlayM4_Slow(int nPort);
int  PlayM4_RefreshPlay(int nPort);
int  PlayM4_InputData(int nPort,unsigned char * pBuf,unsigned int nSize);

int  PlayM4_PlaySound(int nPort);
int  PlayM4_StopSound();
int  PlayM4_PlaySoundShare(int nPort);
int  PlayM4_StopSoundShare(int nPort);
int  PlayM4_SetVolume(int nPort,unsigned short nVolume);
unsigned short  PlayM4_GetVolume(int nPort);

int  PlayM4_OneByOne(int nPort);
int  PlayM4_OneByOneBack(int nPort);

int  PlayM4_SetPlayPos(int nPort,float fRelativePos);
float  PlayM4_GetPlayPos(int nPort);

unsigned int  PlayM4_GetFileTime(int nPort);
unsigned int  PlayM4_GetPlayedTime(int nPort);
unsigned int  PlayM4_GetPlayedFrames(int nPort);
unsigned int  PlayM4_GetFileTotalFrames(int nPort);
unsigned int  PlayM4_GetCurrentFrameRate(int nPort);
unsigned int  PlayM4_GetCurrentFrameNum(int nPort);
unsigned int  PlayM4_GetSpecialData(int nPort);
unsigned int  PlayM4_GetAbsFrameNum(int nPort); 
unsigned int  PlayM4_GetFileHeadLength();
unsigned int  PlayM4_GetSdkVersion();
unsigned int  PlayM4_GetLastError(int nPort);
unsigned int  PlayM4_GetPlayedTimeEx(int nPort);

int  PlayM4_GetSystemTime(int nPort, PLAYM4_SYSTEM_TIME *pstSystemTime);
int  PlayM4_GetFileTimeEx(int nPort, unsigned int* pStart, unsigned int* pStop, unsigned int* pRev);
int  PlayM4_GetCurrentFrameRateEx(int nPort, float* pfFrameRate);
int  PlayM4_GetPictureSize(int nPort,int *pWidth,int *pHeight);
int  PlayM4_GetKeyFramePos(int nPort,unsigned int nValue, unsigned int nType, PFRAME_POS pFramePos);
int  PlayM4_GetNextKeyFramePos(int nPort,unsigned int nValue, unsigned int nType, PFRAME_POS pFramePos);

int  PlayM4_ConvertToBmpFile(char * pBuf,int nSize,int nWidth,int nHeight,int nType,char *sFileName);
int  PlayM4_ConvertToJpegFile(char * pBuf,int nSize,int nWidth,int nHeight,int nType,char *sFileName);
int  PlayM4_SetJpegQuality(int nQuality);
int  PlayM4_GetBMP(int nPort,unsigned char * pBitmap,unsigned int nBufSize,unsigned int* pBmpSize);
int  PlayM4_GetJPEG(int nPort,unsigned char * pJpeg,unsigned int nBufSize,unsigned int* pJpegSize);

int  PlayM4_SetPlayedTimeEx(int nPort,unsigned int nTime);
int  PlayM4_SetCurrentFrameNum(int nPort,unsigned int nFrameNum);
int  PlayM4_SetDisplayRegion(int nPort,unsigned int nRegionNum, HKRECT *pSrcRect, PLAYM4_HWND hDestWnd, int bEnable);
int  PlayM4_SetDisplayRegionOnWnd(int nPort,unsigned int nRegionNum, HKRECT *pSrcRect, int bEnable);///<锟洁窗锟节分革拷涌锟�
int  PlayM4_SetDecodeFrameType(int nPort,unsigned int nFrameType);
int  PlayM4_SetSecretKey(int nPort, int lKeyType, char *pSecretKey, int lKeyLen);

int  PlayM4_SetDecCBStream(int nPort,unsigned int nStream);
int  PlayM4_SetDecCallBackMend(int nPort,void (CALLBACK* DecCBFun)(int nPort,char * pBuf,int nSize,FRAME_INFO * pFrameInfo, void* nUser,int nReserved2), void* nUser);
int  PlayM4_SetDecCallBackExMend(int nPort, void (CALLBACK* DecCBFun)(int nPort, char* pBuf, int nSize, FRAME_INFO* pFrameInfo, void* nUser, int nReserved2), char* pDest, int nDestSize, void* nUser);

int  PlayM4_SetDisplayCallBack(int nPort,void (CALLBACK* DisplayCBFun)(int nPort,char * pBuf,int nSize,int nWidth,int nHeight,int nStamp,int nType,int nReserved));
int  PlayM4_SetDisplayCallBackEx(int nPort,void (CALLBACK* DisplayCBFun)(DISPLAY_INFO *pstDisplayInfo), void* nUser);
int  PlayM4_SetFileRefCallBack(int nPort, void (CALLBACK *pFileRefDone)(unsigned int nPort,void* nUser),void* nUser);
int  PlayM4_SetEncTypeChangeCallBack(int nPort, void(CALLBACK *funEncChange)(int nPort, void* nUser), void* nUser);
int  PlayM4_SetCheckWatermarkCallBack(int nPort, void(CALLBACK* funCheckWatermark)(int nPort, WATERMARK_INFO* pWatermarkInfo, void* nUser), void* nUser);
int  PlayM4_SetFileEndCallback(int nPort, void(CALLBACK*FileEndCallback)(int nPort, void *pUser), void *pUser);

int  PlayM4_ResetSourceBuffer(int nPort);
int  PlayM4_SetDisplayBuf(int nPort, unsigned int nNum);
int  PlayM4_ResetBuffer(int nPort,unsigned int nBufType);
unsigned int  PlayM4_GetSourceBufferRemain(int nPort);
unsigned int  PlayM4_GetDisplayBuf(int nPort);
unsigned int  PlayM4_GetBufferValue(int nPort,unsigned int nBufType);

int  PlayM4_GetRefValue(int nPort,unsigned char  *pBuffer, unsigned int *pSize);
int  PlayM4_SetRefValue(int nPort,unsigned char  *pBuffer, unsigned int nSize);
int  PlayM4_GetRefValueEx(int nPort,unsigned char *pBuffer, unsigned int *pSize);///< 锟斤拷锟斤拷帧锟斤拷锟酵回碉拷

int  PlayM4_RegisterDrawFun(int nPort,void (CALLBACK* DrawFun)(int nPort,PLAYM4_HDC hDc,void* nUser),void* nUser);

int  PlayM4_ThrowBFrameNum(int nPort,unsigned int nNum);
int  PlayM4_SkipErrorData(int nPort, int bSkip);

int  PlayM4_ReversePlay(int nPort);

//锟斤拷锟斤拷锟斤拷锟绞撅拷氐锟斤拷芯锟斤拷锟绞憋拷锟斤拷锟斤拷帧锟脚ｏ拷锟斤拷锟斤拷锟绞憋拷锟斤拷锟斤拷帧锟脚ｏ拷锟侥回碉拷锟斤拷锟斤拷;
// nModule 锟斤拷示锟截碉拷模锟斤拷选锟斤拷0 锟斤拷示默锟较斤拷锟斤拷氐锟斤拷锟斤拷锟绞撅拷氐锟� 1锟斤拷锟斤拷示锟斤拷锟斤拷氐锟斤拷锟�2锟斤拷锟斤拷示锟斤拷示锟截碉拷锟斤拷
// nType 锟斤拷示锟截碉拷锟斤拷锟斤拷时锟斤拷锟斤拷锟街★拷牛锟斤拷锟斤拷锟斤拷锟斤拷时锟斤拷锟斤拷锟街★拷牛锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷茫锟�0锟斤拷锟斤拷示锟截碉拷锟斤拷锟绞憋拷锟斤拷锟斤拷锟斤拷锟街★拷锟� 1: 锟斤拷示锟截碉拷锟斤拷锟斤拷时锟斤拷锟斤拷途锟斤拷锟街★拷锟�
//锟斤拷示锟截碉拷锟斤拷没锟斤拷帧锟脚回碉拷锟侥ｏ拷锟斤拷锟斤拷锟斤拷示锟截碉拷锟斤拷 0锟斤拷锟斤拷示锟截碉拷锟斤拷锟绞憋拷锟斤拷 1: 锟斤拷示锟截碉拷锟斤拷锟斤拷时锟斤拷锟�
int  PlayM4_SetDecOrDisplayCallbackType(int nPort, int nModule, int nType);


#ifndef PLAYM4_SESSION_INFO_TAG
#define PLAYM4_SESSION_INFO_TAG
//nProtocolType
#define PLAYM4_PROTOCOL_RTSP    1
//nSessionInfoType
#define PLAYM4_SESSION_INFO_SDP 1

typedef struct _PLAYM4_SESSION_INFO_     //锟斤拷锟斤拷锟斤拷息锟结构
{
    int            nSessionInfoType;   //锟斤拷锟斤拷锟斤拷息锟斤拷锟酵ｏ拷锟斤拷锟斤拷SDP锟斤拷锟斤拷锟界海锟斤拷私锟斤拷锟斤拷息头
    int            nSessionInfoLen;    //锟斤拷锟斤拷锟斤拷息锟斤拷锟斤拷
    unsigned char* pSessionInfoData;   //锟斤拷锟斤拷锟斤拷息锟斤拷锟斤拷

} PLAYM4_SESSION_INFO;
#endif

PLAYM4_API int __stdcall PlayM4_OpenStreamAdvanced(int nPort, int nProtocolType, PLAYM4_SESSION_INFO* pstSessionInfo, unsigned int nBufPoolSize);

#define R_ANGLE_0   -1  //锟斤拷锟斤拷转
#define R_ANGLE_L90  0  //锟斤拷锟斤拷锟斤拷转90锟斤拷
#define R_ANGLE_R90  1  //锟斤拷锟斤拷锟斤拷转90锟斤拷
#define R_ANGLE_180  2  //锟斤拷转180锟斤拷

PLAYM4_API int __stdcall PlayM4_SetRotateAngle(int nPort, unsigned int nRegionNum, unsigned int dwType);

#ifndef PLAYM4_ADDITION_INFO_TAG
#define PLAYM4_ADDITION_INFO_TAG
typedef struct _PLAYM4_ADDITION_INFO_     //锟斤拷锟斤拷锟斤拷息锟结构
{
    unsigned char*  pData;			//锟斤拷锟斤拷锟斤拷锟斤拷
    unsigned int    dwDatalen;		//锟斤拷锟斤拷锟斤拷锟捷筹拷锟斤拷
    unsigned int	dwDataType;		//锟斤拷锟斤拷锟斤拷锟斤拷
    unsigned int	dwTimeStamp;	//锟斤拷锟绞憋拷锟斤拷
} PLAYM4_ADDITION_INFO;
#endif

//dwGroupIndex 锟斤拷约锟斤拷取值0~3锟斤拷锟斤拷一锟芥本取锟斤拷同锟斤拷只锟斤拷同锟斤拷closestream锟斤拷锟斤拷
PLAYM4_API int __stdcall PlayM4_SetSycGroup(int nPort, unsigned int dwGroupIndex);
//锟捷诧拷实锟街此猴拷锟斤拷锟斤拷同锟斤拷锟斤拷锟斤拷锟矫碉拷锟斤拷始时锟戒不一锟铰ｏ拷锟斤拷锟斤拷小锟斤拷时锟斤拷锟斤拷为锟斤拷锟斤拷锟斤拷悖伙拷锟斤拷只锟斤拷一路
PLAYM4_API int __stdcall PlayM4_SetSycStartTime(int nPort, PLAYM4_SYSTEM_TIME *pstSystemTime);

// 锟斤拷锟斤拷实锟斤拷锟斤拷锟斤拷锟斤拷氐慕涌锟�
#ifndef FISH_EYE_TAG
#define FISH_EYE_TAG

// 锟斤拷锟斤拷锟斤拷锟斤拷
typedef enum tagFECPlaceType
{
    FEC_PLACE_WALL = 0x1,			// 锟斤拷装锟斤拷式		(锟斤拷锟斤拷水平)
    FEC_PLACE_FLOOR = 0x2,			// 锟斤拷锟芥安装		(锟斤拷锟斤拷锟斤拷锟斤拷)
    FEC_PLACE_CEILING = 0x3,		// 锟斤拷装锟斤拷式		(锟斤拷锟斤拷锟斤拷锟斤拷)

}FECPLACETYPE;

typedef enum tagFECCorrectType
{
	FEC_CORRECT_NULL       = 0x0,       // 锟斤拷锟斤拷锟斤拷(原图)
	FEC_CORRECT_PTZ        = 0x100,		// PTZ
	FEC_CORRECT_180        = 0x200,		// 180锟饺斤拷锟斤拷  锟斤拷锟斤拷应2P锟斤拷
	FEC_CORRECT_360        = 0x300,		// 360全锟斤拷锟斤拷锟斤拷 锟斤拷锟斤拷应1P锟斤拷
    FEC_CORRECT_LAT        = 0x400,     // 纬锟斤拷展锟斤拷
	FEC_CORRECT_SEMISPHERE = 0x500,     // 3D锟斤拷锟斤拷锟斤拷锟�
    FEC_CORRECT_CYLINDER                = 0x0600, // 锟斤拷锟斤拷圆锟斤拷锟斤拷示 - 锟斤拷装/锟斤拷装
    FEC_CORRECT_CYLINDER_SPLIT          = 0x0700, // 锟斤拷锟斤拷锟叫匡拷锟斤拷圆锟斤拷锟斤拷示 - 锟斤拷装/锟斤拷装
    FEC_CORRECT_PLANET                  = 0x0800, // 锟斤拷锟斤拷小锟斤拷锟斤拷
    FEC_CORRECT_ARCSPHERE_HORIZONTAL    = 0x0900, // 锟斤拷锟斤拷水平锟斤拷锟斤拷 - 锟斤拷装
    FEC_CORRECT_ARCSPHERE_VERTICAL      = 0x0A00, // 锟斤拷锟桔达拷直锟斤拷锟斤拷 - 锟斤拷装

}FECCORRECTTYPE;

typedef enum tagFECCorrectEffect
{
    FEC_CORRECT_EFFECT_BACK_FACE_CULLING    = 0x100,        // 锟斤拷锟斤拷锟睫筹拷锟斤拷锟斤拷0锟斤拷示锟斤拷锟矫ｏ拷为0锟斤拷示锟斤拷锟斤拷锟矫ｏ拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷强转锟斤拷锟斤拷锟斤拷

}FECCORRECTEFFECT;


typedef struct tagCycleParam
{
    float	fRadiusLeft;	// 圆锟斤拷锟斤拷锟斤拷锟絏锟斤拷锟斤拷
    float	fRadiusRight;	// 圆锟斤拷锟斤拷锟揭憋拷X锟斤拷锟斤拷
    float   fRadiusTop;		// 圆锟斤拷锟斤拷锟较憋拷Y锟斤拷锟斤拷
    float   fRadiusBottom;	// 圆锟斤拷锟斤拷锟铰憋拷Y锟斤拷锟斤拷

}CYCLEPARAM;

typedef struct tagPTZParam
{
    float fPTZPositionX;		// PTZ 锟斤拷示锟斤拷锟斤拷锟斤拷位锟斤拷 X锟斤拷锟斤拷
    float fPTZPositionY;		// PTZ 锟斤拷示锟斤拷锟斤拷锟斤拷位锟斤拷 Y锟斤拷锟斤拷	

}PTZPARAM;

// PTZ锟斤拷原始锟斤拷锟斤拷图锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷示模式
typedef enum tagFECShowMode
{
    FEC_PTZ_OUTLINE_NULL,   // 锟斤拷锟斤拷示
    FEC_PTZ_OUTLINE_RECT,   // 锟斤拷锟斤拷锟斤拷示
    FEC_PTZ_OUTLINE_RANGE,  // 锟斤拷实锟斤拷锟斤拷锟斤拷示
}FECSHOWMODE; 

// 锟斤拷锟铰憋拷潜锟斤拷锟斤拷锟斤拷锟�

#define 		FEC_UPDATE_RADIUS			 0x1
#define 		FEC_UPDATE_PTZZOOM			 0x2
#define 		FEC_UPDATE_WIDESCANOFFSET	 0x4
#define 		FEC_UPDATE_PTZPARAM			 0x8
#define         FEC_UPDATT_PTZCOLOR          0x10

// 色锟绞结构锟斤拷
typedef struct tagFECColor
{
    unsigned char nR;     // R锟斤拷锟斤拷
    unsigned char nG;	  // G锟斤拷锟斤拷
    unsigned char nB;     // B锟斤拷锟斤拷
    unsigned char nAlpha; // Alpha锟斤拷锟斤拷
}FECCOLOR;

typedef struct tagFECParam
{
	unsigned int 	nUpDateType;			// 锟斤拷锟铰碉拷锟斤拷锟斤拷
	unsigned int	nPlaceAndCorrect;		// 锟斤拷装锟斤拷式锟酵斤拷锟斤拷锟斤拷式锟斤拷只锟斤拷锟斤拷锟节伙拷取锟斤拷SetParam锟斤拷时锟斤拷锟斤拷效,锟斤拷值锟斤拷示锟斤拷装锟斤拷式锟酵斤拷锟斤拷锟斤拷式锟侥猴拷
	PTZPARAM		stPTZParam;				// PTZ 校锟斤拷锟侥诧拷锟斤拷
	CYCLEPARAM		stCycleParam;			// 锟斤拷锟斤拷图锟斤拷圆锟侥诧拷锟斤拷
	float			fZoom;					// PTZ 锟斤拷示锟侥凤拷围锟斤拷锟斤拷
	float			fWideScanOffset;		// 180锟斤拷锟斤拷360锟斤拷校锟斤拷锟斤拷偏锟狡角讹拷
    FECCOLOR        stPTZColor;             // PTZ锟斤拷色
	int				nResver[15];			// 锟斤拷锟斤拷锟街讹拷

}FISHEYEPARAM;

#define         FEC_JPEG   0  // JPEG抓图
#define         FEC_BMP    1  // BMP 抓图

///<锟铰碉拷3d锟斤拷锟桔帮拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟接角变化锟斤拷锟斤拷(锟斤拷锟脚猴拷锟斤拷转)
typedef enum tagPLAYM4HRViewParamType
{
    PLAYM4_HR_VPT_ROTATION_X       = 0x1,          ///<水平锟斤拷转
    PLAYM4_HR_VPT_ROTATION_Y       = 0x2,          ///<锟斤拷直锟斤拷转
    PLAYM4_HR_VPT_SCALE            = 0x3,          ///<锟斤拷锟斤拷(锟斤拷锟斤拷锟街滴拷锟斤拷锟斤拷锟�0值时为锟斤拷锟斤拷-锟斤拷锟斤拷效锟斤拷)
}PLAYM4HRVIEWPARAMTYPE;	

// 锟斤拷锟斤拷3D模锟酵诧拷锟斤拷
typedef enum tagPLAYM4FEC3DModelParam
{
    PLAYM4_FEC_3DMP_CYLINDER_HEIGHT              = 0x1,       ///< 圆锟斤拷模锟酵革拷
    PLAYM4_FEC_3DMP_CYLINDER_RADIUS              = 0x2,       ///< 圆锟斤拷模锟酵半径
}PLAYM4FEC3DMODELPARAM;

// 锟截讹拷锟接斤拷状态
typedef enum tagPLAYM4FECSpecialViewType
{
    PLAYM4_FEC_SVT_EDGE                          = 0x1        ///<锟斤拷锟斤拷锟斤拷锟斤拷模锟斤拷锟诫窗锟斤拷锟斤拷锟斤拷锟接斤拷
}PLAYM4FECSPECIALVIEWTYPE;


#endif

typedef void (__stdcall * FISHEYE_CallBack )(  void* pUser  , unsigned int  nPort , unsigned int nCBType , void * hDC ,   unsigned int nWidth , unsigned int nHeight); 

// 锟斤拷锟斤拷锟斤拷锟斤拷
PLAYM4_API int __stdcall PlayM4_FEC_Enable(int nPort);

// 锟截憋拷锟斤拷锟斤拷模锟斤拷
PLAYM4_API int __stdcall PlayM4_FEC_Disable(int nPort);

// 锟斤拷取锟斤拷锟桔斤拷锟斤拷锟斤拷锟斤拷锟接端匡拷 [1~31] 
PLAYM4_API int  __stdcall PlayM4_FEC_GetPort(int nPort , unsigned int* nSubPort , FECPLACETYPE emPlaceType , FECCORRECTTYPE emCorrectType);

// 删锟斤拷锟斤拷锟桔斤拷锟斤拷锟斤拷锟斤拷锟接端匡拷
PLAYM4_API int __stdcall PlayM4_FEC_DelPort(int nPort , unsigned int nSubPort);

// 锟斤拷锟斤拷锟斤拷锟桔斤拷锟斤拷锟斤拷锟斤拷
PLAYM4_API int __stdcall PlayM4_FEC_SetParam(int nPort , unsigned int nSubPort , FISHEYEPARAM * pPara);

// 锟斤拷取锟斤拷锟桔斤拷锟斤拷锟斤拷锟斤拷
PLAYM4_API int __stdcall PlayM4_FEC_GetParam(int nPort , unsigned int nSubPort , FISHEYEPARAM * pPara);

// 锟斤拷锟斤拷锟斤拷示锟斤拷锟节ｏ拷锟斤拷锟斤拷锟斤拷时锟叫伙拷
PLAYM4_API int __stdcall PlayM4_FEC_SetWnd(int nPort , unsigned int nSubPort , void * hWnd);

// 锟斤拷锟斤拷锟斤拷锟桔达拷锟节的伙拷图锟截碉拷
PLAYM4_API int __stdcall PlayM4_FEC_SetCallBack(int nPort , unsigned int nSubPort , FISHEYE_CallBack cbFunc , void * pUser);

PLAYM4_API int __stdcall PlayM4_FEC_Capture(int nPort, unsigned int nSubPort , unsigned int nType, char *pFileName);

PLAYM4_API int __stdcall PlayM4_FEC_GetCurrentPTZPort(int nPort, float fPositionX,float fPositionY, unsigned int *pnPort);

PLAYM4_API int __stdcall PlayM4_FEC_SetCurrentPTZPort(int nPort, unsigned int nSubPort);

PLAYM4_API int __stdcall PlayM4_FEC_SetPTZOutLineShowMode(int nPort,FECSHOWMODE nPTZShowMode);
														 									 
//锟铰碉拷锟斤拷锟桔帮拷锟斤拷锟斤拷锟斤拷咏潜浠�(锟斤拷转)锟斤拷锟斤拷锟斤拷亟涌锟�
//锟斤拷取锟斤拷锟斤拷锟斤拷锟斤拷咏遣锟斤拷锟�(锟斤拷锟斤拷前锟饺伙拷取锟斤拷前锟斤拷值)
PLAYM4_API int __stdcall PlayM4_FEC_GetViewParam(int nPort, unsigned int nSubPort, PLAYM4HRVIEWPARAMTYPE enViewParamType, float* fValue);
//锟斤拷锟矫帮拷锟斤拷锟斤拷锟斤拷咏潜浠拷锟斤拷锟�(锟斤拷锟矫碉拷值为锟斤拷取值锟斤拷锟斤拷要偏锟斤拷值)
PLAYM4_API int __stdcall PlayM4_FEC_SetViewParam(int nPort, unsigned int nSubPort, PLAYM4HRVIEWPARAMTYPE enViewParamType, float fValue);

//锟斤拷锟桔碉拷锟接放达拷 nType = 0锟斤拷
//锟斤拷锟桔达拷锟节分革拷 nType = 1锟斤拷
//注锟解，锟斤拷锟节分革拷时hDestWnd锟斤拷效锟斤拷锟斤拷锟斤拷锟斤拷为NULL锟斤拷20180813锟捷诧拷支锟街ｏ拷
//目前锟斤拷锟接放达拷支锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟较放达拷nRegionNum锟斤拷为0锟斤拷hDestWnd锟斤拷为NULL锟斤拷bEnable锟斤拷为0取锟斤拷锟斤拷锟接放大，凤拷0为锟斤拷锟接放达拷
//pSrcRect锟斤拷锟斤拷锟揭伙拷锟斤拷锟斤拷锟斤拷锟�1000锟斤拷锟皆匡拷锟斤拷锟竭高ｏ拷锟斤拷值锟斤拷0-1000之锟戒）
//只锟狡硷拷原图锟斤拷180锟斤拷360锟斤拷纬锟斤拷展锟斤拷锟斤拷锟斤拷锟斤拷PTZ锟斤拷示锟斤拷锟斤拷锟接放达拷锟劫匡拷ptz锟结导锟铰碉拷锟接放达拷失效-3D锟斤拷锟桔诧拷锟斤拷锟斤拷使锟矫此接匡拷(锟斤拷锟接角变化锟接口斤拷锟斤拷锟斤拷锟脚ｏ拷
PLAYM4_API bool __stdcall PlayM4_FEC_SetDisplayRegion(int nPort, unsigned int nSubPort,unsigned int nType, unsigned int nRegionNum, HKRECT *pSrcRect, PLAYM4_HWND hDestWnd, int bEnable);
//锟斤拷锟斤拷锟睫筹拷锟斤拷锟斤拷0锟斤拷示锟斤拷锟矫ｏ拷为0锟斤拷示锟斤拷锟斤拷锟矫ｏ拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷强转锟斤拷锟斤拷锟斤拷
PLAYM4_API bool __stdcall PlayM4_FEC_SetCorrectEffect(int nPort, unsigned int nSubPort, FECCORRECTEFFECT nCorrectEffect, float fValue);

// 锟斤拷锟斤拷3D模锟酵诧拷锟斤拷-锟斤拷锟�3D圆锟斤拷展锟斤拷锟斤拷效
PLAYM4_API bool __stdcall PlayM4_FEC_Set3DModelParam(int nPort, unsigned int nSubPort, PLAYM4FEC3DMODELPARAM enType, float fValue);

// 锟斤拷取锟截讹拷锟接角诧拷锟斤拷 - 只锟斤拷锟斤拷锟节伙拷锟芥，锟斤拷SetViewParam锟接匡拷锟斤拷锟绞癸拷锟�
PLAYM4_API bool __stdcall PlayM4_FEC_GetSpecialViewParam(int nPort, unsigned int nSubPort, PLAYM4FECSPECIALVIEWTYPE enSVType, PLAYM4HRVIEWPARAMTYPE enVPType, float* pValue);


//图锟斤拷锟斤拷强锟斤拷锟�-Linux锟芥本锟斤拷支锟斤拷
#ifndef PLAYM4_HIKVIE_TAG
#define PLAYM4_HIKVIE_TAG

typedef struct _PLAYM4_VIE_DYNPARAM_
{
    int moduFlag;      //锟斤拷锟矫碉拷锟姐法锟斤拷锟斤拷模锟介，锟斤拷PLAYM4_VIE_MODULES锟叫讹拷锟斤拷
    //锟斤拷 PLAYM4_VIE_MODU_ADJ | PLAYM4_VIE_MODU_EHAN
    //模锟斤拷锟斤拷锟矫后，憋拷锟斤拷锟斤拷锟斤拷锟斤拷应锟侥诧拷锟斤拷锟斤拷
    //PLAYM4_VIE_MODU_ADJ
    int brightVal;     //锟斤拷锟饺碉拷锟斤拷值锟斤拷[-255, 255]
    int contrastVal;   //锟皆比度碉拷锟斤拷值锟斤拷[-256, 255]
    int colorVal;      //锟斤拷锟酵度碉拷锟斤拷值锟斤拷[-256, 255]
    //PLAYM4_VIE_MODU_EHAN
    int toneScale;     //锟剿诧拷锟斤拷围锟斤拷[0, 100]
    int toneGain;      //锟皆比度碉拷锟节ｏ拷全锟街对比讹拷锟斤拷锟斤拷值锟斤拷[-256, 255]
    int toneOffset;    //锟斤拷锟饺碉拷锟节ｏ拷锟斤拷锟斤拷平锟斤拷值偏锟狡ｏ拷[-255, 255]
    int toneColor;     //锟斤拷色锟斤拷锟节ｏ拷锟斤拷色锟斤拷锟斤拷值锟斤拷[-256, 255]
    //PLAYM4_VIE_MODU_DEHAZE
    int dehazeLevel;   //去锟斤拷强锟饺ｏ拷[0, 255]
    int dehazeTrans;   //透锟斤拷值锟斤拷[0, 255]
    int dehazeBright;  //锟斤拷锟饺诧拷锟斤拷锟斤拷[0, 255]
    //PLAYM4_VIE_MODU_DENOISE
    int denoiseLevel;  //去锟斤拷强锟饺ｏ拷[0, 255]
    //PLAYM4_VIE_MODU_SHARPEN
    int usmAmount;     //锟斤拷强锟饺ｏ拷[0, 255]
    int usmRadius;     //锟今化半径锟斤拷[1, 15]
    int usmThreshold;  //锟斤拷锟斤拷值锟斤拷[0, 255]
    //PLAYM4_VIE_MODU_DEBLOCK
    int deblockLevel;  //去锟斤拷强锟饺ｏ拷[0, 100]
    //PLAYM4_VIE_MODU_LENS
    int lensWarp;      //锟斤拷锟斤拷锟斤拷锟斤拷[-256, 255]
    int lensZoom;      //锟斤拷锟斤拷锟斤拷锟斤拷[-256, 255]
    //PLAYM4_VIE_MODU_CRB
    //锟斤拷锟斤拷应锟斤拷锟斤拷
} PLAYM4_VIE_PARACONFIG;

typedef enum _PLAYM4_VIE_MODULES
{
    PLAYM4_VIE_MODU_ADJ      = 0x00000001, //图锟斤拷锟斤拷锟斤拷锟斤拷锟�
    PLAYM4_VIE_MODU_EHAN     = 0x00000002, //锟街诧拷锟斤拷强模锟斤拷
    PLAYM4_VIE_MODU_DEHAZE   = 0x00000004, //去锟斤拷模锟斤拷
    PLAYM4_VIE_MODU_DENOISE  = 0x00000008, //去锟斤拷模锟斤拷
    PLAYM4_VIE_MODU_SHARPEN  = 0x00000010, //锟斤拷模锟斤拷
    PLAYM4_VIE_MODU_DEBLOCK  = 0x00000020, //去锟斤拷锟剿诧拷模锟斤拷
    PLAYM4_VIE_MODU_CRB      = 0x00000040, //色锟斤拷平锟斤拷模锟斤拷
    PLAYM4_VIE_MODU_LENS     = 0x00000080, //锟斤拷头锟斤拷锟斤拷锟斤拷锟侥ｏ拷锟�
}PLAYM4_VIE_MODULES;
#endif

//锟斤拷锟矫关憋拷/锟斤拷锟斤拷模锟斤拷 -- NO SUPPORT
//dwModuFlag锟斤拷应PLAYM4_VIE_MODULES锟斤拷,锟斤拷锟斤拷锟�
//锟斤拷锟斤拷锟斤拷模锟介开锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷模锟斤拷锟斤拷锟斤拷锟斤拷诩锟斤拷锟斤拷默锟较的诧拷锟斤拷;
//锟截憋拷模锟斤拷锟斤拷洗锟斤拷锟斤拷玫牟锟斤拷锟斤拷锟斤拷
//锟斤拷锟斤拷锟接口碉拷锟矫ｏ拷锟斤拷锟斤拷锟节该接口匡拷锟斤拷模锟斤拷螅环锟斤拷颍锟斤拷卮锟斤拷锟�
PLAYM4_API int __stdcall PlayM4_VIE_SetModuConfig(int nPort, int nModuFlag, int bEnable);

//锟斤拷锟斤拷图锟斤拷锟斤拷强锟斤拷锟斤拷NULL全图锟斤拷锟斤拷锟斤拷全图锟斤拷锟斤拷锟斤拷全图锟斤拷锟斤拷小锟斤拷锟斤拷16*16锟斤拷锟斤拷 -- NO SUPPORT
//锟斤拷支锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟饺斤拷说4锟斤拷锟斤拷锟斤拷一锟斤拷锟芥本锟斤拷锟斤拷只支锟斤拷一锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟揭拷锟斤拷锟斤拷氐锟斤拷锟斤拷锟斤拷氐锟斤拷捅锟斤拷锟�
PLAYM4_API int __stdcall PlayM4_VIE_SetRegion(int nPort, int nRegNum, HKRECT* pRect);

//锟斤拷取锟斤拷锟斤拷模锟斤拷 -- NO SUPPORT
PLAYM4_API int __stdcall PlayM4_VIE_GetModuConfig(int nPort, int* pdwModuFlag);

//锟斤拷锟矫诧拷锟斤拷
//未锟斤拷锟斤拷模锟斤拷牟锟斤拷锟斤拷锟斤拷帽锟斤拷锟斤拷锟� -- NO SUPPORT
PLAYM4_API int __stdcall PlayM4_VIE_SetParaConfig(int nPort, PLAYM4_VIE_PARACONFIG* pParaConfig);

//锟斤拷取锟斤拷锟斤拷模锟斤拷牟锟斤拷锟� -- NO SUPPORT
PLAYM4_API int __stdcall PlayM4_VIE_GetParaConfig(int nPort, PLAYM4_VIE_PARACONFIG* pParaConfig);

// 私锟斤拷锟斤拷息模锟斤拷锟斤拷锟斤拷
typedef enum _PLAYM4_PRIDATA_RENDER
{	
    PLAYM4_RENDER_ANA_INTEL_DATA   = 0x00000001, //锟斤拷锟杰凤拷锟斤拷
    PLAYM4_RENDER_MD               = 0x00000002, //锟狡讹拷锟斤拷锟�
    PLAYM4_RENDER_ADD_POS          = 0x00000004, //POS锟斤拷息锟斤拷锟斤拷锟�
    PLAYM4_RENDER_ADD_PIC          = 0x00000008, //图片锟斤拷锟斤拷锟斤拷息
    PLAYM4_RENDER_FIRE_DETCET      = 0x00000010, //锟饺筹拷锟斤拷锟斤拷息
    PLAYM4_RENDER_TEM              = 0x00000020, //锟铰讹拷锟斤拷息
}PLAYM4_PRIDATA_RENDER;

typedef enum _PLAYM4_FIRE_ALARM
{
    PLAYM4_FIRE_FRAME_DIS             = 0x00000001, //锟斤拷锟斤拷锟斤拷示
    PLAYM4_FIRE_MAX_TEMP              = 0x00000002, //锟斤拷锟斤拷露锟�
    PLAYM4_FIRE_MAX_TEMP_POSITION     = 0x00000004, //锟斤拷锟斤拷露锟轿伙拷锟斤拷锟绞�
    PLAYM4_FIRE_DISTANCE              = 0x00000008, //锟斤拷锟斤拷露染锟斤拷锟�
}PLAYM4_FIRE_ALARM;

typedef enum _PLAYM4_TEM_FLAG
{
    PLAYM4_TEM_REGION_BOX             = 0x00000001, //锟斤拷锟斤拷锟�
    PLAYM4_TEM_REGION_LINE            = 0x00000002, //锟竭诧拷锟斤拷
    PLAYM4_TEM_REGION_POINT           = 0x00000004, //锟斤拷锟斤拷锟�
}PLAYM4_TEM_FLAG;

// 锟斤拷锟斤拷锟斤拷息锟斤拷锟斤拷
PLAYM4_API int __stdcall PlayM4_RenderPrivateData(int nPort, int nIntelType, int bTrue);
///<锟斤拷锟斤拷锟斤拷息锟接匡拷锟斤拷
PLAYM4_API int __stdcall PlayM4_RenderPrivateDataEx(int nPort, int nIntelType, int nSubType, int bTrue);

//ENCRYPT Info
typedef struct{
    long nVideoEncryptType;  //锟斤拷频锟斤拷锟斤拷锟斤拷锟斤拷
    long nAudioEncryptType;  //锟斤拷频锟斤拷锟斤拷锟斤拷锟斤拷
    long nSetSecretKey;      //锟角凤拷锟斤拷锟矫ｏ拷1锟斤拷示锟斤拷锟斤拷锟斤拷钥锟斤拷0锟斤拷示没锟斤拷锟斤拷锟斤拷锟斤拷钥
}ENCRYPT_INFO;

// 锟斤拷锟斤拷锟斤拷锟斤拷锟截碉拷,nType=0锟斤拷示锟斤拷锟斤拷锟斤拷锟杰憋拷锟轿伙拷锟斤拷锟斤拷浠拷突氐锟斤拷锟絥Type=1锟斤拷示锟斤拷锟斤拷锟叫硷拷锟斤拷位锟斤拷锟斤拷锟截碉拷
PLAYM4_API int __stdcall PlayM4_SetEncryptTypeCallBack(int nPort, unsigned int nType, void (CALLBACK* EncryptTypeCBFun)(int nPort, ENCRYPT_INFO* pEncryptInfo, void* nUser, int nReserved2), void* nUser);

#define PLAYM4_MEDIA_HEAD     1   //系统头锟斤拷锟斤拷
#define PLAYM4_VIDEO_DATA     2   //锟斤拷频锟斤拷锟斤拷锟斤拷
#define PLAYM4_AUDIO_DATA     3   //锟斤拷频锟斤拷锟斤拷锟斤拷
#define PLAYM4_PRIVT_DATA     4   //私锟斤拷锟斤拷锟斤拷锟斤拷

//预录锟斤拷锟斤拷锟斤拷锟斤拷息- NO SUPPORT
typedef struct  
{
    long nType;                     // 锟斤拷锟斤拷锟斤拷锟酵ｏ拷锟斤拷锟侥硷拷头锟斤拷锟斤拷频锟斤拷锟斤拷频锟斤拷私锟斤拷锟斤拷锟捷碉拷
    long nStamp;                    // 时锟斤拷锟�
    long nFrameNum;                 // 帧锟斤拷
    long nBufLen;                   // 锟斤拷锟捷筹拷锟斤拷
    char* pBuf;                     // 帧锟斤拷锟捷ｏ拷锟斤拷帧为锟斤拷位锟截碉拷
    PLAYM4_SYSTEM_TIME  stSysTime;  // 全锟斤拷时锟斤拷
}RECORD_DATA_INFO;

//锟斤拷锟斤拷预录锟今开关ｏ拷bFlag=1锟斤拷锟斤拷锟斤拷bFlag=0锟截憋拷-- NO SUPPORT
PLAYM4_API int __stdcall PlayM4_SetPreRecordFlag(int nPort, int bFlag);

//预录锟斤拷锟斤拷锟斤拷锟斤拷锟捷回碉拷- NO SUPPORT
PLAYM4_API int __stdcall PlayM4_SetPreRecordCallBack(int nPort, void (CALLBACK* PreRecordCBfun)(int nPort, RECORD_DATA_INFO* pRecordDataInfo, void* pUser), void* pUser);

typedef struct
{
    long    lDataType;          //私锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
    long    lDataStrVersion;    //锟斤拷锟捷凤拷锟截的结构锟斤拷姹撅拷锟斤拷锟揭拷锟轿拷思锟斤拷锟斤拷锟�
    long    lDataTimeStamp;
    long    lDataLength;
    char*   pData;
}AdditionDataInfo;

PLAYM4_API int __stdcall PlayM4_SetAdditionDataCallBack(int nPort, unsigned int nSyncType, void (CALLBACK* AdditionDataCBFun)(int nPort, AdditionDataInfo* pstAddDataInfo, void* pUser), void* pUser);

//lType: 1 锟斤拷示锟斤拷取锟斤拷前锟斤拷示帧PTZ锟斤拷息锟斤拷锟斤拷锟截讹拷锟结构锟斤拷锟斤拷式锟芥储锟斤拷pInfo锟节ｏ拷plLen锟斤拷锟截筹拷锟斤拷锟斤拷息;锟斤拷锟饺达拷锟斤拷pInfo = null锟斤拷锟斤拷锟皆伙拷取锟斤拷锟斤拷要锟斤拷锟斤拷锟斤拷诖娉わ拷锟絧lLen
PLAYM4_API int __stdcall PlayM4_GetStreamAdditionalInfo(int nPort, int lType, unsigned char* pInfo, int* plLen);

#define PLAYM4_SOURCE_MODULE             0 // 锟斤拷锟斤拷源模锟斤拷
#define PLAYM4_DEMUX_MODULE              1 // 锟斤拷锟斤拷模锟斤拷
#define PLAYM4_DECODE_MODULE             2 // 锟斤拷锟斤拷模锟斤拷
#define PLAYM4_RENDER_MODULE             3 // 锟斤拷染模锟斤拷
#define PLAYM4_MANAGER_MODULE            4 // 锟斤拷锟斤拷模锟斤拷

#define PLAYM4_RTINFO_HARDDECODE_ERROR          0 // 硬锟斤拷锟斤拷锟斤拷锟斤拷(锟斤拷要锟斤拷锟斤拷锟斤拷)锟斤拷锟斤拷
#define PLAYM4_RTINFO_SOFTDECODE_ERROR          1 // 锟斤拷锟斤拷锟斤拷锟斤拷螅ú锟街э拷郑锟�
#define PLAYM4_RTINFO_MEDIAHEADER_ERROR         2 // 媒锟斤拷头锟斤拷锟斤拷
#define PLAYM4_RTINFO_SWITCH_SOFT_DEC           3 // 锟叫伙拷锟斤拷锟斤拷锟斤拷
#define PLAYM4_RTINFO_ALLOC_MEMORY_ERROR        4 // 锟节达拷锟斤拷锟绞э拷锟�
#define PLAYM4_RTINFO_ENCRYPT_ERROR             5 // 锟斤拷钥锟斤拷锟斤拷
#define PLAYM4_RTINFO_RENDER_OVER               8 // 锟斤拷染一帧锟斤拷锟斤拷
#define PLAYM4_RTINFO_ERR_PRESENT               16 // 锟斤拷染锟斤拷示锟斤拷锟斤拷[锟斤拷前锟斤拷染锟斤拷锟斤拷锟斤拷染失锟斤拷,锟较诧拷锟斤拷锟斤拷锟叫伙拷锟斤拷锟斤拷]
#define PLAYM4_RTINFO_IDMX_DATA_ERROR           32 // 锟斤拷锟斤拷锟斤拷锟斤拷,锟斤拷锟斤拷失锟斤拷
#define PLAYM4_RTINFO_DECODE_PARAM_ERROR        64 // 锟斤拷锟斤拷锟斤拷锟斤拷,锟斤拷锟斤拷失锟斤拷
#define PLAYM4_RTINFO_SOFTDECODE_DATA_ERROR     128 // 锟斤拷锟斤拷锟斤拷锟斤拷锟捷达拷锟斤拷

#define PLAYM4_RTINFO_SOURCE_DATA_INTERVAL      0x40000  // 实时锟斤拷锟斤拷 帧时锟斤拷锟斤拷

typedef struct
{
    int            nRunTimeModule;     //锟斤拷前锟斤拷锟斤拷模锟介，锟捷讹拷2为锟斤拷锟斤拷模锟介，锟斤拷锟斤拷锟斤拷展
    int            nStrVersion;        //锟斤拷锟捷凤拷锟截的结构锟斤拷姹撅拷锟斤拷锟揭拷锟轿拷思锟斤拷锟斤拷锟�,锟斤拷一锟斤拷锟芥本锟斤拷锟斤拷锟�0x0001
    int            nFrameTimeStamp;    //帧锟斤拷
    int            nFrameNum;          //时锟斤拷锟�
    int            nErrorCode;         //锟斤拷锟斤拷锟斤拷,0为硬锟斤拷锟斤拷锟�
    unsigned char  reserved[12];       //锟斤拷锟斤拷锟街斤拷
}RunTimeInfo;

///<实时锟斤拷息锟截碉拷锟接匡拷
PLAYM4_API int __stdcall PlayM4_SetRunTimeInfoCallBackEx(int nPort, int nModule, void (CALLBACK* RunTimeInfoCBFun)(int nPort, RunTimeInfo* pstRunTimeInfo, void* pUser), void* pUser);

// 1锟斤拷SetRunTimeInfoCallBackEx锟接口ｏ拷nErrorCode锟斤拷锟斤拷6锟斤拷为锟斤拷锟斤拷8锟斤拷锟皆猴拷锟斤拷展锟斤拷式 16锟斤拷32锟斤拷64锟斤拷锟揭达拷8锟斤拷始锟斤拷息默锟较关闭诧拷锟斤拷锟酵★拷
// 2锟斤拷锟斤拷锟斤拷锟斤拷息锟斤拷锟狡接口ｏ拷锟斤拷锟狡达拷8锟皆猴拷锟斤拷锟较拷锟街э拷执锟�8锟斤拷始锟斤拷锟斤拷息锟斤拷拼锟斤拷模式 8|16|32 锟斤拷锟街凤拷式锟斤拷锟较诧拷锟斤拷锟斤拷选锟斤拷锟斤拷锟斤拷锟斤拷汀锟�
// 3锟斤拷nType锟斤拷锟斤拷通锟斤拷锟斤拷姆锟绞斤拷锟斤拷锟斤拷痛锟斤拷耄琻Flag锟斤拷示锟斤拷锟斤拷锟轿�0锟斤拷锟斤拷锟竭斤拷锟叫回碉拷锟斤拷锟斤拷0锟斤拷锟斤拷
PLAYM4_API int __stdcall PlayM4_SetRunTimeInfoCallbackType(int nPort, int nModule, unsigned int nType, int nFlag);


///<锟斤拷染锟斤拷示锟斤拷亟涌锟�
#ifndef PLAYM4_HIKD3D11_TAG
#define PLAYM4_HIKD3D11_TAG

///<锟斤拷染抓图锟结构锟斤拷
typedef struct _tagD3D11_PIC_INFO_
{
    unsigned int   nPicMode;     //抓图模式锟斤拷0-锟斤拷锟斤拷锟斤拷锟斤拷实锟绞分憋拷锟斤拷抓图(之前抓图模式)锟斤拷1-锟斤拷锟斤拷锟斤拷锟芥传锟斤拷目锟斤拷锟阶ネ硷拷锟絥PicWidth*nPicHeight为锟斤拷示锟斤拷锟节匡拷锟斤拷时效锟斤拷锟斤拷眩锟�
    unsigned char* pBuf;         //抓图锟斤拷锟斤拷buffer
    unsigned int   nBufSize;     //锟斤拷锟斤拷buffer锟斤拷小-锟斤拷锟斤拷锟絥PicMode为0锟斤拷为之前锟侥革拷锟捷伙拷取锟斤拷锟斤拷锟斤拷锟斤拷锟街憋拷锟斤拷锟斤拷锟斤拷锟叫伙拷锟斤拷锟斤拷锟诫；锟斤拷锟絥PicMode为1锟斤拷锟较诧拷锟斤拷锟斤拷锟斤拷玫姆直锟斤拷锟斤拷锟斤拷锟斤拷牖猴拷妫�
    unsigned int*  pPicSize;     //实锟斤拷图片锟斤拷小
    unsigned int   nPicWidth;    //锟斤拷锟斤拷抓图锟斤拷-nPicMode为1时锟斤拷效锟斤拷锟揭匡拷>=32,nPicWidth*nPicHeight<5000w锟街憋拷锟绞★拷
    unsigned int   nPicHeight;   //锟斤拷锟斤拷抓图锟斤拷-nPicMode为1时锟斤拷效锟斤拷锟揭革拷>=32,nPicWidth*nPicHeight<5000w锟街憋拷锟绞★拷
    unsigned char  chReserve[8]; //reserve锟斤拷锟斤拷锟街讹拷
}D3D_PIC_INFO;

/*锟斤拷染图锟斤拷锟斤拷锟斤拷锟斤拷锟�*/
typedef enum tagPLAYM4PostProcType
{
    PLAYM4_PPT_BRIGHTNESS               = 0x1,            ///< 锟斤拷锟斤拷   [-1.0, 1.0]
    PLAYM4_PPT_HUE                      = 0x2,            ///< 色锟斤拷   [0.0, 1.0]----0.166锟桔硷拷为一锟斤拷锟斤拷色锟戒化锟斤拷0锟斤拷1为同一锟斤拷锟斤拷色
    PLAYM4_PPT_SATURATION               = 0x3,            ///< 锟斤拷锟酵讹拷 [-1.0, 1.0]
    PLAYM4_PPT_CONTRAST                 = 0x4,            ///< 锟皆比讹拷 [-1.0, 1.0]
    PLAYM4_PPT_SHARPNESS                = 0x5,            ///< 锟斤拷锟�   [ 0.0, 1.0]
}PLAYM4PostProcType;

#endif

///<锟斤拷染锟斤拷抓图:nType:0-jpeg,1-bmp.
PLAYM4_API int __stdcall PlayM4_GetD3DCapture(int nPort, unsigned int nType, D3D_PIC_INFO* pstPicInfo);

///<锟斤拷染锟斤拷锟斤拷-锟斤拷锟矫诧拷锟斤拷
PLAYM4_API int __stdcall PlayM4_SetD3DPostProcess(int nPort, PLAYM4PostProcType nPostType, float fValue);

///<锟斤拷染锟斤拷锟斤拷-锟斤拷取锟斤拷锟斤拷
PLAYM4_API int __stdcall PlayM4_GetD3DPostProcess(int nPort, PLAYM4PostProcType nPostType, float* fValue);

///<锟街凤拷锟斤拷锟接碉拷锟斤拷锟斤拷锟铰凤拷锟斤拷锟斤拷锟斤拷锟斤拷锟绞憋拷锟斤拷锟侥拷锟斤拷锟斤拷锟解）-play前锟斤拷锟斤拷
PLAYM4_API int __stdcall PlayM4_SetConfigFontPath(int nPort, char* pFontPath);

// 锟斤拷锟斤拷锟斤拷锟绞憋拷锟斤拷取mp4锟斤拷装锟斤拷锟竭讹拷位偏锟斤拷
PLAYM4_API int __stdcall PlayM4_GetMpOffset(int nPort, int nTime, int* nOffset);

// 锟斤拷取锟斤拷频锟侥凤拷装锟酵憋拷锟斤拷锟绞�
PLAYM4_API int __stdcall PlayM4_GetStreamInfo(long nPort, int* pSysFormat, int* pCodeType);

///<时锟斤拷锟侥憋拷示锟斤拷锟斤拷为锟斤拷位锟斤拷锟斤拷锟斤拷为锟斤拷锟斤拷锟斤拷锟斤拷为锟斤拷-同锟斤拷锟截凤拷
PLAYM4_API bool __stdcall PlayM4_SetSupplementaryTimeZone(int nPort, int nTimeZone); 
///<锟斤拷锟窖撅拷锟斤拷锟斤拷时锟斤拷锟津返伙拷锟斤拷锟斤拷时锟斤拷锟斤拷锟斤拷锟斤拷失锟斤拷-同锟斤拷锟截凤拷
PLAYM4_API bool __stdcall PlayM4_GetSupplementaryTimeZone(int nPort, int* pTimeZone); 

////////////////////////////////////

///<锟斤拷锟节达拷小锟侥憋拷通知锟接匡拷
PLAYM4_API int __stdcall PlayM4_WndResolutionChange(int nPort);//new add

//锟斤拷锟斤拷锟斤拷使锟斤拷
PLAYM4_API int __stdcall PlayM4_SetRunTimeInfoCallBack(int nPort, void (CALLBACK* RunTimeInfoCBFun)(int nPort, RunTimeInfo* pstRunTimeInfo, void* pUser), void* pUser);
int  PlayM4_RigisterDrawFun(int nPort,void (CALLBACK* DrawFun)(int nPort,PLAYM4_HDC hDc,void* nUser),void* nUser);
int  PlayM4_SetDecCallBack(int nPort,void (CALLBACK* DecCBFun)(int nPort,char* pBuf,int nSize,FRAME_INFO * pFrameInfo, void* nReserved1,int nReserved2));
int  PlayM4_SetDecCallBackEx(int nPort,void (CALLBACK* DecCBFun)(int nPort,char * pBuf,int nSize,FRAME_INFO * pFrameInfo, void* nReserved1,int nReserved2), char* pDest, int nDestSize);
int  PlayM4_SetTimerType(int nPort,unsigned int nTimerType,unsigned int nReserved);
int  PlayM4_GetTimerType(int nPort,unsigned int *pTimerType,unsigned int *pReserved);

int  PlayM4_SetDisplayMode(int nPort, unsigned int dwType);
int  PlayM4_SetVideoWindow(int nPort, unsigned int nRegionNum, PLAYM4_HWND hWnd);
/////////////////////////////////////////////////////////////////////////////

////////////////NO SUPPORT///////////////////////////////////////////////////

int          PlayM4_InitDDraw(PLAYM4_HWND hWnd);
int          PlayM4_RealeseDDraw();
#if (WINVER >= 0x0400)
//Note: These funtion must be builded under win2000 or above with Microsoft Platform sdk.
//You can download the sdk from "http://www.microsoft.com/msdownload/platformsdk/sdkupdate/";
int          PlayM4_InitDDrawDevice();
void         PlayM4_ReleaseDDrawDevice();
int          PlayM4_SetDDrawDevice(int nPort, unsigned int nDeviceNum);
int          PlayM4_SetDDrawDeviceEx(int nPort,unsigned int nRegionNum,unsigned int nDeviceNum);
int          PlayM4_GetDDrawDeviceInfo(unsigned int nDeviceNum, char* lpDriverDescription, unsigned int nDespLen, char* lpDriverName, unsigned int nNameLen, HMONITOR* hhMonitor);
int          PlayM4_GetCapsEx(unsigned int nDDrawDeviceNum);
unsigned int PlayM4_GetDDrawDeviceTotalNums();
#endif
int          PlayM4_GetCaps();
int          PlayM4_OpenStreamEx(int nPort, unsigned char* pFileHeadBuf, unsigned int nSize, unsigned int nBufPoolSize);
int          PlayM4_CloseStreamEx(int nPort);
int          PlayM4_InputVideoData(int nPort, unsigned char* pBuf, unsigned int nSize);
int          PlayM4_InputAudioData(int nPort, unsigned char* pBuf, unsigned int nSize);
int          PlayM4_GetFileSpecialAttr(int nPort, unsigned int* pTimeStamp, unsigned int* pFileNum, unsigned int* pReserved);
//int          PlayM4_SetOverlayMode(int nPort, int bOverlay, COLORREF colorKey);
int          PlayM4_GetOverlayMode(int nPort);
int          PlayM4_SetOverlayFlipMode(int nPort, int bTrue);
//COLORREF     PlayM4_GetColorKey(int nPort);
int          PlayM4_SetPicQuality(int nPort, int bHighQuality);
int          PlayM4_GetPictureQuality(int nPort, int* bHighQuality);
int          PlayM4_ResetSourceBufFlag(int nPort);
int          PlayM4_SetDisplayType(int nPort, int nType);
int          PlayM4_GetDisplayType(int nPort);
int          PlayM4_SyncToAudio(int nPort, int bSyncToAudio);
int          PlayM4_RefreshPlayEx(int nPort, unsigned int nRegionNum);
int          PlayM4_AdjustWaveAudio(int nPort, int nCoefficient);
int          PlayM4_SetPlayMode(int nPort, int bNormal);
int          PlayM4_SetColor(int nPort, unsigned int nRegionNum, int nBrightness, int nContrast, int nSaturation, int nHue);
int          PlayM4_GetColor(int nPort, unsigned int nRegionNum, int* pBrightness, int* pContrast, int* pSaturation, int* pHue);
int          PlayM4_SetImageSharpen(int nPort, unsigned int nLevel);
int          PlayM4_SetDeflash(int nPort, int bDefalsh);
int          PlayM4_CheckDiscontinuousFrameNum(int nPort, int bCheck);
int          PlayM4_SetFileEndMsg(int nPort, PLAYM4_HWND hWnd, unsigned int nMsg);
int          PlayM4_SetVerifyCallBack(int nPort, unsigned int nBeginTime, unsigned int nEndTime, void (__stdcall* funVerify)(int nPort, FRAME_POS* pFilePos, unsigned int bIsVideo, unsigned int nUser), unsigned int nUser);
int          PlayM4_SetEncChangeMsg(int nPort, PLAYM4_HWND hWnd, unsigned int nMsg);
int          PlayM4_SetGetUserDataCallBack(int nPort, void(CALLBACK* funGetUserData)(int nPort, unsigned char* pUserBuf, unsigned int nBufLen, unsigned int nUser), unsigned int nUser);
int          PlayM4_SetSourceBufCallBack(int nPort, unsigned int nThreShold, void (CALLBACK* SourceBufCallBack)(int nPort, unsigned int nBufSize, unsigned int dwUser, void* pResvered), unsigned int dwUser, void* pReserved);
int          PlayM4_GetOriginalFrameCallBack(int nPort, int bIsChange, int bNormalSpeed, int nStartFrameNum, int nStartStamp, int nFileHeader, void(CALLBACK *funGetOrignalFrame)(int nPort, FRAME_TYPE* frameType, int nUser), int nUser);
int          PlayM4_GetThrowBFrameCallBack(int nPort, void(CALLBACK* funThrowBFrame)(int nPort, unsigned int nBFrame, unsigned int nUser), unsigned int nUser);
int          PlayM4_SetAudioCallBack(int nPort, void (__stdcall* funAudio)(int nPort, char* pAudioBuf, int nSize, int nStamp, int nType, int nUser), int nUser);
//motionflow
PLAYM4_API int __stdcall PlayM4_MotionFlow(int nPort, unsigned int dwAdjustType);
	

////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
    }
#endif

#endif //_PLAYM4_H_
