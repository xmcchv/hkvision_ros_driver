#ifndef _PLAYM4_H_ 
#define _PLAYM4_H_

#if defined( _WINDLL)
    #define PLAYM4_API  extern "C" __declspec(dllexport) 
#else 
    #define PLAYM4_API  extern "C" __declspec(dllimport) 
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
#define BUF_VIDEO_RENDER            (3) //video render node count 
#define BUF_AUDIO_RENDER            (4) //audio render node count 
#define BUF_VIDEO_DECODED           (5) //video decoded node count to render
#define BUF_AUDIO_DECODED           (6) //audio decoded node count to render
#define BUF_DISPLAY_NODE            (7) //display node

//Error code
#define  PLAYM4_NOERROR                            0    //no error
#define     PLAYM4_PARA_OVER                        1    //input parameter is invalid;
#define  PLAYM4_ORDER_ERROR                        2    //The order of the function to be called is error.
#define     PLAYM4_TIMER_ERROR                        3    //Create multimedia clock failed;
#define  PLAYM4_DEC_VIDEO_ERROR                    4    //Decode video data failed.
#define  PLAYM4_DEC_AUDIO_ERROR                    5    //Decode audio data failed.
#define     PLAYM4_ALLOC_MEMORY_ERROR                6    //Allocate memory failed.
#define  PLAYM4_OPEN_FILE_ERROR                    7    //Open the file failed.
#define  PLAYM4_CREATE_OBJ_ERROR                8    //Create thread or event failed
#define  PLAYM4_CREATE_DDRAW_ERROR                9    //Create DirectDraw object failed.
#define  PLAYM4_CREATE_OFFSCREEN_ERROR            10    //failed when creating off-screen surface.
#define  PLAYM4_BUF_OVER                        11    //buffer is overflow
#define  PLAYM4_CREATE_SOUND_ERROR                12    //failed when creating audio device.    
#define     PLAYM4_SET_VOLUME_ERROR                13    //Set volume failed
#define  PLAYM4_SUPPORT_FILE_ONLY                14    //The function only support play file.
#define  PLAYM4_SUPPORT_STREAM_ONLY                15    //The function only support play stream.
#define  PLAYM4_SYS_NOT_SUPPORT                    16    //System not support.
#define  PLAYM4_FILEHEADER_UNKNOWN                17    //No file header.
#define  PLAYM4_VERSION_INCORRECT                18    //The version of decoder and encoder is not adapted.  
#define  PLAYM4_INIT_DECODER_ERROR                19    //Initialize decoder failed.
#define  PLAYM4_CHECK_FILE_ERROR                20    //The file data is unknown.
#define  PLAYM4_INIT_TIMER_ERROR                21    //Initialize multimedia clock failed.
#define     PLAYM4_BLT_ERROR                        22    //Blt failed.
#define  PLAYM4_UPDATE_ERROR                    23    //Update failed.
#define  PLAYM4_OPEN_FILE_ERROR_MULTI            24   //openfile error, streamtype is multi
#define  PLAYM4_OPEN_FILE_ERROR_VIDEO            25   //openfile error, streamtype is video
#define  PLAYM4_JPEG_COMPRESS_ERROR                26   //JPEG compress error
#define  PLAYM4_EXTRACT_NOT_SUPPORT                27    //Don't support the version of this file.
#define  PLAYM4_EXTRACT_DATA_ERROR                28    //extract video data failed.
#define  PLAYM4_SECRET_KEY_ERROR                29    //Secret key is error //add 20071218
#define  PLAYM4_DECODE_KEYFRAME_ERROR            30   //add by hy 20090318
#define  PLAYM4_NEED_MORE_DATA                    31   //add by hy 20100617
#define  PLAYM4_INVALID_PORT                    32    //add by cj 20100913
#define  PLAYM4_NOT_FIND                        33    //add by cj 20110428
#define  PLAYM4_NEED_LARGER_BUFFER              34  //add by pzj 20130528
#define  PLAYM4_FAIL_UNKNOWN                    99   //Fail, but the reason is unknown;    

//锟斤拷锟桔癸拷锟杰达拷锟斤拷锟斤拷
#define PLAYM4_FEC_ERR_ENABLEFAIL                100 // 锟斤拷锟斤拷模锟斤拷锟斤拷锟绞э拷锟�
#define PLAYM4_FEC_ERR_NOTENABLE                101 // 锟斤拷锟斤拷模锟斤拷没锟叫硷拷锟斤拷
#define PLAYM4_FEC_ERR_NOSUBPORT                102 // 锟接端匡拷没锟叫凤拷锟斤拷
#define PLAYM4_FEC_ERR_PARAMNOTINIT                103 // 没锟叫筹拷始锟斤拷锟斤拷应锟剿口的诧拷锟斤拷
#define PLAYM4_FEC_ERR_SUBPORTOVER                104 // 锟接端匡拷锟窖撅拷锟斤拷锟斤拷
#define PLAYM4_FEC_ERR_EFFECTNOTSUPPORT            105 // 锟矫帮拷装锟斤拷式锟斤拷锟斤拷锟斤拷效锟斤拷锟斤拷支锟斤拷
#define PLAYM4_FEC_ERR_INVALIDWND                106 // 锟角凤拷锟侥达拷锟斤拷
#define PLAYM4_FEC_ERR_PTZOVERFLOW                107 // PTZ位锟斤拷越锟斤拷
#define PLAYM4_FEC_ERR_RADIUSINVALID            108 // 圆锟侥诧拷锟斤拷锟角凤拷
#define PLAYM4_FEC_ERR_UPDATENOTSUPPORT            109 // 指锟斤拷锟侥帮拷装锟斤拷式锟酵斤拷锟斤拷效锟斤拷锟斤拷锟矫诧拷锟斤拷锟斤拷锟铰诧拷支锟斤拷
#define PLAYM4_FEC_ERR_NOPLAYPORT                110 // 锟斤拷锟脚匡拷丝锟矫伙拷锟斤拷锟斤拷锟�
#define PLAYM4_FEC_ERR_PARAMVALID                111 // 锟斤拷锟斤拷为锟斤拷
#define PLAYM4_FEC_ERR_INVALIDPORT                112 // 锟角凤拷锟接端匡拷
#define PLAYM4_FEC_ERR_PTZZOOMOVER                113 // PTZ锟斤拷锟斤拷锟斤拷围越锟斤拷
#define PLAYM4_FEC_ERR_OVERMAXPORT                114  // 锟斤拷锟斤拷通锟斤拷锟斤拷锟酵ｏ拷锟斤拷锟街э拷值慕锟斤拷锟酵拷锟轿拷母锟�
#define PLAYM4_FEC_ERR_ENABLED                  115  //锟矫端匡拷锟窖撅拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷模锟斤拷
#define PLAYM4_FEC_ERR_D3DACCENOTENABLE            116 // D3D锟斤拷锟斤拷没锟叫匡拷锟斤拷


