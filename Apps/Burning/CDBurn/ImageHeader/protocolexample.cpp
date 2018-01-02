// ProtocolExample.cpp: implementation of the CProtocolExample class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../BIGlobals/BI_ImageHeader.h"
#include "ProtocolExample.h"

#include "BI_Constants.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProtocolExample::CProtocolExample()
{

}

CProtocolExample::~CProtocolExample()
{

	
}

//Localization.
void CProtocolExample::SeriesSESag(SeriesField* seriesField, ScanField* scanField)
{
	SeriesSE(seriesField);

	memcpy(seriesField->Desc, "Sag SE2D T1W", 100);
    memcpy(seriesField->Protocol,"Sag SE2D T1W", 31);
    seriesField->Plane = ipSagittal;
	seriesField->NumAvg = 4;			// Number of scans, == ui_NumAvg			*/
	seriesField->FovX = 250;
	seriesField->FovY = 250;
	seriesField->PhasePoints = 224;
	seriesField->RepTime = 420000;
	seriesField->EchoTime = 18000;
		
	ScanSagital(scanField);
    
}


void CProtocolExample::SeriesSECor(SeriesField* seriesField, ScanField* scanField)
{
	SeriesSE(seriesField);

	memcpy(seriesField->Desc, "Cor SE2D T1W", 100);
    memcpy(seriesField->Protocol,"Cor SE2D T1W", 31);
    seriesField->Plane = ipCoronal;
	ScanCoronal(scanField);
	seriesField->FovX = 250;
	seriesField->FovY = 250;

    
}

void CProtocolExample::SeriesSEAx(SeriesField* seriesField, ScanField* scanField)
{
	SeriesSE(seriesField);
	seriesField->FovX = 220;
	seriesField->FovY = 220;

	ScanAxial(scanField);
    
}

//AX SE T1-W
void CProtocolExample::SeriesSE(SeriesField* seriesField)
{
	seriesField->Version = 0;
	seriesField->Size = sizeof(SeriesField);
    memcpy(seriesField->Desc, "Axial SE2D T1W", 100);
    memcpy(seriesField->Protocol,"Axial SE2D T1W", 31);
    seriesField->NucType = ntH1;
	seriesField->GRR = 42580000;	//nuclei (Hz/Tesla)
	seriesField->TXCoil = ctHeadQD;
	seriesField->RcvCoil = ctHeadQD;	// Receiver RF coil: == oi_coilRecv.		
	memcpy(seriesField->PulseSeqName, "SpinEcho 2D", 63);
	seriesField->SequenceOptions &= ~255;
    seriesField->SequenceOptions |= cnstSE;    /* Options related to pulse sequences.      */
	seriesField->SequenceOptions |= cnstChop;
    seriesField->OtherOptions |= cnstDefaultFrequencyDir; // added by YG
    seriesField->OtherOptions |= cnstSliceInterleave;
	seriesField->OtherOptions |= cnstHalfEcho;
    seriesField->Plane = ipAxial; 
	seriesField->Mode = im2D;
    seriesField->FovX = 240;		//* Display field-of-view along X (mm).
    seriesField->FovY = 240;		//* Diplay field-of-view along Y (mm).
    seriesField->ReadPoints = 256;
    seriesField->PhasePoints = 224;
	seriesField->ResolutionX = 256;		// The number of data poI4s along read 
	seriesField->ResolutionY = 256;		// The number of data poI4s along phase 
	seriesField->ResolutionZ = 14;		// The number of data poI4s along second 
	seriesField->SliceThickness = 8;	// Slice thickness in mm,  ==ui_sliceThk;   */
	seriesField->SliceGap = 1;		// Gap between two adjacent slices in mm. 
	seriesField->EchoTime = 17000;			// TE, the echo time in ms, == ui_TE		*/
	seriesField->RepTime = 400000;			// pusle repetition time in ms, == ui_TR	*/
	seriesField->NumEchoImages = 1;		// Number of different T2/T2* weighted 
	seriesField->AcqBandwidth = 20833;		// Acquisition bandwidth of the first echo,
	seriesField->EchoTrainLength = 1;	// Echo train length for EPI or FSE,
	seriesField->FlipAngle = 90;			// Flip angle of the excitation pulse. It's
	seriesField->HalfKSpaceRatio = 1.0;	// The ratio of phase and frequency 
	//seriesField->ContrastFlag;		// Whether a contrast agent is used.        */
    seriesField->NumAvg = 4;			// Number of scans, == ui_NumAvg			*/
    seriesField->PhEncOrder = peoSequential;	
    seriesField->DataType = cnstMagnitudeImage; 
}


