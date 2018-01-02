// GRADPAL.H
// Written by chensu


// m_nPaintDir:
// GPD_TTOB - top to bottom,
// GPD_BTOT - bottom to top,
// GPD_LTOR - left to right,
// GPD_RTOL - right to left
#define    GPD_TTOB			0
#define    GPD_BTOT			1
#define    GPD_LTOR			2
#define    GPD_RTOL			3

// m_nPaintRGB: a combination of one or more of the following values
// i.e.:
// GPC_RED							-	Red
// GPC_GREEN						-	Green
// GPC_BLUE							-	Blue
// GPC_RED | GPC_GREEN				-	Yellow
// GPC_RED | GPC_BLUE				-	Purple
// GPC_GREEN | GPC_BLUE				-	Cyan
// GPC_RED | GPC_GREEN | GPC_BLUE	-	Grey
#define    GPC_RED			0x0001
#define    GPC_GREEN 		0x0002
#define    GPC_BLUE			0x0004


//-----------------------------------------------------------------------------
class CGradpalApp : public CWinApp
{
	public:
		virtual BOOL InitInstance();
};
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
class CGradpalWnd : public CFrameWnd
{
	public:
		CGradpalWnd();
		inline BOOL CreateWnd();
	
	protected:
		afx_msg BOOL OnQueryNewPalette();
		afx_msg void OnPaletteChanged(CWnd *pFocusWnd);
		afx_msg void OnPaint();
		
		DECLARE_MESSAGE_MAP()
	
	private:
		const int m_nPaintSteps, m_nPaintDir;
		const UINT m_nPaintRGB;

		CPalette m_Pal;
		
		void PaintGradiantRect(CDC *pDC, const RECT &rect) const;
		BOOL CreateGradPalette();
};
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
inline BOOL CGradpalWnd::CreateWnd()
{
	return this->Create(NULL, _T("Gradient Palette"));
}
//-----------------------------------------------------------------------------


// End of GRADPAL.H