//Max display regions.
#define MAX_DISPLAY_WND 4

//Display type
#define DISPLAY_NORMAL                0x00000001   
#define DISPLAY_QUARTER                0x00000002
#define DISPLAY_YC_SCALE            0x00000004    //add by gb 20091116
#define DISPLAY_NOTEARING            0x00000008
//Display buffers
#define MAX_DIS_FRAMES 50
#define MIN_DIS_FRAMES 1

//Locate by
#define BY_FRAMENUM  1
#define BY_FRAMETIME 2

//Source buffer
#define SOURCE_BUF_MAX    1024*100000
#define SOURCE_BUF_MIN    1024*50

//Stream type
#define STREAME_REALTIME 0
#define STREAME_FILE     1

//frame type
#define T_AUDIO16    101
#define T_AUDIO8    100
#define T_UYVY        1
#define T_YV12        3
#define T_RGB32        7

//capability
#define SUPPORT_DDRAW        1 
#define SUPPORT_BLT         2 
#define SUPPORT_BLTFOURCC   4 
#define SUPPORT_BLTSHRINKX  8 
#define SUPPORT_BLTSHRINKY  16
#define SUPPORT_BLTSTRETCHX 32
#define SUPPORT_BLTSTRETCHY 64
#define SUPPORT_SSE         128
#define SUPPORT_MMX            256 

// 锟斤拷锟铰宏定锟斤拷锟斤拷锟斤拷HIK_MEDIAINFO锟结构
#define FOURCC_HKMI            0x484B4D49    // "HKMI" HIK_MEDIAINFO锟结构锟斤拷锟�
// 系统锟斤拷装锟斤拷式    
#define SYSTEM_NULL            0x0                // 没锟斤拷系统锟姐，锟斤拷锟斤拷频锟斤拷锟斤拷锟斤拷频锟斤拷    
#define SYSTEM_HIK          0x1                // 锟斤拷锟斤拷锟侥硷拷锟斤拷
#define SYSTEM_MPEG2_PS     0x2                // PS锟斤拷装
#define SYSTEM_MPEG2_TS     0x3                // TS锟斤拷装
#define SYSTEM_RTP          0x4                // rtp锟斤拷装
#define SYSTEM_RTPHIK       0x401                // rtp锟斤拷装

// 锟斤拷频锟斤拷锟斤拷锟斤拷锟斤拷
#define VIDEO_NULL          0x0 // 没锟斤拷锟斤拷频
#define VIDEO_H264          0x1 // 锟斤拷锟斤拷H.264
#define VIDEO_MPEG4         0x3 // 锟斤拷准MPEG4
#define VIDEO_MJPEG            0x4
#define VIDEO_AVC264        0x0100

// 锟斤拷频锟斤拷锟斤拷锟斤拷锟斤拷
#define AUDIO_NULL          0x0000 // 没锟斤拷锟斤拷频
#define AUDIO_ADPCM         0x1000 // ADPCM 
#define AUDIO_MPEG          0x2000 // MPEG 系锟斤拷锟斤拷频锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷应锟斤拷锟斤拷MPEG锟斤拷频
#define AUDIO_AAC            0X2001 // AAC 锟斤拷锟斤拷
// G系锟斤拷锟斤拷频
#define AUDIO_RAW_DATA8        0x7000      //锟斤拷锟斤拷锟斤拷为8k锟斤拷原始锟斤拷锟斤拷
#define AUDIO_RAW_UDATA16    0x7001      //锟斤拷锟斤拷锟斤拷为16k锟斤拷原始锟斤拷锟捷ｏ拷锟斤拷L16
#define AUDIO_G711_U        0x7110
#define AUDIO_G711_A        0x7111
#define AUDIO_G722_1        0x7221
#define AUDIO_G723_1        0x7231
#define AUDIO_G726_U        0x7260
#define AUDIO_G726_A        0x7261
#define AUDIO_G726_16       0x7262 
#define AUDIO_G729          0x7290
#define AUDIO_AMR_NB        0x3000

#define SYNCDATA_VEH        1 //同锟斤拷锟斤拷锟斤拷:锟斤拷锟斤拷锟斤拷息    
#define SYNCDATA_IVS        2 //同锟斤拷锟斤拷锟斤拷:锟斤拷锟斤拷锟斤拷息

//motion flow type
#define    MOTION_FLOW_NONE            0
#define MOTION_FLOW_CPU                1
#define MOTION_FLOW_GPU                2

//锟斤拷锟斤拷频锟斤拷锟斤拷锟斤拷锟斤拷
#define ENCRYPT_AES_3R_VIDEO     1 
#define ENCRYPT_AES_10R_VIDEO    2 
#define ENCRYPT_AES_3R_AUDIO     1  
#define ENCRYPT_AES_10R_AUDIO    2

//Frame position
typedef struct{
    long nFilePos;
    long nFrameNum;
    long nFrameTime;
    long nErrorFrameNum;
    SYSTEMTIME *pErrorTime;
    long nErrorLostFrameNum;
    long nErrorFrameSize;
}FRAME_POS,*PFRAME_POS;

//Frame Info
typedef struct{
    long nWidth;
    long nHeight;
    long nStamp;
    long nType;
    long nFrameRate;
    DWORD dwFrameNum;
}FRAME_INFO;

typedef struct
{
    long         nPort;        //通锟斤拷锟斤拷
    char         *pBuf;        //锟斤拷锟截的碉拷一路图锟斤拷锟斤拷锟斤拷指锟斤拷
    unsigned int nBufLen;      //锟斤拷锟截的碉拷一路图锟斤拷锟斤拷锟捷达拷小
    char         *pBuf1;       //锟斤拷锟截的第讹拷路图锟斤拷锟斤拷锟斤拷指锟斤拷
    unsigned int nBufLen1;     //锟斤拷锟截的第讹拷路图锟斤拷锟斤拷锟捷达拷小
    char         *pBuf2;       //锟斤拷锟截的碉拷锟斤拷路图锟斤拷锟斤拷锟斤拷指锟斤拷
    unsigned int nBufLen2;     //锟斤拷锟截的碉拷锟斤拷路图锟斤拷锟斤拷锟捷达拷小
    unsigned int nWidth;       //锟斤拷锟斤拷锟�
    unsigned int nHeight;      //锟斤拷锟斤拷锟�
    unsigned int nStamp;       //时锟斤拷锟斤拷息锟斤拷锟斤拷位锟斤拷锟斤拷
    unsigned int nType;        //锟斤拷锟斤拷锟斤拷锟斤拷
    void         *pUser;       //锟矫伙拷锟斤拷锟斤拷
    unsigned int reserved[4];  //锟斤拷锟斤拷
}DISPLAY_INFO_YUV;