//for axial.
void CProtocolExample::SeriesFSE(SeriesField* seriesField)
{
	seriesField->Version = 0;
	seriesField->Size = sizeof(SeriesField);
	memcpy(seriesField->Desc, "Axial FSE2D T2W", 100);
    memcpy(seriesField->Protocol,"Axial FSE2D T2W", 31);
    seriesField->NucType = ntH1;
	seriesField->GRR = 42580000;	//nuclei (Hz/Tesla)
	seriesField->TXCoil = ctHeadQD;
	seriesField->RcvCoil = ctHeadQD;	// Receiver RF coil: == oi_coilRecv.		
	memcpy(seriesField->PulseSeqName, "FSE 2D", 63);
	
	seriesField->SequenceOptions &= ~255;
    seriesField->SequenceOptions |= cnstFSE;    /* Options related to pulse sequences.      */
	seriesField->OtherOptions |= cnstDefaultFrequencyDir; // added by YG
    seriesField->OtherOptions |= cnstSliceInterleave; 
    seriesField->Plane = ipAxial; 
	seriesField->Mode = im2D;
    seriesField->FovX = 240;		//* Display field-of-view along X (mm).
    seriesField->FovY = 240;		//* Diplay field-of-view along Y (mm).
    seriesField->ReadPoints = 256;
    seriesField->PhasePoints = 224;
	seriesField->ResolutionX = 256;		// The number of data poI4s along read 
	seriesField->ResolutionY = 256;		// The number of data poI4s along phase 
	seriesField->ResolutionZ = 14;		// The number of data poI4s along second 
	seriesField->SliceThickness = 8;	// Slice thickness in mm,  ==ui_sliceThk;   */
    seriesField->SliceGap = 1;		// Gap between two adjacent slices in mm. 
	seriesField->EchoTime = 120000;			// TE, the echo time in ms, == ui_TE		*/
	seriesField->RepTime = 4000000;			// pusle repetition time in ms, == ui_TR	*/
	seriesField->NumEchoImages = 1;		// Number of different T2/T2* weighted 
	seriesField->AcqBandwidth = 15625;		// Acquisition bandwidth of the first echo,
	
	seriesField->EchoTrainLength = 7;	// Echo train length for EPI or FSE,
	seriesField->FlipAngle = 90;			// Flip angle of the excitation pulse. It's
									//filter whose type is DigFilterType.		*/
    seriesField->HalfKSpaceRatio = 1.0;	// The ratio of phase and frequency 
	seriesField->NumAvg = 3;			// Number of scans, == ui_NumAvg			*/
    seriesField->PhEncOrder = peoSequential;	
    seriesField->DataType = cnstMagnitudeImage; 
	seriesField->EchoSpacing = 37000;
	
}
//
void CProtocolExample::SeriesFSEAx(SeriesField* seriesField, ScanField* scanField)
{
	SeriesFSE(seriesField);
	seriesField->FlowCompensation = fcNone;

	ScanAxial(scanField);

    
}

void CProtocolExample::SeriesFSESag(SeriesField* seriesField, ScanField* scanField)
{
	SeriesFSE(seriesField);
	seriesField->FlowCompensation = fcRead;

	memcpy(seriesField->Desc, "Sag FSE2D T2W FC", 100);
    memcpy(seriesField->Protocol,"Sag FSE2D T2W Fc", 31);
    seriesField->Plane = ipSagittal;
	seriesField->FovX = 250;
	seriesField->FovY = 250;
	seriesField->EchoSpacing = 41000;
	seriesField->ResolutionZ = 12;		// The number of data poI4s along second 
	ScanSagital(scanField);
    
}

void CProtocolExample::SeriesFSECor(SeriesField* seriesField, ScanField* scanField)
{
	SeriesFSE(seriesField);

	seriesField->FlowCompensation = fcRead;

	memcpy(seriesField->Desc, "Cor FSE2D T2W FC", 100);
    memcpy(seriesField->Protocol,"Cor FSE2D T2W FC", 31);
    seriesField->Plane = ipCoronal;
	seriesField->FovX = 250;
	seriesField->FovY = 250;
	seriesField->EchoSpacing = 41000;
	seriesField->ResolutionZ = 12;		// The number of data poI4s along second 
    ScanCoronal(scanField);
}

void CProtocolExample::SeriesFLAIRAx(SeriesField* seriesField, ScanField* scanField)
{
	SeriesFSE(seriesField);

	seriesField->SequenceOptions &= ~255;
	seriesField->SequenceOptions |= cnstFLAIR;    /* Options related to pulse sequences.      */

	memcpy(seriesField->Desc, "AX FLAIR", 100);
    memcpy(seriesField->Protocol,"AX FLAIR", 31);
    seriesField->Plane = ipAxial;
	seriesField->RepTime = 11000000;
	seriesField->EchoTrainLength = 8;
	seriesField->AcqBandwidth = 20833;
	seriesField->EchoSpacing = 28000;
	seriesField->TI = 1700000;
	seriesField->EchoTime = 100000;
	seriesField->ResolutionZ = 16;
	seriesField->ReadPoints = 200;
	seriesField->PhasePoints = 192;
	seriesField->NumAvg = 2 ;
	ScanAxial(scanField);
    
}

void CProtocolExample::SeriesFLAIRSag(SeriesField* seriesField, ScanField* scanField)
{
	SeriesFSE(seriesField);

	seriesField->SequenceOptions &= ~255;
	seriesField->SequenceOptions |= cnstFLAIR;    /* Options related to pulse sequences.      */

	memcpy(seriesField->Desc, "Sag FLAIR", 100);
    memcpy(seriesField->Protocol,"Sag FLAIR", 31);
    seriesField->Plane = ipSagittal;
	seriesField->RepTime = 11000000;
	seriesField->TI = 1700000;
	seriesField->EchoTime = 100000;
	seriesField->ResolutionZ = 16;
	seriesField->ReadPoints = 200;
	seriesField->PhasePoints = 192;
	seriesField->NumAvg = 2 ;
	seriesField->EchoTrainLength = 8;
	seriesField->AcqBandwidth = 20833;
	seriesField->EchoSpacing = 28000;
	seriesField->FovX = 250;
	seriesField->FovY = 250;
	ScanSagital(scanField);
    
}
void CProtocolExample::SeriesFLAIRCor(SeriesField* seriesField, ScanField* scanField)
{
	SeriesFSE(seriesField);

	seriesField->SequenceOptions &= ~255;
	seriesField->SequenceOptions |= cnstFLAIR;    /* Options related to pulse sequences.      */

	memcpy(seriesField->Desc, "Cor FLAIR", 100);
    memcpy(seriesField->Protocol,"Cor FLAIR", 31);
    seriesField->Plane = ipCoronal;
	seriesField->RepTime = 11000000;
	seriesField->TI = 1700000;
	seriesField->EchoTime = 100000;
	seriesField->ResolutionZ = 16;
	seriesField->ReadPoints = 200;
	seriesField->PhasePoints = 192;
	seriesField->NumAvg = 2 ;
	seriesField->EchoTrainLength = 8;
	seriesField->AcqBandwidth = 20833;
	seriesField->EchoSpacing = 28000;
	seriesField->FovX = 250;
	seriesField->FovY = 250;
	
    ScanCoronal(scanField);
}

