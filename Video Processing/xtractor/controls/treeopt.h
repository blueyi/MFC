#ifndef __TREEOPT_H_INC
#define __TREEOPT_H_INC

#include <windows.h>

/*
 * Tree-like structure for creating our TreeView property sheet
 */
typedef struct _tag_prefsheet {
  LPCTSTR lpszTemplate;        // the dialog template to use
  DLGPROC dlgproc;             // callback function
  BOOL isDefault;
  LPCTSTR lpszCaption;         // if NULL, the dialog caption is used
  struct _tag_prefsheet *sibling;
  struct _tag_prefsheet *child;
} PREFSHEET, *LPPREFSHEET;


typedef struct {
  LPCTSTR lpszTitle;
  HINSTANCE hInst;
  HWND hWndParent;
  LPPREFSHEET lpPrefSheet;
} CTPREFDIALOG, *LPCTPREFDIALOG;


int CreateTreeOptionDialog( LPCTPREFDIALOG );

#endif