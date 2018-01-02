/*
 * mp3dlg.c - Copyright (C) 1999,2000 Jay A. Key
 *
 * The MP3 options dialog for the options property sheet.  Allows the 
 * user to set the output bitrate, and enable CRC and ID3v1 tagging.
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
#include <windows.h>
#include <commctrl.h>
#include "resources.h"
#include "globals.h"

void ConfigureMP3Dlg( HWND hWnd );
BOOL ValidateMP3Dlg( HWND hWnd );

// save old settings for output dialog config
static BOOL bCRCTmp;
static BOOL bID3Tmp;
static BOOL bPrivateTmp;
static BOOL bOriginalTmp;
static BOOL bCopyrightTmp;
static WORD wTmpBitrate;
static WORD wTmpMaxBitrate;
static WORD wTmpLameMode;
static BOOL bTmpVBR;
static BOOL bTmpVBRHeader;
static MPEG_QUALITY nTmpQuality;
static INT  nTmpVBRQuality;
static BOOL bInInit = FALSE;
static BOOL bListsInit = FALSE;
#define NUMBITRATES 14
static WORD bitrates[NUMBITRATES] = { 32, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320 };
static BOOL bNiceThreadsTmp;

/*
 * Called in response to PSN_KILLACTIVE.  Should validate all values in the
 * dialog, and save them to the temp variables.
 */
BOOL ValidateMP3Dlg( HWND hWnd )
{
  hWnd = hWnd;
  return TRUE;
}



/*
 * Called in response to PSN_SETACTIVE.  Sets dialog items with the values
 * from the temp variables.
 */
void ConfigureMP3Dlg( HWND hWnd )
{
  int i;
  BOOL bCFound = FALSE;
  BOOL bMFound = FALSE;
  char buf[32];

  bInInit = FALSE;

  CheckDlgButton( hWnd, IDCKB_CRC, bCRCTmp?BST_CHECKED:BST_UNCHECKED );
  CheckDlgButton( hWnd, IDCKB_ID3, bID3Tmp?BST_CHECKED:BST_UNCHECKED );
  CheckDlgButton( hWnd, IDCKB_ORIGINAL, bOriginalTmp?BST_CHECKED:BST_UNCHECKED );
  CheckDlgButton( hWnd, IDCKB_PRIVATE, bPrivateTmp?BST_CHECKED:BST_UNCHECKED );
  CheckDlgButton( hWnd, IDCKB_COPYRIGHT, bCopyrightTmp?BST_CHECKED:BST_UNCHECKED );

  CheckDlgButton( hWnd, IDCKB_VBR, bTmpVBR?BST_CHECKED:BST_UNCHECKED );
  CheckDlgButton( hWnd, IDCKB_VBRHEADER, bTmpVBRHeader?BST_CHECKED:BST_UNCHECKED );
  CheckDlgButton( hWnd, IDCKB_NICETHREADS, bNiceThreadsTmp?BST_CHECKED:BST_UNCHECKED );
  CheckDlgButton( hWnd, IDCKB_JSTEREO, wTmpLameMode==BE_MP3_MODE_JSTEREO?BST_CHECKED:BST_UNCHECKED );

  if ( !bListsInit )
    {
      SendDlgItemMessage( hWnd, IDCBX_QUALITY, CB_ADDSTRING, 0, (LPARAM)"Normal" );
      SendDlgItemMessage( hWnd, IDCBX_QUALITY, CB_ADDSTRING, 0, (LPARAM)"Low" );
      SendDlgItemMessage( hWnd, IDCBX_QUALITY, CB_ADDSTRING, 0, (LPARAM)"High" );
      SendDlgItemMessage( hWnd, IDCBX_QUALITY, CB_ADDSTRING, 0, (LPARAM)"Voice" );
      SendDlgItemMessage( hWnd, IDCBX_QUALITY, CB_SETCURSEL, (WPARAM)nTmpQuality, 0L );

      for( i = 0; i < 10; i++ )
	{
	  wsprintf( buf, "%d", i );
	  SendDlgItemMessage( hWnd, IDCBX_VBRQUALITY, CB_ADDSTRING, 0, (LPARAM)buf );
	}
      SendDlgItemMessage( hWnd, IDCBX_VBRQUALITY, CB_SETCURSEL, (WPARAM)nVBRQuality, 0L );

      for( i = 0; i < NUMBITRATES; i++ )
	{
	  wsprintf( buf, "%d", bitrates[i] );
	  SendDlgItemMessage( hWnd, IDCBX_CBITRATE, CB_ADDSTRING, 0, (LPARAM)buf );
	  SendDlgItemMessage( hWnd, IDCBX_MBITRATE, CB_ADDSTRING, 0, (LPARAM)buf );
	}

      i = 0;
      bListsInit = TRUE;

    }

  for( i = 0; (i < NUMBITRATES); i++ )
    {
      if ( wTmpBitrate == bitrates[i] )
	{
	  SendDlgItemMessage( hWnd, IDCBX_CBITRATE, CB_SETCURSEL, (WPARAM)i, 0L );
	  bCFound = TRUE;
	}
      if ( wTmpMaxBitrate == bitrates[i] )
	{
	  SendDlgItemMessage( hWnd, IDCBX_MBITRATE, CB_SETCURSEL, (WPARAM)i, 0L );
	  bMFound = TRUE;
	}
    }

  // if we didn't match any of the valid bitrates (ie, someone used regedit
  // to change the default value in the registry), set to 128 kbps.
  if ( !bCFound && !bMFound )
    {
      wBitrate = wTmpBitrate = wMaxBitrate = wTmpBitrate = 128;
      SendDlgItemMessage( hWnd, IDCBX_CBITRATE, CB_SETCURSEL, (WPARAM)8, 0L );
      SendDlgItemMessage( hWnd, IDCBX_MBITRATE, CB_SETCURSEL, (WPARAM)8, 0L );
    }

  bInInit = TRUE;
}