void CProtocolExample::SeriesSPGR3DCor(SeriesField* seriesField)
{
	seriesField->Version = 0;
	seriesField->Size = sizeof(SeriesField);
    // seriesField->Id = 2;
	memcpy(seriesField->Desc, "Coronal SPGR3D  T1W", 100);
    memcpy(seriesField->Protocol,"Coronal SPGR3D  T1W", 31);
    seriesField->NucType = ntH1;
	seriesField->GRR = 42580000;	//nuclei (Hz/Tesla)
	seriesField->TXCoil = ctHeadSolonoid;
	//seriesField->UserTxCoilDesc[32];	// Used only when TXCoil == USER.
	seriesField->RcvCoil = ctHeadSolonoid;	// Receiver RF coil: == oi_coilRecv.		
	//seriesField->UserRcvCoilDesc[32];// Used only when RcvCoil == USER.
	memcpy(seriesField->PulseSeqName, "SPGR3D", 63);
	seriesField->SequenceOptions &= ~255;
    seriesField->SequenceOptions |= cnstSPGR;    /* Options related to pulse sequences.      */
	//seriesField->SequenceOptions |= cnstChop;
    seriesField->OtherOptions |= cnstDefaultFrequencyDir; // added by YG
    seriesField->Plane = ipCoronal; 
	seriesField->Mode = im3D;
    seriesField->FovX = 180;		//* Display field-of-view along X (mm).
    seriesField->FovY = 180;		//* Diplay field-of-view along Y (mm).
    //seriesField->FovZ;				// Display field-of-view along Z (mm). only 
    seriesField->ReadPoints = 192;
    seriesField->PhasePoints = 192;
	seriesField->ResolutionX = 256;		// The number of data poI4s along read 
	seriesField->ResolutionY = 256;		// The number of data poI4s along phase 
	seriesField->ResolutionZ = 16;		// The number of data poI4s along second 
	seriesField->SliceThickness = 3;	// Slice thickness in mm,  ==ui_sliceThk;   */
    seriesField->NumSlab = 1;			// Number of slabs in 3D scan.				*/
    //seriesField->SlabOrder = 1;		// Order of a slab, see enum PhEncOrder		*/
	//seriesField->NumPntsPerSlab;		// Resolution along Z in one slab			*/
	//seriesField->SlabOverlap;			// Number of overlapped slice between two adjacent slabs.							*/
	seriesField->SliceGap = 0;		// Gap between two adjacent slices in mm. 
	seriesField->EchoTime = 15000;			// TE, the echo time in us, == ui_TE		*/
	//seriesField->Echo2Time;			// TE2, the second echo time, this is used 
	seriesField->RepTime = 45000;			// pusle repetition time in us, == ui_TR	*/
	seriesField->NumEchoImages = 1;		// Number of different T2/T2* weighted 
	seriesField->AcqBandwidth = 7813;		// Acquisition bandwidth of the first echo,
	//seriesField->AcqBandwidth2;		// Bandwidth of second or higher echoes,
	seriesField->EchoTrainLength = 1;	// Echo train length for EPI or FSE,
	seriesField->FlipAngle = 45;			// Flip angle of the excitation pulse. It's
	seriesField->HalfKSpaceRatio = 1.0;	// The ratio of phase and frequency 
	//seriesField->ContrastFlag;		// Whether a contrast agent is used.        */
    seriesField->NumAvg = 1;			// Number of scans, == ui_NumAvg			*/
    seriesField->PhEncOrder = peoSequential;	
    seriesField->DataType = cnstMagnitudeImage;
}


void CProtocolExample::ScanCoronal(ScanField* scanField)
{
	scanField->Version = 0;				// Version of this field. Format:
	scanField->Size = sizeof(ScanField);// Size of this field.                      	
    // scanField->Id = 1;			        // Scan ID, sequential number in series.	
	scanField->FreqDir = hcdSI;			// The frequency encoding direciton, can 
	scanField->FreqDirX = 0;			//
	scanField->FreqDirY = 1;			//
	scanField->FreqDirZ = 0;			// Frequence encoding direction			
	scanField->PhaseDirX = 1;			//
	scanField->PhaseDirY = 0;			//
	scanField->PhaseDirZ = 0;			// Phase encoding direction 
    scanField->SliceDirX = 0;			//
	scanField->SliceDirY = 0;			//
	scanField->SliceDirZ = 1;			//

	scanField->ReadOffset  = 0;			//
	scanField->PhaseOffset = 0;			// center poI4, in mm						*/
	scanField->SliceOffset = 0;			//
    //scanField->AnaRCGain;			// Hardware analog receiver level (.1db).							   
    scanField->DigRCGain = 0.5f;			// Digital receiver gain. (.1db)(?)			*/
    scanField->O1 = 0;					// Transmitter center frequency offset.		*/
    //scanField->Reservered[256];	// User defined scan variables.				*/

}

