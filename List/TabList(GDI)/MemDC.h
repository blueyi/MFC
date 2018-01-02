#if !defined _MEMDC_H_
#define _MEMDC_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////////////////

class CMemDC : public CDC
{
public:
    CMemDC(CDC* pDC) : CDC()
    {
        ASSERT(pDC != NULL);

        m_pDC = pDC;
        m_pOldBitmap = NULL;
#ifndef WCE_NO_PRINTING
        m_bMemDC = !pDC->IsPrinting();
#else
        m_bMemDC = FALSE;
#endif
              
        if (m_bMemDC)    //创建内存DC
        {
            pDC->GetClipBox(&m_rect);
            CreateCompatibleDC(pDC);
            m_bitmap.CreateCompatibleBitmap(pDC, m_rect.Width(), m_rect.Height());
            m_pOldBitmap = SelectObject(&m_bitmap);
#ifndef _WIN32_WCE
            SetWindowOrg(m_rect.left, m_rect.top);
#endif
        }
        else        // 打印模式
        {
#ifndef WCE_NO_PRINTING
            m_bPrinting = pDC->m_bPrinting;
#endif
            m_hDC       = pDC->m_hDC;
            m_hAttribDC = pDC->m_hAttribDC;
        }
    }
    
    ~CMemDC()
    {
        if (m_bMemDC) 
        {    
            // 拷贝缓冲到对应DC
            m_pDC->BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(),
                          this, m_rect.left, m_rect.top, SRCCOPY);

            //恢复原样
            SelectObject(m_pOldBitmap);
        } 
		else 
		{
            m_hDC = m_hAttribDC = NULL;
        }
    }

    CMemDC* operator->() {return this;}
       
    operator CMemDC*() {return this;}

private:
    CBitmap  m_bitmap;      // 缓冲位图
    CBitmap* m_pOldBitmap;  // 原本位图
    CDC*     m_pDC;         // 保存对应的DC句柄
    CRect    m_rect;        // 对应的DC区域
    BOOL     m_bMemDC;      // 
};

/////////////////////////////////////////////////////////////////////////////


#endif 