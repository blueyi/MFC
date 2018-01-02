#ifndef _SOUNDDEFS_INCLUDED
#define _SOUNDDEFS_INCLUDED

#include <windows.h>
#include <Mmreg.h>

class SOUNDFORMAT
{
public:

	unsigned short NbChannels;				// number of channels: 1:mono 2:stéréo
	unsigned short SamplingRate;
	unsigned short NbBitsPerSample;			// bits per sample:	8 ou 16 bits


	void fromWFX( WAVEFORMATEX wfx )
	{
		NbChannels = wfx.nChannels;
		SamplingRate = (unsigned short)wfx.nSamplesPerSec;
		NbBitsPerSample = wfx.wBitsPerSample;
	}

	void toWFX( WAVEFORMATEX &wfx )
	{
		wfx.wFormatTag=WAVE_FORMAT_PCM;
		wfx.nChannels = NbChannels;
		wfx.nSamplesPerSec = SamplingRate;
		wfx.wBitsPerSample = NbBitsPerSample;
		wfx.nBlockAlign = wfx.nChannels * wfx.wBitsPerSample / 8;
		wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;
		wfx.cbSize=0;	

	}
};

#endif