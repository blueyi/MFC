// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <windows.h>
#include "CpuUsage.h"

int main(int argc, char* argv[])
{
	int processID=0;
	CCpuUsage usageA;
	CCpuUsage usageB;
	CCpuUsage usageC;

	printf("SystemWide Cpu Usage	 Explorer cpu usage	   Cpu Usage for processID 0\n"); 
	printf("====================	 ==================	   ========================\n"); 
	while (true)
	{
		// Display the system-wide cpu usage and the "Explorer" cpu usage
		
		int SystemWideCpuUsage = usageA.GetCpuUsage();
		int ProcessCpuUsageByName = usageB.GetCpuUsage("explorer");
		int ProcessCpuUsageByID = usageC.GetCpuUsage(processID);
		printf("%19d%%%22d%%%31d%%\r",SystemWideCpuUsage, ProcessCpuUsageByName, ProcessCpuUsageByID);

		Sleep(1000);
	}
	return 0;
}
