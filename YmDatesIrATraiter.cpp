//## Module : YmDatesIrTraitees
//SFD
//  Name    : YmDatesIrATraiter.cpp
//  Author  : plf
//  Desc    : Contenu de la classe qui mappe la table des Dates/J_X ATraiter 
//EFD

using namespace std;

//## Includes
#include "YmDatesIrATraiter.h"

//SMD
// Name : Constructor
// Desc : Create YmDatesIrATraiter and assign values to the attributes
//EMD
YmDatesIrATraiter::YmDatesIrATraiter(YmDate DateATraiter, unsigned char Busy)
{
  _DateATraiter = DateATraiter;
  _Busy = Busy;
}