//Frame 
typedef struct{
    char *pDataBuf;
    long  nSize;
    long  nFrameNum;
    BOOL  bIsAudio;
    long  nReserved;
}FRAME_TYPE;

//Watermark Info    //add by gb 080119
typedef struct{
    char *pDataBuf;
    long  nSize;
    long  nFrameNum;
    BOOL  bRsaRight;
    long  nReserved;
}WATERMARK_INFO;

typedef struct SYNCDATA_INFO 
{
    DWORD dwDataType;        //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷同锟斤拷锟侥革拷锟斤拷锟斤拷息锟斤拷锟酵ｏ拷目前锟叫ｏ拷锟斤拷锟斤拷锟斤拷息锟斤拷锟斤拷锟斤拷锟斤拷息
    DWORD dwDataLen;        //锟斤拷锟斤拷锟斤拷息锟斤拷锟捷筹拷锟斤拷
    BYTE* pData;            //指锟斤拷锟斤拷锟斤拷息锟斤拷锟捷结构锟斤拷指锟斤拷,锟斤拷锟斤拷IVS_INFO锟结构
} SYNCDATA_INFO;

#ifndef _HIK_MEDIAINFO_FLAG_
#define _HIK_MEDIAINFO_FLAG_
typedef struct _HIK_MEDIAINFO_                // modified by gb 080425
{
    unsigned int    media_fourcc;            // "HKMI": 0x484B4D49 Hikvision Media Information
    unsigned short  media_version;            // 锟芥本锟脚ｏ拷指锟斤拷锟斤拷息锟结构锟芥本锟脚ｏ拷目前为0x0101,锟斤拷1.01锟芥本锟斤拷01锟斤拷锟斤拷锟芥本锟脚ｏ拷01锟斤拷锟接版本锟脚★拷
    unsigned short  device_id;                // 锟借备ID锟斤拷锟斤拷锟节革拷锟斤拷/锟斤拷锟斤拷            
    
    unsigned short  system_format;          // 系统锟斤拷装锟斤拷
    unsigned short  video_format;           // 锟斤拷频锟斤拷锟斤拷锟斤拷锟斤拷

    unsigned short  audio_format;           // 锟斤拷频锟斤拷锟斤拷锟斤拷锟斤拷
    unsigned char   audio_channels;         // 通锟斤拷锟斤拷  
    unsigned char   audio_bits_per_sample;  // 锟斤拷位锟斤拷
    unsigned int    audio_samplesrate;      // 锟斤拷锟斤拷锟斤拷 
    unsigned int    audio_bitrate;          // 压锟斤拷锟斤拷频锟斤拷锟斤拷,锟斤拷位锟斤拷bit

    unsigned int    reserved[4];            // 锟斤拷锟斤拷
}HIK_MEDIAINFO;
#endif

typedef struct  
{
    long nPort;
    char * pBuf;
    long nBufLen;
    long nWidth;
    long nHeight;
    long nStamp;
    long nType;
    long nUser;
}DISPLAY_INFO;

typedef struct
{
    long nPort;
    char *pVideoBuf;
    long nVideoBufLen;
    char *pPriBuf;
    long nPriBufLen;
    long nWidth;
    long nHeight;
    long nStamp;
    long nType;
    long nUser;
}DISPLAY_INFOEX;

typedef struct PLAYM4_SYSTEM_TIME //锟斤拷锟斤拷时锟斤拷 
{
    DWORD dwYear;    //锟斤拷
    DWORD dwMon;    //锟斤拷
    DWORD dwDay;    //锟斤拷
    DWORD dwHour;    //时
    DWORD dwMin;    //锟斤拷
    DWORD dwSec;    //锟斤拷
    DWORD dwMs;        //锟斤拷锟斤拷
} PLAYM4_SYSTEM_TIME;

//ENCRYPT Info
typedef struct{
    long nVideoEncryptType;  //锟斤拷频锟斤拷锟斤拷锟斤拷锟斤拷
    long nAudioEncryptType;  //锟斤拷频锟斤拷锟斤拷锟斤拷锟斤拷
    long nSetSecretKey;      //锟角凤拷锟斤拷锟矫ｏ拷1锟斤拷示锟斤拷锟斤拷锟斤拷钥锟斤拷0锟斤拷示没锟斤拷锟斤拷锟斤拷锟斤拷钥
}ENCRYPT_INFO;

//////////////////////////////////////////////////////////////////////////////
//API
//////////////////////////////////////////////////////////////////////////////

////////////////ver 1.0///////////////////////////////////////
//Initialize DirecDraw.Now invalid.
PLAYM4_API BOOL __stdcall  PlayM4_InitDDraw(HWND hWnd);
//Release directDraw; Now invalid.
PLAYM4_API BOOL __stdcall PlayM4_RealeseDDraw();
PLAYM4_API BOOL __stdcall PlayM4_OpenFile(LONG nPort,LPSTR sFileName);
PLAYM4_API BOOL __stdcall PlayM4_CloseFile(LONG nPort);
PLAYM4_API BOOL __stdcall PlayM4_Play(LONG nPort, HWND hWnd);
PLAYM4_API BOOL __stdcall PlayM4_Stop(LONG nPort);
PLAYM4_API BOOL __stdcall PlayM4_Pause(LONG nPort,DWORD nPause);
PLAYM4_API BOOL __stdcall PlayM4_Fast(LONG nPort);
PLAYM4_API BOOL __stdcall PlayM4_Slow(LONG nPort);
PLAYM4_API BOOL __stdcall PlayM4_OneByOne(LONG nPort);
PLAYM4_API BOOL __stdcall PlayM4_SetPlayPos(LONG nPort,float fRelativePos);
PLAYM4_API float __stdcall PlayM4_GetPlayPos(LONG nPort);
PLAYM4_API BOOL __stdcall PlayM4_SetFileEndMsg(LONG nPort,HWND hWnd,UINT nMsg);
PLAYM4_API BOOL __stdcall PlayM4_SetVolume(LONG nPort,WORD nVolume);
PLAYM4_API BOOL __stdcall PlayM4_StopSound();
PLAYM4_API BOOL __stdcall PlayM4_PlaySound(LONG nPort);
PLAYM4_API BOOL __stdcall PlayM4_OpenStream(LONG nPort,PBYTE pFileHeadBuf,DWORD nSize,DWORD nBufPoolSize);
PLAYM4_API BOOL __stdcall PlayM4_InputData(LONG nPort,PBYTE pBuf,DWORD nSize);
PLAYM4_API BOOL __stdcall PlayM4_CloseStream(LONG nPort);
PLAYM4_API int  __stdcall  PlayM4_GetCaps();
PLAYM4_API DWORD __stdcall PlayM4_GetFileTime(LONG nPort);
PLAYM4_API DWORD __stdcall PlayM4_GetPlayedTime(LONG nPort);
PLAYM4_API DWORD __stdcall PlayM4_GetPlayedFrames(LONG nPort);