BOOL CALLBACK MP3DlgProc( HWND hWnd, UINT uMsg, WPARAM wParam,
			     LPARAM lParam )
{
  //  char buf[81];
  NMHDR *l = (NMHDR *)lParam;
  WORD wID;
  WORD wNotify;
  BOOL bChanged;
  int i;

  switch( uMsg )
    {
    case WM_INITDIALOG:
      //hOutDlg = hWnd;
      break;

    case WM_COMMAND:
      wID = LOWORD( wParam );
      wNotify = HIWORD( wParam );
      bChanged = TRUE;
      switch( wID )
	{
	case IDCKB_ID3:
	  bID3Tmp = !bID3Tmp;
	  break;

	case IDCKB_CRC:
	  bCRCTmp = !bCRCTmp;
	  break;

	case IDCKB_ORIGINAL:
	  bOriginalTmp = !bOriginalTmp;
	  break;

	case IDCKB_PRIVATE:
	  bPrivateTmp = !bPrivateTmp;
	  break;

	case IDCKB_COPYRIGHT:
	  bCopyrightTmp = !bCopyrightTmp;
	  break;

	case IDCKB_VBR:
	  bTmpVBR = !bTmpVBR;
	  break;

	case IDCKB_VBRHEADER:
	  bTmpVBRHeader = !bTmpVBRHeader;
	  break;
        
        case IDCKB_JSTEREO:
          if ( wTmpLameMode == BE_MP3_MODE_JSTEREO )
            wTmpLameMode = BE_MP3_MODE_STEREO;
          else
            wTmpLameMode = BE_MP3_MODE_JSTEREO;
          break;

	case IDCBX_CBITRATE:
	  if ( wNotify == CBN_SELCHANGE )
	    {
	      i = SendDlgItemMessage( hWnd, IDCBX_CBITRATE, CB_GETCURSEL, 0, 0L );
	      wTmpBitrate = bitrates[i];
	    }
	  else
	    bChanged = FALSE;
	  break;

	case IDCBX_MBITRATE:
	  if ( wNotify == CBN_SELCHANGE )
	    {
	      i = SendDlgItemMessage( hWnd, IDCBX_MBITRATE, CB_GETCURSEL, 0, 0L );
	      wTmpMaxBitrate = bitrates[i];
	    }
	  else
	    bChanged = FALSE;
	  break;

	case IDCBX_QUALITY:
	  if ( wNotify == CBN_SELCHANGE )
	    nTmpQuality = SendDlgItemMessage( hWnd, IDCBX_QUALITY, CB_GETCURSEL, 0, 0L );
	  else
	    bChanged = FALSE;
	  break;
	  
	case IDCBX_VBRQUALITY:
	  if ( wNotify == CBN_SELCHANGE )
	    nTmpVBRQuality = SendDlgItemMessage( hWnd, IDCBX_VBRQUALITY, CB_GETCURSEL, 0, 0L );
	  else
	    bChanged = FALSE;
	  break;
	  
	case IDCKB_NICETHREADS:
	  bNiceThreadsTmp = !bNiceThreadsTmp;
	  break;

	default:
	  break;
	}
      if ( bInInit && bChanged )
	SendMessage( (HWND)GetWindowLong( hWnd, GWL_HWNDPARENT ),
		     PSM_CHANGED, (WPARAM)hWnd, 0L );
      break;

    case WM_NOTIFY:
      switch( l->code )
	{
	case PSN_SETACTIVE:  // sent before page is shown
	  ConfigureMP3Dlg( hWnd );
	  break;

	case PSN_KILLACTIVE:  //losing focus
	  if ( ValidateMP3Dlg( hWnd ) )
	    // ok to lose focus
	    SetWindowLong( hWnd, DWL_MSGRESULT, FALSE );
	  else
	    {
	      // don't use allow loss of focus
	      SetWindowLong( hWnd, DWL_MSGRESULT, TRUE );
	      return TRUE;
	    }
	  break;

	case PSN_QUERYCANCEL:
	  break;

	case PSN_APPLY:
	  bCRC = bCRCTmp;
	  bID3 = bID3Tmp;
	  bOriginal = bOriginalTmp;
	  bCopyright = bCopyrightTmp;
	  bPrivate = bPrivateTmp;
	  wBitrate = wTmpBitrate;
	  wMaxBitrate = wTmpMaxBitrate;
	  bVBR = bTmpVBR;
	  bVBRHeader = bTmpVBRHeader;
	  nQuality = nTmpQuality;
	  nVBRQuality = nTmpVBRQuality;
	  bNiceThreads = bNiceThreadsTmp;
          wLameMode = wTmpLameMode;
	  break;

	case PSN_HELP:
	  break;

	case PSN_RESET:
	  break;

	default:
	  break;
	}
      break;
    }

  return FALSE;
}


