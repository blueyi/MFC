// SliderBoth.cpp : implementation file
//

#include "stdafx.h"
#include "SliderBoth.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
#define MARGIN_ME	14

SliderBoth::SliderBoth()
{
	b_Initialized=0;

	pos.Init(0,200,10);
}

SliderBoth::~SliderBoth()
{
}


BEGIN_MESSAGE_MAP(SliderBoth,CWnd)
	//{{AFX_MSG_MAP(SliderBoth)
	ON_WM_PAINT()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// SliderBoth message handlers

BOOL SliderBoth::Create(CWnd*pMum,CRect rcBd,BOOL bHorz,int iID)
{
	//height is 27 pixels if no text
	i_ID	=iID;
	b_Horz	=bHorz;
	
	i_SliderY=5+6+8;	//top+tic+gap;

	int iH=i_SliderY+3+5;	//sliderH+bottom;

	CRect rc=rcBd;
	if(bHorz)	rc.bottom=rc.top+iH;
	else		rc.right=rc.left+iH;

	UINT u=WS_CHILD|WS_VISIBLE;
	BOOL b=CWnd::Create(0,0,u,rc,pMum,iID);
	if(b==0)	return 0;

	tic0.Create(this,bHorz,1);
	tic1.Create(this,bHorz,0);
	return b;
}

void SliderBoth::MoveWindow(CRect*pRect,BOOL bRepaint)
{
	CRect rc,rc0=*pRect;
	GetWindowRect(&rc);

	if(b_Horz)	rc0.bottom=rc0.top+rc.Height();
	else		rc0.right=rc0.left+rc.Width();

	int iL,iR;
	if(b_Initialized)	GetPosition(iL,iR);
	CWnd::MoveWindow(&rc0,bRepaint);
	if(b_Initialized)	P_SetPosition(iL,iR,1,1);
}

void SliderBoth::MoveWindow(int iX,int iY,int iW,int iH,BOOL bRepaint)
{
	CRect rc(iX,iY,iX+iW,iY+iH);
	MoveWindow(&rc,bRepaint);
}


void SliderBoth::OnSize(UINT nType,int cx,int cy) 
{
	CWnd::OnSize(nType,cx,cy);
	
	if(::IsWindow(m_hWnd)==0)	return;
	if(::IsWindow(tic0.m_hWnd)==0)	return;
	if(::IsWindow(tic1.m_hWnd)==0)	return;

	if(b_Initialized)
	{
		P_SetPosition(pos.iL,pos.iR,1,1);
	}
}

void SliderBoth::P_SetPosition(int iL,int iR,BOOL bFst,BOOL bSnd)
{
	if(b_Initialized==0)	return;
	if(b_Horz)	P_SetPosition_Horz(iL,iR,bFst,bSnd);
	else		P_SetPosition_Vert(iL,iR,bFst,bSnd);
}

void SliderBoth::P_SetPosition_Horz(int iL,int iR,BOOL bFst,BOOL bSnd)
{
	CRect rcMe;
	GetClientRect(&rcMe);

	const int iXL=MARGIN_ME;
	const int iXR=rcMe.right-MARGIN_ME;

	const double dbOne=(iXR-iXL)*1.0/(pos.iMax-pos.iMin);

	CRect rc;
	tic0.GetWindowRect(&rc);
	const int iW=rc.Width();
	const int iH=rc.Height();

	rc.top=i_SliderY-iW-1;
	rc.bottom=rc.top+iH;

	if(iL<pos.iMin)	iL=pos.iMin;
	if(iR>pos.iMax)	iR=pos.iMax;

	if(bFst)	
	{
		if(iL>iR)	iL=iR;
	}

	if(bSnd)
	{
		if(iR<iL)	iR=iL;
	}

	const int iPixL=iXL+(int)((iL-pos.iMin)*dbOne);
	const int iPixR=iXL+(int)((iR-pos.iMin)*dbOne);

	if(bFst)
	{
		pos.iL=iL;
		rc.right=iPixL+1;
		rc.left=rc.right-iW;
		tic0.MoveWindow(&rc);
	}

	if(bSnd)
	{
		pos.iR=iR;
		rc.left=iPixR;
		rc.right=rc.left+iW;
		tic1.MoveWindow(&rc);
	}
}

void SliderBoth::P_SetPosition_Vert(int iL,int iR,BOOL bFst,BOOL bSnd)
{
	CRect rcMe;
	GetClientRect(&rcMe);

	const int iXL=rcMe.bottom-MARGIN_ME;
	const int iXR=rcMe.top+MARGIN_ME;

	const double dbOne=abs(iXL-iXR)*1.0/(pos.iMax-pos.iMin);

	CRect rc;
	tic0.GetWindowRect(&rc);
	const int iW=rc.Width();
	const int iH=rc.Height();

	rc.left=i_SliderY-iH-1;
	rc.right=rc.left+iW;

	if(iL<pos.iMin)	iL=pos.iMin;
	if(iR>pos.iMax)	iR=pos.iMax;

	if(bFst)	
	{
		if(iL>iR)	iL=iR;
	}

	if(bSnd)
	{
		if(iR<iL)	iR=iL;
	}

	const int iPixL=iXL-(int)((iL-pos.iMin)*dbOne);
	const int iPixR=iXL-(int)((iR-pos.iMin)*dbOne);
	if(bFst)
	{
		pos.iL=iL;
		rc.top=iPixL;
		rc.bottom=rc.top+iH;
		tic0.MoveWindow(&rc);
	}

	if(bSnd)
	{
		pos.iR=iR;
		rc.bottom=iPixR;
		rc.top=rc.bottom-iH;
		tic1.MoveWindow(&rc);
	}
}

