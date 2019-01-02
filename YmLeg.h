//## Module : YmLeg
//SFD
//  Name    : YmLeg.h
//  Author  : Lienard william
//  Desc    : Description de la class YmLeg
//EFD

#ifndef YmLeg_h
#define YmLeg_h 1

//## Includes
#include <string>
#include "YmIrGlobal.h"
#include "YmDate.h"


class YmTranche;

class YmLeg
{
public:
  //## Constructeurs
  YmLeg();
  YmLeg(YmTranche *pTranche, string legOrigin,string legDest,
	YmDate dptDateLeg, int dptTime,	int arvTime, int Train_no); //DT23805 JRO

  //## Destructeur

  ~YmLeg();

  //## Accesseurs

  YmTranche	*get_YmTranche() { return pYmTranche; }
  string	get_legOrigin() { return _legOrigin; }
  string	get_legDest() { return _legDest; }
  YmDate	get_dptDate() { return _dptDate; }
  int		get_dptTime() { return _dptTime; }
  int		get_arvTime() { return _arvTime; }
  int		get_sequence() { return _sequence; }
  int		get_Train_no() { return _Train_no; } //DT23805 JRO

  //## Mutateurs

  void set_YmTranche(YmTranche *value) { pYmTranche = value; }
  void set_sequence(int value) { _sequence = value; }
  void set_legOrigin(string value) { _legOrigin = value; }
  void set_legDest(string value) { _legDest = value; }
  void set_dptDate(YmDate value) { _dptDate = value; }
  void set_dptTime(int value) { _dptTime = value; }
  void set_arvTime(int value) { _arvTime = value; }
  void set_Train_no(int value) { _Train_no = value; } //DT23805 - JRO -  IC SRO

  //## Other
  void add_dptDate() { _dptDate += 1; }

 private:

  //## Donnees
  /* Leg Orig */
  string	_legOrigin;
  /* Leg Dest */
  string	_legDest;
  /* Date de depart du leg */
  YmDate	_dptDate;
  /* Heure de depart du leg */
  int		_dptTime;
  /* Heure d'arrivee du leg */
  int		_arvTime;
  /* Numero de sequence */
  int		_sequence;
  /* Pointeur sur la tranche */
  YmTranche	*pYmTranche;
  
/* Numero de Train */
int 	_Train_no; //DT23805 JRO - IC SRO
};



/* Pointer on class */
typedef class YmLeg *YmLegP;



#endif