//23
////////////////ver 2.0 added///////////////////////////////////////
PLAYM4_API BOOL __stdcall    PlayM4_SetDecCallBack(LONG nPort,void (CALLBACK* DecCBFun)(long nPort,char * pBuf,long nSize,FRAME_INFO * pFrameInfo, long nReserved1,long nReserved2));
PLAYM4_API BOOL __stdcall    PlayM4_SetDisplayCallBackYUV(LONG nPort, void (CALLBACK* DisplayCBFun)(DISPLAY_INFO_YUV *pstDisplayInfo), BOOL bTrue, void* pUser);
PLAYM4_API BOOL __stdcall    PlayM4_SetDisplayCallBack(LONG nPort,void (CALLBACK* DisplayCBFun)(long nPort,char * pBuf,long nSize,long nWidth,long nHeight,long nStamp,long nType,long nReserved));
PLAYM4_API BOOL __stdcall    PlayM4_ConvertToBmpFile(char * pBuf,long nSize,long nWidth,long nHeight,long nType,char *sFileName);
PLAYM4_API DWORD __stdcall    PlayM4_GetFileTotalFrames(LONG nPort);
PLAYM4_API DWORD __stdcall    PlayM4_GetCurrentFrameRate(LONG nPort);
PLAYM4_API DWORD __stdcall    PlayM4_GetPlayedTimeEx(LONG nPort);
PLAYM4_API BOOL __stdcall    PlayM4_SetPlayedTimeEx(LONG nPort,DWORD nTime);
PLAYM4_API DWORD __stdcall    PlayM4_GetCurrentFrameNum(LONG nPort);
PLAYM4_API BOOL __stdcall    PlayM4_SetStreamOpenMode(LONG nPort,DWORD nMode);
PLAYM4_API DWORD __stdcall    PlayM4_GetFileHeadLength();
PLAYM4_API DWORD __stdcall    PlayM4_GetSdkVersion();
//11
////////////////ver 2.2 added///////////////////////////////////////
PLAYM4_API DWORD __stdcall  PlayM4_GetLastError(LONG nPort);
PLAYM4_API BOOL __stdcall PlayM4_RefreshPlay(LONG nPort);
PLAYM4_API BOOL __stdcall PlayM4_SetOverlayMode(LONG nPort,BOOL bOverlay,COLORREF colorKey);
PLAYM4_API BOOL __stdcall PlayM4_GetPictureSize(LONG nPort,LONG *pWidth,LONG *pHeight);
PLAYM4_API BOOL __stdcall PlayM4_SetPicQuality(LONG nPort,BOOL bHighQuality);
PLAYM4_API BOOL __stdcall PlayM4_PlaySoundShare(LONG nPort);
PLAYM4_API BOOL __stdcall PlayM4_StopSoundShare(LONG nPort);
//7
////////////////ver 2.4 added///////////////////////////////////////
PLAYM4_API LONG __stdcall PlayM4_GetStreamOpenMode(LONG nPort);
PLAYM4_API LONG __stdcall PlayM4_GetOverlayMode(LONG nPort);
PLAYM4_API COLORREF __stdcall PlayM4_GetColorKey(LONG nPort);
PLAYM4_API WORD __stdcall PlayM4_GetVolume(LONG nPort);
PLAYM4_API BOOL __stdcall PlayM4_GetPictureQuality(LONG nPort,BOOL *bHighQuality);
PLAYM4_API DWORD __stdcall PlayM4_GetSourceBufferRemain(LONG nPort);
PLAYM4_API BOOL __stdcall PlayM4_ResetSourceBuffer(LONG nPort);
PLAYM4_API BOOL __stdcall PlayM4_SetSourceBufCallBack(LONG nPort,DWORD nThreShold,void (CALLBACK * SourceBufCallBack)(long nPort,DWORD nBufSize,DWORD dwUser,void*pResvered),DWORD dwUser,void *pReserved);
PLAYM4_API BOOL __stdcall PlayM4_ResetSourceBufFlag(LONG nPort);
PLAYM4_API BOOL __stdcall PlayM4_SetDisplayBuf(LONG nPort,DWORD nNum);
PLAYM4_API DWORD __stdcall PlayM4_GetDisplayBuf(LONG nPort);
PLAYM4_API BOOL __stdcall PlayM4_OneByOneBack(LONG nPort);
PLAYM4_API BOOL __stdcall PlayM4_SetFileRefCallBack(LONG nPort, void (__stdcall *pFileRefDone)(DWORD nPort,DWORD nUser),DWORD nUser);
PLAYM4_API BOOL __stdcall PlayM4_SetCurrentFrameNum(LONG nPort,DWORD nFrameNum);
PLAYM4_API BOOL __stdcall PlayM4_GetKeyFramePos(LONG nPort,DWORD nValue, DWORD nType, PFRAME_POS pFramePos);
PLAYM4_API BOOL __stdcall PlayM4_GetNextKeyFramePos(LONG nPort,DWORD nValue, DWORD nType, PFRAME_POS pFramePos);
#if (WINVER >= 0x0400)
//Note: These funtion must be builded under win2000 or above with Microsoft Platform sdk.
//        You can download the sdk from "http://www.microsoft.com/msdownload/platformsdk/sdkupdate/";
PLAYM4_API BOOL __stdcall PlayM4_InitDDrawDevice();
PLAYM4_API void __stdcall PlayM4_ReleaseDDrawDevice();
PLAYM4_API DWORD __stdcall PlayM4_GetDDrawDeviceTotalNums();
PLAYM4_API BOOL __stdcall PlayM4_SetDDrawDevice(LONG nPort,DWORD nDeviceNum);
//PLAYM4_API BOOL __stdcall PlayM4_GetDDrawDeviceInfo(DWORD nDeviceNum,LPSTR  lpDriverDescription,DWORD nDespLen,LPSTR lpDriverName ,DWORD nNameLen,HMONITOR *hhMonitor);
PLAYM4_API int  __stdcall  PlayM4_GetCapsEx(DWORD nDDrawDeviceNum);
#endif
PLAYM4_API BOOL __stdcall PlayM4_ThrowBFrameNum(LONG nPort,DWORD nNum);
//23
////////////////ver 2.5 added///////////////////////////////////////
PLAYM4_API BOOL __stdcall PlayM4_SetDisplayType(LONG nPort,LONG nType);
PLAYM4_API long __stdcall PlayM4_GetDisplayType(LONG nPort);
//2
////////////////ver 3.0 added///////////////////////////////////////
PLAYM4_API BOOL __stdcall PlayM4_SetDecCBStream(LONG nPort,DWORD nStream);
PLAYM4_API BOOL __stdcall PlayM4_SetDisplayRegion(LONG nPort,DWORD nRegionNum, RECT *pSrcRect, HWND hDestWnd, BOOL bEnable);
PLAYM4_API BOOL __stdcall PlayM4_RefreshPlayEx(LONG nPort,DWORD nRegionNum);
#if (WINVER >= 0x0400)
//Note: The funtion must be builded under win2000 or above with Microsoft Platform sdk.
//        You can download the sdk from http://www.microsoft.com/msdownload/platformsdk/sdkupdate/;
PLAYM4_API BOOL __stdcall PlayM4_SetDDrawDeviceEx(LONG nPort,DWORD nRegionNum,DWORD nDeviceNum);
#endif
//4
/////////////////v3.2 added/////////////////////////////////////////

