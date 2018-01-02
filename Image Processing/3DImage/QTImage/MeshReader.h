
#ifndef __MeshReader_h
#define __MeshReader_h

#include "vtkPolyDataAlgorithm.h"

class CMeshReader : public vtkPolyDataAlgorithm 
{
public:
  static CMeshReader *New();
  vtkTypeRevisionMacro(CMeshReader,vtkPolyDataAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Specify file name of Wavefront .obj file.
  vtkSetStringMacro(FileName);
  vtkGetStringMacro(FileName);

protected:
  CMeshReader();
  ~CMeshReader();
  
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

  char *FileName;
private:
  int is_whitespace(char c);
  CMeshReader(const CMeshReader&);  // Not implemented.
  void operator=(const CMeshReader&);  // Not implemented.
};

#endif
