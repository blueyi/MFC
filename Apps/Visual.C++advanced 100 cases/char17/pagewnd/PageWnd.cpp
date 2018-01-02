// PageWnd.cpp : implementation file
//

#include "stdafx.h"
#include "math.h"

//#include "TestPage.h"
#include "PageWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageWnd

CPageWnd::CPageWnd(int nrows, int ncols)
{
  m_nrows = nrows;
  m_ncols = ncols;
  m_ncells = m_nrows * m_ncols;
  
  Init();
}

CPageWnd::~CPageWnd()
{
  if(m_pScrollData)     delete m_pScrollData;
  if(m_pDefFont)        delete m_pDefFont;
  if(m_pDefFontBold)    delete m_pDefFontBold;

  delete m_pEditCtrl;

  if(m_pBrushList)   {
    int nItems = m_pBrushList->GetSize();
    for(int i = 0; i < nItems; i++)  
      delete (*m_pBrushList)[i];
    delete m_pBrushList;
  }

  if(m_pFontList)    {
    int nItems = m_pFontList->GetSize();
    for(int i = 0; i < nItems; i++)  
      delete (*m_pFontList)[i];
    delete m_pFontList;
  }

  if(m_pGridPen)     delete m_pGridPen;

  for(int i = 0; i < m_ncells; i++)
    delete m_pCells[i];
  delete []m_pCells;
  
  delete []m_height;
  delete []m_width;
}


BEGIN_MESSAGE_MAP(CPageWnd, CWnd)
	//{{AFX_MSG_MAP(CPageWnd)
  ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPageWnd message handlers


void CPageWnd::Init()
{
  m_pEditCtrl = new CPageEdit();

  BkgndColor = GetSysColor(COLOR_BTNFACE);

  m_height = new int[m_nrows];
  m_width = new int[m_ncols];
  
  m_pCells = new CCell*[m_ncells];
  for(int i = 0; i < m_ncells; i++)  
    m_pCells[i] = new CCell;

  m_pScrollData = 0;
  m_pDefFont = 0;  
  m_pDefFontBold = 0;
  m_bCapture = false;      //capturing is not in progress
  m_ex_x 		 = - 1;        //capturing prevoius x position
  m_bGrid = true;
  m_charClip = '.';
  m_bReadOnly = false;
  m_CurSize = LoadCursor(NULL, IDC_SIZEWE);
  m_CurArrow = LoadCursor(NULL, IDC_ARROW);

  //ex position and current position of edit control
  m_rowEdit     = 1;
  m_colEdit     = 1;
  m_rowEditEx   = 1;
  m_colEditEx   = 1;
  m_EditRect.SetRectEmpty();
}

int CPageWnd::HeightInPixels(int h)
{
  CClientDC  dc(this);
  return MulDiv(-h, dc.GetDeviceCaps(LOGPIXELSY), 72);
}


int CPageWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
  CRect r(0, 0, 0, 0);
  m_pEditCtrl->Create(WS_CHILD | ES_LEFT | ES_WANTRETURN | WS_BORDER, r, this, 201);

  LOGFONT lf;
  TEXTMETRIC tm;
  ZeroMemory(&lf, sizeof(lf));
  lf.lfWeight = FW_NORMAL;
  lf.lfHeight = HeightInPixels(8);
  lf.lfCharSet = DEFAULT_CHARSET;
  strcpy(lf.lfFaceName, "Verdana");
  
  m_pDefFont = new CFont();
  if(!m_pDefFont->CreateFontIndirect(&lf))  {
    HFONT stdFont = HFONT(::GetStockObject(ANSI_VAR_FONT));
    ::GetObject(stdFont, sizeof(lf), &lf);
    m_pDefFont->CreateFontIndirect(&lf);
  }

  LOGFONT lf2 = lf;
  m_pDefFontBold = new CFont();
  lf2.lfWeight = FW_BOLD;
  m_pDefFontBold->CreateFontIndirect(&lf2);

  CClientDC dc(this);
  dc.SelectObject(m_pDefFont);
  dc.GetTextMetrics(&tm);

  m_stdwidth  = 5 * tm.tmMaxCharWidth;
  m_stdheight = (3 * tm.tmHeight) / 2;

  m_pScrollData = new CScrollData;
  m_pScrollData->XUnit   = m_stdwidth;
  m_pScrollData->YUnit   = m_stdheight;
  m_pScrollData->XRange  = m_ncols - 2;
  m_pScrollData->YRange  = m_nrows - 2;

  m_PageSize.cx = 0;
  m_PageSize.cy = 0;

  for(int row = 0; row < m_nrows; row++)  {
    m_height[row] = m_stdheight;
    m_PageSize.cy += m_height[row];
  }

  for(int col = 0; col < m_ncols; col++)  {
    m_width[col] = m_stdwidth;
    m_PageSize.cx += m_width[col];
  }

  m_pBrushList= new CArray<CBrush*, CBrush*>;
  m_pFontList = new CArray<CFont*, CFont*>;
  
  m_pBrushList->SetSize(0, 1);
  m_pBrushList->SetSize(0, 1);
  
  CFont* pDefFont = new CFont();
  pDefFont->CreateFontIndirect(&lf);
  m_pFontList->Add(pDefFont);

  COLORREF c1 = GetSysColor(COLOR_BTNFACE);
  COLORREF c2 = GetSysColor(COLOR_WINDOW);

  m_pBrushList->Add(new CBrush(c1));
  m_pBrushList->Add(new CBrush(c2));

  int row,col;
  for(row = 0; row < m_nrows; row++) {
    SetCellColor(row, 0, c1);
    SetCellAlign(row, 0, TA_CENTER);
  }

  for(col = 0; col < m_ncols; col++)  {
    SetCellColor(0, col, c1);
    SetCellAlign(0, col, TA_CENTER);
  }

  for(row = 1; row < m_nrows; row++)
    for(col = 1; col < m_ncols; col++)
      SetCellColor(row, col, c2);
  
  m_pGridPen = new CPen(PS_SOLID, 1, c1);

  return 0;
}



