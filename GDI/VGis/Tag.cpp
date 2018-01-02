// Tag.cpp: implementation of the Tag class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VGis.h"
#include "Tag.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Tag::Tag()
{

}

Tag::~Tag()
{

}

Tag::Tag(short ColorPen, int Layer, bool Delete, float InsertX, float InsertY, float ScaleX, float ScaleY, float Angle, int id, int idBlock)
    :Gis(ColorPen,0,0,1,Layer,id,Delete)
{
	m_InsertX=InsertX;
	m_InsertY=InsertY;
	m_ScaleX=ScaleX;
	m_ScaleY=ScaleY;
	this->m_Angle=Angle;
	this->m_idBlock=idBlock;
}

void Tag::Release()
{
	delete this;
}
