/*
 * cddlg.c - Copyright (C) 1999,2000 Jay A. Key
 *
 * CD configuration dialog for options property sheet.
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

HCDROM openCDHandle( int idx );
BYTE getReadType( void );

// save old settings for CD configuration
static DWORD tmpReadMode;           // jitter correction mode
static DWORD tmpMaxRip;             // number of frames to read at once
static DWORD tmpJitterCheck;        // # of frames to match for jitter corr.
static DWORD tmpNumOverlap;         // # of frames to overlap for jitter corr.
static int   tmpCdlistIdx;          // index of selected CD unit (in cdlist)
static BOOL tmpAutoTOC;             // automatically scan TOC of CD-ROM
static BOOL tmpAutoCheck;           // automatically check all tracks
static BOOL tmpReadType;            // read algorithm to use
static BOOL bCDInit;                // set to TRUE while initializing
static BOOL bCDListInit = FALSE;    // have we already filled the combo-boxes?

static HWND hCDDlg = NULL;          // cd-options dialog handle

/*
 * This array defines the mapping between items in the drive type combobox
 * and the read function to use for GetCDHandle().  There are seven items in 
 * the combobox.  For example, selecting item 5 in the combobox will map to
 * read type 6 (CDR_READ_D4).
 *
 * It is necessary because CDR_READ6 is not implemented in the current version,
 * and defaults to CDR_READ10.  Future versions may deprecate the CDR_READ6
 * mode entirely.
 *
 *   Index  Value  Type          Text
 *       0      0  CDR_ANY       Autodetect
 *       1      1  CDR_ATAPI1    ATAPI (1)
 *       2      2  CDR_ATAPI2    ATAPI (2)
 *       3      4  CDR_READ10    SCSI - Generic
 *       4      5  CDR_READ_D8   SCSI - Plextor
 *       5      6  CDR_READ_D4   SCSI - NEC
 *       6      7  CDR_READ_D_1  SCSI - NEC(2)
 *       7      8  CDR_READ10_2  SCSI - Generic(2)
 */
#define NUMDRVTYPES 9
// maps drive type to index in combobox
// drvtypeidx[drivetype] = comboboxindex
static int drvtypeidx[NUMDRVTYPES] = { 0, 1, 2, 3, 3, 4, 5, 6, 7 };


/*
 * Performs any necessary validation.  Reads the values from the dialog into
 * local variables, and validates them.  If they pass, the values are stored
 * in the static temp variables.
 */
BOOL ValidateCDDlg( HWND hWnd )
{
  if ( tmpReadMode != CDRM_NOJITTER )
    {
      if ( (tmpNumOverlap < tmpJitterCheck + 2)
	   || (tmpNumOverlap >= tmpMaxRip) )
	{
	  MessageBox( hWnd, "Invalid Jitter Correction Settings!",
		      "X-Tractor",
		      MB_APPLMODAL | MB_ICONERROR | MB_OK );
	  return FALSE;
	}
    }

  return TRUE;
}