//
// Cell index functions
// ~~~~~~~~~~~~~~~~~~~~
//

// from cell index in structure (idx) to cell position in page (row, col)
//
void CPageWnd::GetCellPosition(int idx, int& row, int& col)
{
  if(idx < 0 || idx >= m_ncells)  {
    char szDebug[64];
    sprintf(szDebug, "Cell index %d is not valid", idx);
    OutputDebugString(szDebug);
    row = -1;
    col = -1;
  }
  else  {
    row = idx / m_ncols;
    col = int(fmod((double)idx, (double)m_ncols));
  }
}

// reverse
//
int CPageWnd::GetCellIndex(int row, int col)
{
  if( (row < 0 || row >= m_nrows) || (col < 0 || col >= m_ncols) )  {
    char szDebug[64];
    sprintf(szDebug, "Cell page idx (%d, %d) is not valid", row, col);
    OutputDebugString(szDebug);
    return -1;
  }
  else
    return (row * m_ncols + col);
}

// get pointer on cell at row, col position
//
CCell* CPageWnd::GetCell(int row, int col)
{
  int cellIdx = GetCellIndex(row, col);
  if(cellIdx == -1)
    return 0; //null cell
  else
    return m_pCells[cellIdx];
}

// get pointer with index cellIdx
//
CCell* CPageWnd::GetCell(int cellIdx)
{
  if(cellIdx < 0 || cellIdx >= m_ncells)
    return 0; //null cell
  else
    return m_pCells[cellIdx];
}

void CPageWnd::OnPaint() 
{
  CPaintDC dc(this);
  CRect&   rect = *(CRect*)&dc.m_ps.rcPaint;
  
  Paint(dc, dc.m_ps.fErase, rect);
}
  
void CPageWnd::Paint(CDC& dc, BOOL erase, CRect& rect)
{
  BOUND bound;
  //find start and end col nearest to invRect boundaries
  int width = m_width[0];
  bound.startcol = m_pScrollData->XPos + 1;
  if(width < rect.left)  {
    while(width < rect.left && bound.startcol < m_ncols)
      width += m_width[bound.startcol++];
    bound.startcol  -= 1;
    width           -= m_width[bound.startcol];
  }
  bound.startwidth = width;
  bound.endcol = bound.startcol;
  while(width < rect.right && bound.endcol < m_ncols)
    width += m_width[bound.endcol++];
  bound.endwidth = width;

  //find start and end row nearest to invRect boundaries
  int height = m_height[0];
  bound.startrow = m_pScrollData->YPos + 1;
  if(height < rect.top)  {
    while(height < rect.top && bound.startrow < m_nrows)
      height += m_height[bound.startrow++];
    bound.startrow  -= 1;
    height    -= m_height[bound.startrow];
  }
  bound.startheight = height;
  bound.endrow      = bound.startrow;
  while(height < rect.bottom && bound.endrow < m_nrows)
    height += m_height[bound.endrow++];
  bound.endheight = height;

  Draw_ZeroZero(dc, rect);
  Draw_ZeroRow(dc, bound);
  Draw_ZeroCol(dc, bound);
  Draw_Contents(dc, bound);
  if(m_bGrid)
    Draw_Grid(dc, bound);

  if(!m_pEditCtrl->IsWindowVisible())
    MarkActiveCell(false, true);

  //update empty area
  CBrush* pBkBrush = new CBrush(BkgndColor);
  if(bound.endwidth < rect.right)  {
    CRect r(bound.endwidth, rect.top, rect.right, rect.bottom);
    dc.SelectObject(pBkBrush);
    dc.PatBlt(r.left, r.top, r.Width(), r.Height(), PATCOPY);
  }

  if(bound.endheight < rect.bottom)  {
    CRect r(rect.left, bound.endheight, rect.right, rect.bottom);
    dc.SelectObject(pBkBrush);
    dc.PatBlt(r.left, r.top, r.Width(), r.Height(), PATCOPY);
  }
  delete pBkBrush;

}

