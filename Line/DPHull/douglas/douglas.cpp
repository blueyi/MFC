// douglas.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <tchar.h>
#include <map>
#include <vector>
#include <list>
#include "DPHull.h"
#include "KeyFramer.h"
#include "Containers.h"

using namespace hull;
using namespace std;

template<class T>
void Get_Points(int n, vector<T>& vX,vector<T>&vY)
{
	int i;
	
	vX.resize(n);
	vY.resize(n);

	for (i = 0; i < n; i++)
	{
		vX[i] = i;
		vY[i] = n / 2.0 * sin((2*3.14 * i) / n);
	}
};


template <class T, class TPointContainer, class TKeyContainer>
void Get_NOAA_Points( TLine<T,TPointContainer,TKeyContainer>& line )
{
	using namespace std;
	using namespace hull;

	TPointContainer& pc = line.GetPoints();
	list<TPointContainer::value_type> lPoints;
	TPointContainer::value_type p;

	FILE * fp = NULL;
	
	char szLine[ 50 ] = "";
	
	fp = fopen( "32756-727bis.txt","rt" );
	
	while( fgets( szLine, sizeof( szLine ), fp ) )
	{
		double dLat = 0, dLon= 0; 
		
		int t = sscanf( szLine,
			"%lf %lf",&dLat,&dLon );
		
		if ( t == 2 )
		{
			p.x=dLat; p.y=dLon;
			lPoints.push_back(p);
		}
	} 
	
	fclose( fp );
	
	pc.resize( lPoints.size());
	UINT i=0;
	while (!lPoints.empty())
	{
		pc[i++]=lPoints.front();
		lPoints.pop_front();
	}
}

template<class T, class TPointContainer>
void GetLimni( TPointContainer& pc)
{
	using namespace std;
	using namespace hull;

	T dt;
	int nt;

	ifstream in( "limni0.dat");
	if (!in.is_open())
	{
		cerr<<"Could not open file\n";
		exit(-1);
	}

	in>>dt>>nt;

	pc.resize(nt);
	for (UINT i=0;i<pc.size();i++)
	{
		pc[i]->x=i*dt;
		in>>pc[i].y;
	}
}

int main(int argc, char* argv[])
{
	using namespace hull;
	using namespace std;


/*
	//Creating a hull that:
	//	- uses PointContainer as its point container
	//	- uses KeyContainer as its key container
	vector<float> vX,vY;
	list<float> vKeyX,vKeyY;

	typedef TPointDoubleContainer<float, vector<float>, vector<float> > PointContainer;
	typedef TKeyDoubleContainer<float, list< float >, list< float >, PointContainer > KeyContainer;

	PointContainer p;
	KeyContainer k;

	TDPHull<float, PointContainer, KeyContainer > dp;
	dp.GetPoints().SetContainers(&vX,&vY);
	dp.GetKeys().SetContainers(&vKeyX,&vKeyY);
*/
	
	CDPHullF dp;

	vector<float> vx(5000),vy(5000);
	Get_Points(5000, vx,vy);
	dp.SetPoints(vx,vy);
	dp.GetKeys(vx,vy);
	dp.SetTol(0.00001);

	dp.Simplify();
	cout<<"Tol: "<<dp.GetTol()<<"\tPoints/Keys: "<<dp.GetPointSize()<<", "<<dp.GetKeySize()<<std::endl; 

//	Get_NOAA_Points(dp);

	// Setting the orginal curve data, and performing approximation with different 
	// tolerance values.
	size_t nIter=0;
	
	cout<<_T("Starting...\n");
	dp.SetTol(1e-7);
	try
	{
		nIter=dp.ShrinkNorm(40.0f/100,0);
	}
	catch(TCHAR* str)
	{
		cerr<<str<<_T("\n");
	}
	cout<<"Tol: "<<dp.GetTol()<<"\tPoints/Keys: "<<dp.GetPointSize()<<", "<<dp.GetKeySize()<<" points in "<<nIter<<" iterations."; 

/*
	// retreiving keys...
	const CDPHullF::KeyContainer& kc=dp.GetKeys();
	CDPHullF::KeyContainer::const_iterator it;
	TPoint<float> key;
	for (it=kc.begin(); it!=kc.end(); ++it)
	{
		key=**it;
	}
*/

	return 0;
}