void CProtocolExample::ScanSagital(ScanField* scanField)
{
	scanField->Version = 0;				// Version of this field. Format:
	scanField->Size = sizeof(ScanField);// Size of this field.                      	
    scanField->FreqDir = hcdSI;			// The frequency encoding direciton, can 
	scanField->FreqDirX = 0;			//
	scanField->FreqDirY = 1;			//
	scanField->FreqDirZ = 0;			// Frequence encoding direction			
	scanField->PhaseDirX = 0;			//
	scanField->PhaseDirY = 0;			//
	scanField->PhaseDirZ = 1;			// Phase encoding direction 
    scanField->SliceDirX = 1;			//
	scanField->SliceDirY = 0;			//
	scanField->SliceDirZ = 0;			//
	scanField->ReadOffset  = 0;			//
	scanField->PhaseOffset = 0;			// center poI4, in mm						*/
	scanField->SliceOffset = 0;			//
    scanField->DigRCGain = 0.5;			// Digital receiver gain. (.1db)(?)			*/
    scanField->O1 = 0;					// Transmitter center frequency offset.		*/

}

void CProtocolExample::ScanAxial(ScanField* scanField)
{
	scanField->Version = 0;				// Version of this field. Format:
	scanField->Size = sizeof(ScanField);// Size of this field.                      	
    // scanField->Id = 1;			        // Scan ID, sequential number in series.	
	scanField->FreqDir = hcdAP;			// The frequency encoding direciton, can 
	scanField->FreqDirX = 0;			//
	scanField->FreqDirY = 0;			//
	scanField->FreqDirZ = 1;			// Frequence encoding direction			
	scanField->PhaseDirX = 1;			//
	scanField->PhaseDirY = 0;			//
	scanField->PhaseDirZ = 0;			// Phase encoding direction 
    scanField->SliceDirX = 0;			//
	scanField->SliceDirY = 1;			//
	scanField->SliceDirZ = 0;			//

	scanField->ReadOffset  = 0;			//
	scanField->PhaseOffset = 0;			// center poI4, in mm						*/
	scanField->SliceOffset = 0;			//
    //scanField->AnaRCGain;			// Hardware analog receiver level (.1db).							   
    scanField->DigRCGain = 0.5;			// Digital receiver gain. (.1db)(?)			*/
    scanField->O1 = 0;					// Transmitter center frequency offset.		*/
    //scanField->Reservered[256];	// User defined scan variables.				*/

}

////////pelvis.
void CProtocolExample::PelvScanAxial(ScanField* scanField)
{
	scanField->Version = 0;				// Version of this field. Format:
	scanField->Size = sizeof(ScanField);// Size of this field.                      	
    scanField->FreqDir = hcdLR;			// The frequency encoding direciton, can 
	scanField->FreqDirX = 1;			//
	scanField->FreqDirY = 0;			//
	scanField->FreqDirZ = 0;			// Frequence encoding direction			
	scanField->PhaseDirX = 0;			//
	scanField->PhaseDirY = 0;			//
	scanField->PhaseDirZ = 1;			// Phase encoding direction 
    scanField->SliceDirX = 0;			//
	scanField->SliceDirY = 1;			//
	scanField->SliceDirZ = 0;			//

	scanField->ReadOffset  = 0;			//
	scanField->PhaseOffset = 0;			// center poI4, in mm						*/
	scanField->SliceOffset = 0;			//
    //scanField->AnaRCGain;			// Hardware analog receiver level (.1db).							   
    scanField->DigRCGain = 0.5;			// Digital receiver gain. (.1db)(?)			*/
    scanField->O1 = 0;					// Transmitter center frequency offset.		*/
    //scanField->Reservered[256];	// User defined scan variables.				*/

}
void CProtocolExample::PelvScanCoronal(ScanField* scanField)
{
	scanField->Version = 0;				// Version of this field. Format:
	scanField->Size = sizeof(ScanField);// Size of this field.                      	
    scanField->FreqDir = hcdSI;			// The frequency encoding direciton, can 
	scanField->FreqDirX = 0;			//
	scanField->FreqDirY = 1;			//
	scanField->FreqDirZ = 0;			// Frequence encoding direction			
	scanField->PhaseDirX = 1;			//
	scanField->PhaseDirY = 0;			//
	scanField->PhaseDirZ = 0;			// Phase encoding direction 
    scanField->SliceDirX = 0;			//
	scanField->SliceDirY = 0;			//
	scanField->SliceDirZ = 1;			//

	scanField->ReadOffset  = 0;			//
	scanField->PhaseOffset = 0;			// center poI4, in mm						*/
	scanField->SliceOffset = 0;			//
    scanField->DigRCGain = 0.5f;			// Digital receiver gain. (.1db)(?)			*/
    scanField->O1 = 0;					// Transmitter center frequency offset.		*/
    
}
void CProtocolExample::PelvScanSagital(ScanField* scanField)
{
	scanField->Version = 0;				// Version of this field. Format:
	scanField->Size = sizeof(ScanField);// Size of this field.                      	
    scanField->FreqDir = hcdSI;			// The frequency encoding direciton, can 
	scanField->FreqDirX = 0;			//
	scanField->FreqDirY = 1;			//
	scanField->FreqDirZ = 0;			// Frequence encoding direction			
	scanField->PhaseDirX = 0;			//
	scanField->PhaseDirY = 0;			//
	scanField->PhaseDirZ = 1;			// Phase encoding direction 
    scanField->SliceDirX = 1;			//
	scanField->SliceDirY = 0;			//
	scanField->SliceDirZ = 0;			//
	scanField->ReadOffset  = 0;			//
	scanField->PhaseOffset = 0;			// center poI4, in mm						*/
	scanField->SliceOffset = 0;			//
    scanField->DigRCGain = 0.5;			// Digital receiver gain. (.1db)(?)			*/
    scanField->O1 = 0;					// Transmitter center frequency offset.		*/
}



