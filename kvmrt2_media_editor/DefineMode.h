#pragma once

const bool OFFICIAL_RELEASE = false;


#define ME_FOLDER_PATH "C:/PapisProgram/MediaEditor/"
#define ME_LOG_FOLDER_PATH "C:/PapisProgram/MediaEditor/Logs/"

#define INI_FILE_ME_DEFAULT "medefault.ini"
#define INI_FILE_ME_ACCOUNT "meaccount.ini"
#define INI_FILE_ME_STNINFO "mestninfo.ini"

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

#define MSG_ID_WELCOME 1
#define MSG_ID_NEXT_BM 5000
#define MSG_ID_NEXT_EN 5500
#define MSG_ID_ARRIVING_BM 6000
#define MSG_ID_ARRIVING_EN 6000
#define MSG_ID_ARRIVAL_BM 7000
#define MSG_ID_ARRIVAL_BM 7500

#define MSG_ID_DOOR_OPEN_L 400
#define MSG_ID_DOOR_OPEN_R 401
#define MSG_ID_DOOR_OPEN_LR 402

#define MSG_ID_FINAL_FULL_BM 2000
#define MSG_ID_FINAL_FULL_EN 2500
#define MSG_ID_FINAL_PH1_BM 1000
#define MSG_ID_FINAL_PH1_EN 1500

#define MSG_ID_THANK_YOU 900
#define MSG_ID_SPECIAL1 3000
#define MSG_ID_SPECIAL2 3001
#define MSG_ID_SPECIAL3 3002
#define MSG_ID_SPECIAL4 3003
#define MSG_ID_SPECIAL5 3004

#define MSG_ID_EMG1 4000
#define MSG_ID_EMG2 4001
#define MSG_ID_EMG3 4002
#define MSG_ID_EMG4 4003
#define MSG_ID_EMG5 4004
#define MSG_ID_EMG6 4005
#define MSG_ID_EMG7 4006
#define MSG_ID_EMG8 4007
#define MSG_ID_EMG9 4008
#define MSG_ID_EMG10 4009
#define MSG_ID_EMG11 4010
#define MSG_ID_EMG12 4011
#define MSG_ID_EMG13 4012
#define MSG_ID_EMG14 4013
#define MSG_ID_EMG15 4014
#define MSG_ID_EMG16 4015

#define MSG_ID_EX101_BM 8101
#define MSG_ID_EX101_EN 8601
#define MSG_ID_EX104_BM 8104
#define MSG_ID_EX104_EN 8604
#define MSG_ID_EX108_BM 8108
#define MSG_ID_EX108_EN 8608
#define MSG_ID_EX113_BM 8113
#define MSG_ID_EX113_EN 8613
#define MSG_ID_EX117_BM 8117
#define MSG_ID_EX117_EN 8617
#define MSG_ID_EX120_BM 8120
#define MSG_ID_EX120_EN 8620
#define MSG_ID_EX123_BM 8123
#define MSG_ID_EX123_EN 8623
#define MSG_ID_EX124_BM 8124
#define MSG_ID_EX124_EN 8624
#define MSG_ID_EX129_BM 8129
#define MSG_ID_EX129_EN 8629
#define MSG_ID_EX141_BM 8141
#define MSG_ID_EX141_EN 8641







