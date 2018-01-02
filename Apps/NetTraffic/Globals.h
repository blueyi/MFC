/*******************************************

	MFTrafficButton

	Version:	1.0
	Date:		31.10.2001
	Author:		Michael Fatzi
	Mail:		Michael_Fatzi@hotmail.com
	Copyright 1996-1997, Keith Rule

	You may freely use or modify this code provided this
	Copyright is included in all derived versions.
	
	History: 10.2001 Startup

	Handy little button control to display current 
	nettraffic as graph in a button.

********************************************/

#ifndef __GOBALS_H__
#define __GOBALS_H__

typedef struct _TRAFFIC_ENTRY_
{
	double value;
	BOOL connected;
} TRAFFICENTRY;

#define PLOTGRANULATRITY 2		// Defines the width of the rectangle representing a bar in the diagram

#define NETUPDATESPEED	1000	// Value for the statistics timer
#define GRIDUPDATESPEED 50		// Value vor the grid timer
#define GRIDTIMER		1		// ID for the grid timer
#define NETTIMER		2		// ID for the statistics timer
	
#define GRIDXRESOLUTION	10		// Distance for grid in x direction
#define GRIDYRESOLUTION	10		// Distance for grid in y direction
#define GRIDSCROLLXSPEED -1		// How fast grid scrolls in x direction
#define GRIDSCROLLYSPEED 0		// How fast grid scrolls in y direction

#endif