void CProtocolExample::PelvSESag(SeriesField* seriesField, ScanField* scanField)
{

	SeriesSE(seriesField);

	memcpy(seriesField->Desc, "Sag SE2D T1W", 100);
    memcpy(seriesField->Protocol,"Sag SE2D T1W", 31);
    seriesField->Plane = ipSagittal;
	seriesField->TXCoil =ctBodyQDL;
	seriesField->RcvCoil = ctBodyQDL;	// Receiver RF coil: == oi_coilRecv.		

	
	seriesField->NumAvg = 1;			// Number of scans, == ui_NumAvg			*/
	seriesField->PhasePoints = 192;

	seriesField->FovX = 350;
	seriesField->FovY = 350;

	seriesField->SliceGap = 2;
	seriesField->RepTime = 600000;
	seriesField->EchoTime = 24000;
	seriesField->AcqBandwidth = 17857;
	
		
	PelvScanSagital(scanField);

}
void CProtocolExample::PelvSEAx(SeriesField* seriesField,  ScanField* scanField)
{
	SeriesSE(seriesField);
	
	seriesField->TXCoil =ctBodyQDL;
	seriesField->RcvCoil = ctBodyQDL;	// Receiver RF coil: == oi_coilRecv.

	seriesField->FovX = 350;
	seriesField->FovY = 350;

	seriesField->SliceGap = 2;
	seriesField->RepTime = 600000;
	seriesField->EchoTime = 24000;
	seriesField->AcqBandwidth = 17857;
	seriesField->PhasePoints = 192;

	PelvScanAxial(scanField);
	

}
void CProtocolExample::PelvSECor(SeriesField* seriesField, ScanField* scanField)
{
	SeriesSE(seriesField);

	memcpy(seriesField->Desc, "Cor SE2D T1W", 100);
    memcpy(seriesField->Protocol,"Cor SE2D T1W", 31);
    seriesField->Plane = ipCoronal;
	
	seriesField->TXCoil =ctBodyQDL;
	seriesField->RcvCoil = ctBodyQDL;	// Receiver RF coil: == oi_coilRecv.		

	seriesField->FovX = 350;
	seriesField->FovY = 350;

	seriesField->SliceGap = 2;
	seriesField->RepTime = 600000;
	seriesField->EchoTime = 24000;
	seriesField->AcqBandwidth = 17857;
	seriesField->PhasePoints = 192;


	PelvScanCoronal(scanField);

}
void CProtocolExample::PelvFSEAx(SeriesField* seriesField, ScanField* scanField)
{
	SeriesFSE(seriesField);
	seriesField->FlowCompensation = fcNone;

	seriesField->TXCoil =ctBodyQDL;
	seriesField->RcvCoil = ctBodyQDL;	// Receiver RF coil: == oi_coilRecv.		

	seriesField->FovX = 350;
	seriesField->FovY = 350;
	seriesField->EchoTrainLength = 11;
	seriesField->EchoSpacing = 26000;
	seriesField->SliceGap = 2;
	seriesField->AcqBandwidth = 35714;
	seriesField->NumAvg = 6;
	seriesField->PhasePoints = 220;
	seriesField->RepTime = 4200000;
	
	PelvScanAxial(scanField);
}
void CProtocolExample::PelvFSESag(SeriesField* seriesField, ScanField* scanField)
{
	SeriesFSE(seriesField);
	seriesField->FlowCompensation = fcRead;

	memcpy(seriesField->Desc, "Sag FSE2D T2W FC", 100);
    memcpy(seriesField->Protocol,"Sag FSE2D T2W Fc", 31);
    seriesField->Plane = ipSagittal;

	seriesField->FovX = 350;
	seriesField->FovY = 350;
	seriesField->EchoTrainLength = 11;
	seriesField->EchoSpacing = 30000;
	seriesField->SliceGap = 2;
	seriesField->AcqBandwidth = 35714;
	seriesField->NumAvg = 6;
	seriesField->TXCoil =ctBodyQDL;
	seriesField->RcvCoil = ctBodyQDL;	// Receiver RF coil: == oi_coilRecv.		
	seriesField->PhasePoints = 220;
	seriesField->RepTime = 4000000;
	seriesField->ResolutionZ = 11;

	PelvScanSagital(scanField);
}
void CProtocolExample::PelvFSECor(SeriesField* seriesField, ScanField* scanField)
{
	SeriesFSE(seriesField);

	seriesField->FlowCompensation = fcRead;

	memcpy(seriesField->Desc, "Cor FSE2D T2W FC", 100);
    memcpy(seriesField->Protocol,"Cor FSE2D T2W FC", 31);
    seriesField->Plane = ipCoronal;
	seriesField->TXCoil =ctBodyQDL;
	seriesField->RcvCoil = ctBodyQDL;	// Receiver RF coil: == oi_coilRecv.		

	
	seriesField->FovX = 350;
	seriesField->FovY = 350;
	seriesField->EchoTrainLength = 11;
	seriesField->EchoSpacing = 30000;
	seriesField->SliceGap = 2;
	seriesField->AcqBandwidth = 35714;
	seriesField->NumAvg = 6;

	seriesField->PhasePoints = 220;
	seriesField->RepTime = 4000000;
	seriesField->ResolutionZ = 11;
	
    PelvScanCoronal(scanField);
}
void CProtocolExample::PelvSTIRAx(SeriesField* seriesField, ScanField* scanField)
{
	SeriesFSE(seriesField);

	seriesField->SequenceOptions &= ~255;
	seriesField->SequenceOptions |= cnstSTIR;

	memcpy(seriesField->Desc, "AX STIR", 100);
    memcpy(seriesField->Protocol,"AX STIR", 31);
    seriesField->Plane = ipAxial;
	
	seriesField->TI = 80000;
	seriesField->ReadPoints = 256;
	seriesField->TXCoil =ctBodyQDL;
	seriesField->RcvCoil = ctBodyQDL;	// Receiver RF coil: == oi_coilRecv.		
	seriesField->FovX = 350;
	seriesField->FovY = 350;

	seriesField->ResolutionZ = 12;
	seriesField->SliceGap = 2;
	seriesField->RepTime = 4000000;
	seriesField->EchoTime = 20000;
	seriesField->AcqBandwidth = 35714;
	seriesField->EchoTrainLength = 7;
	seriesField->PhasePoints = 224;
	seriesField->EchoSpacing = 26000;
	seriesField->NumAvg = 4;


	PelvScanAxial(scanField);
    
}
void CProtocolExample::PelvSTIRSag(SeriesField* seriesField, ScanField* scanField)
{
	SeriesFSE(seriesField);

	seriesField->SequenceOptions &= ~255;
	seriesField->SequenceOptions |= cnstSTIR;    /* Options related to pulse sequences.      */

	memcpy(seriesField->Desc, "Sag STIR", 100);
    memcpy(seriesField->Protocol,"Sag STIR", 31);
    seriesField->Plane = ipSagittal;
	
	seriesField->TI = 80000;
	seriesField->ReadPoints = 256;
	seriesField->TXCoil =ctBodyQDL;
	seriesField->RcvCoil = ctBodyQDL;	// Receiver RF coil: == oi_coilRecv.		
	seriesField->FovX = 350;
	seriesField->FovY = 350;

	seriesField->ResolutionZ = 12;
	seriesField->SliceGap = 2;
	seriesField->RepTime = 4000000;
	seriesField->EchoTime = 20000;
	seriesField->AcqBandwidth = 35714;
	seriesField->EchoTrainLength = 7;
	seriesField->PhasePoints = 224;
	seriesField->EchoSpacing = 26000;
	seriesField->NumAvg = 4;

	PelvScanSagital(scanField);
    
}
void CProtocolExample::PelvSTIRCor(SeriesField* seriesField, ScanField* scanField)
{
	SeriesFSE(seriesField);

	seriesField->SequenceOptions &= ~255;
	seriesField->SequenceOptions |= cnstSTIR;    /* Options related to pulse sequences.      */

	memcpy(seriesField->Desc, "Cor STIR", 100);
    memcpy(seriesField->Protocol,"Cor STIR", 31);
    seriesField->Plane = ipCoronal;
	
	seriesField->TI = 80000;
	seriesField->ReadPoints = 256;
	seriesField->TXCoil =ctBodyQDL;
	seriesField->RcvCoil = ctBodyQDL;	// Receiver RF coil: == oi_coilRecv.		
	seriesField->FovX = 350;
	seriesField->FovY = 350;

	seriesField->ResolutionZ = 12;
	seriesField->SliceGap = 2;
	seriesField->RepTime = 4000000;
	seriesField->EchoTime = 20000;
	seriesField->AcqBandwidth = 35714;
	seriesField->EchoTrainLength = 7;
	seriesField->PhasePoints = 224;
	seriesField->EchoSpacing = 26000;
	seriesField->NumAvg = 4;

    PelvScanCoronal(scanField);
	

}