//drawing cell text
//
void CPageWnd::CellEntry(CDC& dc, int row, int col, CRect cellRect)
{
  char* celltext = GetCellTextPtr(row, col);
  if(celltext == 0) 
      return;

  cellRect.InflateRect(-1, -1);
  if(dc.GetBkMode() != TRANSPARENT);
    dc.SetBkMode(TRANSPARENT);

  dc.SelectObject(GetCellFont(row, col));
  bool useclip = false;
  CSize textsize = dc.GetTextExtent(celltext, strlen(celltext));
  if(row > 0 && col > 0 && textsize.cx > cellRect.Width())
    useclip = true;

  int x0, y0;
  y0 = cellRect.bottom - 2;
  short align = GetCellAlign(row, col);
  switch(align) {
    case TA_LEFT:
      x0 = cellRect.left + 2;
      break;

    case TA_CENTER:
      x0 = (cellRect.left + cellRect.right) / 2;
      break;

    case TA_RIGHT:
      x0 = cellRect.right - 2;
      break;
  }

  dc.SetTextAlign(align | TA_BOTTOM);
  dc.SetTextColor(GetCellTextColor(row, col));
  if(useclip)  {
    textsize = dc.GetTextExtent(&m_charClip, 1);
    int nchars = cellRect. Width() / textsize.cx + 2;
    char* lpszText = new char[nchars + 1];
    int i = 0;
    while(i < nchars)
      lpszText[i++] = m_charClip;
    lpszText[i] = 0;
    dc.ExtTextOut(x0, y0, ETO_CLIPPED, &cellRect, lpszText, strlen(lpszText), 0);
    delete []lpszText;
  }
  else
    dc.ExtTextOut(x0, y0, ETO_CLIPPED, &cellRect, celltext, strlen(celltext), 0);
}



//drawing 0,0  cell
//
void CPageWnd::Draw_ZeroZero(CDC& dc, CRect& rect)
{
  if(rect.left < m_width[0] || rect.top < m_height[0] ||
     (m_bCapture /*&& m_idx == 0*/))
  {
    CRect cellRect(0, 0, m_width[0] + 1, m_height[0] + 1);    
    dc.DrawEdge(&cellRect, EDGE_ETCHED, BF_RECT | BF_MIDDLE);
  }
}

//zero row painting (invRect as invalidated rect)
//
void CPageWnd::Draw_ZeroRow(CDC& dc, BOUND& bound)
{
  CRect cell(bound.startwidth, 0, bound.endwidth + 1, m_height[0]);

  for(int col = bound.startcol; col < bound.endcol; col++)  {
    cell.right = cell.left + m_width[col];
    CRect borRect(cell.left, cell.top, cell.right, cell.bottom);
    dc.DrawEdge(&borRect, BDR_RAISEDINNER, BF_RECT | BF_MIDDLE);
    CellEntry(dc, 0, col, borRect);
    cell.left = cell.right;
  }
}


//
//zero column painting
//
void CPageWnd::Draw_ZeroCol(CDC& dc, BOUND& bound)
{
  CRect cell(0, bound.startheight, m_width[0], bound.endheight);
  for(int row = bound.startrow; row < bound.endrow; row++)  {
    cell.bottom = cell.top + m_height[row];
    CRect borRect(cell.left, cell.top, cell.right, cell.bottom);
    dc.DrawEdge(&borRect, BDR_RAISEDINNER, BF_RECT | BF_MIDDLE);    
    CellEntry(dc, row, 0, borRect);
    cell.top = cell.bottom;
  }
}


//
//painting all cell contents except zero row and column
//
void CPageWnd::Draw_Contents(CDC& dc, BOUND& bound)
{
  CRect cellRect(bound.startwidth, bound.startheight,
                 bound.startwidth + m_width[bound.startcol],
                 bound.startheight + m_height[bound.startrow]);

  for(int row = bound.startrow; row < bound.endrow; row++)  {
    cellRect.left = bound.startwidth;
    for(int col = bound.startcol; col < bound.endcol; col++)  {
      cellRect.right = cellRect.left + m_width[col];
      dc.SelectObject(GetCellBrush(row, col));
      dc.PatBlt(cellRect.left, cellRect.top, cellRect.Width(), cellRect.Height(), PATCOPY);
      CellEntry(dc, row, col, cellRect);
      cellRect.left = cellRect.right;
    }
    cellRect.top = cellRect.bottom;
    cellRect.bottom = cellRect.bottom + m_height[row];
  }
}

//
//grid drawing
//
void CPageWnd::Draw_Grid(CDC& dc, BOUND& bound)
{
  dc.SelectObject(*m_pGridPen);

  CRect cellRect(bound.startwidth, bound.startheight,
                 bound.startwidth + m_width[bound.startcol],
                 bound.startheight + m_height[bound.startrow]);

  //vertical lines
  int y = bound.startheight;
  for(int row = bound.startrow; row < bound.endrow; row++)  {
    dc.MoveTo(bound.startwidth, y);
    dc.LineTo(bound.endwidth, y);
    y += m_height[row];
  }
  int x = bound.startwidth;
  for(int col = bound.startcol; col < bound.endcol; col++)  {
    dc.MoveTo(x, bound.startheight);
    dc.LineTo(x, bound.endheight);
    x += m_width[col];
  }
}

CBrush* CPageWnd::GetCellBrush(int row, int col)
{
  CCell* cell = GetCell(row, col);
  if(cell)  {
    CBrush* pbrush = (*m_pBrushList)[cell->m_bClrIdx];
    if(pbrush)  {
      return (pbrush);
    }
  }
  return 0;
}

//background color
COLORREF CPageWnd::GetCellColor(int row, int col)
{
  CCell* cell = GetCell(row, col);
  if(cell)  {
    CBrush* pbrush = (*m_pBrushList)[cell->m_bClrIdx];
    if(pbrush)  {
      LOGBRUSH lb;
      pbrush->GetObject(sizeof(lb), &lb);
      return lb.lbColor;
    }
  }
  return (COLORREF(GetSysColor(COLOR_WINDOW)));
}