void ConfigureCDDlg( HWND hWnd )
{
  BYTE i;

  hCDDlg = hWnd;

  bCDInit = FALSE;
  switch( tmpReadMode )
    {
    case CDRM_NOJITTER:
      SendDlgItemMessage( hWnd, IDE_NUMOVER, WM_ENABLE, (WPARAM)FALSE, 0L );
      SendDlgItemMessage( hWnd, IDE_NUMCHECK, WM_ENABLE, (WPARAM)FALSE, 0L );
      CheckRadioButton( hWnd, IDRBN_ALWAYS, IDRBN_NEVER, IDRBN_NEVER );
      break;
    case CDRM_JITTER:
      CheckRadioButton( hWnd, IDRBN_ALWAYS, IDRBN_NEVER, IDRBN_ALWAYS );
      break;
    default:
    case CDRM_JITTERONERR:
      tmpReadMode = CDRM_JITTERONERR;
      CheckRadioButton( hWnd, IDRBN_ALWAYS, IDRBN_NEVER, IDRBN_ONERR );
      break;
    }
  CheckDlgButton( hWnd, IDCKB_AUTOTOC, bAutoTOC?BST_CHECKED:BST_UNCHECKED );
  CheckDlgButton( hWnd, IDCKB_AUTOCHECK, bAutoCheck?BST_CHECKED:BST_UNCHECKED );

  SetDlgItemInt( hWnd, IDE_NUMREAD, tmpMaxRip, FALSE );
  SetDlgItemInt( hWnd, IDE_NUMCHECK, tmpJitterCheck, FALSE );
  SetDlgItemInt( hWnd, IDE_NUMOVER, tmpNumOverlap, FALSE );
  if ( tmpCdlistIdx == -1 )
    tmpCdlistIdx = 0;
  SendDlgItemMessage( hWnd, IDCBX_CDLIST, CB_SETCURSEL, (WPARAM)tmpCdlistIdx,
		      0L );

  if ( !bCDListInit )
    {
      for( i = 0; i < cdlist.num; i++ )
	SendDlgItemMessage( hWnd, IDCBX_CDLIST, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)cdlist.cd[i].id );
      bCDListInit = TRUE;
      SendDlgItemMessage( hWnd, IDCBX_DRVTYPE, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"Autodetect" );
      SendDlgItemMessage( hWnd, IDCBX_DRVTYPE, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"ATAPI (1)" );
      SendDlgItemMessage( hWnd, IDCBX_DRVTYPE, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"ATAPI (2)" );
      SendDlgItemMessage( hWnd, IDCBX_DRVTYPE, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"SCSI - Generic" );
      SendDlgItemMessage( hWnd, IDCBX_DRVTYPE, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"SCSI - Plextor" );
      SendDlgItemMessage( hWnd, IDCBX_DRVTYPE, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"SCSI - NEC" );
      SendDlgItemMessage( hWnd, IDCBX_DRVTYPE, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"SCSI - NEC(2)" );
      SendDlgItemMessage( hWnd, IDCBX_DRVTYPE, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"SCSI - Generic(2)" );
    }

  if ( cdlistIdx != -1 )
    SendDlgItemMessage( hWnd, IDCBX_CDLIST, CB_SETCURSEL, (WPARAM)cdlistIdx,
			0L );
  else
    SendDlgItemMessage( hWnd, IDCBX_CDLIST, CB_SETCURSEL, 0, 0L );

  if ( tmpReadType > 8 )
    tmpReadType = 0;
  SendDlgItemMessage( hWnd, IDCBX_DRVTYPE, CB_SETCURSEL,
		      (WPARAM)drvtypeidx[tmpReadType], 0L );

  bCDInit = TRUE;
}


