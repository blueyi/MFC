//////////////////////////////////////////////////////////////////////////////
///
/// @file checkedCombo.c
///
/// @brief A checked comboBox control in Win32 SDK C.
///
/// @author David MacDermot
///
/// @par Comments:
///         This source is distributed in the hope that it will be useful,
///         but WITHOUT ANY WARRANTY; without even the implied warranty of
///         MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
/// 
/// @date 9-07-10
/// 
/// @todo 
///
/// @bug 
///
//////////////////////////////////////////////////////////////////////////////

#define UNICODE
#define _UNICODE

#define WIN32_LEAN_AND_MEAN

#include <tchar.h>
#include <stdlib.h>
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include "CheckedCombo.h"

#define WPROC _T("Wprc")          ///<Generic property tag
#define HCOMBO _T("hCombo")       ///<Generic property tag
#define PROPTEXT _T("Text")       ///<Generic property tag
#define PROPSTORAGE _T("Storage") ///<Generic property tag
#define ID_COMBOBOX 2000          ///<An Id for the ComboBox
#define FLATCHECKS 0x01           ///<Draw flat checks flag
#define CHECKALL 0x02             ///<Enable RMB check/uncheck all


/// @name Macroes
/// @{

/// @def NELEMS(a)
///
/// @brief Computes number of elements of an array.
///
/// @param a An array.
#define NELEMS(a) (sizeof(a) / sizeof((a)[0]))

/// @def ListBox_ItemFromPoint(hwndCtl, xPos, yPos)
///
/// @brief Gets the zero-based index of the item nearest the specified point
///         in a list box.
///
/// @param hwndCtl The handle of a listbox.
/// @param xPos The x coordinate of a point. 
/// @param yPos The y coordinate of a point.
///
/// @returns The return value contains the index of the nearest item
///           in the low-order word.  The high-order word is zero if
///           the specified point is in the client area of the list box,
///           or one if it is outside the client area.
#define ListBox_ItemFromPoint(hwndCtl, xPos, yPos) \
    (DWORD)SendMessage((hwndCtl),LB_ITEMFROMPOINT, \
        (WPARAM)0,MAKELPARAM((UINT)(xPos),(UINT)(yPos)))

/// @}

LPCTSTR g_szClassName = _T("CheckedComboBox");  ///< The classname.

/****************************************************************************/
//Functions
static LRESULT CALLBACK Combo_Proc(HWND, UINT, WPARAM, LPARAM);
static LRESULT CALLBACK ListBox_Proc(HWND, UINT, WPARAM, LPARAM);
static LRESULT CALLBACK Control_Proc(HWND, UINT, WPARAM, LPARAM);

#pragma region strings

/// @brief Concatenates two sub strings into a new string.
///
/// @param hwnd The handle to this control (where circular buffer stored)
/// @param str1 A string
/// @param str2 Another string.
///
/// @returns A pointer to a temporarily allocated string.
LPTSTR Join(HWND hwnd, LPTSTR str1, LPTSTR str2)
{
    register INT tmplen = 0;
    register LPTSTR strtmp;
    static INT StrCnt = 0;

    tmplen = _tcslen(str1) + _tcslen(str2);

    LPTSTR *ppStoriage = GetProp(hwnd, PROPSTORAGE);   //ppStoriage = allocated two string pointers
    StrCnt = (StrCnt + 1) & 1;
    if (ppStoriage[StrCnt])
        free(ppStoriage[StrCnt]);

    strtmp = (ppStoriage[StrCnt] = (LPTSTR)calloc(tmplen + 1, sizeof(TCHAR)));

    _tcscat(strtmp, str1);
    _tcscat(strtmp, str2);

    return strtmp;
}

/// @brief Allocate and store a string.
///
/// @param str The string to store.
///
/// @returns a Pointer to the allocated string.
LPTSTR New_AllocatedString(LPCTSTR str)
{
    if (NULL == str || _T('\0') == *str)
        str = _T("");
    LPTSTR tmp = (LPTSTR)calloc(_tcslen(str) + 1, sizeof(TCHAR));

    if (NULL == tmp)
    {
        return (LPTSTR)calloc(1, sizeof(TCHAR));
    }
    return _tmemmove(tmp, str, _tcslen(str));
}