// Removed for release version 2005-06-05
/*
void CProtocolExample::TESTHeadSPRGCor(SeriesField* seriesField, ScanField* scanField)
{
	SeriesSPGR3DCor(seriesField);
	memcpy(seriesField->Desc, "TEST SPGR3D  Coronal", 100);
    memcpy(seriesField->Protocol,"TEST SPGR3D Coronal", 31);

	memcpy(seriesField->PulseSeqName, "TESTSPGR", 63);
	seriesField->SequenceOptions &= ~255;
	seriesField->SequenceOptions |= cnstTESTSPGR;    // Options related to pulse sequences.     
   

	ScanCoronal(scanField);
	
}
void CProtocolExample::TESTSeriesSEAx(SeriesField* seriesField,  ScanField* scanField)
{
	SeriesSE(seriesField);

	memcpy(seriesField->Desc, "TESTSE AXIAL", 100);
    memcpy(seriesField->Protocol,"TESTSE AXIAL", 31);

	memcpy(seriesField->PulseSeqName, "TESTSE", 63);
	seriesField->SequenceOptions &= ~255;
	seriesField->SequenceOptions |= cnstTESTSE;    // Options related to pulse sequences.
   

	seriesField->FovX = 220;
	seriesField->FovY = 220;

	ScanAxial(scanField);


}
void CProtocolExample::TESTSeiresFSEAx(SeriesField* seriesField, ScanField* scanField)
{
	SeriesFSE(seriesField);
	seriesField->FlowCompensation = 0; //none.
	memcpy(seriesField->Desc, "TESTFSE AXIAL", 100);
    memcpy(seriesField->Protocol,"TESFTSE AXIAL", 31);

	memcpy(seriesField->PulseSeqName, "TESTFSE", 63);
	seriesField->SequenceOptions &= ~255;
	seriesField->SequenceOptions |= cnstTESTFSE;    // Options related to pulse sequences.
   
	ScanAxial(scanField);
}
*/

