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
              
        if (m_bMemDC)    //�����ڴ�DC
        {
            pDC->GetClipBox(&m_rect);
            CreateCompatibleDC(pDC);
            m_bitmap.CreateCompatibleBitmap(pDC, m_rect.Width(), m_rect.Height());
            m_pOldBitmap = SelectObject(&m_bitmap);
#ifndef _WIN32_WCE
            SetWindowOrg(m_rect.left, m_rect.top);
#endif
        }
        else        // ��ӡģʽ
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
            // �������嵽��ӦDC
            m_pDC->BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(),
                          this, m_rect.left, m_rect.top, SRCCOPY);

            //�ָ�ԭ��
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
    CBitmap  m_bitmap;      // ����λͼ
    CBitmap* m_pOldBitmap;  // ԭ��λͼ
    CDC*     m_pDC;         // �����Ӧ��DC���
    CRect    m_rect;        // ��Ӧ��DC����
    BOOL     m_bMemDC;      // 
};

/////////////////////////////////////////////////////////////////////////////


#endif 