/// @brief Allocate and store window text.
///
/// @param hwnd The handle to the the control's window.
/// @param szText The text to store.
///
/// @returns VOID.
VOID Text_SetProp(HWND hwnd, LPCTSTR szText)
{
    LPTSTR szProp = (LPTSTR)GetProp(hwnd, PROPTEXT);
    if (NULL != szProp)
        free(szProp);
    SetProp(hwnd, PROPTEXT, New_AllocatedString(szText));
}

/// @brief Retrieve a pointer to stored window text.
///
/// @param hwnd The handle to the the control's window.
///
/// @returns a pointer to a string of text.
LPTSTR Text_GetProp(HWND hwnd)
{
    static LPTSTR szProp;
    szProp = (LPTSTR)GetProp(hwnd, PROPTEXT);
    if (NULL == szProp)
        szProp = TEXT("");
    return szProp;
}

/// @brief Create the display text from the list of checked items.
///
/// @param hwnd The handle to this control (where circular buffer stored)
/// @param hwndCtl The handle of the combobox
/// @param pText Pointer to recieve text
///
/// @returns VOID.
VOID RecalcText(HWND hwnd, HWND hwndCtl, LPTSTR * pText)
{
    *pText = TEXT("");

    // Get the list count
    INT nCount = ComboBox_GetCount(hwndCtl);

    // Get the list separator
    TCHAR strSeparator[10] = { 0 };
    GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SLIST,
        strSeparator, sizeof(strSeparator));

    // If none found, then the ';'
    if (0 == _tcslen(strSeparator))
        strSeparator[0] = _T(';');

    // And one...
    strSeparator[1] = _T(' ');

    // Trim extra spaces
    strSeparator[2] = (TCHAR)0;

    for (INT i = 0; i < nCount; i++)
    {

        if (CheckedComboBox_GetCheckState(hwndCtl, i))
        {
            INT iLen = ComboBox_GetLBTextLen(hwndCtl, i);
            TCHAR buf[iLen + 1];
            _tmemset(buf, (TCHAR)0, NELEMS(buf));
            ComboBox_GetLBText(hwndCtl, i, &buf);

            if (0 < _tcslen(*pText))
                *pText = Join(hwnd, *pText, strSeparator);

            *pText = Join(hwnd, *pText, buf);
        }
    }
}

#pragma endregion strings

#pragma region ListBox event handlers

/// @brief Handles WM_CHAR message sent to the listbox.
///
/// @param hwnd  Handle of the listbox.
/// @param ch The character.
/// @param cRepeat The number of times the keystroke is repeated
///         as a result of the user holding down the key.
///
/// @returns VOID.
VOID ListBox_OnChar(HWND hwnd, TCHAR ch, INT cRepeat)
{
    if (VK_SPACE == ch)
    {
        HWND hCombo, hParent;

        hCombo = GetProp(hwnd, HCOMBO);
        if (NULL != hCombo)
        {
            hParent = GetParent(hCombo);
            if (NULL != hParent)
            {
                // Get the current selection
                INT nIndex = CallWindowProc((WNDPROC)GetProp(hwnd, WPROC),
                    hwnd, LB_GETCURSEL, 0, 0L);
                if (LB_ERR != nIndex)
                {
                    RECT rcItem;
                    ListBox_GetItemRect(hwnd, nIndex, &rcItem);
                    InvalidateRect(hwnd, &rcItem, FALSE);

                    // Invert the check mark
                    CheckedComboBox_SetCheckState(hCombo, nIndex, !CheckedComboBox_GetCheckState(hCombo, nIndex));
                }
            }
        }
    }
    // Do the default handling now
    FORWARD_WM_CHAR(hwnd, ch, cRepeat, DefWindowProc);
}

