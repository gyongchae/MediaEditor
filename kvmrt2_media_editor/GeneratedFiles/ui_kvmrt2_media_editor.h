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
    QAction *actionUserInfo;
    QAction *actionSyncAudioDur;
    QWidget *centralWidget;
    QGridLayout *gridLayout_21;
    QTabWidget *tabMain;
    QWidget *tabStation;
    QGridLayout *gridLayout_4;
    QSplitter *splitter;
    QGroupBox *gbStationName;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *btnAddStation;
    QPushButton *btnDelStation;
    QPushButton *btnDelAllStation;
    QSpacerItem *horizontalSpacer_3;
    QTableView *m_tblStationInformation;
    QGroupBox *gbDistance;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *btnAddPair;
    QPushButton *btnDelPair;
    QPushButton *btnDelAllPair;
    QSpacerItem *horizontalSpacer_4;
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
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *btnAddStopPattern;
    QPushButton *btnDelStopPattern;
    QPushButton *btnDelAllStopPattern;
    QSpacerItem *horizontalSpacer_5;
    QTableView *m_tblStopPtnHeader;
    QGroupBox *gbTrainRoute;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *btnAddRoute;
    QPushButton *btnDelRoute;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnRouteAutoAdd;
    QPushButton *btnDelRoutes;
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
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_10;
    QHBoxLayout *horizontalLayout_11;
    QPushButton *btnAddDisplayList;
    QPushButton *btnDelDisplayList;
    QPushButton *btnDelAllDisplayList;
    QSpacerItem *horizontalSpacer_6;
    QTableView *m_tblPIDContents;
    QGroupBox *groupBox_16;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_12;
    QHBoxLayout *horizontalLayout_13;
    QPushButton *btnAddDisplayItem;
    QPushButton *btnDelDisplayItem;
    QPushButton *btnDelAllDisplayItem;
    QSpacerItem *horizontalSpacer_7;
    QTableView *m_tblPIDIndexList;
    QWidget *tabAudio;
    QGridLayout *gridLayout_17;
    QSplitter *splitter_6;
    QGroupBox *groupBox_12;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_14;
    QHBoxLayout *horizontalLayout_15;
    QPushButton *btnAddStnAudio;
    QPushButton *btnDelStnAudio;
    QPushButton *btnDelAllStnAudio;
    QSpacerItem *horizontalSpacer_8;
    QTableView *m_tblAudioStationName;
    QGroupBox *groupBox_13;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_16;
    QHBoxLayout *horizontalLayout_17;
    QPushButton *btnAddAudioList;
    QPushButton *btnDelAudioList;
    QPushButton *btnDelAllAudioList;
    QSpacerItem *horizontalSpacer_9;
    QTableView *m_tblAudioPlayList;
    QWidget *tabVideo;
    QGridLayout *gridLayout_14;
    QSplitter *splitter_5;
    QGroupBox *groupBox_10;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_18;
    QHBoxLayout *horizontalLayout_19;
    QPushButton *btnAddVideoGroup;
    QPushButton *btnDelVideoGroup;
    QPushButton *btnDelAllVideoGroup;
    QSpacerItem *horizontalSpacer_10;
    QTableView *m_tblVideoDeviceGroup;
    QGroupBox *groupBox_9;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_20;
    QHBoxLayout *horizontalLayout_21;
    QPushButton *btnAddVideoList;
    QPushButton *btnDelVideoList;
    QPushButton *btnDelAllVideoList;
    QSpacerItem *horizontalSpacer_11;
    QTableView *m_tblVideoPlayList;
    QWidget *tabDataTag;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout_22;
    QHBoxLayout *horizontalLayout_23;
    QPushButton *btnAddDataTag;
    QPushButton *btnDelDataTag;
    QPushButton *btnDelAllDataTag;
    QSpacerItem *horizontalSpacer_12;
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
        kvmrt2_media_editorClass->resize(1140, 711);
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
        actionUserInfo = new QAction(kvmrt2_media_editorClass);
        actionUserInfo->setObjectName(QStringLiteral("actionUserInfo"));
        actionSyncAudioDur = new QAction(kvmrt2_media_editorClass);
        actionSyncAudioDur->setObjectName(QStringLiteral("actionSyncAudioDur"));
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
        verticalLayout_3 = new QVBoxLayout(gbStationName);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        btnAddStation = new QPushButton(gbStationName);
        btnAddStation->setObjectName(QStringLiteral("btnAddStation"));
        btnAddStation->setFont(font);

        horizontalLayout_4->addWidget(btnAddStation);

        btnDelStation = new QPushButton(gbStationName);
        btnDelStation->setObjectName(QStringLiteral("btnDelStation"));
        btnDelStation->setFont(font);

        horizontalLayout_4->addWidget(btnDelStation);

        btnDelAllStation = new QPushButton(gbStationName);
        btnDelAllStation->setObjectName(QStringLiteral("btnDelAllStation"));
        btnDelAllStation->setFont(font);

        horizontalLayout_4->addWidget(btnDelAllStation);


        horizontalLayout_5->addLayout(horizontalLayout_4);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);


        verticalLayout_3->addLayout(horizontalLayout_5);

        m_tblStationInformation = new QTableView(gbStationName);
        m_tblStationInformation->setObjectName(QStringLiteral("m_tblStationInformation"));

        verticalLayout_3->addWidget(m_tblStationInformation);

        verticalLayout_3->setStretch(1, 1);
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
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        btnAddPair = new QPushButton(gbDistance);
        btnAddPair->setObjectName(QStringLiteral("btnAddPair"));

        horizontalLayout_6->addWidget(btnAddPair);

        btnDelPair = new QPushButton(gbDistance);
        btnDelPair->setObjectName(QStringLiteral("btnDelPair"));

        horizontalLayout_6->addWidget(btnDelPair);

        btnDelAllPair = new QPushButton(gbDistance);
        btnDelAllPair->setObjectName(QStringLiteral("btnDelAllPair"));

        horizontalLayout_6->addWidget(btnDelAllPair);


        horizontalLayout->addLayout(horizontalLayout_6);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

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
        verticalLayout_4 = new QVBoxLayout(gbStopPattern);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        btnAddStopPattern = new QPushButton(gbStopPattern);
        btnAddStopPattern->setObjectName(QStringLiteral("btnAddStopPattern"));

        horizontalLayout_8->addWidget(btnAddStopPattern);

        btnDelStopPattern = new QPushButton(gbStopPattern);
        btnDelStopPattern->setObjectName(QStringLiteral("btnDelStopPattern"));

        horizontalLayout_8->addWidget(btnDelStopPattern);

        btnDelAllStopPattern = new QPushButton(gbStopPattern);
        btnDelAllStopPattern->setObjectName(QStringLiteral("btnDelAllStopPattern"));

        horizontalLayout_8->addWidget(btnDelAllStopPattern);


        horizontalLayout_7->addLayout(horizontalLayout_8);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);


        verticalLayout_4->addLayout(horizontalLayout_7);

        m_tblStopPtnHeader = new QTableView(gbStopPattern);
        m_tblStopPtnHeader->setObjectName(QStringLiteral("m_tblStopPtnHeader"));

        verticalLayout_4->addWidget(m_tblStopPtnHeader);

        splitter_3->addWidget(gbStopPattern);
        gbTrainRoute = new QGroupBox(splitter_3);
        gbTrainRoute->setObjectName(QStringLiteral("gbTrainRoute"));
        verticalLayout_2 = new QVBoxLayout(gbTrainRoute);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        btnAddRoute = new QPushButton(gbTrainRoute);
        btnAddRoute->setObjectName(QStringLiteral("btnAddRoute"));

        horizontalLayout_9->addWidget(btnAddRoute);

        btnDelRoute = new QPushButton(gbTrainRoute);
        btnDelRoute->setObjectName(QStringLiteral("btnDelRoute"));

        horizontalLayout_9->addWidget(btnDelRoute);


        horizontalLayout_3->addLayout(horizontalLayout_9);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        btnRouteAutoAdd = new QPushButton(gbTrainRoute);
        btnRouteAutoAdd->setObjectName(QStringLiteral("btnRouteAutoAdd"));

        horizontalLayout_2->addWidget(btnRouteAutoAdd);

        btnDelRoutes = new QPushButton(gbTrainRoute);
        btnDelRoutes->setObjectName(QStringLiteral("btnDelRoutes"));

        horizontalLayout_2->addWidget(btnDelRoutes);


        horizontalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(horizontalLayout_3);

        m_tblStopPtnRoutes = new QTableView(gbTrainRoute);
        m_tblStopPtnRoutes->setObjectName(QStringLiteral("m_tblStopPtnRoutes"));

        verticalLayout_2->addWidget(m_tblStopPtnRoutes);

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
        verticalLayout_5 = new QVBoxLayout(groupBox_15);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        btnAddDisplayList = new QPushButton(groupBox_15);
        btnAddDisplayList->setObjectName(QStringLiteral("btnAddDisplayList"));

        horizontalLayout_11->addWidget(btnAddDisplayList);

        btnDelDisplayList = new QPushButton(groupBox_15);
        btnDelDisplayList->setObjectName(QStringLiteral("btnDelDisplayList"));

        horizontalLayout_11->addWidget(btnDelDisplayList);

        btnDelAllDisplayList = new QPushButton(groupBox_15);
        btnDelAllDisplayList->setObjectName(QStringLiteral("btnDelAllDisplayList"));

        horizontalLayout_11->addWidget(btnDelAllDisplayList);


        horizontalLayout_10->addLayout(horizontalLayout_11);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_6);


        verticalLayout_5->addLayout(horizontalLayout_10);

        m_tblPIDContents = new QTableView(groupBox_15);
        m_tblPIDContents->setObjectName(QStringLiteral("m_tblPIDContents"));

        verticalLayout_5->addWidget(m_tblPIDContents);

        splitter_7->addWidget(groupBox_15);
        groupBox_16 = new QGroupBox(splitter_7);
        groupBox_16->setObjectName(QStringLiteral("groupBox_16"));
        verticalLayout_6 = new QVBoxLayout(groupBox_16);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        btnAddDisplayItem = new QPushButton(groupBox_16);
        btnAddDisplayItem->setObjectName(QStringLiteral("btnAddDisplayItem"));

        horizontalLayout_13->addWidget(btnAddDisplayItem);

        btnDelDisplayItem = new QPushButton(groupBox_16);
        btnDelDisplayItem->setObjectName(QStringLiteral("btnDelDisplayItem"));

        horizontalLayout_13->addWidget(btnDelDisplayItem);

        btnDelAllDisplayItem = new QPushButton(groupBox_16);
        btnDelAllDisplayItem->setObjectName(QStringLiteral("btnDelAllDisplayItem"));

        horizontalLayout_13->addWidget(btnDelAllDisplayItem);


        horizontalLayout_12->addLayout(horizontalLayout_13);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_7);


        verticalLayout_6->addLayout(horizontalLayout_12);

        m_tblPIDIndexList = new QTableView(groupBox_16);
        m_tblPIDIndexList->setObjectName(QStringLiteral("m_tblPIDIndexList"));

        verticalLayout_6->addWidget(m_tblPIDIndexList);

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
        verticalLayout_7 = new QVBoxLayout(groupBox_12);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        btnAddStnAudio = new QPushButton(groupBox_12);
        btnAddStnAudio->setObjectName(QStringLiteral("btnAddStnAudio"));

        horizontalLayout_15->addWidget(btnAddStnAudio);

        btnDelStnAudio = new QPushButton(groupBox_12);
        btnDelStnAudio->setObjectName(QStringLiteral("btnDelStnAudio"));

        horizontalLayout_15->addWidget(btnDelStnAudio);

        btnDelAllStnAudio = new QPushButton(groupBox_12);
        btnDelAllStnAudio->setObjectName(QStringLiteral("btnDelAllStnAudio"));

        horizontalLayout_15->addWidget(btnDelAllStnAudio);


        horizontalLayout_14->addLayout(horizontalLayout_15);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_8);


        verticalLayout_7->addLayout(horizontalLayout_14);

        m_tblAudioStationName = new QTableView(groupBox_12);
        m_tblAudioStationName->setObjectName(QStringLiteral("m_tblAudioStationName"));
        m_tblAudioStationName->horizontalHeader()->setDefaultSectionSize(130);

        verticalLayout_7->addWidget(m_tblAudioStationName);

        splitter_6->addWidget(groupBox_12);
        groupBox_13 = new QGroupBox(splitter_6);
        groupBox_13->setObjectName(QStringLiteral("groupBox_13"));
        verticalLayout_8 = new QVBoxLayout(groupBox_13);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        btnAddAudioList = new QPushButton(groupBox_13);
        btnAddAudioList->setObjectName(QStringLiteral("btnAddAudioList"));

        horizontalLayout_17->addWidget(btnAddAudioList);

        btnDelAudioList = new QPushButton(groupBox_13);
        btnDelAudioList->setObjectName(QStringLiteral("btnDelAudioList"));

        horizontalLayout_17->addWidget(btnDelAudioList);

        btnDelAllAudioList = new QPushButton(groupBox_13);
        btnDelAllAudioList->setObjectName(QStringLiteral("btnDelAllAudioList"));

        horizontalLayout_17->addWidget(btnDelAllAudioList);


        horizontalLayout_16->addLayout(horizontalLayout_17);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_9);


        verticalLayout_8->addLayout(horizontalLayout_16);

        m_tblAudioPlayList = new QTableView(groupBox_13);
        m_tblAudioPlayList->setObjectName(QStringLiteral("m_tblAudioPlayList"));

        verticalLayout_8->addWidget(m_tblAudioPlayList);

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
        verticalLayout_9 = new QVBoxLayout(groupBox_10);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        btnAddVideoGroup = new QPushButton(groupBox_10);
        btnAddVideoGroup->setObjectName(QStringLiteral("btnAddVideoGroup"));

        horizontalLayout_19->addWidget(btnAddVideoGroup);

        btnDelVideoGroup = new QPushButton(groupBox_10);
        btnDelVideoGroup->setObjectName(QStringLiteral("btnDelVideoGroup"));

        horizontalLayout_19->addWidget(btnDelVideoGroup);

        btnDelAllVideoGroup = new QPushButton(groupBox_10);
        btnDelAllVideoGroup->setObjectName(QStringLiteral("btnDelAllVideoGroup"));

        horizontalLayout_19->addWidget(btnDelAllVideoGroup);


        horizontalLayout_18->addLayout(horizontalLayout_19);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer_10);


        verticalLayout_9->addLayout(horizontalLayout_18);

        m_tblVideoDeviceGroup = new QTableView(groupBox_10);
        m_tblVideoDeviceGroup->setObjectName(QStringLiteral("m_tblVideoDeviceGroup"));

        verticalLayout_9->addWidget(m_tblVideoDeviceGroup);

        splitter_5->addWidget(groupBox_10);
        groupBox_9 = new QGroupBox(splitter_5);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        verticalLayout_10 = new QVBoxLayout(groupBox_9);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setObjectName(QStringLiteral("horizontalLayout_21"));
        btnAddVideoList = new QPushButton(groupBox_9);
        btnAddVideoList->setObjectName(QStringLiteral("btnAddVideoList"));

        horizontalLayout_21->addWidget(btnAddVideoList);

        btnDelVideoList = new QPushButton(groupBox_9);
        btnDelVideoList->setObjectName(QStringLiteral("btnDelVideoList"));

        horizontalLayout_21->addWidget(btnDelVideoList);

        btnDelAllVideoList = new QPushButton(groupBox_9);
        btnDelAllVideoList->setObjectName(QStringLiteral("btnDelAllVideoList"));

        horizontalLayout_21->addWidget(btnDelAllVideoList);


        horizontalLayout_20->addLayout(horizontalLayout_21);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_20->addItem(horizontalSpacer_11);


        verticalLayout_10->addLayout(horizontalLayout_20);

        m_tblVideoPlayList = new QTableView(groupBox_9);
        m_tblVideoPlayList->setObjectName(QStringLiteral("m_tblVideoPlayList"));

        verticalLayout_10->addWidget(m_tblVideoPlayList);

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
        verticalLayout_11 = new QVBoxLayout(groupBox);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setSpacing(6);
        horizontalLayout_22->setObjectName(QStringLiteral("horizontalLayout_22"));
        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setSpacing(6);
        horizontalLayout_23->setObjectName(QStringLiteral("horizontalLayout_23"));
        btnAddDataTag = new QPushButton(groupBox);
        btnAddDataTag->setObjectName(QStringLiteral("btnAddDataTag"));

        horizontalLayout_23->addWidget(btnAddDataTag);

        btnDelDataTag = new QPushButton(groupBox);
        btnDelDataTag->setObjectName(QStringLiteral("btnDelDataTag"));

        horizontalLayout_23->addWidget(btnDelDataTag);

        btnDelAllDataTag = new QPushButton(groupBox);
        btnDelAllDataTag->setObjectName(QStringLiteral("btnDelAllDataTag"));

        horizontalLayout_23->addWidget(btnDelAllDataTag);


        horizontalLayout_22->addLayout(horizontalLayout_23);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_22->addItem(horizontalSpacer_12);


        verticalLayout_11->addLayout(horizontalLayout_22);

        m_tblEditorTagTable = new QTableView(groupBox);
        m_tblEditorTagTable->setObjectName(QStringLiteral("m_tblEditorTagTable"));
        m_tblEditorTagTable->horizontalHeader()->setDefaultSectionSize(200);

        verticalLayout_11->addWidget(m_tblEditorTagTable);


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
        menuFile->addAction(actionSyncAudioDur);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSetting);
        menuFile->addAction(actionUserInfo);
        menuFile->addSeparator();
        menuFile->addAction(actionUpdate);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
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
        mainToolBar->addAction(actionUserInfo);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionExit);

        retranslateUi(kvmrt2_media_editorClass);

        tabMain->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(kvmrt2_media_editorClass);
    } // setupUi

    void retranslateUi(QMainWindow *kvmrt2_media_editorClass)
    {
        kvmrt2_media_editorClass->setWindowTitle(QApplication::translate("kvmrt2_media_editorClass", "Media Editor", Q_NULLPTR));
        actionSave->setText(QApplication::translate("kvmrt2_media_editorClass", "DB &Save", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionSave->setShortcut(QApplication::translate("kvmrt2_media_editorClass", "F5", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionSetting->setText(QApplication::translate("kvmrt2_media_editorClass", "DB &Version", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionSetting->setToolTip(QApplication::translate("kvmrt2_media_editorClass", "DB Version Setting", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionAudioVideoPool->setText(QApplication::translate("kvmrt2_media_editorClass", "&Audio && Video", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionAudioVideoPool->setToolTip(QApplication::translate("kvmrt2_media_editorClass", "Audio and Video", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionFontPool->setText(QApplication::translate("kvmrt2_media_editorClass", "&Font", Q_NULLPTR));
        actionTextPool->setText(QApplication::translate("kvmrt2_media_editorClass", "&Text", Q_NULLPTR));
        actionRouteMapPool->setText(QApplication::translate("kvmrt2_media_editorClass", "Route &Map", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionRouteMapPool->setToolTip(QApplication::translate("kvmrt2_media_editorClass", "Route Map", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionBitmapPool->setText(QApplication::translate("kvmrt2_media_editorClass", "&Bitmap", Q_NULLPTR));
        actionImageListPool->setText(QApplication::translate("kvmrt2_media_editorClass", "Image List", Q_NULLPTR));
        actionLedPool->setText(QApplication::translate("kvmrt2_media_editorClass", "L.E.D", Q_NULLPTR));
        actionDisplayListPool->setText(QApplication::translate("kvmrt2_media_editorClass", "&DRMD && PID", Q_NULLPTR));
        actionAboutQt->setText(QApplication::translate("kvmrt2_media_editorClass", "About &Qt", Q_NULLPTR));
        actionAboutME->setText(QApplication::translate("kvmrt2_media_editorClass", "About &ME", Q_NULLPTR));
        actionExit->setText(QApplication::translate("kvmrt2_media_editorClass", "E&xit Program", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionExit->setToolTip(QApplication::translate("kvmrt2_media_editorClass", "Exit Program", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionNew->setText(QApplication::translate("kvmrt2_media_editorClass", "New DB", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionNew->setShortcut(QApplication::translate("kvmrt2_media_editorClass", "Ctrl+N", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionLoad->setText(QApplication::translate("kvmrt2_media_editorClass", "Load DB", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionLoad->setShortcut(QApplication::translate("kvmrt2_media_editorClass", "Ctrl+O", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionUpdate->setText(QApplication::translate("kvmrt2_media_editorClass", "&File Upload", Q_NULLPTR));
        actionLicenseInfo->setText(QApplication::translate("kvmrt2_media_editorClass", "License Info", Q_NULLPTR));
        actioncanvas_test->setText(QApplication::translate("kvmrt2_media_editorClass", "canvas test", Q_NULLPTR));
        actionTestCanvas->setText(QApplication::translate("kvmrt2_media_editorClass", "canvas test", Q_NULLPTR));
        actionUserInfo->setText(QApplication::translate("kvmrt2_media_editorClass", "&User Information", Q_NULLPTR));
        actionSyncAudioDur->setText(QApplication::translate("kvmrt2_media_editorClass", "Sync Audio Du&ration", Q_NULLPTR));
        gbStationName->setTitle(QApplication::translate("kvmrt2_media_editorClass", "Station Name", Q_NULLPTR));
        btnAddStation->setText(QApplication::translate("kvmrt2_media_editorClass", "Add", Q_NULLPTR));
        btnDelStation->setText(QApplication::translate("kvmrt2_media_editorClass", "Delete", Q_NULLPTR));
        btnDelAllStation->setText(QApplication::translate("kvmrt2_media_editorClass", "Delete All", Q_NULLPTR));
        gbDistance->setTitle(QApplication::translate("kvmrt2_media_editorClass", "Station Pair (Distance table)", Q_NULLPTR));
        btnAddPair->setText(QApplication::translate("kvmrt2_media_editorClass", "Add", Q_NULLPTR));
        btnDelPair->setText(QApplication::translate("kvmrt2_media_editorClass", "Delete", Q_NULLPTR));
        btnDelAllPair->setText(QApplication::translate("kvmrt2_media_editorClass", "Delete All", Q_NULLPTR));
        rbInOrder->setText(QApplication::translate("kvmrt2_media_editorClass", "Auto 1", Q_NULLPTR));
        rbInReverseOrder->setText(QApplication::translate("kvmrt2_media_editorClass", "Auto 2", Q_NULLPTR));
        rbCustomOrder->setText(QApplication::translate("kvmrt2_media_editorClass", "Custom", Q_NULLPTR));
        btnRefreshDistanceTable->setText(QApplication::translate("kvmrt2_media_editorClass", "Fill Description", Q_NULLPTR));
        tabMain->setTabText(tabMain->indexOf(tabStation), QApplication::translate("kvmrt2_media_editorClass", "Station Information", Q_NULLPTR));
        gbStopPattern->setTitle(QApplication::translate("kvmrt2_media_editorClass", "Stop Pattern", Q_NULLPTR));
        btnAddStopPattern->setText(QApplication::translate("kvmrt2_media_editorClass", "Add", Q_NULLPTR));
        btnDelStopPattern->setText(QApplication::translate("kvmrt2_media_editorClass", "Delete", Q_NULLPTR));
        btnDelAllStopPattern->setText(QApplication::translate("kvmrt2_media_editorClass", "Delete All", Q_NULLPTR));
        gbTrainRoute->setTitle(QApplication::translate("kvmrt2_media_editorClass", "Train Route", Q_NULLPTR));
        btnAddRoute->setText(QApplication::translate("kvmrt2_media_editorClass", "Add", Q_NULLPTR));
        btnDelRoute->setText(QApplication::translate("kvmrt2_media_editorClass", "Delete", Q_NULLPTR));
        btnRouteAutoAdd->setText(QApplication::translate("kvmrt2_media_editorClass", "Auto Add All", Q_NULLPTR));
        btnDelRoutes->setText(QApplication::translate("kvmrt2_media_editorClass", "Delete All", Q_NULLPTR));
        gbTrainNumber->setTitle(QApplication::translate("kvmrt2_media_editorClass", "Train Number", Q_NULLPTR));
        gbRouteEvent->setTitle(QApplication::translate("kvmrt2_media_editorClass", "Route Event List", Q_NULLPTR));
        tabMain->setTabText(tabMain->indexOf(tabRoute), QApplication::translate("kvmrt2_media_editorClass", "Train Route Information", Q_NULLPTR));
        groupBox_15->setTitle(QApplication::translate("kvmrt2_media_editorClass", "Display List Name", Q_NULLPTR));
        btnAddDisplayList->setText(QApplication::translate("kvmrt2_media_editorClass", "Add", Q_NULLPTR));
        btnDelDisplayList->setText(QApplication::translate("kvmrt2_media_editorClass", "Delete", Q_NULLPTR));
        btnDelAllDisplayList->setText(QApplication::translate("kvmrt2_media_editorClass", "Delete All", Q_NULLPTR));
        groupBox_16->setTitle(QApplication::translate("kvmrt2_media_editorClass", "Display Item List", Q_NULLPTR));
        btnAddDisplayItem->setText(QApplication::translate("kvmrt2_media_editorClass", "Add", Q_NULLPTR));
        btnDelDisplayItem->setText(QApplication::translate("kvmrt2_media_editorClass", "Delete", Q_NULLPTR));
        btnDelAllDisplayItem->setText(QApplication::translate("kvmrt2_media_editorClass", "Delete All", Q_NULLPTR));
        tabMain->setTabText(tabMain->indexOf(tabScreen), QApplication::translate("kvmrt2_media_editorClass", "Screen Contents", Q_NULLPTR));
        groupBox_12->setTitle(QApplication::translate("kvmrt2_media_editorClass", "Station Name Audio", Q_NULLPTR));
        btnAddStnAudio->setText(QApplication::translate("kvmrt2_media_editorClass", "Add", Q_NULLPTR));
        btnDelStnAudio->setText(QApplication::translate("kvmrt2_media_editorClass", "Delete", Q_NULLPTR));
        btnDelAllStnAudio->setText(QApplication::translate("kvmrt2_media_editorClass", "Delete All", Q_NULLPTR));
        groupBox_13->setTitle(QApplication::translate("kvmrt2_media_editorClass", "Audio Play List", Q_NULLPTR));
        btnAddAudioList->setText(QApplication::translate("kvmrt2_media_editorClass", "Add", Q_NULLPTR));
        btnDelAudioList->setText(QApplication::translate("kvmrt2_media_editorClass", "Delete", Q_NULLPTR));
        btnDelAllAudioList->setText(QApplication::translate("kvmrt2_media_editorClass", "Delete All", Q_NULLPTR));
        tabMain->setTabText(tabMain->indexOf(tabAudio), QApplication::translate("kvmrt2_media_editorClass", "Audio Contents", Q_NULLPTR));
        groupBox_10->setTitle(QApplication::translate("kvmrt2_media_editorClass", "Video Play Group", Q_NULLPTR));
        btnAddVideoGroup->setText(QApplication::translate("kvmrt2_media_editorClass", "Add", Q_NULLPTR));
        btnDelVideoGroup->setText(QApplication::translate("kvmrt2_media_editorClass", "Delete", Q_NULLPTR));
        btnDelAllVideoGroup->setText(QApplication::translate("kvmrt2_media_editorClass", "Delete All", Q_NULLPTR));
        groupBox_9->setTitle(QApplication::translate("kvmrt2_media_editorClass", "Video Play List", Q_NULLPTR));
        btnAddVideoList->setText(QApplication::translate("kvmrt2_media_editorClass", "Add", Q_NULLPTR));
        btnDelVideoList->setText(QApplication::translate("kvmrt2_media_editorClass", "Delete", Q_NULLPTR));
        btnDelAllVideoList->setText(QApplication::translate("kvmrt2_media_editorClass", "Delete All", Q_NULLPTR));
        tabMain->setTabText(tabMain->indexOf(tabVideo), QApplication::translate("kvmrt2_media_editorClass", "Video Contents", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("kvmrt2_media_editorClass", "Data Tag (Editor tag table)", Q_NULLPTR));
        btnAddDataTag->setText(QApplication::translate("kvmrt2_media_editorClass", "Add", Q_NULLPTR));
        btnDelDataTag->setText(QApplication::translate("kvmrt2_media_editorClass", "Delete", Q_NULLPTR));
        btnDelAllDataTag->setText(QApplication::translate("kvmrt2_media_editorClass", "Delete All", Q_NULLPTR));
        tabMain->setTabText(tabMain->indexOf(tabDataTag), QApplication::translate("kvmrt2_media_editorClass", "Data Tag", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("kvmrt2_media_editorClass", "&File", Q_NULLPTR));
        menuFilePool->setTitle(QApplication::translate("kvmrt2_media_editorClass", "&Data File Pool", Q_NULLPTR));
        menuDisplayConfig->setTitle(QApplication::translate("kvmrt2_media_editorClass", "&Display Configuration", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("kvmrt2_media_editorClass", "&Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class kvmrt2_media_editorClass: public Ui_kvmrt2_media_editorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KVMRT2_MEDIA_EDITOR_H
