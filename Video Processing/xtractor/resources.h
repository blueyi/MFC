/*
 * resources.h - Copyright (C) 1999,2000 Jay A. Key
 *
 * Various #define's for menu items, etc., mostly having to do with 
 * program resources
 *
 **********************************************************************
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 */
#define idToolbarBmp     50
#define idClosedFoldIcon  51
#define idCurrFoldIcon    52
#define idFloppyIcon      53
#define idHardIcon        54
#define idNetworkIcon     55
#define idOpenFoldIcon    56
#define idRamIcon         57
#define idCDRomIcon       58
#define idImageList       59
#define idImageListMap    60
#define idToolbarHotBmp   61
#define idToolbar24Bmp    62
#define idToolbarHot24Bmp 63

// menu items
#define IDM_EXIT               100
#define IDM_ABOUT              101
#define IDM_REFRESH            102
#define IDM_TOOLBAR            103
#define IDM_RIP                104
#define IDM_MP3                105
#define IDM_OPTIONS            106
#define IDM_HEADER             107
#define IDM_TRACKWND           108
#define IDM_STATUSBAR          109
#define IDM_CDSETTINGS         110
#define IDM_DIRSETTINGS        111
#define IDM_MP3SETTINGS        112
#define IDM_CHECKALL           113
#define IDM_RENAME             114
#define IDM_DELETE             115
#define IDM_COMBINE            116
#define IDM_INVERT             117
#define IDM_PROPERTIES         118
#define IDM_ID3TAGEDIT         119
#define IDE_ALBUM              120
#define IDE_ARTIST             121
#define IDM_ID3                122
#define IDM_ENABLEID3          123
#define IDM_ENABLECDDB         124
#define IDM_HELPTOPICS         125
#define IDM_CDDBSETTINGS       126
#define IDM_RIPSEGMENT         127
#define IDM_CDPARMS            128
#define IDM_HICOLOR            129
#define IDM_CDPLAYERINI        130
#define IDM_MISCOPT            131
#define IDM_SUBMITCDDB         132
#define IDM_VORBSETTINGS       133


// cd options
#define IDCKB_AUTOTOC         1200
#define IDCBX_CDLIST          1201
#define IDCBX_DRVTYPE         1202
#define IDRBN_ALWAYS          1203
#define IDRBN_ONERR           1204
#define IDRBN_NEVER           1205
#define IDBN_RESET            1206
#define IDE_NUMREAD           1207
#define IDE_NUMCHECK          1208
#define IDE_NUMOVER           1209
#define IDCKB_AUTOCHECK       1210

// directory options
#define IDE_WAVDIR            1300
#define IDBN_BRWSEWAVDIR      1301
#define IDE_MP3DIR            1302
#define IDBN_BRWSEMP3DIR      1303
#define IDRBN_WAV             1304
#define IDRBN_MP3             1305
#define IDCKB_NICETHREADS     1306
#define IDCBX_ENCODER         1307
#define IDT_DESC              1308
#define IDCKB_NORMALIZE       1309
#define IDE_NORMVAL           1310
#define IDE_NORMSCANPCT       1311

// rip dialog
#define IDG_RIPPROG           1400
#define IDG_READBUF           1401
#define IDG_ENCBUF            1402
#define IDBN_CANCELRIP        1403
#define IDT_OUTPUTOPTTEXT     1404
#define IDT_TRACKNAME         1405
#define IDT_ESTTIME           1406
#define IDCKB_FINISHTRACK     1407
#define IDT_RIPPCT            1408