/// @brief Handles WM_LBUTTONDOWN message in the listbox.
///
/// @param hwnd  Handle of listbox.
/// @param fDoubleClick TRUE if this is a double click event.
/// @param x The xpos of the mouse.
/// @param y The ypos of the mouse.
/// @param keyFlags Set if certain keys down at time of click.
///
/// @returns VOID.
VOID ListBox_OnLButtonDown(HWND hwnd, BOOL fDoubleClick, INT x, INT y, UINT keyFlags)
{
    HWND hCombo, hParent;

    hCombo = GetProp(hwnd, HCOMBO);
    if (NULL != hCombo)
    {
        hParent = GetParent(hCombo);
        if (NULL != hParent)
        {
            DWORD dwRtn = ListBox_ItemFromPoint(hwnd, x, y);
            INT nIndex = (INT)LOWORD(dwRtn);
            BOOL fNonClient = (BOOL)HIWORD(dwRtn);

            if (!fNonClient)
            {
                // Invalidate this window
                RECT rcItem;
                ListBox_GetItemRect(hwnd, nIndex, &rcItem);
                InvalidateRect(hwnd, &rcItem, FALSE);

                CheckedComboBox_SetCheckState(hCombo, nIndex, !CheckedComboBox_GetCheckState(hCombo, nIndex));
            }
            else
            {
                // Do the default outside of box handling now (Single click close the popup
                //  window when clicked outside)
                CallWindowProc((WNDPROC)GetProp(hwnd, WPROC), hwnd, WM_LBUTTONDOWN, (WPARAM) (UINT)keyFlags, MAKELPARAM(x, y));
                return;
            }
        }
    }
    // Do the default inside of box handling now (such as hilite item and toggle
    //  check while keeping keyboard focus when clicked inside)
    FORWARD_WM_LBUTTONDOWN(hwnd, fDoubleClick, x, y, keyFlags, DefWindowProc);
}

/// @brief Handles WM_RBUTTONDOWN message in the listbox.
///
/// @param hwnd  Handle of listbox.
/// @param fDoubleClick TRUE if this is a double click event.
/// @param x The xpos of the mouse.
/// @param y The ypos of the mouse.
/// @param keyFlags Set if certain keys down at time of click.
///
/// @returns VOID.
VOID ListBox_OnRButtonDown(HWND hwnd, BOOL fDoubleClick, INT x, INT y, UINT keyFlags)
{
    HWND hCombo, hParent;

    hCombo = GetProp(hwnd, HCOMBO);
    if (NULL != hCombo)
    {
        if (CHECKALL & (DWORD)GetWindowLongPtr(hCombo, GWLP_USERDATA))
        {
            hParent = GetParent(hCombo);
            if (NULL != hParent)
            {
                INT nCount = ComboBox_GetCount(hCombo);
                INT nCheckCount = 0;

                for (INT i = 0; i < nCount; i++)
                {
                    if (CheckedComboBox_GetCheckState(hCombo, i))
                        nCheckCount++;
                }
                BOOL bCheck = nCheckCount != nCount;
                for (INT i = 0; i < nCount; i++)
                    CheckedComboBox_SetCheckState(hCombo, i, bCheck);

                // Make sure to invalidate this window as well
                InvalidateRgn(hwnd, NULL, FALSE);
            }
            // Do the default handling now
            FORWARD_WM_RBUTTONDOWN(hwnd, fDoubleClick, x, y, keyFlags, DefWindowProc);
        }
    }
}

#pragma endregion ListBox event handlers

#pragma region Drawing