//returns brush index in list or -1 if not successful
//
int CPageWnd::SetCellColor(int row, int col, COLORREF clr)
{
  CCell* cell = GetCell(row, col);
  if(cell)  {
    CBrush *pbrush = new CBrush(clr);
    LOGBRUSH lb;
    pbrush->GetObject(sizeof(lb), &lb);  //compare whole LOGBRUSH, not just color
    
    cell->m_bClrIdx = -1;
    int n = m_pBrushList->GetSize();
    for(int i = 0; i < n; i++)  {
      LOGBRUSH lbFound;
      (*m_pBrushList)[i]->GetObject(sizeof(lbFound), &lbFound);
       
      int comp = memcmp(&lb, &lbFound, sizeof(LOGBRUSH));
      if(comp == 0)  {
        cell->m_bClrIdx = i;
        delete pbrush;
        break;
      }
    }
    if(cell->m_bClrIdx == -1)   //not found      
      cell->m_bClrIdx = m_pBrushList->Add(pbrush);
    
    return cell->m_bClrIdx;
  }
  return -1;
}



BOOL CPageWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style |= WS_HSCROLL | WS_VSCROLL;

	return CWnd::PreCreateWindow(cs);
}

void CPageWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
  if(nType != SIZE_MINIMIZED)
  {
    AdjustScrollBars();
    Invalidate(false);
  }	
}


void CPageWnd::AdjustScrollBars()
{
  CRect r;
  GetClientRect(&r);

  SCROLLINFO si;
  int i;

  //horizontal scroll bar
  //

  //determine x page size
  int cx_visible = m_width[0];
  i = m_pScrollData->XPos + 1;
  while(cx_visible < r.right && i < m_pScrollData->XRange)
    cx_visible += m_width[i++];
  m_pScrollData->XPage = i - m_pScrollData->XPos;

  si.cbSize = sizeof(si);
  si.fMask  = SIF_RANGE | SIF_PAGE | SIF_POS;
  si.nMin   = 0;
  si.nMax   = m_pScrollData->XRange;
  si.nPage  = m_pScrollData->XPage;
  si.nPos   = m_pScrollData->XPos;
  ::SetScrollInfo(m_hWnd, SB_HORZ, &si, true);

  //vertical scroll bar
  //

  //determine y page size
  int cy_visible = m_height[0];
  i = m_pScrollData->YPos + 1;
  while(cy_visible < r.bottom && i < m_pScrollData->YRange)
    cy_visible += m_height[i++];
  m_pScrollData->YPage = i - m_pScrollData->YPos;

  si.cbSize = sizeof(si);
  si.fMask  = SIF_RANGE | SIF_PAGE | SIF_POS;
  si.nMin   = 0;
  si.nMax   = m_pScrollData->YRange;
  si.nPage  = m_pScrollData->YPage;
  si.nPos   = m_pScrollData->YPos;
  ::SetScrollInfo(m_hWnd, SB_VERT, &si, true);


  int sum;
  if(m_pScrollData->YPos != 0)
    ShowScrollBar(SB_VERT, true);   //show vert scrollbar
  else  {
    sum = 0;
    for(i = 0; i < m_nrows; i++)
      sum += m_height[i];
    if(sum >= r.Height())
      ShowScrollBar(SB_VERT, true);   //show vert scrollbar
    else
      ShowScrollBar(SB_VERT, false);   //hide vert scrollbar
  }

  if(m_pScrollData->XPos != 0)
    ShowScrollBar(SB_HORZ, true);   //show vert scrollbar
  else  {
    sum = 0;
    for(i = 0; i < m_ncols; i++)
      sum += m_width[i];

    if(sum >= r.Width())
      ShowScrollBar(SB_HORZ, true);
    else
      ShowScrollBar(SB_HORZ, false);   //do not show horz scrollbar
  }
}
void CPageWnd::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
  if(m_pEditCtrl->IsWindowVisible())
    m_pEditCtrl->SendMessage(WM_CHAR, VK_RETURN, 0L);

  int inc = 0;
  switch(nSBCode)  {

    case SB_LINEUP:
      inc = -1;
      break;

    case SB_LINEDOWN:
      inc = 1;
      break;

    case SB_PAGEUP:
      inc = -m_pScrollData->XPage;
      break;

    case SB_PAGEDOWN:
      inc = m_pScrollData->XPage;
      break;

    case SB_THUMBPOSITION:
      inc = nPos - m_pScrollData->XPos;
      break;
  }

  if(inc == 0)
    return;

  //determine amount of pixels to scroll
  int delta = 0;
  int col, newpos;
  if(inc > 0)  {
    newpos = min(m_pScrollData->XRange, m_pScrollData->XPos + inc);
    col = m_pScrollData->XPos + 1;
    while(col <= newpos)    //zero col (when XPos = 0) is not scrolled
      delta += m_width[col++];
  }
  else  {    //inc < 0
    newpos = max(0, m_pScrollData->XPos + inc);
    col = m_pScrollData->XPos;
    while(col > newpos)
      delta -= m_width[col--];
  }
  m_pScrollData->XPos = newpos;

  CRect rcClient;
  GetClientRect(&rcClient);
  CRect scrollRect(m_width[0] + 1, 0, rcClient.right, rcClient.bottom);
  ScrollWindowEx(-delta, 0, &scrollRect, &scrollRect, 0, 0, SW_INVALIDATE | SW_SCROLLCHILDREN);
  SCROLLINFO si;
  si.cbSize = sizeof(si);
  si.fMask  = SIF_POS;
  si.nPos   = m_pScrollData->XPos;
  ::SetScrollInfo(m_hWnd, SB_HORZ, &si, true);
  m_EditRect.OffsetRect(/*m_EditRect.left + */delta, 0/*m_EditRect.top*/);  
  UpdateWindow();
}

