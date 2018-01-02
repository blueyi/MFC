/*
 * outdlg.c - Copyright (C) 1999,2000 Jay A. Key
 *
 * Output options dialog for options property sheet.  Selection of 
 * output format (WAV/MP3), plus output directories are configured here.
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
#include "enc/xtenc.h"

BOOL SelectDirectory( HWND hParent, LPTSTR lpszDir, int len, BOOL bAutoCreate );
BOOL DirExists( char *dir );

// save old settings for output dialog config
static BOOL bInInit = FALSE;
static char szTmpMP3OutputDir[MAX_PATH+1];
static BOOL bTmpNormalize;
static int iTmpNormalizePercent;
static int iTmpNormalizeScanPercent;
static int iTmpEncoder;
static int iEncoders[7];
static BOOL bListsInit = FALSE;
static char *szEncText[] = { "Raw data", "Internal WAV", "Lame Encoder DLL", "Lame Encoder DLL", "Blade Encoder DLL", "Ogg Vorbis" };
static char *szDesc[] = {
  "Outputs only the raw, 44.1 KHz CD audio to the output file.  Requires approximately 10 MB per minute of audio.",
  "Outputs to a standard stereo CD-quality WAV file.  Requires approximately 10 MB per minute of audio.",
  "Encodes to MP3 format using the Lame Encoder DLL.  Disk space required will vary along with the desired bitrate.  At 128 kpbs, it requires approximately 1 MB per minute of audio.",
  "Encodes to MP3 format using the Lame Encoder DLL.  Disk space required will vary along with the desired bitrate.  At 128 kpbs, it requires approximately 1 MB per minute of audio.",
  "Encodes to MP3 format using the Blade Encoder DLL.  Disk space required will vary along with the desired bitrate.  At 128 kpbs, it requires approximately 1 MB per minute of audio.",
  "Encodes to the Ogg Vorbis format using Vorb_Enc.dll.  Disk space required will vary along with the desired bitrate.  At 128 kbps, it requires approximately 1 MB per minute of audio."
};
//static HWND hOutDlg;


/*
 * Called in response to PSN_KILLACTIVE.  Should validate all values in the
 * dialog, and save them to the temp variables.
 */
BOOL ValidateOutputDlg( HWND hWnd )
{
  if ( !DirExists( szTmpMP3OutputDir ) )
    {
      MessageBox( hWnd, "The folder you have selected for MP3 output does not exist, or is not accessible.", "Huh?!?", MB_APPLMODAL | MB_ICONERROR | MB_OK );
      return FALSE;
    }
  
  if ( (iTmpNormalizePercent > 100) || (iTmpNormalizePercent <= 0) )
  {
    MessageBox( hWnd, "You must select a normalization level between 1 and 100 percent.", "Huh?!?", MB_APPLMODAL | MB_ICONERROR | MB_OK );
    return FALSE;
  }

  if ( (iTmpNormalizeScanPercent > 100) || (iTmpNormalizeScanPercent < 10) )
  {
    MessageBox( hWnd, "You must select a normalization scan percentage between 10 and 100.", "Huh?!?", MB_APPLMODAL | MB_ICONERROR | MB_OK );
    return FALSE;
  }

  return TRUE;
}



/*
 * Called in response to PSN_SETACTIVE.  Sets dialog items with the values
 * from the temp variables.
 */
void ConfigureOutputDlg( HWND hWnd )
{
  int i, j;
  bInInit = FALSE;

  // sets the dialog's items with the temporary values.
  SetDlgItemText( hWnd, IDE_MP3DIR, szTmpMP3OutputDir );

  for( i = 0; i < 7; i++ )
    iEncoders[i] = -1;


  if ( !bListsInit )
    {
      for( i = XT_ENC_RAW, j = 0; i <= XT_ENC_VORBIS; i++ )
	if ( xtEncoderAvail( i ) )
	  {
	    iEncoders[j++] = i;
	    SendDlgItemMessage( hWnd, IDCBX_ENCODER, CB_ADDSTRING, 0, (LPARAM)szEncText[i] );
	  }

      SendDlgItemMessage( hWnd, IDCBX_ENCODER, CB_SELECTSTRING, -1, (LPARAM)szEncText[iEncoder] );
      SetDlgItemText( hWnd, IDT_DESC, szDesc[iEncoder] );

      bListsInit = TRUE;
    }
  
  CheckDlgButton( hWnd, IDCKB_NORMALIZE, bTmpNormalize?BST_CHECKED:BST_UNCHECKED );
  SetDlgItemInt( hWnd, IDE_NORMVAL, iTmpNormalizePercent, FALSE );
  SetDlgItemInt( hWnd, IDE_NORMSCANPCT, iTmpNormalizeScanPercent, FALSE );

  bInInit = TRUE;
}


