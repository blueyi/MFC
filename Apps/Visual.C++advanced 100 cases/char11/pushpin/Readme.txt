Enclosed is the source for a CPushPinButton class. Its appearance is similar to the pin button as seen 
on the OpenLook window manager on X-Windows & property dialogs in MSDEV aka VC 4.x IDE.

The class is derived from CButton and can be easily used as follows:


1) Create a dialog template with an owner-draw button positioned where you want the push pin
button. The size of the button in the template does not matter.

2) Using Classwizard associate a CBitmap with the button you just created. Then modify the
declaration of the variable to make it a CPushPinButton instead of CButton




Enjoy,

21st November 1997
PJ Naughter,
email: pjn@indigo.ie
web: http://indigo.ie/~pjn
