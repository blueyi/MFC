/********************************************************************
    File:	        Utilities	
    Creation Date:	2009/11/01
	
	Author: 	    Ahmed Charfeddine
					info@potatosoftware.com

	License:        Copyright [2009] [Potato software]

					Licensed under the Apache License, Version 2.0 (the "License");
					you may not use this file except in compliance with the License.
					You may obtain a copy of the License at

							http://www.apache.org/licenses/LICENSE-2.0

					Unless required by applicable law or agreed to in writing, software
					distributed under the License is distributed on an "AS IS" BASIS,
					WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
					See the License for the specific language governing permissions and
					limitations under the License.
    
	Note :	  		
*********************************************************************/
#pragma once
#include "Profiler.h"

#include <sstream>
class CUtilities
{
public:

	CUtilities(void)
	{
	}

	~CUtilities(void)
	{
	}

	static std::string GetFormattedTime(double value)
	{
		std::stringstream sstr;
		sstr << value;
		return sstr.str();
		/*
		char buffer[64];
				sprintf(buffer, "%.3f", value);
		
				std::string str(buffer);
				return str;*/
	}
	static std::string GetFormattedDWORD(DWORD dwValue)
	{
		char  buffer[800];
		sprintf(buffer,"0x%x",dwValue);
		std::string strSTL(buffer);
		return strSTL;
	}
	static DWORD GetDWORDByString(std::string str)
	{
		DWORD _dwReadValue;
		sscanf(str.c_str() , "%x", &_dwReadValue );  // C4996
		return _dwReadValue;
	}
};