/// @brief Handles WM_DRAWITEM message sent to the control when a visual aspect of
///         the owner-drawn combobox has changed.
///
/// @param hwnd  Handle of control.
/// @param lpDrawItem The structure that contains information about the item
///               to be drawn and the type of drawing required.
///
/// @returns VOID.
VOID Control_OnDrawItem(HWND hwnd, const DRAWITEMSTRUCT * lpDrawItem)
{
    if (lpDrawItem->itemAction & (ODA_DRAWENTIRE | ODA_SELECT))
    {
        COLORREF crBk;
        COLORREF crTx;

        HDC dc = lpDrawItem->hDC;

        RECT rcBitmap = lpDrawItem->rcItem;
        RECT rcText = lpDrawItem->rcItem;

        if (lpDrawItem->itemState & ODS_COMBOBOXEDIT)
        {
            LPTSTR strText;

            // Make sure the Text member is updated
            RecalcText(hwnd, lpDrawItem->hwndItem, &strText);
            Text_SetProp(hwnd, strText);

            // Erase and draw
            ExtTextOut(dc, 0, 0, ETO_OPAQUE, &rcText, 0, 0, 0);

            DrawText(dc, strText, _tcslen(strText), &rcText, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
        }
        else // it is one of the items
        {
            INT iLen = ComboBox_GetLBTextLen(lpDrawItem->hwndItem, lpDrawItem->itemID);
            TCHAR buf[iLen + 1];
            _tmemset(buf, (TCHAR)0, NELEMS(buf));
            ComboBox_GetLBText(lpDrawItem->hwndItem, lpDrawItem->itemID, &buf);

            TEXTMETRIC metrics;
            GetTextMetrics(dc, &metrics);

            // Checkboxes for larger sized fonts seem a bit crowded so adjust
            //  accordingly.
            INT iFactor = 24 < metrics.tmHeight ? -2 : -1;
            InflateRect(&rcBitmap, iFactor, iFactor);
            rcBitmap.right = rcBitmap.left + (rcBitmap.bottom - rcBitmap.top);

            rcText.left = rcBitmap.right + metrics.tmAveCharWidth;

            UINT nState = DFCS_BUTTONCHECK;

            if (lpDrawItem->itemData)
                nState |= DFCS_CHECKED;

            // Draw the checkmark using DrawFrameControl
            DrawFrameControl(dc, &rcBitmap, DFC_BUTTON, nState);

            if (FLATCHECKS & (DWORD)GetWindowLongPtr(lpDrawItem->hwndItem, GWLP_USERDATA))
            {
                //Make border thin
                FrameRect(lpDrawItem->hDC, &rcBitmap, GetSysColorBrush(COLOR_BTNSHADOW));
                // Extra pass for larger font sized checkboxes
                for(int i = 24 < metrics.tmHeight ? 3 : 2; 0 < i; i--)
                {
                    InflateRect(&rcBitmap, -1, -1);
                    FrameRect(lpDrawItem->hDC, &rcBitmap, GetSysColorBrush(COLOR_WINDOW));
                }
            }
            if (lpDrawItem->itemState & (ODS_SELECTED))
            {
                crBk = GetBkColor(dc);
                crTx = GetTextColor(dc);

                SetBkColor(dc, GetSysColor(COLOR_HIGHLIGHT));
                SetTextColor(dc, GetSysColor(COLOR_HIGHLIGHTTEXT));
            }

            // Erase and draw
            ExtTextOut(dc, 0, 0, ETO_OPAQUE, &rcText, 0, 0, 0);

            DrawText(dc, buf, _tcslen(buf), &rcText, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);

            if (lpDrawItem->itemState & (ODS_FOCUS | ODS_SELECTED) == (ODS_FOCUS | ODS_SELECTED))
                DrawFocusRect(dc, &rcText);

            // Ensure Defaults
            if (lpDrawItem->itemState & (ODS_SELECTED))
            {
                SetBkColor(dc, crBk);
                SetTextColor(dc, crTx);
            }
        }
    }
}

/// @brief Handles WM_MEASUREITEM message sent to the control when the owner-drawn
///         combobox is created.
///
/// @param hwnd  Handle of control.
/// @param lpMeasureItem The structure that contains the dimensions of the
///                       owner-drawn listbox.
///
/// @returns VOID.
VOID Control_OnMeasureItem(HWND hwnd, LPMEASUREITEMSTRUCT lpMeasureItem)
{
    // Get the HDC of the dialog or parent window of the custom control
    HWND hParent = GetParent(hwnd);
    HDC hDC = GetDC(hParent);

    // For common device contexts, GetDC assigns default attributes to the device
    //  context each time it is retrieved.  I guess the parent dialog's DC is common
    //  because I do not get the metrics for the dialog's font.  So I'll have to
    //  explicitly select the font into the device context to get it's metrics.
    HFONT hFont = SelectObject(hDC,(HFONT)SendMessage(hParent, WM_GETFONT, 0, 0L));
    TEXTMETRIC metrics;
    GetTextMetrics(hDC, &metrics);

    // Now that I have the metrics clean up (but don't delete the Parent's HFONT)
    SelectObject(hDC, hFont);
    ReleaseDC(hwnd, hDC);

    LONG lHeight = metrics.tmHeight + metrics.tmExternalLeading;
    if(lpMeasureItem->itemHeight < lHeight)
        lpMeasureItem->itemHeight = lHeight; 
}

#pragma endregion Drawing

#pragma region create destroy

/// @brief Initialize and register the checked combobox class.
///
/// @param hInstance Handle of application instance.
///
/// @returns ATOM If the function succeeds, the atom that uniquely identifies
///                the class being registered, otherwise 0.
ATOM InitCheckedComboBox(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    // Get standard combobox information
    wcex.cbSize = sizeof(wcex);
    if (!GetClassInfoEx(NULL, WC_COMBOBOX, &wcex))
        return 0;

    // Add our own stuff
    wcex.lpfnWndProc = (WNDPROC)Control_Proc;
    wcex.hInstance = hInstance;
    wcex.lpszClassName = g_szClassName;

    // Register our new class
    return RegisterClassEx(&wcex);
}

/// @brief Create an new instance of the checked combobox.
///
/// @param hParent Handle of the control's parent.
/// @param dwStyle The window style.
/// @param dwExStyle The extended window style.
/// @param dwID The ID for this control.
/// @param x The horizontal position of control.
/// @param y The vertical position of control.
/// @param nWidth The control width.
/// @param nHeight The control height.
///
/// @par Note:
///       The following Style parameters will be ignored by this control:
///         CBS_SIMPLE, CBS_DROPDOWN, and CBS_OWNERDRAWVARIABLE.
///
/// @returns HWND If the function succeeds, the checked combobox handle, otherwise NULL.
HWND New_CheckedComboBox(HWND hParent, DWORD dwStyle, DWORD dwExStyle, DWORD dwID, INT x, INT y, INT nWidth, INT nHeight)
{
    static ATOM aCheckedComboBox = 0;
    static HWND hCheckedComboBox;

    HINSTANCE hinst = (HINSTANCE)GetWindowLongPtr(hParent, GWLP_HINSTANCE);

    //Only need to register the CheckedComboBox once
    if (!aCheckedComboBox)
        aCheckedComboBox = InitCheckedComboBox(hinst);

    hCheckedComboBox = CreateWindowEx(dwExStyle, g_szClassName, NULL,
         dwStyle, x, y, nWidth, nHeight, hParent, (HMENU)dwID, hinst, NULL);

    return hCheckedComboBox;
}

/// @brief Handles WM_CREATE message.
///
/// @param hwnd Handle of control.
/// @param lpCreateStruct Pointer to a structure with creation data.
///
/// @returns BOOL If an application processes this message,
///                it should return TRUE to continue creation of the window.
BOOL Control_OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
    HWND hCombo;

    // Remove CBS_OWNERDRAWVARIABLE if defined and add the bits we need
    lpCreateStruct->style &= ~((DWORD)CBS_OWNERDRAWVARIABLE);

    // Use default strings. We need the itemdata to store checkmarks
    lpCreateStruct->style |= (CBS_DROPDOWNLIST | CBS_OWNERDRAWFIXED | CBS_HASSTRINGS);

    hCombo = CreateWindowEx(lpCreateStruct->dwExStyle, WC_COMBOBOX, NULL,
                  lpCreateStruct->style, 0, 0,
                  lpCreateStruct->cx, lpCreateStruct->cy, hwnd,
                  (HMENU)ID_COMBOBOX, lpCreateStruct->hInstance, NULL);

    if (!hCombo)
        return FALSE;

    SendMessage(hCombo, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), 0);

    // Subclass combobox and save the old proc
    SetProp(hCombo, WPROC, (HANDLE)GetWindowLongPtr(hCombo, GWLP_WNDPROC));
    SubclassWindow(hCombo, Combo_Proc);

    // Configure the parent window to be invisible,
    //  combobox child to determine appearance.
    SetWindowLongPtr(hwnd, GWL_STYLE, WS_CHILD |
         (WS_TABSTOP & GetWindowLongPtr(hwnd, GWL_STYLE) ? WS_TABSTOP : 0));

    SetWindowLongPtr(hwnd, GWL_EXSTYLE, 0l);

    // Certain window data is cached, so changes you make using SetWindowLongPtr
    //  will not take effect until you call the SetWindowPos() function.  SWP_FRAMECHANGED
    //  causes the window to recalculate the non client area and, in our case,
    //  remove scroll bar and border.
    RECT rc = {0};
    GetClientRect(hCombo, &rc); // Client = just the field of the combo 
    SetWindowPos(hwnd, NULL, lpCreateStruct->x, lpCreateStruct->y,
         lpCreateStruct->cx, rc.bottom - rc.top,
         SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);

    // Create and store a circular buffer (for Join())
    SetProp(hwnd, PROPSTORAGE, calloc(2, sizeof(LPTSTR)));

    return TRUE;
}

