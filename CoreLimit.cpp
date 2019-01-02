//## Module: CoreLimit
//SFD
//  Name   : CoreLimit.cpp
//  Author : 
//  Desc   : Contains CoreLimit Methods
//EFD

using namespace std;

//## Includes
#include <sys/resource.h>
#include <iostream>
#include "CoreLimit.h"

//SMD
// Name : SetCoreLimit
// Desc : Set the core limit size
//EMD
void SetCoreLimit(const int maxCoreSize_)
{
  struct rlimit rlp;

  rlp.rlim_max = maxCoreSize_;
  rlp.rlim_cur = maxCoreSize_;
  setrlimit(RLIMIT_CORE, &rlp);
  getrlimit(RLIMIT_CORE, &rlp);
  cerr << "Core limit Current " << rlp.rlim_cur << " "
       << "Core limit Max " << rlp.rlim_max << endl;
}
