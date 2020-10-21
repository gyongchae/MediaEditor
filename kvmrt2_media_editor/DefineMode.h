#pragma once

const bool OFFICIAL_RELEASE = true;


#define MY_ORGANIZATION_NAME "Woojin BSPSG"
#define MY_APPLICATION_NAME "MRT2 Media Editor"
#define MY_APP_VERSION "1.0.0"

#define ME_FOLDER_PATH "C:/PapisProgram/MediaEditor/"
#define ME_LOG_FOLDER_PATH "C:/PapisProgram/MediaEditor/Logs/"
#define INI_FILE_ME_DEFAULT "medefault.ini"
#define INI_FILE_ME_ACCOUNT "meaccount.ini"

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