/// @brief Handles WM_DESTROY message.
///
/// @param hwnd Handle of Control.
///
/// @returns VOID.
VOID Control_OnDestroy(HWND hwnd)
{
    LPTSTR *ppStoriage = GetProp(hwnd, PROPSTORAGE);
    if (NULL != ppStoriage)
    {
        free(ppStoriage[0]);
        free(ppStoriage[1]);
        free(ppStoriage);
    }
    RemoveProp(hwnd, PROPSTORAGE);

    LPTSTR szText = (LPTSTR)GetProp(hwnd, PROPTEXT);
    if (NULL != szText)
        free(szText);
    RemoveProp(hwnd, PROPTEXT);
}

#pragma endregion create destroy

#pragma region event handlers

/// @brief Handles WM_SIZE message.
///
/// @param hwnd  Handle of control.
/// @param state Specifies the type of resizing requested.
/// @param cx The width of client area.
/// @param cy The height of client area.
///
/// @returns VOID.
VOID Control_OnSize(HWND hwnd, UINT state, INT cx, INT cy)
{
    HWND hCombo = GetDlgItem(hwnd, ID_COMBOBOX);
    RECT rc = {0};
    GetClientRect(hCombo, &rc); // Client = just the field of the combo 

    //Size comboBox component to fill parent
    SetWindowPos(hCombo, NULL, 0, 0, cx, rc.bottom - rc.top,
        SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
}

/// @brief Handles WM_GETTEXT message.
///
/// @param hwnd  Handle of control.
/// @param cchTextMax  Specifies the maximum number of characters to be copied,
///                     including the terminating null character.
/// @param lpszText Points to the buffer that is to receive the text.
///
/// @returns The number of characters copied.
INT Control_OnGetText(HWND hwnd, INT cchTextMax, LPTSTR lpszText)
{
    LPTSTR strText = Text_GetProp(hwnd);
    INT nChars = lstrlen(strText) + 1;
    if (nChars > cchTextMax)
        nChars = cchTextMax;

    lstrcpyn(lpszText, strText, nChars);
    return nChars;
}

/// @brief Handles WM_GETTEXTLENGTH message.
///
/// @param hwnd  Handle of control.
///
/// @returns The length, in characters, of the text.
INT Control_OnGetTextLength(HWND hwnd)
{
    LPTSTR strText = Text_GetProp(hwnd);
    return lstrlen(strText);
}

#pragma endregion event handlers

/// @brief Window procedure for the comboBox's dropdown listbox.
///
/// @param hList Handle of listbox.
/// @param msg Which message?
/// @param wParam Message parameter.
/// @param lParam Message parameter.
///
/// @returns LRESULT depends on message.
static LRESULT CALLBACK ListBox_Proc(HWND hList, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        HANDLE_MSG(hList, WM_CHAR, ListBox_OnChar);
        HANDLE_MSG(hList, WM_LBUTTONDOWN, ListBox_OnLButtonDown);
        HANDLE_MSG(hList, WM_RBUTTONDOWN, ListBox_OnRButtonDown);
        case WM_LBUTTONUP:
            // Don't do anything here so that the mouse continues to
            // track over the choices after keyboard input
            return 0;

        case WM_DESTROY:    //Unsubclass the Dropdown
        {
            WNDPROC wp = (WNDPROC)GetProp(hList, WPROC);
            if (NULL != wp)
            {
                SetWindowLongPtr(hList, GWLP_WNDPROC, (DWORD)wp);
                RemoveProp(hList, WPROC);
                RemoveProp(hList, HCOMBO);
                return CallWindowProc(wp, hList, msg, wParam, lParam);
            }
        }
        default:
            return CallWindowProc((WNDPROC)GetProp(hList, WPROC), hList,
                        msg, wParam, lParam);
    }
}

