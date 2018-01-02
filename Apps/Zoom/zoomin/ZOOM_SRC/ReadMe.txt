Instructions for ZoomIn
--------------------------

To run the ZoomIn utility, simply unzip the attached files into a
local folder and double-click ZoomIn.exe. When you run the program,
the ZoomIn icon (a magnifying glass) will appear at the bottom right
corner of your task bar indicating that the ZoomIn hot-key is enabled.
By default, the hot-key is Ctrl+<left apostrophe> (the left apostrophe--
at least that's what I call it--is located directly above the tab key).

From then on, whenever you press Ctrl+`, a magnification window will
appear beneath the mouse pointer. When you move the pointer, the
magnification window will also move. It takes a bit of getting used to,
but with a little practice you'll see that the magnified window displays
a zoomed-in version of the area around the mouse pointer. In addition,
the mouse pointer is slowed down to make it easier to control.

You can choose whether you want the zoom window to disapper when you
release the hot-key, or to stay visible until you press the hot-key
a second time. What's really nice is that even when the zoom window is
visible you can still perform all of the normal mouse functions. For
example, I always use ZoomIn when I'm editing a bitmap image in
PaintBrush--that way I don't have to waste time switching between
PaintBrush view modes.

To modify the ZoomIn settings (such as the hot-key combination), or to
turn it off completely, simply move the mouse pointer over the ZoomIn
icon in the task bar and click the right mouse button.


Version 1.0 changes
-------------------

- Updated bitmap to read Version 1.0

Version 0.04 changes
--------------------

- Fixed palette bug, which caused colors to display incorrectly
    in the Zoom window.

- Fixed double-click focus problem. However, if no application
    is active, the hot-key won't work.

- Added context sensitive help.

- Shift key combinations (such as Shift-Z) are no longer
    allowed.

- The refresh rate was slowed down from 50ms to 100ms to
    reduce flicker.

- Changed "Window Width" to "Zoom Area"

Version 0.03b changes
---------------------

- Fixed multiple instance problem. Attempting to open a second
	instance of ZoomIn simply displays the Properties dialog
	box of the first instance.

- Changed "Pixel Width" to "Window Width"

- Invalid entries for the Zoom Factor and Window Width are no
	longer allowed. A message is displayed when pressing the OK
	or Apply button.

- Increased the sizes of the text controls in the dialog box
	to account for small fonts.

- Fixed Show/Hide menu item text problem caused by combination
	of double click and hotkey press to open/close the Zoom
	window.

- Fixed problem with Exit while property page is visible. The
	chosen solution was to swith the focus to the property page
	instead of terminating.

Version 0.02b changes
---------------------

- Ability to show/hide zoom window from tray icon menu.
- Tray icon menu have been rearranged to be more consistent with
	Windows standard.
- Mouse movement speed is now properly restored if you exit ZoomIn
	while the zoom window is visible.
- About box now displays correct version number.

