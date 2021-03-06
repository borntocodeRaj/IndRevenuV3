//## Module : YmIrSysParms
//SFD
//  Name    : YmIrSysParms.h
//  Author  : Bernard Sabatti�
//  Desc    : Contains YmIrSysParms Header Class Descriptions
//EFD

#ifndef YmIrSysParms_h
#define YmIrSysParms_h 1

//## Includes
#include 	<string>
#include 	"YmIrGlobal.h"

class YmIrSysParms
{
 public:
  //## Constructor
  YmIrSysParms();

  //## Destructor
  ~YmIrSysParms();

  //## Autres
  string getChar(char *c_sysParmName, char *c_sysParmPlus);
  bool   getFloat(char *c_sysParmName, char *c_sysParmPlus, float &);
  bool   getInt(char *c_sysParmName, char *c_sysParmPlus, int &);
};

typedef class YmIrSysParms *YmIrSysParmsP;

#endif