/// @brief Window procedure for the visible owner-drawn ComboBox control.
///
/// @param hCombo Handle of combobox.
/// @param msg Which message?
/// @param wParam Message parameter.
/// @param lParam Message parameter.
///
/// @par Note:
///      The main reason for this procedure is to catch WM_CTLCOLORLISTBOX before
///       the message is passed up to Control_Proc().  This allows us to associate the
///       HWND hCombo with the listbox we wish to subclass.  This is necessary since
///       GetParent() returns HWND_DESKTOP for the dropdown listbox.
///
/// @returns LRESULT depends on message.
static LRESULT CALLBACK Combo_Proc(HWND hCombo, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_DESTROY: //Unsubclass the ComboBox
        {
            WNDPROC wp = (WNDPROC)GetProp(hCombo, WPROC);
            if (NULL != wp)
            {
                SetWindowLongPtr(hCombo, GWLP_WNDPROC, (DWORD)wp);
                RemoveProp(hCombo, WPROC);
                return CallWindowProc(wp, hCombo, msg, wParam, lParam);
            }
            return 0;
        }

        // TAB to show/hide dropdown
        case WM_GETDLGCODE:
            return DLGC_WANTMESSAGE;
        case WM_KEYDOWN:
            if (VK_TAB == (UINT)wParam)
            {
                if (ComboBox_GetDroppedState(hCombo)) //TRUE == Visible
                {
                    ComboBox_ShowDropdown(hCombo, FALSE);
                    SetFocus(GetParent(GetParent(hCombo)));
                }
                else
                    ComboBox_ShowDropdown(hCombo, TRUE);
            }
            return CallWindowProc((WNDPROC)GetProp(hCombo, WPROC), hCombo,
                        msg, wParam, lParam);
        // End code to show/hide dropdown with TAB

        case WM_CTLCOLORLISTBOX:
        {
            //If the listbox hasn't been subclassed yet, do so...
            HWND hList = (HWND)lParam;
            WNDPROC lpfn = (WNDPROC)GetProp(hList, WPROC);
            if (NULL == lpfn)
            {
                //Store referance to Parent comboBox
                SetProp(hList, HCOMBO, hCombo);

                //Subclass child and save the OldProc
                SetProp(hList, WPROC, (HANDLE)GetWindowLongPtr(hList, GWLP_WNDPROC));
                SubclassWindow(hList, ListBox_Proc);
            }
        }   //Fall through
        default:
            return CallWindowProc((WNDPROC)GetProp(hCombo, WPROC), hCombo,
                        msg, wParam, lParam);
    }
}