void CPageWnd::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
  if(m_pEditCtrl->IsWindowVisible())
    m_pEditCtrl->SendMessage(WM_CHAR, VK_RETURN, 0L);

  int inc = 0;
  switch(nSBCode)  {

    case SB_LINEUP:
      inc = -1;
      break;

    case SB_LINEDOWN:
      inc = 1;
      break;

    case SB_PAGEUP:
      inc = -m_pScrollData->YPage;
      break;

    case SB_PAGEDOWN:
      inc = m_pScrollData->YPage;
      break;

    case SB_THUMBPOSITION:
      inc = nPos - m_pScrollData->YPos;
      break;
  }

  if(inc == 0)
    return;

  //determine amount of pixels to scroll
  int delta = 0;
  int row, newpos;
  if(inc > 0)  {
    newpos = min(m_pScrollData->YRange, m_pScrollData->YPos + inc);
    row = m_pScrollData->YPos + 1;
    while(row <= newpos)    //zero row ( YPos = 0) is not scrolled
      delta += m_height[row++];
  }
  else  {    //inc < 0
    newpos = max(0, m_pScrollData->YPos + inc);
    row = m_pScrollData->YPos;
    while(row > newpos)
      delta -= m_height[row--];
  }
  m_pScrollData->YPos = newpos;

  CRect rcClient;
  GetClientRect(rcClient);
  CRect scrollRect(0, m_height[0] + 1, rcClient.right, rcClient.bottom);

  ScrollWindowEx(0, -delta, &scrollRect, &scrollRect, 0, 0, SW_INVALIDATE | SW_SCROLLCHILDREN);
  SCROLLINFO si;
  si.cbSize = sizeof(si);
  si.fMask  = SIF_POS;
  si.nPos   = m_pScrollData->YPos;
  ::SetScrollInfo(m_hWnd, SB_VERT, &si, true);
  m_EditRect.OffsetRect(0/*m_EditRect.left*/, /*m_EditRect.top + */delta);  
  UpdateWindow();

}


//cell text functions
//~~~~~~~~~~~~~~~~~~~

// returns cell text pointer (useful in internal loops)
//
char* CPageWnd::GetCellTextPtr(int row, int col)
{
  CCell* cell = GetCell(row, col);
  if(cell)
    return cell->m_pcontents;
  else
    return 0;
}


// reverse
//
bool CPageWnd::SetCellText(int row, int col, char* szText)
{
  CCell* cell = GetCell(row, col);
  if(cell)  {
    if(cell->m_pcontents)
      delete []cell->m_pcontents;
    int n = strlen(szText);
    cell->m_pcontents = new char[n + 1];
    strncpy(cell->m_pcontents, szText, n + 1);
    return true;
  }
  return false;
}

// copies cell text in szText (for public use). Copies up to cb chars
//
int CPageWnd::GetCellText(int row, int col, char* szText, int cb)
{
  CCell* cell = GetCell(row, col);
  if(cell)  {
    if(cell->m_pcontents)  {
      strncpy(szText, cell->m_pcontents, cb);
      return strlen(szText);
    }
  }
  return 0;
}

//cell font functions
//~~~~~~~~~~~~~~~~~~~~
HFONT CPageWnd::GetCellFontHandle(int row, int col)
{
  CCell* cell = GetCell(row, col);
  if(cell)  {
    CFont* pfont = (*m_pFontList)[cell->m_fontIdx];
    if(pfont)  {
      return (HFONT(*pfont));
    }
  }
  return 0;
}

CFont* CPageWnd::GetCellFont(int row, int col)
{
  CCell* cell = GetCell(row, col);
  if(cell)  {
    CFont* pfont = (*m_pFontList)[cell->m_fontIdx];
    if(pfont)  
      return (pfont);    
  }
  return 0;
}

// set cell font using LOGFONT
//
int CPageWnd::SetCellFont(int row, int col, LOGFONT* plf)
{
  CCell* cell = GetCell(row, col);
  if(cell)  {      
    cell->m_fontIdx = -1;
    int n = m_pFontList->GetSize();
    for(int i = 0; i < n; i++)  {
      LOGFONT lfFound;
      (*m_pFontList)[i]->GetObject(sizeof(lfFound), &lfFound);
       
      int comp = memcmp(plf, &lfFound, sizeof(LOGFONT));
      if(comp == 0)  {
        cell->m_fontIdx = i;
        break;
      }
    }
    if(cell->m_fontIdx == -1) {  //not found      
      CFont* pFont = new CFont;
      pFont->CreateFontIndirect(plf);
      cell->m_fontIdx = m_pFontList->Add(pFont);
    }
    return cell->m_fontIdx;
  }
  return -1;
}