BOOL CALLBACK OutputDlgProc( HWND hWnd, UINT uMsg, WPARAM wParam,
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
	case IDE_NORMVAL:
	  if ( wNotify == EN_CHANGE )
	    iTmpNormalizePercent = GetDlgItemInt( hWnd, IDE_NORMVAL, NULL, FALSE );
	  else
	    bChanged = FALSE;
	  break;
          
        case IDE_NORMSCANPCT:
          if ( wNotify == EN_CHANGE )
            iTmpNormalizeScanPercent = GetDlgItemInt( hWnd, IDE_NORMSCANPCT, NULL, FALSE );
          else
            bChanged = FALSE;
          break;

	case IDE_MP3DIR:
	  if ( wNotify == EN_CHANGE )
	    GetDlgItemText( hWnd, IDE_MP3DIR, szTmpMP3OutputDir, MAX_PATH+1 );
	  else
	    bChanged = FALSE;
	  break;

	case IDBN_BRWSEMP3DIR:
	  if ( SelectDirectory( hWnd, szTmpMP3OutputDir, MAX_PATH + 1, TRUE ) )
	    SetDlgItemText( hWnd, IDE_MP3DIR, szTmpMP3OutputDir );
	  else
	    bChanged = FALSE;
	  break;

	case IDCBX_ENCODER:
	  if ( wNotify == CBN_SELCHANGE )
          {
  	    i = SendDlgItemMessage( hWnd, IDCBX_ENCODER, CB_GETCURSEL, 0, 0L );
            iTmpEncoder = iEncoders[i];
            SetDlgItemText( hWnd, IDT_DESC, szDesc[iTmpEncoder] );
          }
          else
            bChanged = FALSE;
	  break;
        
        case IDCKB_NORMALIZE:
          bTmpNormalize = !bTmpNormalize;
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
	  ConfigureOutputDlg( hWnd );
	  break;

	case PSN_KILLACTIVE:  //losing focus
#if 1
	  if ( ValidateOutputDlg( hWnd ) )
	    // ok to lose focus
	    SetWindowLong( hWnd, DWL_MSGRESULT, FALSE );
	  else
	    {
	      // don't use allow loss of focus
	      SetWindowLong( hWnd, DWL_MSGRESULT, TRUE );
	      return TRUE;
	    }
#endif
	  break;

	case PSN_QUERYCANCEL:
	  break;

	case PSN_APPLY:
	  //bMP3 = bMP3Tmp;
	  //lstrcpy( szWavOutputDir, szTmpWavOutputDir );
	  lstrcpy( szMP3OutputDir, szTmpMP3OutputDir );
	  iEncoder = iTmpEncoder;
          iNormalizePercent = iTmpNormalizePercent;
          iNormalizeScanPercent = iTmpNormalizeScanPercent;
          bNormalize = bTmpNormalize;
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
void GetSetOutputDlgCurrentVals( BOOL bGet )
{
  if ( bGet )
    {
      lstrcpy( szTmpMP3OutputDir, szMP3OutputDir );
      iTmpEncoder = iEncoder;
      bListsInit = FALSE;
      bTmpNormalize = bNormalize;
      iTmpNormalizePercent = iNormalizePercent;
      iTmpNormalizeScanPercent = iNormalizeScanPercent;
    }
  else
    {
      lstrcpy( szMP3OutputDir, szTmpMP3OutputDir );
      iEncoder = iTmpEncoder;
      bNormalize = bTmpNormalize;
      iNormalizePercent = iTmpNormalizePercent;
      iNormalizeScanPercent = iTmpNormalizeScanPercent;
    }
}