/// @brief Procedure to route unhandled messages to custom control or designated child.
///
/// @param hwnd Handle of control.
/// @param hChild Handle of designated child.
/// @param msg Which message?
/// @param wParam Message parameter.
/// @param lParam Message parameter.
///
/// @returns LRESULT depends on message.
static LRESULT DefaultHandler(HWND hwnd, HWND hChild, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        // These messages to be handled by this window
        case WM_DRAWITEM:
        case WM_MEASUREITEM:
        case WM_CREATE:
        case WM_DESTROY:
        case WM_SIZE:

        // Sending these to child will cause stack overflow
        case WM_CTLCOLORMSGBOX:
        case WM_CTLCOLOREDIT:
        case WM_CTLCOLORLISTBOX:
        case WM_CTLCOLORBTN:
        case WM_CTLCOLORDLG:
        case WM_CTLCOLORSCROLLBAR:
        case WM_CTLCOLORSTATIC:
        case WM_MOUSEACTIVATE:

        // Sending these to child will cause improper sizing / positioning
        case WM_WINDOWPOSCHANGING:
        case WM_WINDOWPOSCHANGED:
        case WM_NCCALCSIZE:

        // Sending this to child will mess up child paint
        case WM_PAINT:
            break; //<- End Fallthrough

        // Pass child notifications to parent
        case WM_COMMAND:
            FORWARD_WM_COMMAND(GetParent(hwnd), GetDlgCtrlID(hwnd), hwnd,
                 HIWORD(wParam), SNDMSG);
             return 0;
        case WM_NOTIFY:
            ((LPNMHDR)lParam)->hwndFrom = hwnd;
            ((LPNMHDR)lParam)->idFrom = GetDlgCtrlID(hwnd);
            return FORWARD_WM_NOTIFY(GetParent(hwnd), ((LPNMHDR)lParam)->idFrom,
                (LPNMHDR)lParam, SNDMSG);

        default: // The rest of the messages passed to child (if it exists)
        {
            if(NULL != hChild)
                return SNDMSG(hChild, msg, wParam, lParam);
        }
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

/// @brief Window procedure and public interface for the checked combo control.
///
/// @param hwnd Handle of control.
/// @param msg Which message?
/// @param wParam Message parameter.
/// @param lParam Message parameter.
///
/// @returns LRESULT depends on message.
static LRESULT CALLBACK Control_Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        HANDLE_MSG(hwnd, WM_DRAWITEM, Control_OnDrawItem);
        HANDLE_MSG(hwnd, WM_MEASUREITEM, Control_OnMeasureItem);
        HANDLE_MSG(hwnd, WM_CREATE, Control_OnCreate);
        HANDLE_MSG(hwnd, WM_DESTROY, Control_OnDestroy);
        HANDLE_MSG(hwnd, WM_SIZE, Control_OnSize);
        HANDLE_MSG(hwnd, WM_GETTEXT, Control_OnGetText);
        HANDLE_MSG(hwnd, WM_GETTEXTLENGTH, Control_OnGetTextLength);
        case WM_SETTEXT:
            return 0; // Text to be set by drop down selection only.
        case CBCM_FLATCHECKS:
        {
            DWORD dwUserData = (DWORD)GetWindowLongPtr(GetDlgItem(hwnd, ID_COMBOBOX),
                                           GWLP_USERDATA);
            if (FALSE != (BOOL)wParam)
                dwUserData |= FLATCHECKS;
            else
                dwUserData &= ~FLATCHECKS;

            return SetWindowLongPtr(GetDlgItem(hwnd, ID_COMBOBOX),
                        GWLP_USERDATA, (LONG_PTR)dwUserData);
        }
        case CBCM_CHECKALL:
        {
            DWORD dwUserData = (DWORD)GetWindowLongPtr(GetDlgItem(hwnd, ID_COMBOBOX),
                                           GWLP_USERDATA);
            if (FALSE != (BOOL)wParam)
                dwUserData |= CHECKALL;
            else
                dwUserData &= ~CHECKALL;

            return SetWindowLongPtr(GetDlgItem(hwnd, ID_COMBOBOX),
                        GWLP_USERDATA, (LONG_PTR)dwUserData);
        }
        default:
            return DefaultHandler(hwnd, GetDlgItem(hwnd, ID_COMBOBOX), msg, wParam, lParam);

    }
}