PLAYM4_API BOOL __stdcall PlayM4_GetRefValue(LONG nPort,BYTE *pBuffer, DWORD *pSize);
PLAYM4_API BOOL __stdcall PlayM4_SetRefValue(LONG nPort,BYTE *pBuffer, DWORD nSize);
PLAYM4_API BOOL __stdcall PlayM4_OpenStreamEx(LONG nPort,PBYTE pFileHeadBuf,DWORD nSize,DWORD nBufPoolSize);
PLAYM4_API BOOL __stdcall PlayM4_CloseStreamEx(LONG nPort);
PLAYM4_API BOOL __stdcall PlayM4_InputVideoData(LONG nPort,PBYTE pBuf,DWORD nSize);
PLAYM4_API BOOL __stdcall PlayM4_InputAudioData(LONG nPort,PBYTE pBuf,DWORD nSize);
PLAYM4_API BOOL __stdcall PlayM4_RegisterDrawFun(LONG nPort,void (CALLBACK* DrawFun)(long nPort,HDC hDc,LONG nUser),LONG nUser);
PLAYM4_API BOOL __stdcall PlayM4_RigisterDrawFun(LONG nPort,void (CALLBACK* DrawFun)(long nPort,HDC hDc,LONG nUser),LONG nUser);
//8
//////////////////v3.4/////////////////////////////////////////////////////
PLAYM4_API BOOL __stdcall PlayM4_SetTimerType(LONG nPort,DWORD nTimerType,DWORD nReserved);
PLAYM4_API BOOL __stdcall PlayM4_GetTimerType(LONG nPort,DWORD *pTimerType,DWORD *pReserved);
PLAYM4_API BOOL __stdcall PlayM4_ResetBuffer(LONG nPort,DWORD nBufType);
PLAYM4_API DWORD __stdcall PlayM4_GetBufferValue(LONG nPort,DWORD nBufType);

//////////////////V3.6/////////////////////////////////////////////////////////
PLAYM4_API BOOL __stdcall PlayM4_AdjustWaveAudio(LONG nPort,LONG nCoefficient);
PLAYM4_API BOOL __stdcall PlayM4_SetVerifyCallBack(LONG nPort, DWORD nBeginTime, DWORD nEndTime, void (__stdcall * funVerify)(long nPort, FRAME_POS * pFilePos, DWORD bIsVideo, DWORD nUser),  DWORD  nUser);
PLAYM4_API BOOL __stdcall PlayM4_SetAudioCallBack(LONG nPort, void (__stdcall * funAudio)(long nPort, char * pAudioBuf, long nSize, long nStamp, long nType, long nUser), long nUser);
PLAYM4_API BOOL __stdcall PlayM4_SetEncTypeChangeCallBack(LONG nPort,void(CALLBACK *funEncChange)(long nPort,long nUser),long nUser);
PLAYM4_API BOOL __stdcall PlayM4_SetColor(LONG nPort, DWORD nRegionNum, int nBrightness, int nContrast, int nSaturation, int nHue);
PLAYM4_API BOOL __stdcall PlayM4_GetColor(LONG nPort, DWORD nRegionNum, int *pBrightness, int *pContrast, int *pSaturation, int *pHue);
PLAYM4_API BOOL __stdcall PlayM4_SetEncChangeMsg(LONG nPort,HWND hWnd,UINT nMsg);
PLAYM4_API BOOL __stdcall PlayM4_GetOriginalFrameCallBack(LONG nPort, BOOL bIsChange,BOOL bNormalSpeed,long nStartFrameNum,long nStartStamp,long nFileHeader,void(CALLBACK *funGetOrignalFrame)(long nPort,FRAME_TYPE *frameType, long nUser),long nUser);
PLAYM4_API BOOL __stdcall PlayM4_GetFileSpecialAttr(LONG nPort, DWORD *pTimeStamp,DWORD *pFileNum ,DWORD *pReserved);
PLAYM4_API DWORD __stdcall PlayM4_GetSpecialData(LONG nPort);
PLAYM4_API BOOL __stdcall PlayM4_SetCheckWatermarkCallBack(LONG nPort,void(CALLBACK* funCheckWatermark)(long nPort,WATERMARK_INFO* pWatermarkInfo,DWORD nUser),DWORD nUser);
PLAYM4_API BOOL __stdcall PlayM4_SetImageSharpen(LONG nPort,DWORD nLevel);
PLAYM4_API BOOL __stdcall PlayM4_SetDecodeFrameType(LONG nPort,DWORD nFrameType);
PLAYM4_API BOOL __stdcall PlayM4_SetPlayMode(LONG nPort,BOOL bNormal);
PLAYM4_API BOOL __stdcall PlayM4_SetOverlayFlipMode(LONG nPort,BOOL bTrue);
PLAYM4_API BOOL __stdcall PlayM4_SetOverlayPriInfoFlag(LONG nPort, DWORD nIntelType, BOOL bTrue,const char *pFontPath);

//PLAYM4_API DWORD __stdcall PlayM4_GetAbsFrameNum(LONG nPort); 