/*
 * Used to initialize the values in the dialog.  If bGet is TRUE, values are
 * read and stored in tmp variables.  Otherwise, the values of the tmp vars
 * are written to the dialogs values.
 */
void GetSetMP3DlgCurrentVals( BOOL bGet )
{
  if ( bGet )
    {
      bCRCTmp = bCRC;
      bID3Tmp = bID3;
      bOriginalTmp = bOriginal;
      bCopyrightTmp = bCopyright;
      bPrivateTmp = bPrivate;
      wTmpBitrate = wBitrate;
      wTmpMaxBitrate = wMaxBitrate;
      bListsInit = FALSE;
      bTmpVBR = bVBR;
      bTmpVBRHeader = bVBRHeader;
      nTmpQuality = nQuality;
      nTmpVBRQuality = nVBRQuality;
      bNiceThreadsTmp = bNiceThreads;
      wTmpLameMode = wLameMode;
    }
  else
    {
      bCRC = bCRCTmp;
      bID3 = bID3Tmp;
      bOriginal = bOriginalTmp;
      bCopyright = bCopyrightTmp;
      bPrivate = bPrivateTmp;
      wBitrate = wTmpBitrate;
      wMaxBitrate = wTmpMaxBitrate;
      bVBR = bTmpVBR;
      bVBRHeader = bTmpVBRHeader;
      nQuality = nTmpQuality;
      nVBRQuality = nTmpVBRQuality;
      bNiceThreads = bNiceThreadsTmp;
      wLameMode = wTmpLameMode;
    }
}

