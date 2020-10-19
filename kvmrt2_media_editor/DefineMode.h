#pragma once

const bool OFFICIAL_RELEASE = false;

#define MY_ORGANIZATION_NAME "Woojin BSPSG"
#define MY_APPLICATION_NAME "MRT2 Media Editor"
#define MY_APP_VERSION "1.0"

#define ME_FOLDER_PATH "C:/PapisProgram/MediaEditor/"
#define ME_LOG_FOLDER_PATH "C:/PapisProgram/MediaEditor/Logs/"
#define INI_FILE_ME_DEFAULT "medefault.ini"
#define INI_FILE_ME_ACCOUNT "meaccount.ini"
#define WIZARD_FILE_PATH "C:/PapisProgram/FileUpload/UploadWizard2.exe"
#define OP_DATA_DB_PATH "C:/PapisProgram/PapisData/OP_DATA.DB"

enum AccountType
{
	ACC_UNDEFINED,
	ACC_ADMIN,
	ACC_NORMAL,
	ACC_GUEST,
};