void SliderBoth::GetPosition(int &iL,int &iR)
{
	iL=pos.iL;
	iR=pos.iR;
}

void SliderBoth::SetPosition(int iL,int iR)
{
	P_SetPosition(iL,iR,1,1);
}

void SliderBoth::OnPaint() 
{
	if(b_Initialized==0)
	{
		PostMessage(WM_USER+100);
	}

	CPaintDC dc(this);

	CRect rc;
	GetClientRect(&rc);
	COLORREF clrBk=::GetSysColor(COLOR_BTNFACE);
	int iV=209;
//	COLORREF clrBk=RGB(iV,iV,iV);
	dc.FillRect(&rc,&CBrush(clrBk));

	P_PaintHorz(&dc,rc);
}

void SliderBoth::P_PaintHorz(CDC*pDC,const CRect &rcMe)
{
	COLORREF clr000=RGB(0,0,0);
	COLORREF clr255=RGB(255,255,255);

	const int iTicT=5;
	const int iTicB=iTicT+3;

	int iNumTic=(pos.iMax-pos.iMin)/pos.iTick;
	int i,iM=iNumTic/2;

	if(b_Horz)
	{
		const int iL=MARGIN_ME;
		const int iR=rcMe.right-MARGIN_ME;
		const double dbStep=(iR-iL)*1.0/iNumTic;
		double db=iL;
		int iX;

		for(i=0;i<=iNumTic;i++)
		{
			iX=(int)db;
			pDC->MoveTo(iX,iTicT);
			if(i%iM==0)	pDC->LineTo(iX,iTicB+3);
			else		pDC->LineTo(iX,iTicB);
			db+=dbStep;
		}

		int iLineT=iTicB+8;
		CRect rc(iL-5,iLineT,iR+5,iLineT+3);
		pDC->Draw3dRect(&rc,clr000,clr255);
	}
	else
	{
		const int iL=rcMe.bottom-MARGIN_ME;
		const int iR=rcMe.top+MARGIN_ME;
		const double dbStep=(iL-iR)*1.0/iNumTic;
		double db=iL;

		int iY;
		for(i=0;i<=iNumTic;i++)
		{
			iY=(int)db;
			pDC->MoveTo(iTicT,iY);
			if(i%iM==0)	pDC->LineTo(iTicB+3,iY);
			else		pDC->LineTo(iTicB,iY);
			db-=dbStep;
		}

		int iLineT=iTicB+8;
		CRect rc(iLineT,iR-5,iLineT+3,iL+5);
		pDC->Draw3dRect(&rc,clr000,clr255);
	}

}

LRESULT SliderBoth::WindowProc(UINT m,WPARAM w,LPARAM l) 
{
	if((m==WM_USER)||(m==WM_USER+1)||(m==WM_USER+100))
	{
		CRect rcMe;
		GetClientRect(&rcMe);

		if(b_Horz)
		{
			const int iXL=MARGIN_ME;
			const int iXR=rcMe.right-MARGIN_ME;
			double dbOne=(iXR-iXL)*1.0/(pos.iMax-pos.iMin);

			if(m==WM_USER)
			{
				int iMove=(int)(((int)w)/dbOne);

				int iL,iR;
				GetPosition(iL,iR);
				if(l)	iL+=iMove;
				else	iR+=iMove;
				P_SetPosition(iL,iR,l,!l);
			}
			else
			if(m==WM_USER+1)
			{
				int iL,iR;
				GetPosition(iL,iR);
				if((pos.iOldL!=iL)||(pos.iOldR!=iR))
				{
					pos.iOldL=iL;
					pos.iOldR=iR;
					//post event
					GetParent()->PostMessage(WM_COMMAND,i_ID);
//wm.DT(100,i_ID);
				}
			}
			if(m==WM_USER+100)
			{
				b_Initialized=1;
				P_SetPosition(pos.iMin,pos.iMax,1,1);
				RedrawWindow();
			}
		}
		else
		{
			const int iXL=rcMe.bottom-MARGIN_ME;
			const int iXR=rcMe.top+MARGIN_ME;
			double dbOne=(iXL-iXR)*1.0/(pos.iMax-pos.iMin);

			if(m==WM_USER)
			{
				int iMove=(int)(((int)w)/dbOne);

				int iL,iR;
				GetPosition(iL,iR);
				if(l)	iL-=iMove;
				else	iR-=iMove;
				P_SetPosition(iL,iR,l,!l);
			}
			else
			if(m==WM_USER+1)
			{
				int iL,iR;
				GetPosition(iL,iR);
				if((pos.iOldL!=iL)||(pos.iOldR!=iR))
				{
					pos.iOldL=iL;
					pos.iOldR=iR;
					//post event;
					GetParent()->PostMessage(WM_COMMAND,i_ID);
//wm.DT(200,i_ID);
				}
			}
			else
			if(m==WM_USER+100)
			{
				b_Initialized=1;
				P_SetPosition(pos.iMin,pos.iMax,1,1);
				RedrawWindow();
			}
		}
	}

	return CWnd::WindowProc(m,w,l);
}

BOOL SliderBoth::SetRange(int iMin,int iMax,int iTick)
{
	int iDis=iMax-iMin;
	if(iDis<2)		return 0;
	if(iDis%2)		return 0;
	if(iTick<1)		return 0;
	if(iDis%iTick)	return 0;

	pos.Init(iMin,iMax,iTick);
	RedrawWindow();
	return 1;
}
void SliderBoth::GetRange(int&iMin,int&iMax,int&iTick)
{
	iMin=pos.iMin;
	iMax=pos.iMax;
	iTick=pos.iTick;
}
