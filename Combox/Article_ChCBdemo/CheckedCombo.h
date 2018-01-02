//////////////////////////////////////////////////////////////////////////////
///
/// @file checkedCombo.h
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

#ifndef CHECKEDCOMBO_H 
#define CHECKEDCOMBO_H

/****************************************************************************/
/// @name Checked combobox specific messages.
/// @{

#define CBCM_FLATCHECKS  WM_USER + 1 ///<Set flat style check boxes
#define CBCM_CHECKALL  WM_USER + 2   ///<Enable right mouse button select/deselect all

/// @}

/****************************************************************************/
/// @name Macroes
/// @{

/// @def CheckedComboBox_SetCheckState(hwndCtl, iIndex, fCheck)
///
/// @brief Checks or unchecks an item in a checked combobox control.
///
/// @param hwndCtl The handle of a checked combobox.
/// @param iIndex The zero-based index of the item for which to set the check state.
/// @param fCheck A value that is set to TRUE to select the item, or FALSE to deselect it.
///
/// @returns The zero-based index of the item in the combobox. If an error occurs,
///           the return value is CB_ERR. 
#define CheckedComboBox_SetCheckState(hwndCtl, iIndex, fCheck) \
    (0 > ComboBox_SetItemData((hwndCtl), (iIndex), (fCheck)) ? CB_ERR : \
     (InvalidateRgn((hwndCtl), NULL, FALSE), (iIndex)))

/// @def CheckedComboBox_GetCheckState(hwndCtl, iIndex)
///
/// @brief Gets the checked state of an item in a checked combobox control.
///
/// @param hwndCtl The handle of a checked combobox.
/// @param iIndex The zero-based index of the item for which to get the check state.
///
/// @returns Nonzero if the given item is checked, or zero otherwise. 
#define CheckedComboBox_GetCheckState(hwndCtl, iIndex) \
    (BOOL) ComboBox_GetItemData(hwndCtl, iIndex)

/// @def CheckedComboBox_SetFlatStyleChecks(hwndCtl, fFlat)
///
/// @brief Sets the appearance of the checkboxes.
///
/// @param hwndCtl The handle of a checked combobox.
/// @param fFlat TRUE for flat checkboxes, or FALSE for standard checkboxes.
///
/// @returns No return value.
#define CheckedComboBox_SetFlatStyleChecks(hwndCtl, fFlat) \
    ((void)SendMessage((hwndCtl),CBCM_FLATCHECKS,(WPARAM)(BOOL) (fFlat),(LPARAM)0L))

/// @def CheckedComboBox_EnableCheckAll(hwndCtl, fEnable)
///
/// @brief Sets the select/deselect all feature.
///
/// @param hwndCtl The handle of a checked combobox.
/// @param fEnable TRUE enables right mouse button select/deselect all feature, or FALSE disables feature.
///
/// @returns No return value.
#define CheckedComboBox_EnableCheckAll(hwndCtl, fEnable) \
    ((void)SendMessage((hwndCtl),CBCM_CHECKALL,(WPARAM)(BOOL) (fEnable),(LPARAM)0L))

/// @}

/****************************************************************************/
// Exported function prototypes

ATOM InitCheckedComboBox(HINSTANCE  hInstance);
HWND New_CheckedComboBox(HWND hParent, DWORD dwStyle, DWORD dwExStyle, DWORD dwID, INT x, INT y, INT nWidth, INT nHeight);

#endif //CHECKEDCOMBO_H
