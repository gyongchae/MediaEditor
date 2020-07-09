/********************************************************************************
** Form generated from reading UI file 'kvmrt2_media_editor.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KVMRT2_MEDIA_EDITOR_H
#define UI_KVMRT2_MEDIA_EDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_kvmrt2_media_editorClass
{
public:
    QAction *actionSave;
    QAction *actionSetting;
    QAction *actionAudioVideoPool;
    QAction *actionFontPool;
    QAction *actionTextPool;
    QAction *actionRouteMapPool;
    QAction *actionBitmapPool;
    QAction *actionImageListPool;
    QAction *actionLedPool;
    QAction *actionDisplayListPool;
    QAction *actionAboutQt;
    QAction *actionAboutME;
    QAction *actionExit;
    QAction *actionNew;
    QAction *actionLoad;
    QAction *actionUpdate;
    QAction *actionLicenseInfo;
    QAction *actioncanvas_test;
    QAction *actionTestCanvas;
    QWidget *centralWidget;
    QGridLayout *gridLayout_21;
    QTabWidget *tabMain;
    QWidget *tabStation;
    QGridLayout *gridLayout_4;
    QSplitter *splitter;
    QGroupBox *gbStationName;
    QGridLayout *gridLayout;
    QTableView *m_tblStationInformation;
    QGroupBox *gbDistance;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QRadioButton *rbInOrder;
    QRadioButton *rbInReverseOrder;
    QRadioButton *rbCustomOrder;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnRefreshDistanceTable;
    QTableView *m_tblStationDistance;
    QWidget *tabRoute;
    QGridLayout *gridLayout_11;
    QSplitter *splitter_4;
    QSplitter *splitter_3;
    QGroupBox *gbStopPattern;
    QGridLayout *gridLayout_8;
    QTableView *m_tblStopPtnHeader;
    QGroupBox *gbTrainRoute;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnRouteAutoAdd;
    QPushButton *btnDelRoutes;
    QSpacerItem *horizontalSpacer_2;
    QTableView *m_tblStopPtnRoutes;
    QSplitter *splitter_2;
    QGroupBox *gbTrainNumber;
    QGridLayout *gridLayout_7;
    QTableView *m_tblTrainNumber;
    QGroupBox *gbRouteEvent;
    QGridLayout *gridLayout_10;
    QTableView *m_tblEventLists;
    QWidget *tabScreen;
    QGridLayout *gridLayout_19;
    QSplitter *splitter_7;
    QGroupBox *groupBox_15;
    QGridLayout *gridLayout_18;
    QTableView *m_tblPIDContents;
    QGroupBox *groupBox_16;
    QGridLayout *gridLayout_3;
    QTableView *m_tblPIDIndexList;
    QWidget *tabAudio;
    QGridLayout *gridLayout_17;
    QSplitter *splitter_6;
    QGroupBox *groupBox_12;
    QGridLayout *gridLayout_15;
    QTableView *m_tblAudioStationName;
    QGroupBox *groupBox_13;
    QGridLayout *gridLayout_16;
    QTableView *m_tblAudioTotal;
    QWidget *tabVideo;
    QGridLayout *gridLayout_14;
    QSplitter *splitter_5;
    QGroupBox *groupBox_10;
    QGridLayout *gridLayout_13;
    QTableView *m_tblVideoDeviceGroup;
    QGroupBox *groupBox_9;
    QGridLayout *gridLayout_12;
    QTableView *m_tblVideoPlayList;
    QWidget *tabDataTag;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_20;
    QTableView *m_tblEditorTagTable;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuFilePool;
    QMenu *menuDisplayConfig;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *kvmrt2_media_editorClass)
    {
        if (kvmrt2_media_editorClass->objectName().isEmpty())
            kvmrt2_media_editorClass->setObjectName(QStringLiteral("kvmrt2_media_editorClass"));
        kvmrt2_media_editorClass->resize(1140, 839);
        QIcon icon;
        icon.addFile(QStringLiteral("Resources/More Kidcons Win/Icons/Kitty.ico"), QSize(), QIcon::Normal, QIcon::Off);
        kvmrt2_media_editorClass->setWindowIcon(icon);
        actionSave = new QAction(kvmrt2_media_editorClass);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        QIcon icon1;
        icon1.addFile(QStringLiteral("Resources/More Kidcons Win/Icons/Barn.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon1);
        actionSetting = new QAction(kvmrt2_media_editorClass);
        actionSetting->setObjectName(QStringLiteral("actionSetting"));
        QIcon icon2;
        icon2.addFile(QStringLiteral("Resources/More Kidcons Win/Icons/Baseball Diamond.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionSetting->setIcon(icon2);
        actionAudioVideoPool = new QAction(kvmrt2_media_editorClass);
        actionAudioVideoPool->setObjectName(QStringLiteral("actionAudioVideoPool"));
        QIcon icon3;
        icon3.addFile(QStringLiteral("Resources/More Kidcons Win/Icons/Bubble Stuff.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionAudioVideoPool->setIcon(icon3);
        actionFontPool = new QAction(kvmrt2_media_editorClass);
        actionFontPool->setObjectName(QStringLiteral("actionFontPool"));
        QIcon icon4;
        icon4.addFile(QStringLiteral("Resources/More Kidcons Win/Icons/Bumble Bee.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionFontPool->setIcon(icon4);
        actionTextPool = new QAction(kvmrt2_media_editorClass);
        actionTextPool->setObjectName(QStringLiteral("actionTextPool"));
        QIcon icon5;
        icon5.addFile(QStringLiteral("Resources/More Kidcons Win/Icons/Bunny.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionTextPool->setIcon(icon5);
        actionRouteMapPool = new QAction(kvmrt2_media_editorClass);
        actionRouteMapPool->setObjectName(QStringLiteral("actionRouteMapPool"));
        QIcon icon6;
        icon6.addFile(QStringLiteral("Resources/More Kidcons Win/Icons/Cat Toy.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionRouteMapPool->setIcon(icon6);
        actionBitmapPool = new QAction(kvmrt2_media_editorClass);
        actionBitmapPool->setObjectName(QStringLiteral("actionBitmapPool"));
        QIcon icon7;
        icon7.addFile(QStringLiteral("Resources/More Kidcons Win/Icons/Cheeseburger.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionBitmapPool->setIcon(icon7);
        actionImageListPool = new QAction(kvmrt2_media_editorClass);
        actionImageListPool->setObjectName(QStringLiteral("actionImageListPool"));
        QIcon icon8;
        icon8.addFile(QStringLiteral("Resources/More Kidcons Win/Icons/Compass.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionImageListPool->setIcon(icon8);
        actionLedPool = new QAction(kvmrt2_media_editorClass);
        actionLedPool->setObjectName(QStringLiteral("actionLedPool"));
        QIcon icon9;
        icon9.addFile(QStringLiteral("Resources/More Kidcons Win/Icons/Cookie Jar.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionLedPool->setIcon(icon9);
        actionDisplayListPool = new QAction(kvmrt2_media_editorClass);
        actionDisplayListPool->setObjectName(QStringLiteral("actionDisplayListPool"));
        QIcon icon10;
        icon10.addFile(QStringLiteral("Resources/More Kidcons Win/Icons/Cupid's Arrow.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionDisplayListPool->setIcon(icon10);
        actionAboutQt = new QAction(kvmrt2_media_editorClass);
        actionAboutQt->setObjectName(QStringLiteral("actionAboutQt"));
        QIcon icon11;
        icon11.addFile(QStringLiteral("Resources/More Kidcons Win/Icons/Draw Four.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionAboutQt->setIcon(icon11);
        actionAboutME = new QAction(kvmrt2_media_editorClass);
        actionAboutME->setObjectName(QStringLiteral("actionAboutME"));
        actionAboutME->setIcon(icon);
        actionExit = new QAction(kvmrt2_media_editorClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        QIcon icon12;
        icon12.addFile(QStringLiteral("Resources/More Kidcons Win/Icons/Flower.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon12);
        actionNew = new QAction(kvmrt2_media_editorClass);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        QIcon icon13;
        icon13.addFile(QStringLiteral("Resources/More Kidcons Win/Icons/Football Helmet.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon13);
        actionLoad = new QAction(kvmrt2_media_editorClass);
        actionLoad->setObjectName(QStringLiteral("actionLoad"));
        QIcon icon14;
        icon14.addFile(QStringLiteral("Resources/More Kidcons Win/Icons/Football.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoad->setIcon(icon14);
        actionUpdate = new QAction(kvmrt2_media_editorClass);
        actionUpdate->setObjectName(QStringLiteral("actionUpdate"));
        QIcon icon15;
        icon15.addFile(QStringLiteral("Resources/More Kidcons Win/Icons/Gingerbread Man.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionUpdate->setIcon(icon15);
        actionLicenseInfo = new QAction(kvmrt2_media_editorClass);
        actionLicenseInfo->setObjectName(QStringLiteral("actionLicenseInfo"));
        QIcon icon16;
        icon16.addFile(QStringLiteral("Resources/More Kidcons Win/Icons/Red Book.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionLicenseInfo->setIcon(icon16);
        actioncanvas_test = new QAction(kvmrt2_media_editorClass);
        actioncanvas_test->setObjectName(QStringLiteral("actioncanvas_test"));
        actionTestCanvas = new QAction(kvmrt2_media_editorClass);
        actionTestCanvas->setObjectName(QStringLiteral("actionTestCanvas"));
        centralWidget = new QWidget(kvmrt2_media_editorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_21 = new QGridLayout(centralWidget);
        gridLayout_21->setSpacing(6);
        gridLayout_21->setContentsMargins(11, 11, 11, 11);
        gridLayout_21->setObjectName(QStringLiteral("gridLayout_21"));
        tabMain = new QTabWidget(centralWidget);
        tabMain->setObjectName(QStringLiteral("tabMain"));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        tabMain->setFont(font);
        tabMain->setTabShape(QTabWidget::Triangular);
        tabMain->setIconSize(QSize(20, 20));
        tabStation = new QWidget();
        tabStation->setObjectName(QStringLiteral("tabStation"));
        gridLayout_4 = new QGridLayout(tabStation);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        splitter = new QSplitter(tabStation);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        gbStationName = new QGroupBox(splitter);
        gbStationName->setObjectName(QStringLiteral("gbStationName"));
        gridLayout = new QGridLayout(gbStationName);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        m_tblStationInformation = new QTableView(gbStationName);
        m_tblStationInformation->setObjectName(QStringLiteral("m_tblStationInformation"));

        gridLayout->addWidget(m_tblStationInformation, 0, 1, 1, 1);

        splitter->addWidget(gbStationName);
        gbDistance = new QGroupBox(splitter);
        gbDistance->setObjectName(QStringLiteral("gbDistance"));
        verticalLayout = new QVBoxLayout(gbDistance);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        rbInOrder = new QRadioButton(gbDistance);
        rbInOrder->setObjectName(QStringLiteral("rbInOrder"));

        horizontalLayout->addWidget(rbInOrder);

        rbInReverseOrder = new QRadioButton(gbDistance);
        rbInReverseOrder->setObjectName(QStringLiteral("rbInReverseOrder"));

        horizontalLayout->addWidget(rbInReverseOrder);

        rbCustomOrder = new QRadioButton(gbDistance);
        rbCustomOrder->setObjectName(QStringLiteral("rbCustomOrder"));

        horizontalLayout->addWidget(rbCustomOrder);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnRefreshDistanceTable = new QPushButton(gbDistance);
        btnRefreshDistanceTable->setObjectName(QStringLiteral("btnRefreshDistanceTable"));

        horizontalLayout->addWidget(btnRefreshDistanceTable);


        verticalLayout->addLayout(horizontalLayout);

        m_tblStationDistance = new QTableView(gbDistance);
        m_tblStationDistance->setObjectName(QStringLiteral("m_tblStationDistance"));

        verticalLayout->addWidget(m_tblStationDistance);

        verticalLayout->setStretch(1, 1);
        splitter->addWidget(gbDistance);

        gridLayout_4->addWidget(splitter, 0, 0, 1, 1);

        QIcon icon17;
        icon17.addFile(QStringLiteral("Resources/IF Halloween 99 Win/Icons/Boris.ico"), QSize(), QIcon::Normal, QIcon::Off);
        tabMain->addTab(tabStation, icon17, QString());
        tabRoute = new QWidget();
        tabRoute->setObjectName(QStringLiteral("tabRoute"));
        gridLayout_11 = new QGridLayout(tabRoute);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        splitter_4 = new QSplitter(tabRoute);
        splitter_4->setObjectName(QStringLiteral("splitter_4"));
        splitter_4->setOrientation(Qt::Vertical);
        splitter_3 = new QSplitter(splitter_4);
        splitter_3->setObjectName(QStringLiteral("splitter_3"));
        splitter_3->setOrientation(Qt::Horizontal);
        gbStopPattern = new QGroupBox(splitter_3);
        gbStopPattern->setObjectName(QStringLiteral("gbStopPattern"));
        gridLayout_8 = new QGridLayout(gbStopPattern);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        m_tblStopPtnHeader = new QTableView(gbStopPattern);
        m_tblStopPtnHeader->setObjectName(QStringLiteral("m_tblStopPtnHeader"));

        gridLayout_8->addWidget(m_tblStopPtnHeader, 0, 0, 1, 1);

        splitter_3->addWidget(gbStopPattern);
        gbTrainRoute = new QGroupBox(splitter_3);
        gbTrainRoute->setObjectName(QStringLiteral("gbTrainRoute"));
        verticalLayout_2 = new QVBoxLayout(gbTrainRoute);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        btnRouteAutoAdd = new QPushButton(gbTrainRoute);
        btnRouteAutoAdd->setObjectName(QStringLiteral("btnRouteAutoAdd"));

        horizontalLayout_2->addWidget(btnRouteAutoAdd);

        btnDelRoutes = new QPushButton(gbTrainRoute);
        btnDelRoutes->setObjectName(QStringLiteral("btnDelRoutes"));

        horizontalLayout_2->addWidget(btnDelRoutes);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_2);

        m_tblStopPtnRoutes = new QTableView(gbTrainRoute);
        m_tblStopPtnRoutes->setObjectName(QStringLiteral("m_tblStopPtnRoutes"));

        verticalLayout_2->addWidget(m_tblStopPtnRoutes);

        verticalLayout_2->setStretch(1, 1);
        splitter_3->addWidget(gbTrainRoute);
        splitter_4->addWidget(splitter_3);
        splitter_2 = new QSplitter(splitter_4);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        gbTrainNumber = new QGroupBox(splitter_2);
        gbTrainNumber->setObjectName(QStringLiteral("gbTrainNumber"));
        gridLayout_7 = new QGridLayout(gbTrainNumber);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        m_tblTrainNumber = new QTableView(gbTrainNumber);
        m_tblTrainNumber->setObjectName(QStringLiteral("m_tblTrainNumber"));

        gridLayout_7->addWidget(m_tblTrainNumber, 0, 0, 1, 1);

        splitter_2->addWidget(gbTrainNumber);
        gbRouteEvent = new QGroupBox(splitter_2);
        gbRouteEvent->setObjectName(QStringLiteral("gbRouteEvent"));
        gridLayout_10 = new QGridLayout(gbRouteEvent);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        m_tblEventLists = new QTableView(gbRouteEvent);
        m_tblEventLists->setObjectName(QStringLiteral("m_tblEventLists"));

        gridLayout_10->addWidget(m_tblEventLists, 0, 0, 1, 1);

        splitter_2->addWidget(gbRouteEvent);
        splitter_4->addWidget(splitter_2);

        gridLayout_11->addWidget(splitter_4, 0, 0, 1, 1);

        QIcon icon18;
        icon18.addFile(QStringLiteral("Resources/IF Halloween 99 Win/Icons/Drac.ico"), QSize(), QIcon::Normal, QIcon::Off);
        tabMain->addTab(tabRoute, icon18, QString());
        tabScreen = new QWidget();
        tabScreen->setObjectName(QStringLiteral("tabScreen"));
        gridLayout_19 = new QGridLayout(tabScreen);
        gridLayout_19->setSpacing(6);
        gridLayout_19->setContentsMargins(11, 11, 11, 11);
        gridLayout_19->setObjectName(QStringLiteral("gridLayout_19"));
        splitter_7 = new QSplitter(tabScreen);
        splitter_7->setObjectName(QStringLiteral("splitter_7"));
        splitter_7->setOrientation(Qt::Horizontal);
        groupBox_15 = new QGroupBox(splitter_7);
        groupBox_15->setObjectName(QStringLiteral("groupBox_15"));
        gridLayout_18 = new QGridLayout(groupBox_15);
        gridLayout_18->setSpacing(6);
        gridLayout_18->setContentsMargins(11, 11, 11, 11);
        gridLayout_18->setObjectName(QStringLiteral("gridLayout_18"));
        m_tblPIDContents = new QTableView(groupBox_15);
        m_tblPIDContents->setObjectName(QStringLiteral("m_tblPIDContents"));

        gridLayout_18->addWidget(m_tblPIDContents, 0, 0, 1, 1);

        splitter_7->addWidget(groupBox_15);
        groupBox_16 = new QGroupBox(splitter_7);
        groupBox_16->setObjectName(QStringLiteral("groupBox_16"));
        gridLayout_3 = new QGridLayout(groupBox_16);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        m_tblPIDIndexList = new QTableView(groupBox_16);
        m_tblPIDIndexList->setObjectName(QStringLiteral("m_tblPIDIndexList"));

        gridLayout_3->addWidget(m_tblPIDIndexList, 0, 0, 1, 1);

        splitter_7->addWidget(groupBox_16);

        gridLayout_19->addWidget(splitter_7, 0, 0, 1, 1);

        QIcon icon19;
        icon19.addFile(QStringLiteral("Resources/IF Halloween 99 Win/Icons/Frankie.ico"), QSize(), QIcon::Normal, QIcon::Off);
        tabMain->addTab(tabScreen, icon19, QString());
        tabAudio = new QWidget();
        tabAudio->setObjectName(QStringLiteral("tabAudio"));
        gridLayout_17 = new QGridLayout(tabAudio);
        gridLayout_17->setSpacing(6);
        gridLayout_17->setContentsMargins(11, 11, 11, 11);
        gridLayout_17->setObjectName(QStringLiteral("gridLayout_17"));
        splitter_6 = new QSplitter(tabAudio);
        splitter_6->setObjectName(QStringLiteral("splitter_6"));
        splitter_6->setOrientation(Qt::Horizontal);
        groupBox_12 = new QGroupBox(splitter_6);
        groupBox_12->setObjectName(QStringLiteral("groupBox_12"));
        gridLayout_15 = new QGridLayout(groupBox_12);
        gridLayout_15->setSpacing(6);
        gridLayout_15->setContentsMargins(11, 11, 11, 11);
        gridLayout_15->setObjectName(QStringLiteral("gridLayout_15"));
        m_tblAudioStationName = new QTableView(groupBox_12);
        m_tblAudioStationName->setObjectName(QStringLiteral("m_tblAudioStationName"));

        gridLayout_15->addWidget(m_tblAudioStationName, 0, 0, 1, 1);

        splitter_6->addWidget(groupBox_12);
        groupBox_13 = new QGroupBox(splitter_6);
        groupBox_13->setObjectName(QStringLiteral("groupBox_13"));
        gridLayout_16 = new QGridLayout(groupBox_13);
        gridLayout_16->setSpacing(6);
        gridLayout_16->setContentsMargins(11, 11, 11, 11);
        gridLayout_16->setObjectName(QStringLiteral("gridLayout_16"));
        m_tblAudioTotal = new QTableView(groupBox_13);
        m_tblAudioTotal->setObjectName(QStringLiteral("m_tblAudioTotal"));

        gridLayout_16->addWidget(m_tblAudioTotal, 0, 0, 1, 1);

        splitter_6->addWidget(groupBox_13);

        gridLayout_17->addWidget(splitter_6, 0, 0, 1, 1);

        QIcon icon20;
        icon20.addFile(QStringLiteral("Resources/IF Halloween 99 Win/Icons/Gill.ico"), QSize(), QIcon::Normal, QIcon::Off);
        tabMain->addTab(tabAudio, icon20, QString());
        tabVideo = new QWidget();
        tabVideo->setObjectName(QStringLiteral("tabVideo"));
        gridLayout_14 = new QGridLayout(tabVideo);
        gridLayout_14->setSpacing(6);
        gridLayout_14->setContentsMargins(11, 11, 11, 11);
        gridLayout_14->setObjectName(QStringLiteral("gridLayout_14"));
        splitter_5 = new QSplitter(tabVideo);
        splitter_5->setObjectName(QStringLiteral("splitter_5"));
        splitter_5->setOrientation(Qt::Horizontal);
        groupBox_10 = new QGroupBox(splitter_5);
        groupBox_10->setObjectName(QStringLiteral("groupBox_10"));
        gridLayout_13 = new QGridLayout(groupBox_10);
        gridLayout_13->setSpacing(6);
        gridLayout_13->setContentsMargins(11, 11, 11, 11);
        gridLayout_13->setObjectName(QStringLiteral("gridLayout_13"));
        m_tblVideoDeviceGroup = new QTableView(groupBox_10);
        m_tblVideoDeviceGroup->setObjectName(QStringLiteral("m_tblVideoDeviceGroup"));

        gridLayout_13->addWidget(m_tblVideoDeviceGroup, 0, 0, 1, 1);

        splitter_5->addWidget(groupBox_10);
        groupBox_9 = new QGroupBox(splitter_5);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        gridLayout_12 = new QGridLayout(groupBox_9);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
        m_tblVideoPlayList = new QTableView(groupBox_9);
        m_tblVideoPlayList->setObjectName(QStringLiteral("m_tblVideoPlayList"));

        gridLayout_12->addWidget(m_tblVideoPlayList, 0, 0, 1, 1);

        splitter_5->addWidget(groupBox_9);

        gridLayout_14->addWidget(splitter_5, 0, 0, 1, 1);

        QIcon icon21;
        icon21.addFile(QStringLiteral("Resources/IF Halloween 99 Win/Icons/Wolfie.ico"), QSize(), QIcon::Normal, QIcon::Off);
        tabMain->addTab(tabVideo, icon21, QString());
        tabDataTag = new QWidget();
        tabDataTag->setObjectName(QStringLiteral("tabDataTag"));
        gridLayout_2 = new QGridLayout(tabDataTag);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        groupBox = new QGroupBox(tabDataTag);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_20 = new QGridLayout(groupBox);
        gridLayout_20->setSpacing(6);
        gridLayout_20->setContentsMargins(11, 11, 11, 11);
        gridLayout_20->setObjectName(QStringLiteral("gridLayout_20"));
        m_tblEditorTagTable = new QTableView(groupBox);
        m_tblEditorTagTable->setObjectName(QStringLiteral("m_tblEditorTagTable"));

        gridLayout_20->addWidget(m_tblEditorTagTable, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 0, 1, 1);

        QIcon icon22;
        icon22.addFile(QStringLiteral("Resources/IF Halloween 99 Win/Icons/ghost1.ico"), QSize(), QIcon::Normal, QIcon::Off);
        tabMain->addTab(tabDataTag, icon22, QString());

        gridLayout_21->addWidget(tabMain, 0, 0, 1, 1);

        kvmrt2_media_editorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(kvmrt2_media_editorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1140, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuFilePool = new QMenu(menuBar);
        menuFilePool->setObjectName(QStringLiteral("menuFilePool"));
        menuDisplayConfig = new QMenu(menuBar);
        menuDisplayConfig->setObjectName(QStringLiteral("menuDisplayConfig"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        kvmrt2_media_editorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(kvmrt2_media_editorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setMovable(false);
        mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        kvmrt2_media_editorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(kvmrt2_media_editorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        kvmrt2_media_editorClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuFilePool->menuAction());
        menuBar->addAction(menuDisplayConfig->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSetting);
        menuFile->addAction(actionUpdate);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuFile->addAction(actionTestCanvas);
        menuFilePool->addAction(actionFontPool);
        menuFilePool->addAction(actionAudioVideoPool);
        menuFilePool->addAction(actionTextPool);
        menuFilePool->addAction(actionBitmapPool);
        menuDisplayConfig->addAction(actionImageListPool);
        menuDisplayConfig->addSeparator();
        menuDisplayConfig->addAction(actionDisplayListPool);
        menuDisplayConfig->addAction(actionRouteMapPool);
        menuDisplayConfig->addSeparator();
        menuDisplayConfig->addAction(actionLedPool);
        menuHelp->addAction(actionAboutME);
        menuHelp->addAction(actionAboutQt);
        menuHelp->addAction(actionLicenseInfo);
        mainToolBar->addAction(actionNew);
        mainToolBar->addAction(actionSave);
        mainToolBar->addAction(actionLoad);
        mainToolBar->addAction(actionSetting);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionFontPool);
        mainToolBar->addAction(actionAudioVideoPool);
        mainToolBar->addAction(actionTextPool);
        mainToolBar->addAction(actionBitmapPool);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionImageListPool);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionDisplayListPool);
        mainToolBar->addAction(actionRouteMapPool);
        mainToolBar->addAction(actionLedPool);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionUpdate);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionExit);

        retranslateUi(kvmrt2_media_editorClass);

        tabMain->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(kvmrt2_media_editorClass);
    } // setupUi

    void retranslateUi(QMainWindow *kvmrt2_media_editorClass)
    {
        kvmrt2_media_editorClass->setWindowTitle(QApplication::translate("kvmrt2_media_editorClass", "M E D I A E D I T O R", Q_NULLPTR));
        actionSave->setText(QApplication::translate("kvmrt2_media_editorClass", "Save", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionSave->setShortcut(QApplication::translate("kvmrt2_media_editorClass", "F5", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionSetting->setText(QApplication::translate("kvmrt2_media_editorClass", "Setting", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionSetting->setToolTip(QApplication::translate("kvmrt2_media_editorClass", "ME Setting", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionAudioVideoPool->setText(QApplication::translate("kvmrt2_media_editorClass", "Audio && Video", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionAudioVideoPool->setToolTip(QApplication::translate("kvmrt2_media_editorClass", "Audio and Video", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionFontPool->setText(QApplication::translate("kvmrt2_media_editorClass", "Font", Q_NULLPTR));
        actionTextPool->setText(QApplication::translate("kvmrt2_media_editorClass", "Text", Q_NULLPTR));
        actionRouteMapPool->setText(QApplication::translate("kvmrt2_media_editorClass", "Route Map", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionRouteMapPool->setToolTip(QApplication::translate("kvmrt2_media_editorClass", "Route Map", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionBitmapPool->setText(QApplication::translate("kvmrt2_media_editorClass", "Bitmap", Q_NULLPTR));
        actionImageListPool->setText(QApplication::translate("kvmrt2_media_editorClass", "Image List", Q_NULLPTR));
        actionLedPool->setText(QApplication::translate("kvmrt2_media_editorClass", "L.E.D", Q_NULLPTR));
        actionDisplayListPool->setText(QApplication::translate("kvmrt2_media_editorClass", "DRMD && PID", Q_NULLPTR));
        actionAboutQt->setText(QApplication::translate("kvmrt2_media_editorClass", "About &Qt", Q_NULLPTR));
        actionAboutME->setText(QApplication::translate("kvmrt2_media_editorClass", "About &ME", Q_NULLPTR));
        actionExit->setText(QApplication::translate("kvmrt2_media_editorClass", "Exit Program", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionExit->setToolTip(QApplication::translate("kvmrt2_media_editorClass", "Exit Program", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionNew->setText(QApplication::translate("kvmrt2_media_editorClass", "New", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionNew->setShortcut(QApplication::translate("kvmrt2_media_editorClass", "Ctrl+N", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionLoad->setText(QApplication::translate("kvmrt2_media_editorClass", "Load", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionLoad->setShortcut(QApplication::translate("kvmrt2_media_editorClass", "Ctrl+O", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionUpdate->setText(QApplication::translate("kvmrt2_media_editorClass", "DB Update", Q_NULLPTR));
        actionLicenseInfo->setText(QApplication::translate("kvmrt2_media_editorClass", "License Info", Q_NULLPTR));
        actioncanvas_test->setText(QApplication::translate("kvmrt2_media_editorClass", "canvas test", Q_NULLPTR));
        actionTestCanvas->setText(QApplication::translate("kvmrt2_media_editorClass", "canvas test", Q_NULLPTR));
        gbStationName->setTitle(QApplication::translate("kvmrt2_media_editorClass", "Station Name", Q_NULLPTR));
        gbDistance->setTitle(QApplication::translate("kvmrt2_media_editorClass", "Station Pair (Distance table)", Q_NULLPTR));
        rbInOrder->setText(QApplication::translate("kvmrt2_media_editorClass", "Auto 1", Q_NULLPTR));
        rbInReverseOrder->setText(QApplication::translate("kvmrt2_media_editorClass", "Auto 2", Q_NULLPTR));
        rbCustomOrder->setText(QApplication::translate("kvmrt2_media_editorClass", "Custom", Q_NULLPTR));
        btnRefreshDistanceTable->setText(QApplication::translate("kvmrt2_media_editorClass", "Fill Description", Q_NULLPTR));
        tabMain->setTabText(tabMain->indexOf(tabStation), QApplication::translate("kvmrt2_media_editorClass", "Station Information", Q_NULLPTR));
        gbStopPattern->setTitle(QApplication::translate("kvmrt2_media_editorClass", "Stop Pattern", Q_NULLPTR));
        gbTrainRoute->setTitle(QApplication::translate("kvmrt2_media_editorClass", "Train Route", Q_NULLPTR));
        btnRouteAutoAdd->setText(QApplication::translate("kvmrt2_media_editorClass", "Auto Add", Q_NULLPTR));
        btnDelRoutes->setText(QApplication::translate("kvmrt2_media_editorClass", "Delete All", Q_NULLPTR));
        gbTrainNumber->setTitle(QApplication::translate("kvmrt2_media_editorClass", "Train Number", Q_NULLPTR));
        gbRouteEvent->setTitle(QApplication::translate("kvmrt2_media_editorClass", "Route Event List", Q_NULLPTR));
        tabMain->setTabText(tabMain->indexOf(tabRoute), QApplication::translate("kvmrt2_media_editorClass", "Train Route Information", Q_NULLPTR));
        groupBox_15->setTitle(QApplication::translate("kvmrt2_media_editorClass", "Display List Name", Q_NULLPTR));
        groupBox_16->setTitle(QApplication::translate("kvmrt2_media_editorClass", "Display List", Q_NULLPTR));
        tabMain->setTabText(tabMain->indexOf(tabScreen), QApplication::translate("kvmrt2_media_editorClass", "Screen Contents", Q_NULLPTR));
        groupBox_12->setTitle(QApplication::translate("kvmrt2_media_editorClass", "Station Name Audio", Q_NULLPTR));
        groupBox_13->setTitle(QApplication::translate("kvmrt2_media_editorClass", "Audio Play List", Q_NULLPTR));
        tabMain->setTabText(tabMain->indexOf(tabAudio), QApplication::translate("kvmrt2_media_editorClass", "Audio Contents", Q_NULLPTR));
        groupBox_10->setTitle(QApplication::translate("kvmrt2_media_editorClass", "Video Play Group", Q_NULLPTR));
        groupBox_9->setTitle(QApplication::translate("kvmrt2_media_editorClass", "Video Play List", Q_NULLPTR));
        tabMain->setTabText(tabMain->indexOf(tabVideo), QApplication::translate("kvmrt2_media_editorClass", "Video Contents", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("kvmrt2_media_editorClass", "Data Tag (Editor tag table)", Q_NULLPTR));
        tabMain->setTabText(tabMain->indexOf(tabDataTag), QApplication::translate("kvmrt2_media_editorClass", "Data Tag", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("kvmrt2_media_editorClass", "File", Q_NULLPTR));
        menuFilePool->setTitle(QApplication::translate("kvmrt2_media_editorClass", "Data File Pool", Q_NULLPTR));
        menuDisplayConfig->setTitle(QApplication::translate("kvmrt2_media_editorClass", "Display Configuration", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("kvmrt2_media_editorClass", "Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class kvmrt2_media_editorClass: public Ui_kvmrt2_media_editorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KVMRT2_MEDIA_EDITOR_H
