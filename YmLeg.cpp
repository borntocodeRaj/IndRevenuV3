//## Module : YmLeg
//SFD
//  Name    : YmLeg.cpp
//  Author  : William Lienard
//  Desc    : Traitement de la class YmLeg
//EFD

using namespace std;

//## Includes

#include <stdlib.h>
#include <string>
#include "YmTranche.h"
#include "YmLeg.h"
#include "YmStations.h"
#include "YmMapStations.h"



//SMD
// Name : Constructor
// Desc : Creates YmLeg
//EMD

YmLeg::YmLeg():
  _legOrigin(),
  _legDest(),
  _dptDate(),
  _dptTime(1),
  _arvTime(1),
  _sequence(0),
  _Train_no(0) //JRO DT23805
{
  pYmTranche = 0;
}

//SMD
// Name : Constructor
// Desc : Creates YmLeg and initializes all attributes
//EMD
YmLeg::YmLeg(YmTranche *ptranche,
	     string legOrigin,
	     string legDest,
	     YmDate dptDate,
	     int dptTime,
	     int arvTime,		 		 
	     int Train_no): //DT23805 JRO
  _legOrigin(legOrigin),
  _legDest(legDest),
  _dptDate(dptDate),
  _dptTime(dptTime),
  _arvTime(arvTime),
  _Train_no(Train_no)
{
  pYmTranche = ptranche;
  _sequence = 0;
}


//SMD
// Name : Destructor
// Desc : Destrorys the leg.
//EMD
YmLeg::~YmLeg()
{
}