//////////////////V4.7.0.0//////////////////////////////////////////////////////
////convert yuv to jpeg
PLAYM4_API BOOL __stdcall PlayM4_ConvertToJpegFile(char * pBuf,long nSize,long nWidth,long nHeight,long nType,char *sFileName);
PLAYM4_API BOOL __stdcall PlayM4_SetJpegQuality(long nQuality);
//set deflash
PLAYM4_API BOOL __stdcall PlayM4_SetDeflash(LONG nPort,BOOL bDefalsh);
//PLAYM4_API BOOL __stdcall PlayM4_SetDecCallBackEx(LONG nPort,void (CALLBACK* DecCBFun)(long nPort,char * pBuf,long nSize,FRAME_INFO * pFrameInfo, long nReserved1,long nReserved2), char* pDest, long nDestSize);
//////////////////V4.8.0.0/////////////////////////////////////////////////////////
//check discontinuous frame number as error data?
PLAYM4_API BOOL __stdcall PlayM4_CheckDiscontinuousFrameNum(LONG nPort, BOOL bCheck);
//get bmp or jpeg
PLAYM4_API BOOL __stdcall PlayM4_GetBMP(LONG nPort,PBYTE pBitmap,DWORD nBufSize,DWORD* pBmpSize);
PLAYM4_API BOOL __stdcall PlayM4_GetJPEG(LONG nPort,PBYTE pJpeg,DWORD nBufSize,DWORD* pJpegSize);
//dec call back mend
PLAYM4_API BOOL __stdcall PlayM4_SetDecCallBackMend(LONG nPort,void (CALLBACK* DecCBFun)(long nPort,char * pBuf,long nSize,FRAME_INFO * pFrameInfo, long nUser,long nReserved2), long nUser);
PLAYM4_API BOOL __stdcall PlayM4_SetSecretKey(LONG nPort, LONG lKeyType, char *pSecretKey, LONG lKeyLen);

// add by gb 2007-12-23
PLAYM4_API BOOL __stdcall PlayM4_SetFileEndCallback(LONG nPort, void(CALLBACK*FileEndCallback)(long nPort, void *pUser), void *pUser);

// add by gb 080131 version 4.9.0.1
PLAYM4_API BOOL __stdcall PlayM4_GetPort(LONG* nPort);
PLAYM4_API BOOL __stdcall PlayM4_FreePort(LONG nPort);
PLAYM4_API BOOL __stdcall PlayM4_SetDisplayCallBackEx(LONG nPort,void (CALLBACK* DisplayCBFun)(DISPLAY_INFO *pstDisplayInfo), long nUser);
PLAYM4_API BOOL __stdcall PlayM4_SkipErrorData(LONG nPort, BOOL bSkip);
PLAYM4_API BOOL __stdcall PlayM4_SetDecCallBackExMend(LONG nPort, void (CALLBACK* DecCBFun)(long nPort, char* pBuf, long nSize, FRAME_INFO* pFrameInfo, 
                                                      long nUser, long nReserved2), char* pDest, long nDestSize, long nUser);
//reverse play add by chenjie 110609
PLAYM4_API BOOL __stdcall PlayM4_ReversePlay(LONG nPort);
PLAYM4_API BOOL __stdcall PlayM4_GetSystemTime(LONG nPort, PLAYM4_SYSTEM_TIME *pstSystemTime);

//PLAYM4_API BOOL __stdcall PlayM4_SetDecodeERC(long nPort, unsigned int nLevel);

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

PLAYM4_API BOOL __stdcall PlayM4_OpenStreamAdvanced(LONG nPort, int nProtocolType, PLAYM4_SESSION_INFO* pstSessionInfo, DWORD nBufPoolSize);

#define R_ANGLE_0   -1  //锟斤拷锟斤拷转
#define R_ANGLE_L90  0  //锟斤拷锟斤拷锟斤拷转90锟斤拷
#define R_ANGLE_R90  1  //锟斤拷锟斤拷锟斤拷转90锟斤拷
#define R_ANGLE_180  2  //锟斤拷转180锟斤拷

PLAYM4_API BOOL __stdcall PlayM4_SetRotateAngle(LONG nPort, DWORD nRegionNum, DWORD dwType);

#ifndef PLAYM4_ADDITION_INFO_TAG
#define PLAYM4_ADDITION_INFO_TAG
typedef struct _PLAYM4_ADDITION_INFO_     //锟斤拷锟斤拷锟斤拷息锟结构
{
    BYTE*   pData;            //锟斤拷锟斤拷锟斤拷锟斤拷
    DWORD   dwDatalen;        //锟斤拷锟斤拷锟斤拷锟捷筹拷锟斤拷
    DWORD    dwDataType;        //锟斤拷锟斤拷锟斤拷锟斤拷
    DWORD    dwTimeStamp;    //锟斤拷锟绞憋拷锟斤拷
} PLAYM4_ADDITION_INFO;
#endif

//dwGroupIndex 锟斤拷约锟斤拷取值0~3锟斤拷锟斤拷一锟芥本取锟斤拷同锟斤拷只锟斤拷同锟斤拷closestream锟斤拷锟斤拷
PLAYM4_API BOOL __stdcall PlayM4_SetSycGroup(LONG nPort, DWORD dwGroupIndex);
//锟捷诧拷实锟街此猴拷锟斤拷锟斤拷同锟斤拷锟斤拷锟斤拷锟矫碉拷锟斤拷始时锟戒不一锟铰ｏ拷锟斤拷锟斤拷小锟斤拷时锟斤拷锟斤拷为锟斤拷锟斤拷锟斤拷悖伙拷锟斤拷只锟斤拷一路
PLAYM4_API BOOL __stdcall PlayM4_SetSycStartTime(LONG nPort, PLAYM4_SYSTEM_TIME *pstSystemTime);


// 锟斤拷锟斤拷实锟斤拷锟斤拷锟斤拷锟斤拷氐慕涌锟�
#ifndef FISH_EYE_TAG
#define FISH_EYE_TAG

// 锟斤拷装锟斤拷锟斤拷
typedef enum tagFECPlaceType
{
    FEC_PLACE_WALL    = 0x1,        // 锟斤拷装锟斤拷式        (锟斤拷锟斤拷水平)
    FEC_PLACE_FLOOR   = 0x2,        // 锟斤拷锟芥安装        (锟斤拷锟斤拷锟斤拷锟斤拷)
    FEC_PLACE_CEILING = 0x3,        // 锟斤拷装锟斤拷式        (锟斤拷锟斤拷锟斤拷锟斤拷)

}FECPLACETYPE;

typedef enum tagFECCorrectType
{
    FEC_CORRECT_PTZ = 0x100,        // PTZ
    FEC_CORRECT_180 = 0x200,        // 180锟饺斤拷锟斤拷  锟斤拷锟斤拷应2P锟斤拷
    FEC_CORRECT_360 = 0x300,        // 360全锟斤拷锟斤拷锟斤拷 锟斤拷锟斤拷应1P锟斤拷
    FEC_CORRECT_LAT = 0x400         //纬锟斤拷展锟斤拷

}FECCORRECTTYPE;