// mp3 options
#define IDRBN_32              1500
#define IDRBN_40              1501
#define IDRBN_48              1502
#define IDRBN_56              1503
#define IDRBN_64              1504
#define IDRBN_80              1505
#define IDRBN_96              1506
#define IDRBN_112             1507
#define IDRBN_128             1508
#define IDRBN_160             1509
#define IDRBN_192             1510
#define IDRBN_224             1511
#define IDRBN_256             1512
#define IDRBN_320             1513
#define IDCKB_CRC             1514
#define IDCKB_ID3             1515
#define IDCKB_ORIGINAL        1516
#define IDCKB_COPYRIGHT       1517
#define IDCKB_PRIVATE         1518
#define IDCBX_CBITRATE        1519
#define IDCBX_MBITRATE        1520
#define IDCBX_MODE            1522
#define IDCBX_QUALITY         1523
#define IDCKB_VBR             1524
#define IDCBX_VBRQUALITY      1525
#define IDCKB_VBRHEADER       1526
#define IDCKB_JSTEREO         1527


// id3 info
#define IDE_ARTIST2           1600
#define IDE_ALBUM2            1601
#define IDBN_ID3OK            1602
#define IDBN_ID3CANCEL        1603
#define IDE_YEAR              1604
#define IDCBX_GENRE           1605


// about dialog
#define IDBN_ABOUTOK          1700
#define ID_BMPPANEL           1701
#define IDT_ABOUTTXT          1702


// cddb options
#define IDE_CDDBSERVER        1800
#define IDBN_SELECTCDDB       1801
#define IDLB_SERVERLIST       1802
#define IDBN_RESETCDDB        1803
#define IDCKB_USEPROXY        1804
#define IDE_PROXYSRVR         1805
#define IDE_PROXYPORT         1806
#define IDE_CDDBCGI           1807
#define IDE_CDDBSUBMIT        1808
#define IDE_PROXYUSER         1809
#define IDE_PROXYPASS         1810
#define IDE_SERVERPORT        1811
#define IDCKB_SAVEPASS        1812


// cddb multiple query dialog
#define IDLB_CDDBQUERYSELECT  1900
#define IDBN_CDDBQUERYOK      1901
#define IDBN_CDDBQUERYCNCL    1902


// directory select dialog
#define IDE_DIRSEL            2000
#define IDCKB_AUTOCREATE      2001
#define IDBN_DIRSELOK         2002
#define IDBN_DIRSELCANCEL     2003
#define ID_DIRSELTREE         2004


// rip segment dialog
#define IDBN_RIPSEGOK         2100
#define IDBN_RIPSEGCANCEL     2101
#define ID_STARTSLIDER        2102
#define ID_ENDSLIDER          2103
#define ID_SLIDER             2104
#define IDE_START             2105
#define IDE_FINISH            2106
#define IDT_STARTTEXT         2107
#define IDT_FINISHTEXT        2108
#define IDT_TRACKLEN          2109
#define IDE_SEGMENTFNAME      2110

// cddb site query dialog
#define IDE_SITEQUERY         2200
#define IDBN_SITEQUERYCANCEL  2201
#define IDBN_SITEQUERYOK      2202

// misc options dialog
#define IDCKB_M3UENABLE       2300
#define IDRBN_M3UALBUMNAME    2301
#define IDRBN_M3USPECIFYNAME  2302
#define IDBN_M3UBROWSE        2303
#define IDE_M3UFILE           2304
#define IDE_FNAMEMACRO        2305

// cddb submit wiz1
#define IDE_WIZ1EMAIL         2400
#define IDBN_WIZ1CANCEL       2401
#define IDBN_WIZ1NEXT         2402
#define IDBN_WIZ2CANCEL       2403
#define IDBN_WIZ2NEXT         2404
#define IDBN_WIZ2BACK         2405
#define IDE_WIZ2ENTRY         2406
#define IDCBX_WIZ1GENRE       2407
#define IDE_WIZ1DGENRE        2408
#define IDE_WIZ1YEAR          2409

// vorb options dialog
#define IDCBX_VORBBITRATE     2500
#define IDE_VORBVERSION       2501
#define IDE_VORBORGANIZATION  2502
#define IDE_VORBDESCRIPTION   2503
#define IDE_VORBGENRE         2504
#define IDE_VORBDATE          2505
#define IDE_VORBLOCATION      2506
#define IDE_VORBCOPYRIGHT     2507