// set cell font using HFONT
//
int CPageWnd::SetCellFont(int row, int col, HFONT hfont)
{
  CCell* cell = GetCell(row, col);
  if(cell)  {
    CFont *pfont = new CFont();
    LOGFONT lf;
    GetObject(hfont, sizeof(lf), &lf);
    pfont->CreateFontIndirect(&lf);
      
    cell->m_fontIdx = -1;
    int n = m_pFontList->GetSize();
    for(int i = 0; i < n; i++)  {
      LOGFONT lfFound;
      (*m_pFontList)[i]->GetObject(sizeof(lfFound), &lfFound);
       
      int comp = memcmp(&lf, &lfFound, sizeof(LOGFONT));
      if(comp == 0)  {
        cell->m_fontIdx = i;
        delete pfont;
        break;
      }
    }
    if(cell->m_fontIdx == -1)   //not found      
      cell->m_fontIdx = m_pFontList->Add(pfont);
    
    return cell->m_fontIdx;
  }
  return -1;
}

// use existing font to set cell font
//
int CPageWnd::SetCellFont(int row, int col, int index)
{
  CCell* cell = GetCell(row, col);
  if(cell)  {
    int maxidx = m_pFontList->GetSize() - 1;
    if(index <= maxidx)
      cell->m_fontIdx = index;
    return cell->m_fontIdx;
  }
  return -1;
}

//cell alignment functions
//~~~~~~~~~~~~~~~~~~~~~~~~
void CPageWnd::SetCellAlign(int row, int col, short fAlign)
{
  CCell* cell = GetCell(row, col);
  if(cell)
    cell->m_falign = fAlign;
}

short CPageWnd::GetCellAlign(int row, int col)
{
  CCell* cell = GetCell(row, col);
  if(cell)
    return cell->m_falign;
  else
    return 0;
}


//text color
//~~~~~~~~~~
COLORREF CPageWnd::GetCellTextColor(int row, int col)
{
  CCell* cell = GetCell(row, col);
  if(cell)
    return cell->m_fclr;
  else
    return (COLORREF(::GetSysColor(COLOR_WINDOWTEXT)));
}

void CPageWnd::SetCellTextColor(int row, int col, COLORREF clr)
{
  CCell* cell = GetCell(row, col);
  if(cell)
    cell->m_fclr = clr;
}

void CPageWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
  if(m_pEditCtrl->IsWindowVisible())  
    m_pEditCtrl->SendMessage(WM_CHAR, VK_RETURN, 0L);
  
  SetFocus();
  CRect r;
  int i, j;

  //is in active zone? (active cell marker)
  //
  if(point.x > m_width[0] && point.y > m_height[0])
  {
    int x_sum = m_width[0];
    i = m_pScrollData->XPos + 1;
    while(x_sum < point.x) {
      x_sum += m_width[i++];
      if(i > m_ncols)
        return;
    }

    int y_sum = m_height[0];
    j = m_pScrollData->YPos + 1;
    while(y_sum < point.y)		{
      y_sum += m_height[j++];
      if(j > m_nrows)
        return;
    }

    m_rowEditEx = m_rowEdit;
    m_colEditEx = m_colEdit;
    m_colEdit   = i - 1;
    m_rowEdit   = j - 1;
    MarkActiveCell(true, true);
    return;
  }

   //is in split column line?
   //
	m_idx = IsSplitLine(point.x, point.y);
	if(m_idx >= 0 && m_width[m_idx] == 0)
	  return;

	if(m_idx >= 0)	 {
	  if(m_idx == 0)
		  m_left_limit = 0;
		else
		  m_left_limit = m_width[0];

	  for(i = m_pScrollData->XPos + 1; i < m_idx; i++)  {
	    m_left_limit += m_width[i];
		  if(i > m_ncols)
			  return;
	  }

	  GetClientRect(&r);
	  m_right_limit = r.right;

	  SetCapture();
	  m_bCapture = true;
	  m_ex_x = -1;
	}
	
	CWnd::OnLButtonDown(nFlags, point);
}


void CPageWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(m_bCapture)
	{
		m_width[m_idx] = max((point.x - m_left_limit), 25);

    m_width[m_idx] = max((point.x - m_left_limit), 25);
    CRect rcClient;
    GetClientRect(&rcClient);
    rcClient.left = point.x - m_width[m_idx];
    InvalidateRect(rcClient, false);
    UpdateWindow();

		m_bCapture = false;
		ReleaseCapture();

		m_idx = -1;

    AdjustScrollBars();
	}

	CWnd::OnLButtonUp(nFlags, point);
}

void CPageWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	CRect r;
	//static bool prev_state = false;

	GetClientRect(r);

	if(m_bCapture)
	{
    if(! ( (point.x - m_left_limit) < 25  ||  (point.x > m_right_limit) ) )
    {
      m_width[m_idx] = max((point.x - m_left_limit), 25);
      CRect rcClient;
      GetClientRect(&rcClient);
      rcClient.left = point.x - m_width[m_idx];
      InvalidateRect(rcClient, false);
      UpdateWindow();

      m_ex_x = point.x;
    }
	}
  /*else {  //tooltip staff
    int x_sum = m_width[0];
    int col = m_pScrollData->XPos + 1;
    while(x_sum < point.x && col < m_ncols) {
      x_sum += m_width[col++];
     }
     col -= 1;
     if(col > 0 && col != m_ToolTipCol)  {
       TRect r;
       r.left  = x_sum - m_width[col - 1];
       r.right = x_sum;
       r.top   = 0;
       r.bottom = m_height[0];
       m_pToolInfo->SetRect(r);
       m_ToolTipCol = col;
       m_pToolTip->NewToolRect(*m_pToolInfo);
     }
  }*/
	CWnd::OnMouseMove(nFlags, point);
}


//
// return column for resizing or -1 if x, y is not over cell border
//
int CPageWnd::IsSplitLine(int x, int y)
{
	int sum, i;

	if(y > m_height[0] || x < 3)
		return -1;

	sum = m_width[0];
	i   = max(1, m_pScrollData->XPos + 1);
	while(sum < x && i < m_ncols)
		sum += m_width[i++];

	i -= 1;
	if(abs(sum - x) < 2)
		return i;
	else
		sum -= m_width[i];

	if((x - sum) < 2)
		return (i - 1);

	return -1;
}

BOOL CPageWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
  if(nHitTest == HTCLIENT &&  message)
  {
    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(&pt);

    if( IsSplitLine(pt.x, pt.y) >= 0 || m_bCapture )
      ::SetCursor(m_CurSize);
    else
      ::SetCursor(m_CurArrow);
  }
  else
    ::SetCursor(m_CurArrow);

  return  true;	
}

void CPageWnd::MarkActiveCell(bool fprev, bool fnext)
{
  if(m_pEditCtrl->IsWindowVisible())
    m_pEditCtrl->SendMessage(WM_CHAR, VK_RETURN, 0L);


  int i, xpos, ypos;
  CRect r(0, 0, 0, 0);

  CClientDC dc(this);
  dc.SelectStockObject(NULL_BRUSH);

	//ex active cell
  //
	if(fprev)	 {
		if(m_pScrollData->XPos < m_colEditEx && m_pScrollData->YPos < m_rowEditEx)  {
      CPen inactivePen(PS_SOLID, 2, GetCellColor(m_rowEditEx, m_colEditEx));
      dc.SelectObject(&inactivePen);
      CRect r(m_EditRect.left + 2, m_EditRect.top + 2, m_EditRect.right, m_EditRect.bottom);
			dc.Rectangle(r);
      MarkHeader(false);
		}
	}

	//active cell
  //
	if(fnext)  {
		if(m_pScrollData->XPos < m_colEdit && m_pScrollData->YPos < m_rowEdit) {
			xpos = m_width[0];
			for(i = m_pScrollData->XPos+ 1; i < m_colEdit; i++)
				xpos += m_width[i];

      ypos  = 0;
			for(i = 0; i < (m_rowEdit - m_pScrollData->YPos); i++)
				ypos += m_height[i];

      m_EditRect.SetRect(xpos, ypos, xpos + m_width[m_colEdit], ypos + m_height[m_rowEdit]);
      CPen activePen(PS_SOLID, 2, ::GetSysColor(COLOR_WINDOWTEXT));
      dc.SelectObject(&activePen);
      CRect r(m_EditRect.left + 2, m_EditRect.top + 2, m_EditRect.right, m_EditRect.bottom);
			dc.Rectangle(r);
      m_pEditCtrl->MoveWindow(r.left, r.top, r.Width(), r.Height(), false);
      MarkHeader(true);
		}
	}
}


void CPageWnd::MarkHeader(bool mark)
{
  CRect rowRect(0, m_EditRect.top, m_width[0], m_EditRect.bottom);
  CRect colRect(m_EditRect.left, 0, m_EditRect.right, m_height[0]);
  CClientDC dc(this);
  if(!mark)  {
    dc.DrawEdge(rowRect, BDR_RAISEDINNER, BF_RECT | BF_MIDDLE);
    SetCellFont(m_rowEditEx, 0, *m_pDefFont);
    CellEntry(dc, m_rowEditEx, 0, rowRect);

    dc.DrawEdge(colRect, BDR_RAISEDINNER, BF_RECT | BF_MIDDLE);    
    SetCellFont(0, m_colEditEx, *m_pDefFont);
    CellEntry(dc, 0, m_colEditEx, colRect);
  }
  else {
    dc.DrawEdge(rowRect, BDR_RAISED,  BF_RECT | BF_MIDDLE);    
    SetCellFont(m_rowEdit, 0, *m_pDefFontBold);
    CellEntry(dc, m_rowEdit, 0, rowRect);

    dc.DrawEdge(colRect, BDR_RAISED,  BF_RECT | BF_MIDDLE);    
    SetCellFont(0, m_colEdit, *m_pDefFontBold);
    CellEntry(dc, 0, m_colEdit, colRect);
  }
}


void CPageWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	bool fPrev = true;
	CRect rClient;
	int i, sum;

	switch(nChar)
	{
		case VK_F2:  {
      if(!m_bReadOnly)  {
        m_pEditCtrl->SetFont(GetCellFont(m_rowEdit, m_colEdit), true);
        m_pEditCtrl->SetWindowText(GetCellTextPtr(m_rowEdit, m_colEdit));
        m_pEditCtrl->ShowWindow(SW_SHOW);
      }
      break;
    }

    case VK_LEFT:  {
      if(m_pScrollData->XPos && (m_pScrollData->XPos >= m_colEdit - 2) && m_colEdit > 1)
        SendMessage(WM_HSCROLL, SB_LINEUP, 0);
      if(m_colEdit - 1)  {
        m_colEditEx = m_colEdit;
        m_rowEditEx = m_rowEdit;
        m_colEdit  -= 1;
        MarkActiveCell(fPrev, true);
      }
			break;
    }

		case VK_RIGHT:  {
      if(m_colEdit + 1 >= m_ncols)  {
        SendMessage(WM_HSCROLL, SB_LINEDOWN, 0);
        return;
      }
      GetClientRect(&rClient);
      i = m_pScrollData->XPos + 1;
      sum = m_width[0];
      while(i < m_colEdit + 2)
        sum += m_width[i++];
      if(sum > rClient.right)
        SendMessage(WM_HSCROLL, SB_LINEDOWN, 0);

      m_colEditEx = m_colEdit;
      m_rowEditEx = m_rowEdit;
      m_colEdit  += 1;
      MarkActiveCell(fPrev, true);
			break;
    }

		case VK_UP:  {
      if( m_pScrollData->YPos && (m_rowEdit > 1) && (m_rowEdit - m_pScrollData->YPos) < 3 )
        SendMessage(WM_VSCROLL, SB_LINEUP, 0);
      if(m_rowEdit - 1)	{
        m_colEditEx = m_colEdit;
        m_rowEditEx = m_rowEdit;
        m_rowEdit  -= 1;
        MarkActiveCell(fPrev, true);
      }
			break;
    }

		case VK_DOWN:  {
      if(m_rowEdit + 1 >= m_nrows)  {
        SendMessage(WM_VSCROLL, SB_LINEDOWN, 0);
        return;
      }
      GetClientRect(&rClient);
      //use height[1] becouse all rows have a same height (except 0. row)
      //
      if(m_rowEdit - m_pScrollData->YPos  > rClient.bottom / m_height[1] - 2)
        SendMessage(WM_VSCROLL, SB_LINEDOWN, 0);

      m_colEditEx = m_colEdit;
      m_rowEditEx = m_rowEdit;
      m_rowEdit  += 1;
      MarkActiveCell(fPrev, true);
			break;
	  }
  }
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CPageWnd::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
  if(m_bReadOnly)
    return;

  if(isalnum(nChar) || nChar == '.') {
    m_pEditCtrl->SendMessage(WM_CHAR, WPARAM(nChar), MAKELPARAM(nRepCnt, nFlags));
  }
  m_pEditCtrl->SetFont(GetCellFont(m_rowEdit, m_colEdit), true);
  m_pEditCtrl->ShowWindow(SW_SHOW);

	CWnd::OnChar(nChar, nRepCnt, nFlags);
}

//
// change cell contents if accept = true
//
void CPageWnd::EditAccept(bool accept)
{
  m_pEditCtrl->ShowWindow(SW_HIDE);
  if(accept)  {
    char string[255];
    m_pEditCtrl->GetWindowText(string, 255);
    SetCellText(m_rowEdit, m_colEdit, string);
  }

  m_pEditCtrl->SetWindowText("");

  InvalidateRect(m_EditRect, false);
}





/////////////////////////////////////////////////////////////////////////////
// CPageEdit

CPageEdit::CPageEdit()
{
  m_pPage = 0;
}

CPageEdit::~CPageEdit()
{

}


BEGIN_MESSAGE_MAP(CPageEdit, CEdit)
	//{{AFX_MSG_MAP(CPageEdit)
	ON_WM_CHAR()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageEdit message handlers

void CPageEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
  if(!(nChar == VK_RETURN || nChar == VK_ESCAPE))
      CEdit::OnChar(nChar, nRepCnt, nFlags);

  switch(nChar)  {
    case VK_RETURN:
      if(m_pPage == 0)
        m_pPage = dynamic_cast<CPageWnd*>(GetParent());
      if(m_pPage)
        m_pPage->EditAccept(true);
      break;

    case VK_ESCAPE:
      if(m_pPage == 0)
        m_pPage = dynamic_cast<CPageWnd*>(GetParent());
      if(m_pPage)
        m_pPage->EditAccept(false);
      break;

    default:
      char szText[255];
      GetWindowText(szText, 255);
      int n = strlen(szText);
      CSize size;
      CClientDC dc(this);
      dc.SelectObject(GetFont());
      size = dc.GetTextExtent(szText, n);
      if(n)
        m_charWidth = size.cx / n;
      size.cx += 2 * m_charWidth;
      GetClientRect(&m_rcClient);
      if(m_rcClient.Width() <= size.cx)  {
        m_rcClient.right += 2 * m_charWidth;
        SetWindowPos(0, m_rcClient.left, m_rcClient.top, m_rcClient.Width(), m_rcClient.Height(), SWP_NOMOVE | SWP_NOZORDER | SWP_SHOWWINDOW);
     }
     break;
  }
}

void CPageEdit::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CEdit::OnShowWindow(bShow, nStatus);
	
  if(bShow)  { 
    GetClientRect(&m_rcClient);
    SetFocus();
  }	
}