typedef struct tagCycleParam
{
    float    fRadiusLeft;    // 圆锟斤拷锟斤拷锟斤拷锟絏锟斤拷锟斤拷
    float    fRadiusRight;    // 圆锟斤拷锟斤拷锟揭憋拷X锟斤拷锟斤拷
    float   fRadiusTop;        // 圆锟斤拷锟斤拷锟较憋拷Y锟斤拷锟斤拷
    float   fRadiusBottom;    // 圆锟斤拷锟斤拷锟铰憋拷Y锟斤拷锟斤拷

}CYCLEPARAM;

typedef struct tagPTZParam
{
    float fPTZPositionX;        // PTZ 锟斤拷示锟斤拷锟斤拷锟斤拷位锟斤拷 X锟斤拷锟斤拷
    float fPTZPositionY;        // PTZ 锟斤拷示锟斤拷锟斤拷锟斤拷位锟斤拷 Y锟斤拷锟斤拷    

}PTZPARAM;


// 锟斤拷锟斤拷锟斤拷
/*********************************************
     

 ********************************************/


// 锟斤拷锟铰憋拷潜锟斤拷锟斤拷锟斤拷锟�
 

#define         FEC_UPDATE_RADIUS             0x1
#define         FEC_UPDATE_PTZZOOM             0x2
#define         FEC_UPDATE_WIDESCANOFFSET     0x4
#define         FEC_UPDATE_PTZPARAM             0x8


typedef struct tagFECParam
{

    
    unsigned int     nUpDateType;            // 锟斤拷锟铰碉拷锟斤拷锟斤拷

    unsigned int    nPlaceAndCorrect;        // 锟斤拷装锟斤拷式锟酵斤拷锟斤拷锟斤拷式锟斤拷只锟斤拷锟斤拷锟节伙拷取锟斤拷SetParam锟斤拷时锟斤拷锟斤拷效,锟斤拷值锟斤拷示锟斤拷装锟斤拷式锟酵斤拷锟斤拷锟斤拷式锟侥猴拷

    PTZPARAM        stPTZParam;                // PTZ 校锟斤拷锟侥诧拷锟斤拷

    CYCLEPARAM        stCycleParam;            // 锟斤拷锟斤拷图锟斤拷圆锟侥诧拷锟斤拷

    float            fZoom;                    // PTZ 锟斤拷示锟侥凤拷围锟斤拷锟斤拷

    float            fWideScanOffset;        // 180锟斤拷锟斤拷360锟斤拷校锟斤拷锟斤拷偏锟狡角讹拷

    int                nResver[16];            // 锟斤拷锟斤拷锟街讹拷

}FISHEYEPARAM;

typedef void (__stdcall * FISHEYE_CallBack )( void* pUser  , unsigned int  nSubPort , unsigned int nCBType , void * hDC ,   unsigned int nWidth , unsigned int nHeight); 

#endif
// 锟斤拷锟斤拷锟斤拷锟斤拷
PLAYM4_API BOOL __stdcall PlayM4_FEC_Enable(LONG nPort);

// 锟截憋拷锟斤拷锟斤拷模锟斤拷
PLAYM4_API BOOL __stdcall PlayM4_FEC_Disable(LONG nPort);

// 锟斤拷取锟斤拷锟桔斤拷锟斤拷锟斤拷锟斤拷锟接端匡拷 [1~31] 
PLAYM4_API BOOL  __stdcall PlayM4_FEC_GetPort(LONG nPort, unsigned int* nSubPort,FECPLACETYPE emPlaceType,FECCORRECTTYPE emCorrectType);

// 删锟斤拷锟斤拷锟桔斤拷锟斤拷锟斤拷锟斤拷锟接端匡拷
PLAYM4_API BOOL __stdcall PlayM4_FEC_DelPort(LONG nPort , unsigned int nSubPort);

// 锟斤拷锟斤拷锟斤拷锟桔斤拷锟斤拷锟斤拷锟斤拷
PLAYM4_API BOOL __stdcall PlayM4_FEC_SetParam(LONG nPort , unsigned int nSubPort , FISHEYEPARAM * pPara);

// 锟斤拷取锟斤拷锟桔斤拷锟斤拷锟斤拷锟斤拷
PLAYM4_API BOOL __stdcall PlayM4_FEC_GetParam(LONG nPort , unsigned int nSubPort , FISHEYEPARAM * pPara);

// 锟斤拷锟斤拷锟斤拷示锟斤拷锟节ｏ拷锟斤拷锟斤拷锟斤拷时锟叫伙拷
PLAYM4_API BOOL __stdcall PlayM4_FEC_SetWnd(LONG nPort , unsigned int nSubPort , void * hWnd);

// 锟斤拷锟斤拷锟斤拷锟桔达拷锟节的伙拷图锟截碉拷
PLAYM4_API BOOL __stdcall PlayM4_FEC_SetCallBack(LONG nPort , unsigned int nSubPort , FISHEYE_CallBack cbFunc , void * pUser);

//motionflow
PLAYM4_API BOOL __stdcall PlayM4_MotionFlow(LONG nPort, DWORD dwAdjustType);


//图锟斤拷锟斤拷强锟斤拷锟�
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

//锟斤拷锟矫关憋拷/锟斤拷锟斤拷模锟斤拷
//dwModuFlag锟斤拷应PLAYM4_VIE_MODULES锟斤拷,锟斤拷锟斤拷锟�
//锟斤拷锟斤拷锟斤拷模锟介开锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷模锟斤拷锟斤拷锟斤拷锟斤拷诩锟斤拷锟斤拷默锟较的诧拷锟斤拷;
//锟截憋拷模锟斤拷锟斤拷洗锟斤拷锟斤拷玫牟锟斤拷锟斤拷锟斤拷
//锟斤拷锟斤拷锟接口碉拷锟矫ｏ拷锟斤拷锟斤拷锟节该接口匡拷锟斤拷模锟斤拷螅环锟斤拷颍锟斤拷卮锟斤拷锟�
PLAYM4_API BOOL __stdcall PlayM4_VIE_SetModuConfig(LONG lPort,int nModuFlag,BOOL bEnable);

//锟斤拷锟斤拷图锟斤拷锟斤拷强锟斤拷锟斤拷NULL全图锟斤拷锟斤拷锟斤拷全图锟斤拷锟斤拷锟斤拷全图锟斤拷锟斤拷小锟斤拷锟斤拷16*16锟斤拷锟斤拷
//锟斤拷支锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟饺斤拷说4锟斤拷锟斤拷锟斤拷一锟斤拷锟芥本锟斤拷锟斤拷只支锟斤拷一锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟揭拷锟斤拷锟斤拷氐锟斤拷锟斤拷锟斤拷氐锟斤拷捅锟斤拷锟�
PLAYM4_API BOOL __stdcall PlayM4_VIE_SetRegion(LONG lPort,LONG lRegNum,RECT* pRect);

