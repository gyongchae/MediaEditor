#pragma once

const bool OFFICIAL_RELEASE = false;


#define ME_FOLDER_PATH "C:/PapisProgram/MediaEditor/"
#define ME_LOG_FOLDER_PATH "C:/PapisProgram/MediaEditor/Logs/"

#define INI_FILE_ME_DEFAULT "medefault.ini"
#define INI_FILE_ME_ACCOUNT "meaccount.ini"
#define INI_FILE_ME_STNINFO "stationinfo.ini"

#define OP_DATA_DB_PATH "C:/PapisProgram/PapisData/OP_DATA.DB"

//#define USING_DEBUG_WIZARD 

#ifdef USING_DEBUG_WIZARD
#define WIZARD_FILE_PATH "C:/Users/yaho/Documents/QtProject/build-UploadWizard2-Desktop_Qt_5_9_9_MinGW_32bit-Release/release/UploadWizard2.exe"
#else
#define WIZARD_FILE_PATH "C:/PapisProgram/FileUpload/UploadWizard2.exe"
#endif //USING_DEBUG_WIZARD


enum AccountType
{
	ACC_UNDEFINED,
	ACC_ADMIN,
	ACC_NORMAL,
	ACC_GUEST,
};

#define MSG_ID_NEXT_BM 5000
#define MSG_ID_NEXT_EN 5500
#define MSG_ID_ARRIVING_BM 6000
#define MSG_ID_ARRIVING_EN 6500
#define MSG_ID_ARRIVAL_BM 7000
#define MSG_ID_ARRIVAL_EN 7500

#define MSG_ID_WELCOME 1
#define MSG_ID_DOOR_OPEN_L 400
#define MSG_ID_DOOR_OPEN_R 401
#define MSG_ID_DOOR_OPEN_LR 402
#define MSG_ID_FINAL_FULL_BM 2000
#define MSG_ID_FINAL_FULL_EN 2500
#define MSG_ID_FINAL_PH1_BM 1000
#define MSG_ID_FINAL_PH1_EN 1500
#define MSG_ID_THANK_YOU 900

#define MSG_ID_EXCHANGE_BM_OFFSET 8000
#define MSG_ID_EXCHANGE_EN_OFFSET 8500

#define MSG_ID_SPECIAL_OFFSET 3000 // including 3000
#define MSG_ID_EMG_OFFSET 4000 // including 4000