BOOL CALLBACK CDDlgProc( HWND hWnd, UINT uMsg, WPARAM wParam,
			     LPARAM lParam )
{
  //char buf[81];
  NMHDR *l = (NMHDR *)lParam;
  WORD wID;
  WORD wNotify;
  BOOL bChanged;

  switch( uMsg )
    {
    case WM_COMMAND:
      wID = LOWORD( wParam );
      wNotify = HIWORD( wParam );
      bChanged = TRUE;
      switch( wID )
	{
	case IDE_NUMREAD:
	  if ( wNotify == EN_CHANGE )
	    tmpMaxRip = GetDlgItemInt( hWnd, IDE_NUMREAD, NULL, FALSE );
	  else
	    bChanged = FALSE;
	  break;

	case IDE_NUMCHECK:
	  if ( wNotify == EN_CHANGE )
	    tmpJitterCheck = GetDlgItemInt( hWnd, IDE_NUMCHECK, NULL, FALSE );
	  else
	    bChanged = FALSE;
	  break;

	case IDE_NUMOVER:
	  if ( wNotify == EN_CHANGE )
	    tmpNumOverlap = GetDlgItemInt( hWnd, IDE_NUMOVER, NULL, FALSE );
	  else
	    bChanged = FALSE;
	  break;

	case IDRBN_NEVER:
	  tmpReadMode = CDRM_NOJITTER;
	  SendDlgItemMessage( hWnd, IDE_NUMOVER, WM_ENABLE, (WPARAM)FALSE, 0L );
	  SendDlgItemMessage( hWnd, IDE_NUMCHECK, WM_ENABLE, (WPARAM)FALSE, 0L );
	  break;

	case IDRBN_ONERR:
	  tmpReadMode = CDRM_JITTERONERR;
	  SendDlgItemMessage( hWnd, IDE_NUMOVER, WM_ENABLE, (WPARAM)TRUE, 0L );
	  SendDlgItemMessage( hWnd, IDE_NUMCHECK, WM_ENABLE, (WPARAM)TRUE, 0L );
	  break;

	case IDRBN_ALWAYS:
	  tmpReadMode = CDRM_JITTER;
	  SendDlgItemMessage( hWnd, IDE_NUMOVER, WM_ENABLE, (WPARAM)TRUE, 0L );
	  SendDlgItemMessage( hWnd, IDE_NUMCHECK, WM_ENABLE, (WPARAM)TRUE, 0L );
	  break;

	case IDBN_RESET:
	  tmpMaxRip = 26;
	  tmpNumOverlap = 3;
	  tmpJitterCheck = 1;
	  tmpReadMode = CDRM_JITTER;
	  ConfigureCDDlg( hWnd );
	  break;

	case IDCKB_AUTOTOC:
	  tmpAutoTOC = !tmpAutoTOC;
	  break;

	case IDCKB_AUTOCHECK:
	  tmpAutoCheck = !tmpAutoCheck;
	  break;

	case IDCBX_DRVTYPE:
	  if ( wNotify == CBN_SELCHANGE )
	    tmpReadType = getReadType();
	  else
	    bChanged = FALSE;
	  break;

	case IDCBX_CDLIST:
	  if ( wNotify == CBN_SELCHANGE )
	    tmpCdlistIdx = SendDlgItemMessage( hWnd, IDCBX_CDLIST,
					       CB_GETCURSEL, 0, 0L );
	  else
	    bChanged = FALSE;
	  break;

	default:
	  bChanged = FALSE;
	  break;
	}
      if ( bCDInit && bChanged )
	SendMessage( (HWND)GetWindowLong( hWnd, GWL_HWNDPARENT ),
		     PSM_CHANGED, (WPARAM)hWnd, 0L );
      break;

    case WM_NOTIFY:
      switch( l->code )
	{
	case PSN_SETACTIVE:  // sent before page is shown
	  ConfigureCDDlg( hWnd );
	  break;

	case PSN_KILLACTIVE:  //losing focus (including clicking on Apply)
#if 1
	  if ( ValidateCDDlg( hWnd ) )
	    // ok to lose focus
	    SetWindowLong( hWnd, DWL_MSGRESULT, FALSE );
	  else
	    {
	      SetWindowLong( hWnd, DWL_MSGRESULT, TRUE );
	      return TRUE;
	    }
#endif
	  break;

	case PSN_QUERYCANCEL:
	  break;

	case PSN_APPLY:
	  bReadType    = tmpReadType;
	  if ( hCD )
	    CloseCDHandle( hCD );
	  hCD = NULL;
	  readMode     = tmpReadMode;
	  numOverlap   = tmpNumOverlap;
	  jitterCheck  = tmpJitterCheck;
	  maxRip       = tmpMaxRip;
	  bAutoTOC     = tmpAutoTOC;
          bAutoCheck   = tmpAutoCheck;
	  cdlistIdx    = tmpCdlistIdx;
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
 * are written to the application's global variables.
 */
void GetSetCDDlgCurrentVals( BOOL bGet )
{
  if ( bGet )
    {
      tmpReadMode = readMode;
      tmpNumOverlap = numOverlap;
      tmpJitterCheck = jitterCheck;
      tmpMaxRip = maxRip;
      tmpCdlistIdx = cdlistIdx;
      bCDListInit = FALSE;
      tmpAutoTOC = bAutoTOC;
      tmpAutoCheck = bAutoCheck;
      tmpReadType = bReadType;
    }
  else
    {
      readMode = tmpReadMode;
      numOverlap = tmpNumOverlap;
      jitterCheck = tmpJitterCheck;
      maxRip = tmpMaxRip;
      // if either a new cd unit is selected, or a new read algorithm
      // is selected, we have to close the current CD handle and open a
      // new one.
      if ( hCD &&
	   ( (cdlistIdx != tmpCdlistIdx) || (tmpReadType != bReadType) ) )
	{
	  CloseCDHandle( hCD );
	  hCD = NULL;
	}
      bReadType = tmpReadType;
      cdlistIdx = tmpCdlistIdx;
      if ( !hCD )
	hCD = openCDHandle( cdlistIdx );
      bAutoTOC = tmpAutoTOC;
      bAutoCheck = tmpAutoCheck;
    }
}


HCDROM openCDHandle( int idx )
{
  GETCDHAND cdh;

  ZeroMemory( &cdh, sizeof(cdh) );
  cdh.size        = sizeof(GETCDHAND);
  cdh.ver         = 1;
  cdh.ha          = cdlist.cd[idx].ha;
  cdh.tgt         = cdlist.cd[idx].tgt;
  cdh.lun         = cdlist.cd[idx].lun;
  cdh.readType    = bReadType;
  cdh.numOverlap  = (BYTE)numOverlap;
  cdh.numJitter   = (BYTE)jitterCheck;
  return GetCDHandle( &cdh );
}


BYTE getReadType( void )
{
  BYTE bTmp, i;

  bTmp = (BYTE)SendDlgItemMessage( hCDDlg, IDCBX_DRVTYPE, CB_GETCURSEL, 0, 0L );
  for( i = 0; i < NUMDRVTYPES; i++ )
    if ( drvtypeidx[i] == bTmp )
      return i;

  return 0;
}