//锟斤拷取锟斤拷锟斤拷模锟斤拷
PLAYM4_API BOOL __stdcall PlayM4_VIE_GetModuConfig(LONG lPort,int* pdwModuFlag);

//锟斤拷锟矫诧拷锟斤拷
//未锟斤拷锟斤拷模锟斤拷牟锟斤拷锟斤拷锟斤拷帽锟斤拷锟斤拷锟�
PLAYM4_API BOOL __stdcall PlayM4_VIE_SetParaConfig(LONG lPort,PLAYM4_VIE_PARACONFIG* pParaConfig);

//锟斤拷取锟斤拷锟斤拷模锟斤拷牟锟斤拷锟�
PLAYM4_API BOOL __stdcall PlayM4_VIE_GetParaConfig(LONG lPort,PLAYM4_VIE_PARACONFIG* pParaConfig);

//锟斤拷锟斤拷频同锟斤拷锟接匡拷
PLAYM4_API BOOL __stdcall PlayM4_SyncToAudio(LONG nPort, BOOL bSyncToAudio);

// 私锟斤拷锟斤拷息模锟斤拷锟斤拷锟斤拷
typedef enum _PLAYM4_PRIDATA_RENDER
{    
    PLAYM4_RENDER_ANA_INTEL_DATA   = 0x00000001, //锟斤拷锟杰凤拷锟斤拷
    PLAYM4_RENDER_MD               = 0x00000002, //锟狡讹拷锟斤拷锟�
    PLAYM4_RENDER_ADD_POS          = 0x00000004, //POS锟斤拷息锟斤拷锟斤拷锟�        
    PLAYM4_RENDER_ADD_PIC          = 0x00000008, //图片锟斤拷锟斤拷
    PLAYM4_RENDER_FIRE_DETCET      = 0x00000010,  //锟饺筹拷锟斤拷锟斤拷息
    PLAYM4_RENDER_TEM              = 0x00000020,   //锟铰讹拷锟斤拷息
    PLAYM4_RENDER_TRACK_TEM        = 0x00000040,    //锟届迹锟斤拷息
    PLAYM4_RENDER_THERMAL          = 0x00000080 //锟斤拷锟斤拷锟斤拷锟斤拷锟教伙拷锟斤拷锟斤拷锟斤拷息
}PLAYM4_PRIDATA_RENDER;

typedef enum _PLAYM4_THERMAL_FLAG
{
    PLAYM4_THERMAL_FIREMASK = 0x00000001, //锟教伙拷锟斤拷锟斤拷
    PLAYM4_THERMAL_RULEGAS = 0x00000002, //锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
    PLAYM4_THERMAL_TARGETGAS = 0x00000004 //目锟斤拷锟斤拷锟斤拷锟斤拷
}PLAYM4_THERMAL_FLAG;

typedef enum _PLAYM4_FIRE_ALARM{
    PLAYM4_FIRE_FRAME_DIS           = 0x00000001, //锟斤拷锟斤拷锟斤拷示
    PLAYM4_FIRE_MAX_TEMP            = 0x00000002, //锟斤拷锟斤拷露锟�
    PLAYM4_FIRE_MAX_TEMP_POSITION   = 0x00000004, //锟斤拷锟斤拷露锟轿伙拷锟斤拷锟绞�
    PLAYM4_FIRE_DISTANCE            = 0x00000008, //锟斤拷锟斤拷露染锟斤拷锟絵PLAYM4_FIRE_ALARM
}PLAYM4_FIRE_ALARM;

typedef enum _PLAYM4_TEM_FLAG{
    PLAYM4_TEM_REGION_BOX           = 0x00000001, //锟斤拷锟斤拷锟�
    PLAYM4_TEM_REGION_LINE          = 0x00000002, //锟竭诧拷锟斤拷
    PLAYM4_TEM_REGION_POINT         = 0x00000004, //锟斤拷锟斤拷锟絵PLAYM4_TEM_FLAG
}PLAYM4_TEM_FLAG;

typedef enum _PLAYM4_TRACK_FLAG
{
    PLAYM4_TRACK_PEOPLE = 0x00000001, //锟剿轨迹
    PLAYM4_TRACK_VEHICLE = 0x00000002, //锟斤拷锟届迹
}PLAYM4_TRACK_FLAG;

typedef struct TI_PTZ_INFO_
{
    unsigned short dwDefVer;    //锟结构锟斤拷姹�
    unsigned short dwLength;    //PTZ_info锟斤拷锟饺ｏ拷锟斤拷8锟街斤拷为锟斤拷位
    DWORD          dwP;    //P锟斤拷0~3600锟斤拷
    DWORD          dwT;         //T锟斤拷0~3600锟斤拷
    DWORD          dwZ;         //Z锟斤拷0~3600锟斤拷
    BYTE        chFSMState; //锟斤拷锟斤拷状态
    BYTE           bClearFocusState; //锟桔斤拷锟斤拷锟斤拷状态锟斤拷0,1锟斤拷
    BYTE        reserved[6]; //6锟斤拷锟街节憋拷锟斤拷
}PTZ_INFO;


// 锟斤拷锟斤拷锟斤拷息锟斤拷锟斤拷
PLAYM4_API BOOL __stdcall PlayM4_RenderPrivateData(LONG nPort, int nIntelType, BOOL bTrue);

PLAYM4_API BOOL __stdcall PlayM4_RenderPrivateDataEx(LONG nPort, int nIntelType, int nSubType, BOOL bTrue);

// 锟斤拷锟斤拷锟斤拷锟斤拷锟截碉拷,nType=0锟斤拷示锟斤拷锟斤拷锟斤拷锟杰憋拷锟轿伙拷锟斤拷锟斤拷浠拷突氐锟斤拷锟絥Type=1锟斤拷示锟斤拷锟斤拷锟叫硷拷锟斤拷位锟斤拷锟斤拷锟截碉拷
PLAYM4_API BOOL __stdcall PlayM4_SetEncryptTypeCallBack(LONG nPort, DWORD nType,
                                                        void (CALLBACK* EncryptTypeCBFun)(long nPort, ENCRYPT_INFO* pEncryptInfo, long nUser, long nReserved2), long nUser);
//lType: 1 锟斤拷示锟斤拷取锟斤拷前锟斤拷示帧PTZ锟斤拷息锟斤拷锟斤拷锟截讹拷锟结构锟斤拷锟斤拷式锟芥储锟斤拷pInfo锟节ｏ拷plLen锟斤拷锟截筹拷锟斤拷锟斤拷息
PLAYM4_API BOOL __stdcall PlayM4_GetStreamAdditionalInfo(LONG nPort, LONG lType, BYTE* pInfo, LONG* plLen);


#endif //_PLAYM4_H_
