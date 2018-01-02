#ifndef __GROWSTRING_H_INC
#define __GROWSTRING_H_INC

class GrowString
{
public:
  GrowString();
  GrowString( char * );
  ~GrowString();
  char *append( char * );
  char *strValue( void ) { return _s; };
  int length() { return _len; };
  void reset( void ) { _s[0] = 0; _len = 0; };
private:
  char *_s;
  int _len;
  int _max;
};


#endif