void CProtocolExample::KneeSESag(SeriesField* seriesField, ScanField* scanField)
{
	SeriesSE(seriesField);

	memcpy(seriesField->Desc, "Sag SE2D T1W", 100);
    memcpy(seriesField->Protocol,"Sag SE2D T1W", 31);
    seriesField->Plane = ipSagittal;
	seriesField->TXCoil =ctKneeQD;
	seriesField->RcvCoil = ctKneeQD;	// Receiver RF coil: == oi_coilRecv.		
		
	seriesField->NumAvg = 1;			// Number of scans, == ui_NumAvg			*/
	seriesField->PhasePoints = 192;

	seriesField->FovX = 240;
	seriesField->FovY = 240;

	seriesField->SliceGap = 2;
	seriesField->RepTime = 600000;
	seriesField->EchoTime = 24000;
	seriesField->AcqBandwidth = 17857;
	
		
	ScanSagital(scanField);

}
void CProtocolExample::KneeSEAx(SeriesField* seriesField,  ScanField* scanField)
{
	SeriesSE(seriesField);
	
	seriesField->TXCoil =ctKneeQD;
	seriesField->RcvCoil = ctKneeQD;	// Receiver RF coil: == oi_coilRecv.

	seriesField->FovX = 200;
	seriesField->FovY = 200;

	seriesField->SliceGap = 1;
	seriesField->SliceThickness = 4.0f;
	seriesField->RepTime = 600000;
	seriesField->EchoTime = 24000;
	seriesField->AcqBandwidth = 17857;
	seriesField->PhasePoints = 192;
	seriesField->NumAvg = 4;

	ScanAxial(scanField);
	
}
void CProtocolExample::KneeSECor(SeriesField* seriesField, ScanField* scanField)
{
	SeriesSE(seriesField);

	memcpy(seriesField->Desc, "Cor SE2D T1W", 100);
    memcpy(seriesField->Protocol,"Cor SE2D T1W", 31);
    seriesField->Plane = ipCoronal;
	
	seriesField->TXCoil =ctKneeQD;
	seriesField->RcvCoil = ctKneeQD;	// Receiver RF coil: == oi_coilRecv.		

	seriesField->FovX = 240;
	seriesField->FovY = 240;

	seriesField->SliceGap = 2;
	seriesField->RepTime = 600000;
	seriesField->EchoTime = 24000;
	seriesField->AcqBandwidth = 17857;
	seriesField->PhasePoints = 192;
	PelvScanCoronal(scanField);

}

void CProtocolExample::KneeFSESag(SeriesField* seriesField, ScanField* scanField)
{
	SeriesFSE(seriesField);
	
	memcpy(seriesField->Desc, "Sag FSE2D T2W", 100);
    memcpy(seriesField->Protocol,"Sag FSE2D T2W Fc", 31);
    seriesField->Plane = ipSagittal;

	seriesField->EchoTime = 100000;

	seriesField->FovX = 200;
	seriesField->FovY = 200;
	seriesField->EchoTrainLength = 8;
	seriesField->EchoSpacing = 25000;
	seriesField->SliceGap = 1;
	seriesField->SliceThickness = 4.0f;
	seriesField->AcqBandwidth = 25000;
	seriesField->NumAvg = 4;
	seriesField->TXCoil =ctKneeQD;
	seriesField->RcvCoil = ctKneeQD;	// Receiver RF coil: == oi_coilRecv.		
	seriesField->PhasePoints = 224;
	seriesField->RepTime = 4000000;
	seriesField->ResolutionZ = 16;

	ScanSagital(scanField);

}

void CProtocolExample::KneeSTIRSag(SeriesField* seriesField, ScanField* scanField)
{
	SeriesFSE(seriesField);

	seriesField->SequenceOptions &= ~255;
	seriesField->SequenceOptions |= cnstSTIR;    /* Options related to pulse sequences.      */

	memcpy(seriesField->Desc, "Sag STIR", 100);
    memcpy(seriesField->Protocol,"Sag STIR", 31);
    seriesField->Plane = ipSagittal;
	
	seriesField->TI = 80000;
	seriesField->ReadPoints = 256;
	seriesField->TXCoil =ctKneeQD;
	seriesField->RcvCoil = ctKneeQD;	// Receiver RF coil: == oi_coilRecv.		
	seriesField->FovX = 200;
	seriesField->FovY = 200;

	seriesField->ResolutionZ = 16;
	seriesField->SliceGap = 1;
	seriesField->SliceThickness = 4.0f;

	seriesField->RepTime = 5000000;
	seriesField->EchoTime = 20000;
	seriesField->AcqBandwidth = 35714;
	seriesField->EchoTrainLength = 7;
	seriesField->PhasePoints = 224;
	seriesField->EchoSpacing = 26000;
	seriesField->NumAvg = 4;

	ScanSagital(scanField);

}

