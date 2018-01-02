#ifndef _MEMDC_H_
#define _MEMDC_H_

class CMemDC : public CDC 
{
public:
	// Something wrong when we wanted to retrieve the client area
	// with the GetClipBox function of variant pDC which pointed to
	// the device context of a dialog child contrl.
	// e.g. pDC->GetClipBox(m_rect);

	/***************************************************************
	// Example, syc, 2001.08.14
	void CMyView::OnDraw(CDC* pDC)
	{
		CRect client;
		GetClientRect(&client);
		
		// don't use pDC->GetClipBox() to retrieve the region
		// which to be update. if you use background bitmap
		// in a window, when you dragging it and it z-order under
		// other windows, the region which you just retrieve not
		// equal actual client region, in other words, not the
		// whole window can be refresh.

		pDC->DPtoLP(&client);
		CMemDC memDC(pDC, client);

		// Drawing code...
	}
	/**************************************************************/
	
	CMemDC(CDC* pDC, const CRect& rect)	// rect - logical units
		: m_pDC(pDC), m_rect(rect)
	{
		m_pOldBitmap = NULL;
		ASSERT(m_pDC != NULL);
                
		m_bMemDC = !pDC->IsPrinting();
                
		if (m_bMemDC && !m_rect.IsRectEmpty())
		{
			// Create a Memory DC
			CreateCompatibleDC(pDC);
			m_bitmap.CreateCompatibleBitmap(pDC, abs(m_rect.Width()), abs(m_rect.Height()));
			m_pOldBitmap = SelectObject(&m_bitmap);
			SetWindowOrg(m_rect.left, m_rect.top);
		}
		else 
		{
			// Make a copy of the relevent parts of the current DC for printing
			m_bPrinting = pDC->m_bPrinting;
			m_hDC = pDC->m_hDC;
			m_hAttribDC = pDC->m_hAttribDC;
		}
	}

	CMemDC(CDC* pDC) : m_pDC(pDC)
	{
		m_pOldBitmap = NULL;
		ASSERT(m_pDC != NULL);
                
		m_bMemDC = !pDC->IsPrinting();
            
		pDC->GetClipBox(&m_rect);
		if (m_bMemDC && !m_rect.IsRectEmpty())
		{
			// Create a Memory DC
			CreateCompatibleDC(pDC);
			m_bitmap.CreateCompatibleBitmap(pDC, abs(m_rect.Width()), abs(m_rect.Height()));
			m_pOldBitmap = SelectObject(&m_bitmap);
			SetWindowOrg(m_rect.left, m_rect.top);
		}
		else 
		{
			// Make a copy of the relevent parts of the current DC for printing
			m_bPrinting = pDC->m_bPrinting;
			m_hDC = pDC->m_hDC;
			m_hAttribDC = pDC->m_hAttribDC;
		}
	}
        
	~CMemDC()
	{
		if (m_bMemDC)
		{
			// Copy the offscreen bitmap onto the screen.
			m_pDC->BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(),
							this, m_rect.left, m_rect.top, SRCCOPY);
			// Swap back the original bitmap.
			if( m_pOldBitmap )
				SelectObject(m_pOldBitmap);
		} 
		else
		{
			// All we need to do is replace the DC with an NULL value,
			// this keeps us from accidently deleting the handles associated with
			// the CDC that was passed to the constructor.
			m_hDC = m_hAttribDC = NULL;
		}
	}
        
private:
	CBitmap m_bitmap;		// Offscreen bitmap
	CBitmap* m_pOldBitmap;	// bitmap originally found in CMemDC
	CDC* m_pDC;				// Saves CDC passed in constructor
	CRect m_rect;			// Rectangle of drawing area.
	BOOL m_bMemDC;			// TRUE if CDC really is a Memory DC.
};


#endif // _MEMDC_H_