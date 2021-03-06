#pragma once

const bool OFFICIAL_RELEASE = true;


#define ME_APP_PATH "C:/PapisProgram/MediaEditor/"
#define ME_LOG_PATH "C:/PapisProgram/MediaEditor/Logs/"
#define ME_DATA_PATH "C:/PapisProgram/PapisData/"

#define INI_FILE_ME_DEFAULT "medefault.ini"
#define INI_FILE_ME_ACCOUNT "meaccount.ini"
#define INI_FILE_ME_STNINFO "stationinfo.ini"

#define OP_DATA_DB_PATH "C:/PapisProgram/PapisData/TOTAL_PAPIS_DATA.DB"
#define OP_DISPLAY_DB_PATH "C:/PapisProgram/PapisData/OP_DISPLAY_DATA.DB"

//#define USING_DEBUG_WIZARD 

#ifdef USING_DEBUG_WIZARD
#define WIZARD_FILE_PATH "C:/Users/yaho/Documents/QtProject/build-UploadWizard2-Desktop_Qt_5_9_9_MinGW_32bit-Release/release/UploadWizard2.exe"
#else
#define WIZARD_FILE_PATH "C:/PapisProgram/FileUpload/UploadWizard2.exe"
#endif //USING_DEBUG_WIZARD

#ifdef SYS_WIN64
#define FFMPEG_FILE_PATH "C:/PapisProgram/MediaEditor/ffmpeg64/ffmpeg.exe"
#define FFPLAY_FILE_PATH "C:/PapisProgram/MediaEditor/ffmpeg64/ffplay.exe"
#else
#define FFMPEG_FILE_PATH "C:/PapisProgram/MediaEditor/ffmpeg32/ffmpeg.exe"
#define FFPLAY_FILE_PATH "C:/PapisProgram/MediaEditor/ffmpeg32/ffplay.exe"
#define FFPROB_FILE_PATH "C:/PapisProgram/MediaEditor/ffmpeg32/ffprobe.exe"
#endif // 



enum AccountType
{
	ACC_UNDEFINED,
	ACC_ADMIN,
	ACC_NORMAL,
	ACC_GUEST,
};

const int MSG_ID_NEXT_BM = 5000;
const int MSG_ID_NEXT_EN = 5500;
const int MSG_ID_ARRIVING_BM = 6000;
const int MSG_ID_ARRIVING_EN = 6500;
const int MSG_ID_ARRIVAL_BM = 7000;
const int MSG_ID_ARRIVAL_EN = 7500;

const int MSG_ID_WELCOME = 1;
const int MSG_ID_DOOR_OPEN_L = 400;
const int MSG_ID_DOOR_OPEN_R = 401;
const int MSG_ID_DOOR_OPEN_LR = 402;
const int MSG_ID_FINAL_FULL_BM = 2000;
const int MSG_ID_FINAL_FULL_EN = 2500;
const int MSG_ID_FINAL_PH1_BM = 1000;
const int MSG_ID_FINAL_PH1_EN = 1500;
const int MSG_ID_THANK_YOU = 900;

const int MSG_ID_EXCHANGE_BM_OFFSET = 8000;
const int MSG_ID_EXCHANGE_EN_OFFSET = 8500;

const int MSG_ID_SPECIAL_MIN_OFFSET = 3000; // including 3000
const int MSG_ID_SPECIAL_MAX_OFFSET = 3999; // including 3000

const int MSG_ID_EMG_MIN_OFFSET = 4000; // including 4000
const int MSG_ID_EMG_MAX_OFFSET = 4999; // including 4000