void CProtocolExample::SeriesGE2D(SeriesField* seriesField)
{

	seriesField->Version = 0;
	seriesField->Size = sizeof(SeriesField);
    memcpy(seriesField->Desc, "Axial GE2D", 100);
    memcpy(seriesField->Protocol,"Axial GE2D T1W", 31);
    seriesField->NucType = ntH1;
	seriesField->GRR = 42580000;	//nuclei (Hz/Tesla)
	seriesField->TXCoil = ctHeadQD;
	seriesField->RcvCoil = ctHeadQD;	// Receiver RF coil: == oi_coilRecv.		
	memcpy(seriesField->PulseSeqName, "GradientEcho 2D", 63);
	seriesField->SequenceOptions &= ~255;
    seriesField->SequenceOptions |= cnstGRE;    /* Options related to pulse sequences.      */
	seriesField->SequenceOptions |= cnstChop;
    seriesField->OtherOptions |= cnstDefaultFrequencyDir; // added by YG
    seriesField->OtherOptions |= cnstSliceInterleave;
	seriesField->OtherOptions |= cnstHalfEcho;
    seriesField->Plane = ipAxial; 
	seriesField->Mode = im2D;
    seriesField->FovX = 240;		//* Display field-of-view along X (mm).
    seriesField->FovY = 240;		//* Diplay field-of-view along Y (mm).
    seriesField->ReadPoints = 256;
    seriesField->PhasePoints = 224;
	seriesField->ResolutionX = 256;		// The number of data poI4s along read 
	seriesField->ResolutionY = 256;		// The number of data poI4s along phase 
	seriesField->ResolutionZ = 14;		// The number of data poI4s along second 
	seriesField->SliceThickness = 8;	// Slice thickness in mm,  ==ui_sliceThk;   */
	seriesField->SliceGap = 1;		// Gap between two adjacent slices in mm. 
	seriesField->EchoTime = 17000;			// TE, the echo time in ms, == ui_TE		*/
	seriesField->RepTime = 400000;			// pusle repetition time in ms, == ui_TR	*/
	seriesField->NumEchoImages = 1;		// Number of different T2/T2* weighted 
	seriesField->AcqBandwidth = 20833;		// Acquisition bandwidth of the first echo,
	seriesField->EchoTrainLength = 1;	// Echo train length for EPI or FSE,
	seriesField->FlipAngle = 30;			// Flip angle of the excitation pulse. It's
	seriesField->HalfKSpaceRatio = 1.0;	// The ratio of phase and frequency 
	//seriesField->ContrastFlag;		// Whether a contrast agent is used.        */
    seriesField->NumAvg = 1;			// Number of scans, == ui_NumAvg			*/
    seriesField->PhEncOrder = peoSequential;	
    seriesField->DataType = cnstMagnitudeImage; 
}

void CProtocolExample::Shimming(SeriesField* seriesField, ScanField* scanField) //LZ 2004-08-25
{
	seriesField->Version = 0;
	seriesField->Size = sizeof(SeriesField);
    memcpy(seriesField->Desc, "Axial SHIM2D", 100);
    memcpy(seriesField->Protocol,"Axial SHIM2D", 31);
    seriesField->NucType = ntH1;
	seriesField->GRR = 42580000;	//nuclei (Hz/Tesla)
	seriesField->TXCoil = ctHeadQD;
	seriesField->RcvCoil = ctHeadQD;	// Receiver RF coil: == oi_coilRecv.		
	memcpy(seriesField->PulseSeqName, "GradientEcho 2D", 63);
	seriesField->SequenceOptions &= ~255;
    seriesField->SequenceOptions |= cnstShimming;    /* Options related to pulse sequences.      */
	seriesField->SequenceOptions |= cnstChop;
    seriesField->OtherOptions |= cnstDefaultFrequencyDir; // added by YG
    seriesField->OtherOptions |= cnstSliceInterleave;
	seriesField->OtherOptions |= cnstHalfEcho;
    seriesField->Plane = ipAxial; 
	seriesField->Mode = im2D;
    seriesField->FovX = 240;		//* Display field-of-view along X (mm).
    seriesField->FovY = 240;		//* Diplay field-of-view along Y (mm).
    seriesField->ReadPoints = 256;
    seriesField->PhasePoints = 224;
	seriesField->ResolutionX = 256;		// The number of data poI4s along read 
	seriesField->ResolutionY = 256;		// The number of data poI4s along phase 
	seriesField->ResolutionZ = 1;		// The number of data poI4s along second 
	seriesField->SliceThickness = 8;	// Slice thickness in mm,  ==ui_sliceThk;   */
	seriesField->SliceGap = 1;		// Gap between two adjacent slices in mm. 
	seriesField->EchoTime = 17000;			// TE, the echo time in ms, == ui_TE		*/
	seriesField->RepTime = 100000;			// pusle repetition time in ms, == ui_TR	*/
	seriesField->NumEchoImages = 1;		// Number of different T2/T2* weighted 
	seriesField->AcqBandwidth = 20833;		// Acquisition bandwidth of the first echo,
	seriesField->EchoTrainLength = 1;	// Echo train length for EPI or FSE,
	seriesField->FlipAngle = 30;			// Flip angle of the excitation pulse. It's
	seriesField->HalfKSpaceRatio = 1.0;	// The ratio of phase and frequency 
	//seriesField->ContrastFlag;		// Whether a contrast agent is used.        */
    seriesField->NumAvg = 1;			// Number of scans, == ui_NumAvg			*/
    seriesField->PhEncOrder = peoSequential;	
    seriesField->DataType = cnstMagnitudeImage; 
	ScanAxial(scanField);
}
